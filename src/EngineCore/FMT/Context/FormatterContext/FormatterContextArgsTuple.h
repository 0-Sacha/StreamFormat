
#pragma once

#include "FMT/Detail/Detail.h"

#include "Utils/FormatterType.h"
#include "Utils/NamedArgs.h"
#include "Utils/IndexArgs.h"
#include "Utils/FormatterContextTemplate.h"

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

        template <typename T>
        inline const Detail::GetBaseType<T>* GetTypeAtIndexThrow(const Detail::FormatIndex& idx)
                    { throw Detail::FormatGivenTypeError(); return nullptr; }
        
        template <typename T>
        inline T GetTypeAtIndexConvertThrow(const Detail::FormatIndex& idx)
                    { throw Detail::FormatGivenTypeError(); return T{}; }

        template <typename FormatterContext>
        inline Detail::FormatIndex GetIndexOfCurrentNameArg(FormatterContext& context, const Detail::FormatIndex& beginSearchIndex)
                    { return Detail::FormatIndex(); }
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
        template <typename T, class KType = TypeWithoutRef>
        requires (Context::FormatterContextArgsTupleSameAs<T, KType>::SameAs)
        inline const Detail::GetBaseType<T>* GetTypeAtIndexThrow(const Detail::FormatIndex& idx)
        {
            if (idx.Is0())
                return &m_Value;
            return FormatterContextArgsTuple<Rest...>::template GetTypeAtIndexThrow<T>(idx.GetPrev());
        }

        template <typename T, class KType = TypeWithoutRef>
        requires (!Context::FormatterContextArgsTupleSameAs<T, KType>::SameAs)
        inline const Detail::GetBaseType<T>* GetTypeAtIndexThrow(const Detail::FormatIndex& idx)
        {
            if (idx.Is0())
                return nullptr;
            return FormatterContextArgsTuple<Rest...>::template GetTypeAtIndexThrow<T>(idx.GetPrev());
        }

    public:       
        template <typename T, class KType = TypeWithoutRef>
        requires (Context::FormatterContextArgsTupleConvertFunc<T, KType>::IsConvertible)
        inline T GetTypeAtIndexConvertThrow(const Detail::FormatIndex& idx)
        {
            if (idx.Is0())
                return Context::FormatterContextArgsTupleConvertFunc<T, KType>::Convert(m_Value);
            return FormatterContextArgsTuple<Rest...>::template GetTypeAtIndexConvertThrow<T>(idx.GetPrev());
        }

        template <typename T, class KType = TypeWithoutRef>
        requires (!Context::FormatterContextArgsTupleConvertFunc<T, KType>::IsConvertible)
        inline T GetTypeAtIndexConvertThrow(const Detail::FormatIndex& idx)
        {
            if (idx.Is0())
                return T{};
            return FormatterContextArgsTuple<Rest...>::template GetTypeAtIndexConvertThrow<T>(idx.GetPrev());
        }

    public:
        template<typename FormatterContext, class KType = TypeWithoutRef>
        requires (Detail::IsANamedArgs<Detail::GetBaseType<KType>>::value)
        inline Detail::FormatIndex GetIndexOfCurrentNameArg(FormatterContext& context, const Detail::FormatIndex& beginSearchIndex) {
            if (context.Format().NextIsANamedArgs(m_Value.GetName()))
                return beginSearchIndex;
            return FormatterContextArgsTuple<Rest...>::GetIndexOfCurrentNameArg(context, beginSearchIndex.GetNext());
        }

        template<typename FormatterContext, class KType = TypeWithoutRef>
        requires (!Detail::IsANamedArgs<Detail::GetBaseType<KType>>::value)
        inline Detail::FormatIndex GetIndexOfCurrentNameArg(FormatterContext& context, const Detail::FormatIndex& beginSearchIndex) {
            return FormatterContextArgsTuple<Rest...>::GetIndexOfCurrentNameArg(context, beginSearchIndex.GetNext());
        }
    };
}