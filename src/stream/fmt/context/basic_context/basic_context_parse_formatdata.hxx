#pragma once

#include "stream/fmt/buf/manip.hxx"
#include "stream/fmt/buf/test_manip.hxx"
#include "stream/fmt/buf/write_manip.hxx"
#include "stream/fmt/buf/read_manip.hxx"
#include "stream/fmt/buf/fmt_manip_io.hxx"
#include "stream/fmt/buf/fmt_read_manip.hxx"

#include "basic_context_parse_getindex.hxx"

namespace stream::fmt::detail {
    namespace {
        template <typename Executor>
        std::basic_string_view<typename Executor::TChar> parse_next_override_format_data(Executor& executor, buf::StreamView<typename Executor::TChar>& stream,
                                                                                         detail::FormatData<typename Executor::TChar>& data) {
            buf::TestAccess access(stream);
            buf::TestManip  manip(stream);

            manip.is_equal_to_forward(':');
            manip.ignore_every_spaces();

            const typename Executor::TChar* begin  = stream.current_pos;
            int                             scopes = 0;
            while (buf::FMTParamsManip(stream).is_end_of_parameter() == false || scopes > 0) {
                manip.GoTo('\'', '}', '{');
                if (access.is_equal_to('\'')) {
                    buf::Manip(stream).forward();
                    manip.go_to_forward('\'');
                } else if (access.is_equal_to('{')) {
                    buf::Manip(stream).forward();
                    scopes++;
                } else if (scopes > 0 && access.is_equal_to('}')) {
                    buf::Manip(stream).forward();
                    scopes--;
                }
            }
            const typename Executor::TChar* end = stream.current_pos;
            return std::basic_string_view<typename Executor::TChar>(begin, end - begin);
        }

        template <typename Executor>
        void parse_format_data_base(Executor& executor, buf::StreamView<typename Executor::TChar>& stream, detail::FormatData<typename Executor::TChar>& data) {
            buf::TestAccess access(stream);

            if (access.is_equal_to('C')) {
                buf::Manip(stream).forward();
                executor.text_manager.parse_color(executor.get_context(), stream);
            } else if (access.is_equal_to('S')) {
                buf::Manip(stream).forward();
                executor.text_manager.parse_style(executor.get_context(), stream);
                buf::Manip(stream).forward();
            } else if (access.is_equal_to('F')) {
                executor.text_manager.parse_front(executor.get_context(), stream);
            }

            else if (access.is_equal_to('K')) {
                buf::Manip(stream).forward();
                data.keep_new_style = true;
            }
        }

        template <typename Executor>
        void parse_format_data_special_shift_type(Executor& executor, buf::StreamView<typename Executor::TChar>& stream, detail::FormatData<typename Executor::TChar>& data,
                                                  const detail::ShiftInfo::ShiftType type) {
            data.shift.type = type;
            data.shift.size = format_read_parameter(executor, stream, -1);
            if (buf::TestAccess(stream).is_equal_to(':')) {
                buf::Manip(stream).forward();
                data.shift.print.before = stream.get();
                data.shift.print.after  = data.shift.print.before;
                buf::Manip(stream).forward();
                if (buf::TestAccess(stream).is_equal_to('|')) {
                    buf::Manip(stream).forward();
                    data.shift.print.after = stream.get();
                    buf::Manip(stream).forward();
                }
            }
        }

        template <typename Executor>
        bool parse_format_data_special(Executor& executor, buf::StreamView<typename Executor::TChar>& stream, detail::FormatData<typename Executor::TChar>& data) {
            buf::TestAccess access(stream);
            buf::TestManip  manip(stream);

            bool local_spec = false;

            if (access.is_equal_to('{')) {
                local_spec = true;
                buf::Manip(stream).forward();
                std::optional<std::int32_t> format_index = get_format_index(executor, stream);

                bool ableToapply = false;
                if (format_index.has_value()) {
                    auto applyFormatData = executor.get_context().args_interface.template get_type_at<detail::FormatData<typename Executor::TChar>>(format_index.value());
                    ableToapply |= data.testapply(applyFormatData);
                    auto applyFormatSpecifier = executor.get_context().args_interface.template get_type_at<detail::FormatSpecifier<typename Executor::TChar>>(format_index.value());
                    ableToapply |= data.testapply(applyFormatSpecifier);
                    auto applyIntegerPrintBase = executor.get_context().args_interface.template get_type_at<detail::IntegerPrintBase>(format_index.value());
                    ableToapply |= data.testapply(applyIntegerPrintBase);
                    auto applyShiftInfo = executor.get_context().args_interface.template get_type_at<detail::ShiftInfo>(format_index.value());
                    ableToapply |= data.testapply(applyShiftInfo);
                }

                if (not ableToapply) {
                    throw std::runtime_error("fmt error: Context_CannotapplyType");
                }
                manip.skip_one_of('}');
            }

            if (access.is_equal_to('#')) {
                local_spec = true;
                buf::Manip(stream).forward();
                data.prefix_suffix = true;
            }

            bool is_integer_spec = access.is_equal_to('d', 'b', 'b', 'o', 'O', 'x', 'X');
            is_integer_spec      = is_integer_spec && (stream.get_buffer_remaining_size() == 1 || (buf::Access(stream).get_next() > 'z' && buf::Access(stream).get_next() < 'a'));
            if (is_integer_spec) {
                local_spec         = true;
                data.integer_print = static_cast<detail::IntegerPrintBase>(stream.get());
                buf::Manip(stream).forward();
            }

            if (access.is_equal_to('.')) {
                local_spec = true;
                buf::Manip(stream).forward();
                data.float_precision = format_read_parameter(executor, stream, -1);
            }

            if (access.is_equal_to('>')) {
                local_spec = true;
                buf::Manip(stream).forward();
                parse_format_data_special_shift_type(executor, stream, data, detail::ShiftInfo::ShiftType::Right);
            } else if (access.is_equal_to('<')) {
                buf::Manip(stream).forward();
                parse_format_data_special_shift_type(executor, stream, data, detail::ShiftInfo::ShiftType::Left);
            } else if (access.is_equal_to('^')) {
                buf::Manip(stream).forward();
                if (access.is_equal_to('<')) {
                    buf::Manip(stream).forward();
                    parse_format_data_special_shift_type(executor, stream, data, detail::ShiftInfo::ShiftType::CenterLeft);
                } else {
                    manip.ignore_one_of('>');
                    parse_format_data_special_shift_type(executor, stream, data, detail::ShiftInfo::ShiftType::CenterRight);
                }
            }

            if (access.is_equal_to(':')) {
                local_spec = true;
                buf::Manip(stream).forward();
                data.next_override = parse_next_override_format_data(executor, stream, data);
            }

            return local_spec;
        }

        template <typename Executor>
        void parse_format_data_custom(Executor& executor, buf::StreamView<typename Executor::TChar>& stream, detail::FormatData<typename Executor::TChar>& data) {
            buf::TestAccess access(stream);
            buf::TestManip  manip(stream);

            std::basic_string_view<typename Executor::TChar> name = manip.view_exec([&] { buf::FMTParamsManip(stream).param_go_to(' ', '=', '\'', '{', ','); });
            buf::FMTParamsManip(stream).param_go_to('=', '\'', '{', ',');
            manip.ignore_one_of('=');
            manip.ignore_every_spaces();

            if (access.is_equal_to('\'')) {
                buf::Manip(stream).forward();
                std::basic_string_view<typename Executor::TChar> value = buf::TestManip(stream).view_until('\'');
                data.specifiers.concat(detail::FormatSpecifier{name, value});
                buf::Manip(stream).forward();
            } else if (access.is_a_digit()) {
                std::int32_t value = 0;
                buf::ReadManip(stream).fast_read_integer(value);
                data.specifiers.concat(detail::FormatSpecifier{name, value});
            } else if (access.is_equal_to('{')) {
                buf::Manip(stream).forward();
                std::optional<std::int32_t> idx = get_format_index(executor, stream);
                // TODO / FIXME
                // data.specifiers.concat(detail::FormatSpecifier{name, GetTypeAtIndexAuto(idx)});
                manip.skip_one_of('}');
            } else if (access.is_equal_to(',', '}')) {
                data.specifiers.concat(detail::FormatSpecifier{name});
            }
        }
    }  // namespace

    template <typename Executor>
    detail::FormatData<typename Executor::TChar> parse_format_data(Executor& executor, buf::StreamView<typename Executor::TChar>& stream) {
        detail::FormatData<typename Executor::TChar> data;

        buf::TestAccess access(stream);

        data.has_spec = true;
        while (stream.is_end_of_string() == false && buf::FMTParamsManip(stream).is_end_of_parameter() == false) {
            buf::TestManip(stream).ignore_every_spaces();

            if (access.is_upper_case()) {
                parse_format_data_base(executor, stream, data);
            } else if (parse_format_data_special(executor, stream, data)) {
            } else {
                parse_format_data_custom(executor, stream, data);
            }

            buf::FMTParamsManip(stream).param_go_to(',');
            buf::TestManip(stream).ignore_one_of(',');
        }

        return data;
    }
}  // namespace stream::fmt::detail
