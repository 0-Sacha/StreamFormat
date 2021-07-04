
#pragma once

#include "CPPTools/Formater/Core/Core.h"

#include "BaseFormat/FormatType.h"
#include "BaseFormat/NamedArgs.h"
#include "BaseFormat/FormatArgs.h"

namespace CPPTools::Fmt::Detail {

	template <typename... Types>
	struct FormatContextArgsTuple;

    template <>
    struct FormatContextArgsTuple<> {
    public:
        FormatContextArgsTuple() {}

    public:
        template <typename FormatContext>
        inline void FormatTypeFromIdx(FormatContext &context, FormatIdx idx) {}

        template <typename FormatContext>
        inline void GetParameterDataFromIdx(FormatContext &context, FormatIdx idx) {}

        template <typename FormatContext>
        inline void GetParameterData(FormatContext &context, FormatIdx idx) { context.GetFormatData() = FormatData(); }

        template <typename FormatContext>
        inline void GetNamedArgsIdx(FormatContext& context, FormatIdx& idx, FormatIdx currentIdx) { idx = FormatIdxNotFound; }

        template <class ValueType>
        inline void GetFormatValueAt(ValueType& value, FormatIdx idx) {}
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
        /////---------- FormatTypeFromIdx ----------/////
        template <typename FormatContext>
        inline void FormatTypeFromIdx(FormatContext &context, FormatIdx idx) {
            if (idx == 0)           context.WriteType(m_Value);
            else if (idx > 0)       FormatContextArgsTuple<Rest...>::FormatTypeFromIdx(context, idx - 1);
        }

        /////---------- GetParameterDataFromIdx ----------/////
        template <typename FormatContext, class KType = Type>
        inline auto GetParameterDataFromIdx(FormatContext &context, FormatIdx idx) -> std::enable_if_t<std::is_same_v<GetBaseType<KType>, FormatData>> {
            if (idx == 0)           context.GetFormatData() = m_Value;
            else if (idx > 0)       FormatContextArgsTuple<Rest...>::GetParameterDataFromIdx(context, idx - 1);
        }

        template <typename FormatContext, class KType = Type>
        inline auto GetParameterDataFromIdx(FormatContext &context, FormatIdx idx) -> std::enable_if_t<!std::is_same_v<GetBaseType<KType>, FormatData>> {
            if (idx > 0)      FormatContextArgsTuple<Rest...>::GetParameterDataFromIdx(context, idx - 1);
        }


        /////---------- GetNamedArgsIdx ----------/////
        template<typename FormatContext, class KType = Type>
        inline auto GetNamedArgsIdx(FormatContext& context, FormatIdx& idx, FormatIdx currentIdx) -> std::enable_if_t<!Detail::IsANamedArgs<GetBaseType<KType>>::value>{
            FormatContextArgsTuple<Rest...>::GetNamedArgsIdx(context, idx, currentIdx + 1);
        }

        template<typename FormatContext, class KType = Type>
        inline auto GetNamedArgsIdx(FormatContext& context, FormatIdx& idx, FormatIdx currentIdx) -> std::enable_if_t<Detail::IsANamedArgs<GetBaseType<KType>>::value>{
            if (context.FormatNextIsANamedArgs(m_Value.GetName()))    idx = currentIdx;
            else                                                    FormatContextArgsTuple<Rest...>::GetNamedArgsIdx(context, idx, currentIdx + 1);
        }

        /////---------- GetFormatValueAt ----------/////
        template <class ValueType, class KType = Type>
        inline auto GetFormatValueAt(ValueType& value, FormatIdx idx) -> std::enable_if_t<!std::is_convertible_v<KType, ValueType>> {
		    if (idx > 0)	    FormatContextArgsTuple<Rest...>::GetFormatValueAt(value, idx - 1);
        }

        template <class ValueType, class KType = Type>
        inline auto GetFormatValueAt(ValueType& value, FormatIdx idx) -> std::enable_if_t<std::is_convertible_v<KType, ValueType>> {
		    if (idx == 0)		value = static_cast<ValueType>(m_Value);
		    else if(idx > 0)    FormatContextArgsTuple<Rest...>::GetFormatValueAt(value, idx - 1);
        }
    };
}