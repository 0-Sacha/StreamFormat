
#pragma once

#include "Formatter/Core/Detail/Detail.h"

#include "Utils/UnFormatType.h"

namespace EngineCore::FMT::Detail {

    template <typename... Types>
    struct UnFormatContextArgsTuple;

    template <>
    struct UnFormatContextArgsTuple<> {

    public:
        UnFormatContextArgsTuple() = default;

    public:
        static inline constexpr std::size_t Size()  { return 0; }

    public:
        template <typename FormatContext>
        inline void RunTypeAtIndex(FormatContext& context, const Detail::FormatIndex& idx)                                          { throw Detail::FormatBufferWrongIndex(); }

        template <typename T, typename FormatContext>
        inline const Detail::GetBaseType<T>* GetTypeAtIndexThrow(FormatContext& context, const Detail::FormatIndex& idx)            { throw Detail::FormatGivenTypeError(); return nullptr; }

        template <typename T, typename FormatContext>
        inline T GetTypeAtIndexConvertThrow(FormatContext& context, const Detail::FormatIndex& idx)                                 { throw Detail::FormatGivenTypeError(); return T{}; }

        template <typename FormatContext>
        inline Detail::FormatIndex GetIndexOfCurrentNameArg(FormatContext& context, const Detail::FormatIndex& beginSearchIndex)    { return Detail::FormatIndex(); }
    };


    template <typename Type, typename... Rest>
    struct UnFormatContextArgsTuple<Type, Rest...> : UnFormatContextArgsTuple<Rest...>
    {
    private:
        using TypeWithoutRef = std::remove_reference_t<Type>;

    public:
        UnFormatContextArgsTuple(TypeWithoutRef& t, Rest &&...rest) : UnFormatContextArgsTuple<Rest...>(std::forward<Rest>(rest)...), m_Value(t) {}
        UnFormatContextArgsTuple(TypeWithoutRef&& t, Rest &&...rest) : UnFormatContextArgsTuple<Rest...>(std::forward<Rest>(rest)...), m_Value(t) {}

    private:
        TypeWithoutRef& m_Value;

    public:
        static inline constexpr std::size_t Size() { return sizeof...(Rest) + 1; }

    public:
        template <typename FormatContext>
        inline void RunTypeAtIndex(FormatContext& context, const Detail::FormatIndex& idx) {
            if (idx.Is0())
                return context.RunType(m_Value);
            return UnFormatContextArgsTuple<Rest...>::RunTypeAtIndex(context, idx.GetPrev());
        }


        template <typename T, typename FormatContext, class KType = TypeWithoutRef>
            requires (Context::FormatContextArgsTupleSameAs<T, KType>::SameAs)
        inline const Detail::GetBaseType<T>* GetTypeAtIndexThrow(FormatContext& context, const Detail::FormatIndex& idx)
        {
            if (idx.Is0())
                return &m_Value;
            return UnFormatContextArgsTuple<Rest...>::template GetTypeAtIndexThrow<T>(context, idx.GetPrev());
        }

        template <typename T, typename FormatContext, class KType = TypeWithoutRef>
            requires (!Context::FormatContextArgsTupleSameAs<T, KType>::SameAs)
        inline const Detail::GetBaseType<T>* GetTypeAtIndexThrow(FormatContext& context, const Detail::FormatIndex& idx)
        {
            if (idx.Is0())
                return nullptr;
            return UnFormatContextArgsTuple<Rest...>::template GetTypeAtIndexThrow<T>(context, idx.GetPrev());
        }

        template <typename T, typename FormatContext, class KType = TypeWithoutRef>
            requires (Context::FormatContextArgsTupleConvertFunc<T, KType>::IsConvertible)
        inline T GetTypeAtIndexConvertThrow(FormatContext& context, const Detail::FormatIndex& idx)
        {
            if (idx.Is0())
                return Context::FormatContextArgsTupleConvertFunc<T, KType>::Convert(m_Value);
            return UnFormatContextArgsTuple<Rest...>::template GetTypeAtIndexConvertThrow<T>(context, idx.GetPrev());
        }

        template <typename T, typename FormatContext, class KType = TypeWithoutRef>
            requires (!Context::FormatContextArgsTupleConvertFunc<T, KType>::IsConvertible)
        inline T GetTypeAtIndexConvertThrow(FormatContext& context, const Detail::FormatIndex& idx)
        {
            if (idx.Is0())
                return T{};
            return UnFormatContextArgsTuple<Rest...>::template GetTypeAtIndexConvertThrow<T>(context, idx.GetPrev());
        }

        /////---------- GetNamedArgsIdx ----------/////
        template<typename FormatContext, class KType = TypeWithoutRef>
            requires (Detail::IsANamedArgs<Detail::GetBaseType<KType>>::value)
        inline Detail::FormatIndex GetIndexOfCurrentNameArg(FormatContext& context, const Detail::FormatIndex& beginSearchIndex) {
            if (context.Format().NextIsANamedArgs(m_Value.GetName()))
                return beginSearchIndex;
            return UnFormatContextArgsTuple<Rest...>::GetIndexOfCurrentNameArg(context, beginSearchIndex.GetNext());
        }

        template<typename FormatContext, class KType = TypeWithoutRef>
            requires (!Detail::IsANamedArgs<Detail::GetBaseType<KType>>::value)
        inline Detail::FormatIndex GetIndexOfCurrentNameArg(FormatContext& context, const Detail::FormatIndex& beginSearchIndex) {
            return UnFormatContextArgsTuple<Rest...>::GetIndexOfCurrentNameArg(context, beginSearchIndex.GetNext());
        }

    };
}