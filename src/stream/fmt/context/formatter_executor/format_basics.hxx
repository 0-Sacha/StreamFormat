#pragma once

#include "basic_formatter_executor.hxx"

#include "stream/fmt/buf/fmt_write_manip.hxx"

#include "forwarders.hxx"

namespace stream::fmt {
    //---------------------------------------------//
    //----------------- Internals -----------------//
    //---------------------------------------------//

    template <typename FormatterExecutor>
    struct FormatterType<typename FormatterExecutor::detail::template FormatSpecifier<typename FormatterExecutor::TChar>, FormatterExecutor> {
        static void format(const typename FormatterExecutor::detail::template FormatSpecifier<typename FormatterExecutor::TChar>& specifier, FormatterExecutor& executor) {
            if (specifier.ValueIsText) {
                executor.run("{ '{}', '{}' }", specifier.name, specifier.as_text);
            } else {
                executor.run("{ '{}', '{}' }", specifier.name, specifier.as_number);
            }
            return;
        }
    };

    //-----------------------------------------------//
    //----------------- C/CXX Types -----------------//
    //-----------------------------------------------//

    template <typename FormatterExecutor>
    struct FormatterType<bool, FormatterExecutor> {
        static void format(const bool t, FormatterExecutor& executor) {
            if (executor.data.prefix_suffix) {
                if (t == true)
                    return buf::WriteManip(executor.ostream).fast_write_literal("True");
                else
                    return buf::WriteManip(executor.ostream).fast_write_literal("False");
            } else {
                if (t == true)
                    return buf::ManipIO(executor.ostream).pushback('1');
                else
                    return buf::ManipIO(executor.ostream).pushback('0');
            }

            return;
        }
    };

    template <typename T, typename FormatterExecutor>
        requires(std::is_integral_v<T> && !std::is_floating_point_v<T> && !detail::IsCharType<T>::value)
    struct FormatterType<T, FormatterExecutor> {
        static inline void format(const T t, FormatterExecutor& executor) {
            return buf::FMTWriteManip(executor.ostream).write_integer_format_data(t, executor.data);
        }
    };

    template <typename T, typename FormatterExecutor>
        requires std::is_floating_point_v<T>
    struct FormatterType<T, FormatterExecutor> {
        static inline void format(const T t, FormatterExecutor& executor) {
            return buf::FMTWriteManip(executor.ostream).write_float_formatdata(t, executor.data);
        }
    };

    template <typename T, typename FormatterExecutor>
        requires detail::IsCharType<T>::value
    struct FormatterType<T, FormatterExecutor> {
        static inline void format(const T t, FormatterExecutor& executor) {
            return buf::ManipIO(executor.ostream).pushback(t);
        }
    };

    //-------------------------------------------------------//
    //----------------- Pointers and Arrays -----------------//
    //-------------------------------------------------------//

    template <typename FormatterExecutor>
    struct FormatterType<void*, FormatterExecutor> {
        static inline void format(const void* const t, FormatterExecutor& executor) {
            if (t == nullptr) return buf::ManipIO(executor.ostream).fast_write_sv(executor.data.get_as_text("null", "nullptr"));
            return buf::FMTWriteManip(executor.ostream).write_integer_format_data(std::size_t(t), executor.data);
        }
    };

    template <typename T, typename FormatterExecutor>
    struct FormatterType<T*, FormatterExecutor> {
        static inline void format(const T* const t, FormatterExecutor& executor) {
            if (t == nullptr) {
                return buf::WriteManip(executor.ostream).fast_write_sv(executor.data.specifiers.get_as_text("null", "nullptr"));
            }

            if constexpr (detail::IsCharType<T>::value) {
                detail::forwarders::format_string_view(std::basic_string_view(t), executor);
            } else {
                detail::forwarders::format_span(std::span(t), executor);
            }
        }
    };

    template <typename T, std::size_t SIZE, typename FormatterExecutor>
    struct FormatterType<T[SIZE], FormatterExecutor> {
        static inline void format(T const (&t)[SIZE], FormatterExecutor& executor) {
            if constexpr (detail::IsCharType<T>::value) {
                std::size_t size = SIZE;
                while (t[size - 1] == '\0')
                    --size;
                return detail::forwarders::format_string_view(std::basic_string_view(t, size), executor);
            } else {
                return detail::forwarders::format_span(std::span(t, SIZE), executor);
            }
        }
    };
}  // namespace stream::fmt
