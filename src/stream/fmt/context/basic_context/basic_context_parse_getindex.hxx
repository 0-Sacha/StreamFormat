#pragma once

#include "stream/fmt/buf/manip.hxx"
#include "stream/fmt/buf/test_manip.hxx"
#include "stream/fmt/buf/write_manip.hxx"
#include "stream/fmt/buf/read_manip.hxx"
#include "stream/fmt/buf/fmt_manip_io.hxx"
#include "stream/fmt/buf/fmt_read_manip.hxx"

namespace stream::fmt::context {
    namespace {
        template <typename Executor>
        std::optional<std::int32_t> get_format_index_number(Executor& executor, buf::StreamView<typename Executor::TChar>& stream) {
            std::int32_t index = -1;
            buf::ReadManip(stream).fast_read_integer(index);
            if (buf::TestAccess(stream).is_equal_to(':') || buf::TestAccess(stream).is_equal_to('}')) {
                if (index >= 0 && index < executor.get_context().args_interface.size()) {
                    return index;
                }
            }
            return std::nullopt;
        }
        template <typename Executor>
        std::optional<std::int32_t> get_format_index_name(Executor& executor, buf::StreamView<typename Executor::TChar>& stream) {
            std::optional<std::int32_t> index = executor.get_context().args_interface.get_index_of_current_named_arg(stream);
            if (index.has_value() == false) return std::nullopt;
            if (buf::TestAccess(stream).is_equal_to(':') || buf::TestAccess(stream).is_equal_to('}')) {
                if (index >= 0 && index < executor.get_context().args_interface.size()) {
                    return index;
                }
            }
            return std::nullopt;
        }
        template <typename Executor>
        std::optional<std::int32_t> get_format_index_sub_index(Executor& executor, buf::StreamView<typename Executor::TChar>& stream) {
            buf::TestAccess access(stream);
            buf::TestManip  manip(stream);

            if (access.is_equal_to('{')) {
                buf::Manip(stream).forward();
                std::optional<std::int32_t> rec_index = get_format_index(executor, stream);
                if (rec_index.has_value() == false) {
                    return std::nullopt;
                }
                if (access.is_equal_to('}') && rec_index >= 0 && rec_index < executor.get_context().args_interface.size()) {
                    buf::Manip(stream).forward();
                    manip.ignore_every_spaces();
                    if (access.is_equal_to(':', '}')) {
                        std::int32_t final_rec_index = (std::int32_t)executor.get_context().args_interface.get_int_at(rec_index.value());
                        if (final_rec_index >= 0 && final_rec_index < executor.get_context().args_interface.size()) {
                            return final_rec_index;
                        }
                    }
                }
            }
            return std::nullopt;
        }
    }  // namespace

    template <typename Executor>
    std::optional<std::int32_t> get_format_index(Executor& executor, buf::StreamView<typename Executor::TChar>& stream) {
        buf::TestAccess access(stream);

        // I : if there is no number specified : ':' or '}'
        if (access.is_equal_to(':') || access.is_equal_to('}'))
            if (executor.get_context().values_index < executor.get_context().args_interface.size()) {
                return executor.get_context().values_index++;
            }

        // II: A number(idx)
        if (access.is_a_digit()) {
            return get_format_index_number(executor, stream);
        }

        // III : A name
        if (access.is_lower_case() || access.is_upper_case()) {
            return get_format_index_name(executor, stream);
        }

        // VI : { which is a idx to an argument
        if (access.is_equal_to('{')) {
            const typename Executor::TChar* oldPos = stream.current_pos;
            std::optional<std::int32_t>     res    = get_format_index_sub_index(executor, stream);
            if (res.has_value() == false) {
                stream.current_pos = oldPos;
                return std::nullopt;
            }
            return res;
        }

        return std::nullopt;
    }

    template <typename Executor, typename T>
    T format_read_parameter(Executor& executor, buf::StreamView<typename Executor::TChar>& stream, const T& default_value) {
        if (!buf::TestAccess(stream).is_equal_to('{')) {
            T t;
            buf::ReadManip(stream).fast_read_integer(t);
            return t;
        }

        // SubIndex
        buf::TestManip(stream).skip_one_of('{');
        std::optional<std::int32_t> format_idx = get_format_index(executor, stream);
        if constexpr (std::is_convertible_v<T, int64_t>) {
            return executor.get_context().args_interface.get_int_at(format_idx.value());
        } else if constexpr (std::is_convertible_v<T, std::basic_string_view<typename Executor::TChar>>) {
            return executor.get_context().args_interface.get_string_at(format_idx.value());
        }

        throw std::runtime_error("fmt error: Context_ArgumentIndexExpected");
    }
}  // namespace stream::fmt::context
