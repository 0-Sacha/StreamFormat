#pragma once

#include "formatter_type.h"
#include "stream/fmt/context/utils/context_functions.h"
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

        inline const T& get_value() const { return m_Value; }

        inline std::basic_string_view<CharEnd>   get_str_join() const { return m_StrJoin; }
        inline std::basic_string_view<CharBegin> get_str_begin() const { return m_StrBegin; }
        inline std::basic_string_view<CharEnd>   get_str_end() const { return m_StrEnd; }

        inline std::int32_t get_begin_idx() const { return m_BeginIdx; }
        inline std::int32_t get_size() const { return m_Size; }

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
            SF_TRY(executor.ostream.write_indent_string_view(enumerable.get_str_begin()));
            SF_TRY(executor.ostream.add_indent(enumerable.get_str_begin().size()));

            {
                // TODO: Why ? ...
                detail::FunctionapplyNextOverride apply_next_override(executor);

                bool first = true;
                std::for_each_n(enumerable.get_value().cbegin() + enumerable.get_begin_idx(), enumerable.get_size(), [&](const auto& element) {
                    if (first)
                        { first = false; }
                    else
                        { SF_TRY(executor.ostream.write_indent_string_view(enumerable.get_str_join())); }

                    SF_TRY(executor.write_type(element));
                });
            }

            executor.ostream.remove_indent(enumerable.get_str_begin().size());
            SF_TRY(executor.ostream.write_indent_string_view(enumerable.get_str_end()));
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
            STDEnumerable<T> enumerable(container, executor.data.get_as_text("join", STDEnumerableUtility::DefaultJoin),
                                        executor.data.get_as_text("begin", STDEnumerableUtility::DefaultBegin),
                                        executor.data.get_as_text("end", STDEnumerableUtility::DefaultEnd),
                                        executor.data.get_as_number("begin", 0),
                                        executor.data.get_as_number("size", -1));

            return executor.write_type(enumerable);
        }
    };

}
