#pragma once

#include "basic_context.hxx"

#include "stream/fmt/buf/manip.hxx"
#include "stream/fmt/buf/test_manip.hxx"
#include "stream/fmt/buf/write_manip.hxx"
#include "stream/fmt/buf/read_manip.hxx"
#include "stream/fmt/buf/fmt_manip_io.hxx"
#include "stream/fmt/buf/fmt_read_manip.hxx"

namespace stream::fmt::context {
    template <typename TChar>
    std::basic_string_view<TChar> BasicContext<TChar>::parse_next_override_format_data() {
        // TODO: check that function
        buf::TestAccess access(fmtstream);
        buf::TestManip  manip(fmtstream);

        manip.ignore_every_spaces();
        buf::FMTParamsManip(fmtstream).param_go_to('{', '=', ':');
        manip.ignore_every_spaces();
        manip.ignore_one_of('=', ':');
        manip.ignore_every_spaces();
        buf::FMTParamsManip(fmtstream).param_go_to('{');

        const TChar* begin = fmtstream.current_pos;
        manip.skip_one_of('{');
        int scopes = 0;
        while (buf::FMTParamsManip(fmtstream).is_end_of_parameter() == false || scopes > 0) {
            manip.GoTo('\'', '}', '{');
            if (access.is_equal_to('\'')) {
                buf::Manip(fmtstream).forward();
                manip.go_to_forward('\'');
            } else if (access.is_equal_to('{')) {
                buf::Manip(fmtstream).forward();
                scopes++;
            } else if (scopes > 0 && access.is_equal_to('}')) {
                buf::Manip(fmtstream).forward();
                scopes--;
            }
        }
        manip.skip_one_of('}');
        const TChar* end = fmtstream.current_pos;
        return std::basic_string_view<TChar>(begin, end - begin);
    }

    template <typename TChar>
    void BasicContext<TChar>::parse_format_data_base() {
        buf::TestAccess access(fmtstream);

        if (access.is_equal_to('C')) {
            buf::Manip(fmtstream).forward();
            executor.text_manager.parse_color(*this);
        } else if (access.is_equal_to('S')) {
            buf::Manip(fmtstream).forward();
            executor.text_manager.parse_style(*this);
        } else if (access.is_equal_to('F')) {
            buf::Manip(fmtstream).forward();
            executor.text_manager.parse_front(*this);
        }

        else if (access.is_equal_to('K')) {
            buf::Manip(fmtstream).forward();
            executor.data.keep_new_style = true;
        }

        else if (access.is_equal_to('N')) {
            buf::Manip(fmtstream).forward();
            executor.data.next_override = parse_next_override_format_data();
        }
    }

    template <typename TChar>
    void BasicContext<TChar>::parse_format_data_special_shift_type(const detail::ShiftInfo::ShiftType type) {
        executor.data.shift.type = type;
        executor.data.shift.size = format_read_parameter(-1);
        if (buf::TestAccess(fmtstream).is_equal_to(':')) {
            buf::Manip(fmtstream).forward();
            executor.data.shift.print.before = fmtstream.get();
            executor.data.shift.print.after  = executor.data.shift.print.before;
            buf::Manip(fmtstream).forward();
            if (buf::TestAccess(fmtstream).is_equal_to('|')) {
                buf::Manip(fmtstream).forward();
                executor.data.shift.print.after = fmtstream.get();
                buf::Manip(fmtstream).forward();
            }
        }
    }

    template <typename TChar>
    void BasicContext<TChar>::parse_format_data_special() {
        buf::TestAccess access(fmtstream);
        buf::TestManip  manip(fmtstream);

        if (access.is_equal_to('{')) {
            buf::Manip(fmtstream).forward();
            std::optional<std::int32_t> format_index = get_format_index();

            bool ableToapply = false;
            if (format_index.has_value()) {
                auto applyFormatData = args_interface.template get_type_at<detail::FormatData<TChar>>(format_index.value());
                ableToapply |= executor.data.testapply(applyFormatData);
                auto applyFormatSpecifier = args_interface.template get_type_at<detail::FormatSpecifier<TChar>>(format_index.value());
                ableToapply |= executor.data.testapply(applyFormatSpecifier);
                auto applyIntegerPrintBase = args_interface.template get_type_at<detail::IntegerPrintBase>(format_index.value());
                ableToapply |= executor.data.testapply(applyIntegerPrintBase);
                auto applyShiftInfo = args_interface.template get_type_at<detail::ShiftInfo>(format_index.value());
                ableToapply |= executor.data.testapply(applyShiftInfo);
            }

            if (not ableToapply) {
                throw std::runtime_error("fmt error: Context_CannotapplyType");
            }
            manip.skip_one_of('}');
        }

        else if (access.is_equal_to('.')) {
            buf::Manip(fmtstream).forward();
            executor.data.float_precision = format_read_parameter(-1);
        }

        else if (access.is_equal_to('d', 'b', 'b', 'o', 'O', 'x', 'X')) {
            executor.data.integer_print = static_cast<detail::IntegerPrintBase>(fmtstream.get());
            buf::Manip(fmtstream).forward();
        }

        else if (access.is_equal_to('#')) {
            buf::Manip(fmtstream).forward();
            executor.data.prefix_suffix = true;
        }

        else if (access.is_equal_to('>')) {
            buf::Manip(fmtstream).forward();
            parse_format_data_special_shift_type(detail::ShiftInfo::ShiftType::Right);
        } else if (access.is_equal_to('<')) {
            buf::Manip(fmtstream).forward();
            parse_format_data_special_shift_type(detail::ShiftInfo::ShiftType::Left);
        } else if (access.is_equal_to('^')) {
            buf::Manip(fmtstream).forward();
            if (access.is_equal_to('<')) {
                buf::Manip(fmtstream).forward();
                parse_format_data_special_shift_type(detail::ShiftInfo::ShiftType::CenterLeft);
            } else {
                manip.ignore_one_of('>');
                parse_format_data_special_shift_type(detail::ShiftInfo::ShiftType::CenterRight);
            }
        }
    }

    template <typename TChar>
    void BasicContext<TChar>::parse_format_dataCustom() {
        buf::TestAccess access(fmtstream);
        buf::TestManip  manip(fmtstream);

        std::basic_string_view<TChar> name = manip.view_exec([&] -> void { buf::FMTParamsManip(fmtstream).param_go_to(' ', '=', '\'', '{', ','); });
        buf::FMTParamsManip(fmtstream).param_go_to('=', '\'', '{', ',');
        manip.ignore_one_of('=');
        manip.ignore_every_spaces();

        if (access.is_equal_to('\'')) {
            buf::Manip(fmtstream).forward();
            std::basic_string_view<TChar> value = buf::TestManip(fmtstream).view_until('\'');
            executor.data.specifiers.concat(detail::FormatSpecifier{name, value});
        } else if (access.is_a_digit()) {
            std::int32_t value = 0;
            buf::ReadManip(fmtstream).fast_read_integer(value);
            executor.data.specifiers.concat(detail::FormatSpecifier{name, value});
        } else if (access.is_equal_to('{')) {
            buf::Manip(fmtstream).forward();
            std::optional<std::int32_t> idx = get_format_index();
            // TODO / FIXME
            // executor.data.specifiers.concat(detail::FormatSpecifier{name, GetTypeAtIndexAuto(idx)});
            manip.skip_one_of('}');
        } else if (access.is_equal_to(',', '}')) {
            executor.data.specifiers.concat(detail::FormatSpecifier{name});
        }
    }

    /////---------- Impl ----------/////
    template <typename TChar>
    void BasicContext<TChar>::parse_format_data() {
        buf::TestAccess access(fmtstream);
        buf::TestManip  manip(fmtstream);

        executor.data.has_spec = true;
        while (fmtstream.is_end_of_string() == false && buf::FMTParamsManip(fmtstream).is_end_of_parameter() == false) {
            manip.ignore_every_spaces();

            if (access.is_upper_case()) {
                parse_format_data_base();
            } else if (!access.is_lower_case()) {
                parse_format_data_special();
            } else {
                parse_format_dataCustom();
            }

            buf::FMTParamsManip(fmtstream).param_go_to(',');
            buf::TestManip(fmtstream).ignore_one_of(',');
        }
    }


    template <typename TChar>
    std::optional<std::int32_t> BasicContext<TChar>::get_format_index_number() {
        std::int32_t index = -1;
        buf::ReadManip(fmtstream).fast_read_integer(index);
        if (buf::TestAccess(fmtstream).is_equal_to(':') || buf::TestAccess(fmtstream).is_equal_to('}')) {
            if (index >= 0 && index < args_interface.size()) {
                return index;
            }
        }
        return std::nullopt;
    }
    template <typename TChar>
    std::optional<std::int32_t> BasicContext<TChar>::get_format_index_name() {
        std::optional<std::int32_t> index = args_interface.get_index_of_current_named_arg(fmtstream);
        if (index.has_value() == false) return std::nullopt;
        if (buf::TestAccess(fmtstream).is_equal_to(':') || buf::TestAccess(fmtstream).is_equal_to('}')) {
            if (index >= 0 && index < args_interface.size()) {
                return index;
            }
        }
        return std::nullopt;
    }
    template <typename TChar>
    std::optional<std::int32_t> BasicContext<TChar>::get_format_index_sub_index() {
        buf::TestAccess access(fmtstream);
        buf::TestManip  manip(fmtstream);

        if (access.is_equal_to('{')) {
            buf::Manip(fmtstream).forward();
            std::optional<std::int32_t> rec_index = get_format_index();
            if (rec_index.has_value() == false) {
                return std::nullopt;
            }
            if (access.is_equal_to('}') && rec_index >= 0 && rec_index < args_interface.size()) {
                buf::Manip(fmtstream).forward();
                manip.ignore_every_spaces();
                if (access.is_equal_to(':', '}')) {
                    std::int32_t final_rec_index = (std::int32_t)args_interface.get_int_at(rec_index.value());
                    if (final_rec_index >= 0 && final_rec_index < args_interface.size()) {
                        return final_rec_index;
                    }
                }
            }
        }
        return std::nullopt;
    }

    template <typename TChar>
    std::optional<std::int32_t> BasicContext<TChar>::get_format_index() {
        buf::TestAccess access(fmtstream);

        // I : if there is no number specified : ':' or '}'
        if (access.is_equal_to(':') || access.is_equal_to('}'))
            if (values_index < args_interface.size()) {
                return values_index++;
            }

        // II: A number(idx)
        if (access.is_a_digit()) {
            return get_format_index_number();
        }

        // III : A name
        if (access.is_lower_case() || access.is_upper_case()) {
            return get_format_index_name();
        }

        // VI : { which is a idx to an argument
        if (access.is_equal_to('{')) {
            const TChar*                oldPos = fmtstream.current_pos;
            std::optional<std::int32_t> res    = get_format_index_sub_index();
            if (res.has_value() == false) {
                fmtstream.current_pos = oldPos;
                return std::nullopt;
            }
            return res;
        }

        return std::nullopt;
    }

    template <typename TChar>
    void BasicContext<TChar>::parse_variable(std::int32_t format_idx) {
        detail::FormatData<TChar> saveFormatData              = executor.data;
        executor.data                                         = detail::FormatData<TChar>{};
        detail::TextProperties::Properties saveTextProperties = executor.text_manager.save();

        if (buf::TestAccess(fmtstream).is_equal_to(':', '{')) {
            buf::Manip(fmtstream).forward();
            parse_format_data();
        }

        args_interface.run_type_at(format_idx);

        if (executor.data.keep_new_style == false) {
            executor.text_manager.reload(saveTextProperties);
        }

        executor.data = saveFormatData;
    }

    template <typename TChar>
    void BasicContext<TChar>::parse() {
        buf::Manip(fmtstream).forward();  // Ignore {

        if (buf::TestAccess(fmtstream).is_upper_case()) {
            parse_format_data();
            return buf::FMTParamsManip(fmtstream).param_go_to_forward();  // Ignore }
        }

        std::optional<std::int32_t> format_idx = get_format_index();
        if (format_idx.has_value()) {
            if (format_idx >= 0 && format_idx < args_interface.size()) {
                parse_variable(format_idx.value());
                return buf::FMTParamsManip(fmtstream).param_go_to_forward();  // Ignore }
            }
        }

        executor.exec_raw_string("{");
    }
}  // namespace stream::fmt::context
