#pragma once

#include "formatter_type.h"
#include "stream/fmt/context/utils/ContextFunctions.h"
#include "stream/fmt/detail/prelude.h"

#include <algorithm>
#include <utility>

namespace stream::fmt
{
    class STDEnumerableUtility
    {
    public:
        static constexpr std::string_view DefaultJoin  = ", ";
        static constexpr std::string_view DefaultBegin = "{ ";
        static constexpr std::string_view DefaultEnd   = " }";
    };

    template <typename T, typename CharJoin = char, typename CharBegin = char, typename CharEnd = char>
    class STDEnumerable
    {
    public:
        explicit inline STDEnumerable(const T& value, std::basic_string_view<CharJoin> strJoin = ", ", std::basic_string_view<CharBegin> strBegin = "{ ",
                                      std::basic_string_view<CharEnd> strEnd = " }", const std::int32_t beginIdx = 0,
                                      const std::int32_t size = -1)
            : m_Value(value)
            , m_StrJoin(strJoin)
            , m_StrBegin(strBegin)
            , m_StrEnd(strEnd)
            , m_BeginIdx(beginIdx)
            , m_Size(size < 0 ? (std::int32_t)value.size() - beginIdx : size)
        {}

        inline const T& GetValue() const { return m_Value; }

        inline std::basic_string_view<CharEnd>   GetStrJoin() const { return m_StrJoin; }
        inline std::basic_string_view<CharBegin> GetStrBegin() const { return m_StrBegin; }
        inline std::basic_string_view<CharEnd>   GetStrEnd() const { return m_StrEnd; }

        inline std::int32_t GetBeginIdx() const { return m_BeginIdx; }
        inline std::int32_t GetSize() const { return m_Size; }

    private:
        const T& m_Value;

        std::basic_string_view<CharBegin> m_StrJoin;
        std::basic_string_view<CharBegin> m_StrBegin;
        std::basic_string_view<CharEnd>   m_StrEnd;

        std::int32_t m_BeginIdx;
        std::int32_t m_Size;
    };

    template <typename T, typename CharBegin, typename CharJoin, typename CharEnd, typename FormatterExecutor>
    struct FormatterType<STDEnumerable<T, CharBegin, CharJoin, CharEnd>, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const STDEnumerable<T, CharBegin, CharJoin, CharEnd>& enumerable, FormatterExecutor& executor)
        {
            SF_TRY(executor.buffer_out.WriteIndentStringView(enumerable.GetStrBegin()));
            SF_TRY(executor.buffer_out.AddIndent(enumerable.GetStrBegin().size()));

            {
                // TODO: Why ? ...
                detail::FunctionApplyNextOverride applyNextOverride(executor);

                bool first = true;
                std::for_each_n(enumerable.GetValue().cbegin() + enumerable.GetBeginIdx(), enumerable.GetSize(), [&](const auto& element) {
                    if (first)
                        { first = false; }
                    else
                        { SF_TRY(executor.buffer_out.WriteIndentStringView(enumerable.GetStrJoin())); }

                    SF_TRY(executor.WriteType(element));
                });
            }

            executor.buffer_out.RemoveIndent(enumerable.GetStrBegin().size());
            SF_TRY(executor.buffer_out.WriteIndentStringView(enumerable.GetStrEnd()));
        }
    };

    template <typename T>
    struct ForwardAsSTDEnumerable
    {
    };

    template <typename T, typename FormatterExecutor>
    struct FormatterType<ForwardAsSTDEnumerable<T>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const T& container, FormatterExecutor& executor)
        {
            STDEnumerable<T> enumerable(container, executor.Data.GetAsText("join", STDEnumerableUtility::DefaultJoin),
                                        executor.Data.GetAsText("begin", STDEnumerableUtility::DefaultBegin),
                                        executor.Data.GetAsText("end", STDEnumerableUtility::DefaultEnd),
                                        executor.Data.GetAsNumber("begin", 0),
                                        executor.Data.GetAsNumber("size", -1));

            return executor.WriteType(enumerable);
        }
    };

}
