#pragma once

#include "basic_formatter_executor.hxx"

#include "stream/fmt/buf/fmt_write_manip.hxx"

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

    //----------------------------------------------//
    //----------------- forwarders -----------------//
    //----------------------------------------------//

    namespace detail::forwarders {
        template <typename T, typename FormatterExecutor>
        void format_object_array(const T* const buffer, std::size_t totalsize, FormatterExecutor& executor) {
            std::size_t begin_idx = (std::size_t)executor.data.specifiers.get_as_number("begin", 0);
            totalsize             = executor.data.specifiers.get_as_number("totalsize", totalsize);
            totalsize             = executor.data.specifiers.get_as_number("end", totalsize);

            std::size_t size = executor.data.specifiers.get_as_number("size", totalsize - begin_idx);

            buf::WriteManip(executor.ostream).fast_write_string(executor.data.specifiers.get_as_text("begin", STDEnumerableUtility::DefaultBegin));

            std::basic_string_view<typename FormatterExecutor::TChar> join = executor.data.specifiers.get_as_text("join", STDEnumerableUtility::DefaultJoin);

            bool     first   = true;
            const T* itbegin = buffer + begin_idx;
            const T* itend   = buffer + size + begin_idx;

            while (itbegin < itend) {
                if (first) {
                    first = false;
                } else {
                    buf::FMTWriteManip(executor.ostream).write_indent_string(join);
                }
                executor.write_type(*itbegin++);
            }

            return buf::WriteManip(executor.ostream).fast_write_string(executor.data.specifiers.get_as_text("end", STDEnumerableUtility::DefaultEnd));
        }

        template <typename T, typename FormatterExecutor>
        void format_string(const T* buffer, std::size_t size, FormatterExecutor& executor) {
            std::size_t begin_idx = (std::size_t)executor.data.specifiers.get_as_number("begin", 0);
            size                  = executor.data.specifiers.get_as_number("size", size);
            if (size == std::numeric_limits<std::size_t>::max()) {
                size = std::basic_string_view(buffer).size();
            }

            if (executor.data.specifiers.has("array")) return format_object_array(buffer, size, executor);

            if (begin_idx > size) return;
            const T* begin = buffer + begin_idx;

            // TODO: current indent ignore shift
            if (executor.data.specifiers.has("indent")) return buf::FMTWriteManip(executor.ostream).write_indent_char_ptr(begin, size);

            if (executor.data.prefix_suffix) {
                buf::ManipIO(executor.ostream).pushback('\"');
            }

            if (executor.data.has_spec == false) {
                buf::WriteManip(executor.ostream).fast_write_char_array(begin, size);
            } else {
                buf::FMTWriteManip(executor.ostream).write_char_ptr(begin, size, executor.data.shift);
            }

            if (executor.data.prefix_suffix) {
                buf::ManipIO(executor.ostream).pushback('\"');
            }
        }
    }  // namespace detail::forwarders

    //-----------------------------------------------//
    //----------------- C/CXX Types -----------------//
    //-----------------------------------------------//

    // Bool
    template <typename FormatterExecutor>
    struct FormatterType<bool, FormatterExecutor> {
        static void format(const bool t, FormatterExecutor& executor) {
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
            if (t == nullptr) return buf::ManipIO(executor.ostream).fast_write_string(executor.data.get_as_text("null", "nullptr"));
            return buf::WriteManip(executor.ostream).fast_write_integer(std::size_t(t));
        }
    };

    template <typename T, typename FormatterExecutor>
    struct FormatterType<T*, FormatterExecutor> {
        static inline void format(const T* const t, FormatterExecutor& executor) {
            if (t == nullptr) {
                return buf::WriteManip(executor.ostream).fast_write_string(executor.data.specifiers.get_as_text("null", "nullptr"));
            }

            if constexpr (detail::IsCharType<T>::value) {
                return detail::forwarders::format_string(t, std::numeric_limits<std::size_t>::max(), executor);
            } else {
                detail::forwarders::format_object_array(t, std::numeric_limits<std::size_t>::max(), executor);
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
                return detail::forwarders::format_string(t, size, executor);
            } else {
                return detail::forwarders::format_object_array(t, SIZE, executor);
            }
        }
    };
}  // namespace stream::fmt
