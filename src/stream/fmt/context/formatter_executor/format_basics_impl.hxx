#pragma once

#include "basic_formatter_executor.hxx"

#include "stream/fmt/buf/fmt_write_manip.hxx"

namespace stream::fmt {
    //---------------------------------------------//
    //----------------- Internals -----------------//
    //---------------------------------------------//

    template <typename FormatterExecutor>
    struct FormatterType<typename FormatterExecutor::detail::template FormatSpecifier<typename FormatterExecutor::TChar>, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(const typename FormatterExecutor::detail::template FormatSpecifier<typename FormatterExecutor::TChar>& specifier,
                                                                   FormatterExecutor& executor) {
            if (specifier.ValueIsText) {
                SF_TRY(executor.run("{ '{}', '{}' }", specifier.name, specifier.as_text));
            } else {
                SF_TRY(executor.run("{ '{}', '{}' }", specifier.name, specifier.as_number));
            }
            return {};
        }
    };

    //----------------------------------------------//
    //----------------- Forwarders -----------------//
    //----------------------------------------------//

    namespace detail::Forwarders {
        template <typename T, typename FormatterExecutor>
        [[nodiscard]] std::expected<void, FMTResult> FormatObjectArray(const T* const buffer, std::size_t totalsize, FormatterExecutor& executor) {
            std::size_t beginIdx = (std::size_t)executor.data.specifiers.get_as_number("begin", 0);
            totalsize            = executor.data.specifiers.get_as_number("totalsize", totalsize);
            totalsize            = executor.data.specifiers.get_as_number("end", totalsize);

            std::size_t size = executor.data.specifiers.get_as_number("size", totalsize - beginIdx);

            if (size == std::numeric_limits<std::size_t>::max()) {
                return std::unexpected(FMTResult::GivenArgs_UnableToDeduceSize);
            }

            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string(executor.data.specifiers.get_as_text("begin", STDEnumerableUtility::DefaultBegin)));

            std::basic_string_view<typename FormatterExecutor::TChar> join = executor.data.specifiers.get_as_text("join", STDEnumerableUtility::DefaultJoin);

            bool     first   = true;
            const T* itbegin = buffer + beginIdx;
            const T* itend   = buffer + size + beginIdx;

            while (itbegin < itend) {
                if (first) {
                    first = false;
                } else {
                    SF_TRY(buf::FMTWriteManip(executor.ostream).write_indent_string(join));
                }
                SF_TRY(executor.write_type(*itbegin++));
            }

            return buf::WriteManip(executor.ostream).fast_write_string(executor.data.specifiers.get_as_text("end", STDEnumerableUtility::DefaultEnd));
        }

        template <typename T, typename FormatterExecutor>
        [[nodiscard]] std::expected<void, FMTResult> format_string(const T* buffer, std::size_t size, FormatterExecutor& executor) {
            std::size_t beginIdx = (std::size_t)executor.data.specifiers.get_as_number("begin", 0);
            size                 = executor.data.specifiers.get_as_number("size", size);
            if (size == std::numeric_limits<std::size_t>::max()) {
                size = std::basic_string_view(buffer).size();
            }

            if (executor.data.specifiers.has("array")) return FormatObjectArray(buffer, size, executor);

            if (beginIdx > size) return {};
            const T* begin = buffer + beginIdx;

            // TODO: current indent ignore shift
            if (executor.data.specifiers.has("indent")) return buf::FMTWriteManip(executor.ostream).write_indent_char_ptr(begin, size);

            if (executor.data.prefix_suffix) {
                SF_TRY(buf::ManipIO(executor.ostream).pushback('\"'));
            }

            if (executor.data.has_spec == false) {
                SF_TRY(buf::WriteManip(executor.ostream).fast_write_char_array(begin, size));
            } else {
                SF_TRY(buf::FMTWriteManip(executor.ostream).write_char_ptr(begin, size, executor.data.shift));
            }

            if (executor.data.prefix_suffix) {
                SF_TRY(buf::ManipIO(executor.ostream).pushback('\"'));
            }

            return {};
        }
    }  // namespace detail::Forwarders

    //-----------------------------------------------//
    //----------------- C/CXX Types -----------------//
    //-----------------------------------------------//

    // Bool
    template <typename FormatterExecutor>
    struct FormatterType<bool, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(const bool t, FormatterExecutor& executor) {
            if (executor.data.prefix_suffix) {
                if (t == true)
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("True");
                else
                    return buf::WriteManip(executor.ostream).fast_write_string_literal("False");
            } else {
                if (t == true)
                    return buf::ManipIO(executor.ostream).pushback('1');
                else
                    return buf::ManipIO(executor.ostream).pushback('0');
            }

            return {};
        }
    };

    template <typename T, typename FormatterExecutor>
        requires(std::is_integral_v<T> && !std::is_floating_point_v<T> && !detail::IsCharType<T>::value)
    struct FormatterType<T, FormatterExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const T t, FormatterExecutor& executor) {
            return buf::FMTWriteManip(executor.ostream).write_integer_format_data(t, executor.data);
        }
    };

    template <typename T, typename FormatterExecutor>
        requires std::is_floating_point_v<T>
    struct FormatterType<T, FormatterExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const T t, FormatterExecutor& executor) {
            return buf::FMTWriteManip(executor.ostream).write_float_formatdata(t, executor.data);
        }
    };

    template <typename T, typename FormatterExecutor>
        requires detail::IsCharType<T>::value
    struct FormatterType<T, FormatterExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const T t, FormatterExecutor& executor) {
            return buf::ManipIO(executor.ostream).pushback(t);
        }
    };

    //-------------------------------------------------------//
    //----------------- Pointers and Arrays -----------------//
    //-------------------------------------------------------//

    template <typename FormatterExecutor>
    struct FormatterType<void*, FormatterExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const void* const t, FormatterExecutor& executor) {
            if (t == nullptr) return buf::ManipIO(executor.ostream).fast_write_string(executor.data.get_as_text("null", "nullptr"));
            return buf::WriteManip(executor.ostream).fast_write_integer(std::size_t(t));
        }
    };

    template <typename T, typename FormatterExecutor>
    struct FormatterType<T*, FormatterExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const T* const t, FormatterExecutor& executor) {
            if (t == nullptr) {
                return buf::WriteManip(executor.ostream).fast_write_string(executor.data.specifiers.get_as_text("null", "nullptr"));
            }

            if constexpr (detail::IsCharType<T>::value) {
                return detail::Forwarders::format_string(t, std::numeric_limits<std::size_t>::max(), executor);
            } else {
                detail::Forwarders::FormatObjectArray(t, std::numeric_limits<std::size_t>::max(), executor);
            }

            return {};
        }
    };

    template <typename T, std::size_t SIZE, typename FormatterExecutor>
    struct FormatterType<T[SIZE], FormatterExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(T const (&t)[SIZE], FormatterExecutor& executor) {
            if constexpr (detail::IsCharType<T>::value) {
                std::size_t size = SIZE;
                while (t[size - 1] == '\0')
                    --size;
                return detail::Forwarders::format_string(t, size, executor);
            } else {
                return detail::Forwarders::FormatObjectArray(t, SIZE, executor);
            }

            return {};
        }
    };
}  // namespace stream::fmt
