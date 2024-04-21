#pragma once

#include <utility>
#include <algorithm>

#include "../FormatterType.h"
#include "ProjectCore/FMT/Detail/Detail.h"

namespace ProjectCore::FMT
{
    class STDEnumerableUtility
	{
    public:
        static constexpr std::string_view DefaultJoin    = ", ";
        static constexpr std::string_view DefaultBegin    = "{ ";
        static constexpr std::string_view DefaultEnd    = " }";
    };

    template <typename T, typename CharJoin = char, typename CharBegin = char, typename CharEnd = char>
    class STDEnumerable
	{
    public:
        explicit inline STDEnumerable(const T& value,
            const std::basic_string_view<CharJoin>& strJoin = ", ",
            const std::basic_string_view<CharBegin>& strBegin = "{ ",
            const std::basic_string_view<CharEnd>& strEnd = " }",
            const Detail::DataType beginIdx = 0,
            const Detail::DataType size = Detail::FORMAT_DATA_NOT_SPECIFIED)
            : m_Value(value)
            , m_StrJoin(strJoin)
            , m_StrBegin(strBegin)
            , m_StrEnd(strEnd)
            , m_BeginIdx(beginIdx)
            , m_Size(size == Detail::FORMAT_DATA_NOT_SPECIFIED ? (Detail::DataType)value.size() - beginIdx : size)
        {
        }

        inline const T& GetValue() const { return m_Value; }

        inline std::basic_string_view<CharEnd>        GetStrJoin() const    { return m_StrJoin; }
        inline std::basic_string_view<CharBegin>    GetStrBegin() const    { return m_StrBegin; }
        inline std::basic_string_view<CharEnd>        GetStrEnd() const    { return m_StrEnd; }

        inline Detail::DataType GetBeginIdx() const    { return m_BeginIdx; }
        inline Detail::DataType GetSize() const        { return m_Size; }

    private:
        const T& m_Value;

        std::basic_string_view<CharBegin> m_StrJoin;
        std::basic_string_view<CharBegin> m_StrBegin;
        std::basic_string_view<CharEnd>    m_StrEnd;

        Detail::DataType m_BeginIdx;
        Detail::DataType m_Size;
    };

    template <typename T, typename CharBegin, typename CharJoin, typename CharEnd, typename FormatterContext>
    struct FormatterType<STDEnumerable<T, CharBegin, CharJoin, CharEnd>, FormatterContext> {
        static void Format(const STDEnumerable<T, CharBegin, CharJoin, CharEnd>& enumerable, FormatterContext& context) {
            context.BufferOut().WriteIndentStringView(enumerable.GetStrBegin());
            context.BufferOut().AddIndent(enumerable.GetStrBegin().size());

            {
                Detail::ApplyNextOverrideForThisFunction applNextOverride(context);

                bool first = true;
                std::for_each_n(enumerable.GetValue().cbegin() + enumerable.GetBeginIdx(), enumerable.GetSize(), [&](const auto& element) {
                    if (first)   first = false;
                    else         context.BufferOut().WriteIndentStringView(enumerable.GetStrJoin());
                    
                    context.WriteType(element);
                });
            }

            context.BufferOut().RemoveIndent(enumerable.GetStrBegin().size());
            context.BufferOut().WriteIndentStringView(enumerable.GetStrEnd());
        }
    };


    template<typename T>
    struct ForwardAsSTDEnumerable {};

    template <typename T, typename FormatterContext>
    struct FormatterType<ForwardAsSTDEnumerable<T>, FormatterContext>
	{
        static void Format(const T& container, FormatterContext& context) {
            STDEnumerable<T> enumerable(container,
                context.GetFormatData().GetSpecifierAsText("join",        STDEnumerableUtility::DefaultJoin),
                context.GetFormatData().GetSpecifierAsText("begin",        STDEnumerableUtility::DefaultBegin),
                context.GetFormatData().GetSpecifierAsText("end",        STDEnumerableUtility::DefaultEnd),
                context.GetFormatData().GetSpecifierAsNumber("begin",    0),
                context.GetFormatData().GetSpecifierAsNumber("size",    Detail::FORMAT_DATA_NOT_SPECIFIED));

            context.WriteType(enumerable);
        }
    };

}
