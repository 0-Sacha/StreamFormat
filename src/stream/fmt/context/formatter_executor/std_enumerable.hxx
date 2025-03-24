#pragma once

#include "formatter_type.hxx"
#include "stream/fmt/context/utils/context_functions.hxx"
#include "stream/fmt/detail/prelude.hxx"

#include <algorithm>
#include <utility>

namespace stream::fmt {
    class STDEnumerableUtility {
    public:
        static constexpr std::string_view DefaultJoin  = ", ";
        static constexpr std::string_view DefaultBegin = "{ ";
        static constexpr std::string_view DefaultEnd   = " }";
    };

    template <typename T, typename CharJoin = char, typename CharBegin = char, typename CharEnd = char>
    class STDEnumerable {
    public:
        explicit inline STDEnumerable(const T& value, std::basic_string_view<CharJoin> join_str = ", ", std::basic_string_view<CharBegin> begin_str = "{ ",
                                      std::basic_string_view<CharEnd> end_str = " }", const std::int32_t begin_idx = 0, const std::int32_t size = -1)
            : value_(value), join_str_(join_str), begin_str_(begin_str), end_(end_str), begin_idx_(begin_idx), size_(size < 0 ? (std::int32_t)value.size() - begin_idx : size) {}

        inline const T& get_value() const {
            return value_;
        }

        inline std::basic_string_view<CharEnd> get_str_join() const {
            return join_str_;
        }
        inline std::basic_string_view<CharBegin> get_str_begin() const {
            return begin_str_;
        }
        inline std::basic_string_view<CharEnd> get_str_end() const {
            return end_;
        }

        inline std::int32_t get_begin_idx() const {
            return begin_idx_;
        }
        inline std::int32_t get_size() const {
            return size_;
        }

    private:
        const T& value_;

        std::basic_string_view<CharBegin> join_str_;
        std::basic_string_view<CharBegin> begin_str_;
        std::basic_string_view<CharEnd>   end_;

        std::int32_t begin_idx_;
        std::int32_t size_;
    };

    template <typename T, typename CharBegin, typename CharJoin, typename CharEnd, typename FormatterExecutor>
    struct FormatterType<STDEnumerable<T, CharBegin, CharJoin, CharEnd>, FormatterExecutor> {
        static void format(const STDEnumerable<T, CharBegin, CharJoin, CharEnd>& enumerable, FormatterExecutor& executor) {
            executor.ostream.write_indent_string_view(enumerable.get_str_begin());
            executor.ostream.add_indent(enumerable.get_str_begin().size());

            {
                // TODO: Why ? ...
                detail::FunctionapplyNextOverride apply_next_override(executor);

                bool first = true;
                std::for_each_n(enumerable.get_value().cbegin() + enumerable.get_begin_idx(), enumerable.get_size(), [&](const auto& element) {
                    if (first) {
                        first = false;
                    } else {
                        executor.ostream.write_indent_string_view(enumerable.get_str_join());
                    }

                    executor.write_type(element);
                });
            }

            executor.ostream.remove_indent(enumerable.get_str_begin().size());
            executor.ostream.write_indent_string_view(enumerable.get_str_end());
        }
    };

    template <typename T>
    struct ForwardAsSTDEnumerable {};

    template <typename T, typename FormatterExecutor>
    struct FormatterType<ForwardAsSTDEnumerable<T>, FormatterExecutor> {
        static inline void format(const T& container, FormatterExecutor& executor) {
            STDEnumerable<T> enumerable(container, executor.data.get_as_text("join", STDEnumerableUtility::DefaultJoin),
                                        executor.data.get_as_text("begin", STDEnumerableUtility::DefaultBegin), executor.data.get_as_text("end", STDEnumerableUtility::DefaultEnd),
                                        executor.data.get_as_number("begin", 0), executor.data.get_as_number("size", -1));

            return executor.write_type(enumerable);
        }
    };

}  // namespace stream::fmt
