
#pragma once

#include "FMT/Detail/Detail.h"

#include "Utils/FormatterType.h"
#include "Utils/NamedArgs.h"
#include "Utils/IndexArgs.h"
#include "FMT/Context/BasicContext/Utils/TypeIndexHandler.h"

namespace EngineCore::FMT::Detail {

	template <typename... Types>
	struct FormatterContextArgsTuple;

    template <>
    struct FormatterContextArgsTuple<> {

    public:
        FormatterContextArgsTuple() = default;

	public:
		static inline constexpr std::size_t Size() { return 0; }

    public:
        template <typename FormatterContext>
        inline void RunTypeAtIndex(FormatterContext &context, const Detail::FormatIndex& idx)
                    { throw Detail::FormatBufferWrongIndex(); }

        template <typename FormatterContext>
        inline Detail::FormatIndex GetIndexOfCurrentNameArg(FormatterContext& context, const Detail::FormatIndex& beginSearchIndex)
                    { return Detail::FormatIndex(); }

        inline void* GetTypeAtIndex(const Detail::FormatIndex& idx)
                    { return nullptr; }

        inline int GetRuntimeTypeUID()
                    { return RuntimeTypeUID<void>::value; }

    };

    template <typename Type, typename... Rest>
    struct FormatterContextArgsTuple<Type, Rest...> : FormatterContextArgsTuple<Rest...>
    {
    private:
        using TypeWithoutRef = std::remove_reference_t<Type>;

    public:
        FormatterContextArgsTuple(const TypeWithoutRef &t, Rest &&...rest)     : FormatterContextArgsTuple<Rest...>(std::forward<Rest>(rest)...), m_Value(t) {}
        FormatterContextArgsTuple(const TypeWithoutRef &&t, Rest &&...rest)    : FormatterContextArgsTuple<Rest...>(std::forward<Rest>(rest)...), m_Value(t) {}

    private:
        const TypeWithoutRef &m_Value;

    public:
        static inline constexpr std::size_t Size() { return sizeof...(Rest) + 1; }

    public:
        template <typename FormatterContext>
        inline void RunTypeAtIndex(FormatterContext &context, const Detail::FormatIndex& idx) {
            if (idx.Is0())
                return context.RunType(m_Value);
            return FormatterContextArgsTuple<Rest...>::RunTypeAtIndex(context, idx.GetPrev());
        }

    public:
        template<typename FormatterContext>
        inline Detail::FormatIndex GetIndexOfCurrentNameArg(FormatterContext& context, const Detail::FormatIndex& beginSearchIndex) {
            if constexpr (Detail::IsANamedArgs<Detail::GetBaseType<TypeWithoutRef>>::value)
            {
                if (context.Format().NextIsANamedArgs(m_Value.GetName()))
                    return beginSearchIndex;
            }
            return FormatterContextArgsTuple<Rest...>::GetIndexOfCurrentNameArg(context, beginSearchIndex.GetNext());
        }

    public:
        // return Type : TypeWithoutRef* need to be recast
        inline void* GetTypeAtIndex(const Detail::FormatIndex& idx)
        {
            if (idx.Is0())
                return reinterpret_cast<void*>(&m_Value);
            return FormatterContextArgsTuple<Rest...>::template GetTypeAtIndex(idx.GetPrev());
        }

        inline int GetRuntimeTypeUID()
        {
            return RuntimeTypeUID<TypeWithoutRef>::value;
        }
    };
}