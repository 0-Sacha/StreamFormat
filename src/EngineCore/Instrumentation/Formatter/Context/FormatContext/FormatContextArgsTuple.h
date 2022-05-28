
#pragma once

#include "EngineCore/Instrumentation/Formatter/Core/Detail/Detail.h"

#include "Utils/FormatType.h"
#include "Utils/NamedArgs.h"
#include "Utils/FormatArgs.h"

namespace EngineCore::Instrumentation::FMT::Detail {

	template <typename... Types>
	struct FormatContextArgsTuple;

    template <>
    struct FormatContextArgsTuple<> {

    public:
        FormatContextArgsTuple() = default;

	public:
		static inline constexpr std::size_t Size() { return 0; }

    public:
        template <typename FormatContext>
        inline void RunTypeAtIndex(FormatContext &context, const Detail::FormatIndex& idx)                                          { throw Detail::FormatBufferWrongIndex(); }

        template <typename FormatContext, typename T>
        inline const Detail::GetBaseType<T>* GetTypeAtIndex(FormatContext &context, const Detail::FormatIndex& idx)                 { throw Detail::FormatGivenTypeError(); }

        template <typename FormatContext>
        inline Detail::FormatIndex GetIndexOfCurrentNameArg(FormatContext& context, const Detail::FormatIndex& beginSearchIndex)    { return Detail::FormatIndex(); }
    };


    template <typename Type, typename... Rest>
    struct FormatContextArgsTuple<Type, Rest...> : FormatContextArgsTuple<Rest...>
    {
    private:
        using TypeWithoutRef = std::remove_reference_t<Type>;

    public:
        FormatContextArgsTuple(const TypeWithoutRef &t, Rest &&...rest)     : FormatContextArgsTuple<Rest...>(std::forward<Rest>(rest)...), m_Value(t) {}
        FormatContextArgsTuple(const TypeWithoutRef &&t, Rest &&...rest)    : FormatContextArgsTuple<Rest...>(std::forward<Rest>(rest)...), m_Value(t) {}

    private:
        const TypeWithoutRef &m_Value;

    public:
        static inline constexpr std::size_t Size() { return sizeof...(Rest) + 1; }

    public:
        template <typename FormatContext>
        inline void RunTypeAtIndex(FormatContext &context, const Detail::FormatIndex& idx) {
            if (idx.Is0())              context.RunType(m_Value);
            else if (idx.IsValid())     FormatContextArgsTuple<Rest...>::FormatTypeFromIdx(context, idx.GetPrev());
        }


        template <typename FormatContext, typename T, class KType = TypeWithoutRef>
        requires (std::is_same_v<Detail::GetBaseType<T>, Detail::GetBaseType<KType>>)
        inline const Detail::GetBaseType<T>* GetTypeAtIndex(FormatContext &context, const Detail::FormatIndex& idx)
        {
            if (idx.Is0())              return &m_Value;
            else if (idx.IsValid())     FormatContextArgsTuple<Rest...>::GetTypeAtIdx(context, idx.GetPrev());
        }

        template <typename FormatContext, typename T, class KType = TypeWithoutRef>
        requires (!std::is_same_v<Detail::GetBaseType<T>, Detail::GetBaseType<KType>>)
        inline const Detail::GetBaseType<T>* GetTypeAtIndex(FormatContext &context, const Detail::FormatIndex& idx)
        {
            if (idx.Is0())              { return nullptr; }
            else if (idx.IsValid())     FormatContextArgsTuple<Rest...>::GetTypeAtIdx(context, idx.GetPrev());
        }

        /////---------- GetNamedArgsIdx ----------/////
        template<typename FormatContext, class KType = TypeWithoutRef>
        requires (Detail::IsANamedArgs<Detail::GetBaseType<KType>>::value)
        inline Detail::FormatIndex GetIndexOfCurrentNameArg(FormatContext& context, const Detail::FormatIndex& beginSearchIndex) {
            if (context.Format().NextIsANamedArgs(m_Value.GetName()))    return beginSearchIndex;
            else if (beginSearchIndex.IsValid())                         return FormatContextArgsTuple<Rest...>::GetIndexOfCurrentNameArg(context, beginSearchIndex.GetNext());
        }

        template<typename FormatContext, class KType = TypeWithoutRef>
        requires (!Detail::IsANamedArgs<Detail::GetBaseType<KType>>::value)
        inline Detail::FormatIndex GetIndexOfCurrentNameArg(FormatContext& context, const Detail::FormatIndex& beginSearchIndex) {
            return FormatContextArgsTuple<Rest...>::GetIndexOfCurrentNameArg(context, beginSearchIndex.GetNext());
        }
    };
}