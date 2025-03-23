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
    [[nodiscard]] std::expected<std::basic_string_view<TChar>, FMTResult> BasicContext<TChar>::parse_next_override_format_data() {
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
        SF_VERIFY(manip.skip_one_of('{'));
        int scopes = 0;
        while (buf::FMTParamsManip(fmtstream).is_end_of_parameter() == false || scopes > 0) {
            manip.GoTo('\'', '}', '{');
            if (access.is_equal_to('\'')) {
                SF_VERIFY(buf::Manip(fmtstream).forward());
                manip.go_to_forward('\'');
            } else if (access.is_equal_to('{')) {
                SF_VERIFY(buf::Manip(fmtstream).forward());
                scopes++;
            } else if (scopes > 0 && access.is_equal_to('}')) {
                SF_VERIFY(buf::Manip(fmtstream).forward());
                scopes--;
            }
        }
        manip.skip_one_of('}');
        const TChar* end = fmtstream.current_pos;
        return std::basic_string_view<TChar>(begin, end - begin);
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::parse_format_data_base() {
        buf::TestAccess access(fmtstream);

        if (access.is_equal_to('C')) {
            SF_VERIFY(buf::Manip(fmtstream).forward());
            SF_VERIFY(executor.text_manager.parse_color(*this));
        } else if (access.is_equal_to('S')) {
            SF_VERIFY(buf::Manip(fmtstream).forward());
            SF_VERIFY(executor.text_manager.parse_style(*this));
        } else if (access.is_equal_to('F')) {
            SF_VERIFY(buf::Manip(fmtstream).forward());
            SF_VERIFY(executor.text_manager.parse_front(*this));
        }

        else if (access.is_equal_to('K')) {
            SF_VERIFY(buf::Manip(fmtstream).forward());
            executor.data.keep_new_style = true;
        }

        else if (access.is_equal_to('N')) {
            SF_VERIFY(buf::Manip(fmtstream).forward());
            executor.data.next_override = SF_TRY(parse_next_override_format_data());
        }

        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::parse_format_data_special_shift_type(const detail::ShiftInfo::ShiftType type) {
        executor.data.shift.type = type;
        executor.data.shift.size = SF_TRY(format_read_parameter(-1));
        if (buf::TestAccess(fmtstream).is_equal_to(':')) {
            SF_VERIFY(buf::Manip(fmtstream).forward());
            executor.data.shift.print.before = fmtstream.get();
            executor.data.shift.print.after  = executor.data.shift.print.before;
            SF_VERIFY(buf::Manip(fmtstream).forward());
            if (buf::TestAccess(fmtstream).is_equal_to('|')) {
                SF_VERIFY(buf::Manip(fmtstream).forward());
                executor.data.shift.print.after = fmtstream.get();
                SF_VERIFY(buf::Manip(fmtstream).forward());
            }
        }
        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::parse_format_dataSpecial() {
        buf::TestAccess access(fmtstream);
        buf::TestManip  manip(fmtstream);

        if (access.is_equal_to('{')) {
            SF_VERIFY(buf::Manip(fmtstream).forward());
            std::int32_t formatIndex = SF_TRY(get_format_index());
            bool         ableToapply = false;

            auto applyFormatData = SF_TRY(args_interface.template get_type_at<detail::FormatData<TChar>>(formatIndex));
            ableToapply |= executor.data.testapply(applyFormatData);
            auto applyFormatSpecifier = SF_TRY(args_interface.template get_type_at<detail::FormatSpecifier<TChar>>(formatIndex));
            ableToapply |= executor.data.testapply(applyFormatSpecifier);
            auto applyIntegerPrintBase = SF_TRY(args_interface.template get_type_at<detail::IntegerPrintBase>(formatIndex));
            ableToapply |= executor.data.testapply(applyIntegerPrintBase);
            auto applyShiftInfo = SF_TRY(args_interface.template get_type_at<detail::ShiftInfo>(formatIndex));
            ableToapply |= executor.data.testapply(applyShiftInfo);

            if (not ableToapply) {
                return std::unexpected(FMTResult::Context_CannotapplyType);
            }
            SF_VERIFY(manip.skip_one_of('}'));
        }

        else if (access.is_equal_to('.')) {
            SF_VERIFY(buf::Manip(fmtstream).forward());
            executor.data.float_precision = SF_TRY(format_read_parameter(-1));
        }

        else if (access.is_equal_to('d', 'b', 'b', 'o', 'O', 'x', 'X')) {
            executor.data.integer_print = static_cast<detail::IntegerPrintBase>(fmtstream.get());
            SF_VERIFY(buf::Manip(fmtstream).forward());
        }

        else if (access.is_equal_to('#')) {
            SF_VERIFY(buf::Manip(fmtstream).forward());
            executor.data.prefix_suffix = true;
        }

        else if (access.is_equal_to('>')) {
            SF_VERIFY(buf::Manip(fmtstream).forward());
            SF_VERIFY(parse_format_data_special_shift_type(detail::ShiftInfo::ShiftType::Right));
        } else if (access.is_equal_to('<')) {
            SF_VERIFY(buf::Manip(fmtstream).forward());
            SF_VERIFY(parse_format_data_special_shift_type(detail::ShiftInfo::ShiftType::Left));
        } else if (access.is_equal_to('^')) {
            SF_VERIFY(buf::Manip(fmtstream).forward());
            if (access.is_equal_to('<')) {
                SF_VERIFY(buf::Manip(fmtstream).forward());
                SF_VERIFY(parse_format_data_special_shift_type(detail::ShiftInfo::ShiftType::CenterLeft));
            } else {
                manip.ignore_one_of('>');
                SF_VERIFY(parse_format_data_special_shift_type(detail::ShiftInfo::ShiftType::CenterRight));
            }
        }

        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::parse_format_dataCustom() {
        buf::TestAccess access(fmtstream);
        buf::TestManip  manip(fmtstream);

        std::basic_string_view<TChar> name = SF_TRY(manip.ViewExec([&] -> std::expected<void, FMTResult> {
            buf::FMTParamsManip(fmtstream).param_go_to(' ', '=', '\'', '{', ',');
            return {};
        }));
        buf::FMTParamsManip(fmtstream).param_go_to('=', '\'', '{', ',');
        manip.ignore_one_of('=');
        manip.ignore_every_spaces();

        if (access.is_equal_to('\'')) {
            SF_VERIFY(buf::Manip(fmtstream).forward());
            std::basic_string_view<TChar> value = SF_TRY(buf::TestManip(fmtstream).view_until('\''));
            SF_VERIFY(executor.data.specifiers.concat(detail::FormatSpecifier{name, value}));
        } else if (access.is_a_digit()) {
            std::int32_t value = 0;
            SF_VERIFY(buf::ReadManip(fmtstream).fast_read_integer(value));
            SF_VERIFY(executor.data.specifiers.concat(detail::FormatSpecifier{name, value}));
        } else if (access.is_equal_to('{')) {
            SF_VERIFY(buf::Manip(fmtstream).forward());
            std::int32_t idx = SF_TRY(get_format_index());
            // TODO / FIXME
            // executor.data.specifiers.concat(detail::FormatSpecifier{name, GetTypeAtIndexAuto(idx)});
            SF_VERIFY(manip.skip_one_of('}'));
        } else if (access.is_equal_to(',', '}')) {
            SF_VERIFY(executor.data.specifiers.concat(detail::FormatSpecifier{name}));
        }

        return {};
    }

    /////---------- Impl ----------/////
    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::parse_format_data() {
        buf::TestAccess access(fmtstream);
        buf::TestManip  manip(fmtstream);

        executor.data.has_spec = true;
        while (buf::Access(fmtstream).is_end_of_string() == false && buf::FMTParamsManip(fmtstream).is_end_of_parameter() == false) {
            manip.ignore_every_spaces();

            if (access.is_upper_case()) {
                SF_VERIFY(parse_format_data_base());
            } else if (!access.is_lower_case()) {
                SF_VERIFY(parse_format_dataSpecial());
            } else {
                SF_VERIFY(parse_format_dataCustom());
            }

            buf::FMTParamsManip(fmtstream).param_go_to(',');
            buf::TestManip(fmtstream).ignore_one_of(',');
        }
        return {};
    }


    template <typename TChar>
    [[nodiscard]] std::expected<std::int32_t, FMTResult> BasicContext<TChar>::get_format_index_number() {
        std::int32_t index = -1;
        SF_VERIFY(buf::ReadManip(fmtstream).fast_read_integer(index));

        if (buf::TestAccess(fmtstream).is_equal_to(':') || buf::TestAccess(fmtstream).is_equal_to('}')) {
            if (index >= 0 && index < args_interface.size()) {
                return index;
            }
        }

        return std::unexpected(FMTResult::Context_ArgumentIndexResolution);
    }
    template <typename TChar>
    [[nodiscard]] std::expected<std::int32_t, FMTResult> BasicContext<TChar>::get_format_index_name() {
        std::int32_t index = SF_TRY(args_interface.get_index_of_current_named_arg(fmtstream));
        if (buf::TestAccess(fmtstream).is_equal_to(':') || buf::TestAccess(fmtstream).is_equal_to('}')) {
            if (index >= 0 && index < args_interface.size()) {
                return index;
            }
        }

        return std::unexpected(FMTResult::Context_ArgumentIndexResolution);
    }
    template <typename TChar>
    [[nodiscard]] std::expected<std::int32_t, FMTResult> BasicContext<TChar>::get_format_index_sub_index() {
        buf::TestAccess access(fmtstream);
        buf::TestManip  manip(fmtstream);

        if (access.is_equal_to('{')) {
            SF_VERIFY(buf::Manip(fmtstream).forward());
            std::int32_t rec_index = SF_TRY(get_format_index());
            if (access.is_equal_to('}') && rec_index >= 0 && rec_index < args_interface.size()) {
                SF_VERIFY(buf::Manip(fmtstream).forward());
                manip.ignore_every_spaces();
                if (access.is_equal_to(':', '}')) {
                    std::int32_t final_rec_index = (std::int32_t)SF_TRY(args_interface.get_int_at(rec_index));
                    if (final_rec_index >= 0 && final_rec_index < args_interface.size()) return final_rec_index;
                }
            }
        }
        return std::unexpected(FMTResult::Context_ArgumentIndexResolution);
    }

    template <typename TChar>
    [[nodiscard]] std::expected<std::int32_t, FMTResult> BasicContext<TChar>::get_format_index() {
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
            const TChar*                           oldPos = fmtstream.current_pos;
            std::expected<std::int32_t, FMTResult> res    = get_format_index_sub_index();
            if (res.has_value() == false && res.error() == FMTResult::Context_ArgumentIndexResolution) {
                fmtstream.current_pos = oldPos;
                return std::unexpected(FMTResult::Context_ArgumentIndexResolution);
            }
            return res;
        }

        return std::unexpected(FMTResult::Context_ArgumentIndexResolution);
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::parse_variable(std::int32_t formatIdx) {
        detail::FormatData<TChar> saveFormatData              = executor.data;
        executor.data                                         = detail::FormatData<TChar>{};
        detail::TextProperties::Properties saveTextProperties = executor.text_manager.save();

        if (buf::TestAccess(fmtstream).is_equal_to(':', '{')) {
            SF_VERIFY(buf::Manip(fmtstream).forward());
            SF_VERIFY(parse_format_data());
        }

        SF_VERIFY(args_interface.run_type_at(formatIdx));

        if (executor.data.keep_new_style == false) {
            SF_VERIFY(executor.text_manager.reload(saveTextProperties));
        }

        executor.data = saveFormatData;

        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::parse() {
        buf::Manip(fmtstream).forward();  // Ignore {

        if (buf::TestAccess(fmtstream).is_upper_case()) {
            SF_VERIFY(parse_format_data());
            return buf::FMTParamsManip(fmtstream).param_go_to_forward();  // Ignore }
        }

        auto formatIdx = get_format_index();
        if (formatIdx.has_value()) {
            if (formatIdx.value() >= 0 && formatIdx.value() < args_interface.size()) {
                SF_VERIFY(parse_variable(formatIdx.value()));
                return buf::FMTParamsManip(fmtstream).param_go_to_forward();  // Ignore }
            }
        }

        SF_VERIFY(executor.exec_raw_string("{"));
        return {};
    }
}  // namespace stream::fmt::context
