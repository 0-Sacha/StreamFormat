#pragma once

#include "basic_context.h"

#include "stream/fmt/buf/manip.h"
#include "stream/fmt/buf/test_manip.h"
#include "stream/fmt/buf/write_manip.h"
#include "stream/fmt/buf/read_manip.h"
#include "stream/fmt/buf/fmt_manip_io.h"
#include "stream/fmt/buf/fmt_read_manip.h"

namespace stream::fmt::context
{
    template <typename TChar>
    [[nodiscard]] std::expected<std::basic_string_view<TChar>, FMTResult> BasicContext<TChar>::parse_next_override_format_data()
    {
        // TODO: check that function
        buf::TestAccess access(fmtstream);
        buf::TestManip manip(fmtstream);

        manip.ignore_every_spaces();
        buf::FMTParamsManip(fmtstream).param_go_to('{', '=', ':');
        manip.ignore_every_spaces();
        manip.ignore_one_of('=', ':');
        manip.ignore_every_spaces();
        buf::FMTParamsManip(fmtstream).param_go_to('{');

        const TChar* begin = fmtstream.current_pos;
        SF_TRY(manip.skip_one_of('{'));
        int scopes = 0;
        while (buf::FMTParamsManip(fmtstream).is_end_of_parameter() == false || scopes > 0)
        {
            manip.GoTo('\'', '}', '{');
            if (access.is_equal_to('\''))
            {
                SF_TRY(buf::Manip(fmtstream).forward());
                manip.go_to_forward('\'');
            }
            else if (access.is_equal_to('{'))
            {
                SF_TRY(buf::Manip(fmtstream).forward());
                scopes++;
            }
            else if (scopes > 0 && access.is_equal_to('}'))
            {
                SF_TRY(buf::Manip(fmtstream).forward());
                scopes--;
            }
        }
        manip.skip_one_of('}');
        const TChar* end = fmtstream.current_pos;
        return std::basic_string_view<TChar>(begin, end - begin);
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::parse_format_data_base()
    {
        buf::TestAccess access(fmtstream);

        if (access.is_equal_to('C'))
        {
            SF_TRY(buf::Manip(fmtstream).forward());
            SF_TRY(executor.TextManager.parse_color(*this));
        }
        else if (access.is_equal_to('S'))
        {
            SF_TRY(buf::Manip(fmtstream).forward());
            SF_TRY(executor.TextManager.parse_style(*this));
        }
        else if (access.is_equal_to('F'))
        {
            SF_TRY(buf::Manip(fmtstream).forward());
            SF_TRY(executor.TextManager.parse_front(*this));
        }

        else if (access.is_equal_to('K'))
        {
            SF_TRY(buf::Manip(fmtstream).forward());
            executor.data.keep_new_style = true;
        }

        else if (access.is_equal_to('N'))
        {
            SF_TRY(buf::Manip(fmtstream).forward());
            executor.data.next_override = SF_TRY(parse_next_override_format_data());
        }
        
        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::parse_format_dataSpecial_ShiftType(const detail::ShiftInfo::ShiftType type)
    {
        executor.data.shift.type = type;
        executor.data.shift.size = SF_TRY(format_read_parameter(-1));
        if (buf::TestAccess(fmtstream).is_equal_to(':'))
        {
            SF_TRY(buf::Manip(fmtstream).forward());
            executor.data.shift.print.before = SF_TRY(buf::Manip(fmtstream).get_and_forward());
            executor.data.shift.print.after  = executor.data.shift.print.before;
            if (buf::TestAccess(fmtstream).is_equal_to('|'))
            {
                SF_TRY(buf::Manip(fmtstream).forward());
                executor.data.shift.print.after = SF_TRY(buf::Manip(fmtstream).get_and_forward());
            }
        }
        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::parse_format_dataSpecial()
    {
        buf::TestAccess access(fmtstream);
        buf::TestManip manip(fmtstream);

        if (access.is_equal_to('{'))
        {
            SF_TRY(buf::Manip(fmtstream).forward());
            std::int32_t formatIndex = SF_TRY(GetFormatIndex());
            bool ableToapply = false;
            
            auto applyFormatData = SF_TRY(args_interface.template get_type_at<detail::FormatData<TChar>>(formatIndex));
            ableToapply |= executor.data.testapply(applyFormatData);
            auto applyFormatSpecifier = SF_TRY(args_interface.template get_type_at<detail::FormatSpecifier<TChar>>(formatIndex));
            ableToapply |= executor.data.testapply(applyFormatSpecifier);
            auto applyIntegerPrintBase = SF_TRY(args_interface.template get_type_at<detail::IntegerPrintBase>(formatIndex));
            ableToapply |= executor.data.testapply(applyIntegerPrintBase);
            auto applyShiftInfo = SF_TRY(args_interface.template get_type_at<detail::ShiftInfo>(formatIndex));
            ableToapply |= executor.data.testapply(applyShiftInfo);

            if (not ableToapply)
                { return std::unexpected(FMTResult::Context_CannotapplyType); }
            SF_TRY(manip.skip_one_of('}'));
        }

        else if (access.is_equal_to('.'))
        {
            SF_TRY(buf::Manip(fmtstream).forward());
            executor.data.float_precision = SF_TRY(format_read_parameter(-1));
        }

        else if (access.is_equal_to('d', 'b', 'b', 'o', 'O', 'x', 'X'))
        {
            auto get = SF_TRY(buf::Manip(fmtstream).get_and_forward());
            executor.data.integer_print = static_cast<detail::IntegerPrintBase>(get);
        }

        else if (access.is_equal_to('#'))
        {
            SF_TRY(buf::Manip(fmtstream).forward());
            executor.data.prefix_suffix = true;
        }

        else if (access.is_equal_to('>'))
        {
            SF_TRY(buf::Manip(fmtstream).forward());
            SF_TRY(parse_format_dataSpecial_ShiftType(detail::ShiftInfo::ShiftType::Right));
        }
        else if (access.is_equal_to('<'))
        {
            SF_TRY(buf::Manip(fmtstream).forward());
            SF_TRY(parse_format_dataSpecial_ShiftType(detail::ShiftInfo::ShiftType::Left));
        }
        else if (access.is_equal_to('^'))
        {
            SF_TRY(buf::Manip(fmtstream).forward());
            if (access.is_equal_to('<'))
            {
                SF_TRY(buf::Manip(fmtstream).forward());
                SF_TRY(parse_format_dataSpecial_ShiftType(detail::ShiftInfo::ShiftType::CenterLeft));
            }
            else
            {
                manip.ignore_one_of('>');
                SF_TRY(parse_format_dataSpecial_ShiftType(detail::ShiftInfo::ShiftType::CenterRight));
            }
        }

        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::parse_format_dataCustom()
    {
        buf::TestAccess access(fmtstream);
        buf::TestManip manip(fmtstream);

        std::basic_string_view<TChar> name = SF_TRY(manip.ViewExec(
            [&] -> std::expected<void, FMTResult> { buf::FMTParamsManip(fmtstream).param_go_to(' ', '=', '\'', '{', ','); return {}; }
        ));
        buf::FMTParamsManip(fmtstream).param_go_to('=', '\'', '{', ',');
        manip.ignore_one_of('=');
        manip.ignore_every_spaces();

        if (access.is_equal_to('\''))
        {
            SF_TRY(buf::Manip(fmtstream).forward());
            std::basic_string_view<TChar> value = SF_TRY(buf::TestManip(fmtstream).view_until('\''));
            SF_TRY(executor.data.specifiers.concat(detail::FormatSpecifier{name, value}));
        }
        else if (access.is_a_digit())
        {
            std::int32_t value = 0;
            SF_TRY(buf::ReadManip(fmtstream).fast_read_integer(value));
            SF_TRY(executor.data.specifiers.concat(detail::FormatSpecifier{name, value}));
        }
        else if (access.is_equal_to('{'))
        {
            SF_TRY(buf::Manip(fmtstream).forward());
            std::int32_t idx = SF_TRY(GetFormatIndex());
            // TODO / FIXME
            // executor.data.specifiers.concat(detail::FormatSpecifier{name, GetTypeAtIndexAuto(idx)});
            SF_TRY(manip.skip_one_of('}'));
        }
        else if (access.is_equal_to(',', '}'))
        {
            SF_TRY(executor.data.specifiers.concat(detail::FormatSpecifier{name}));
        }

        return {};
    }

    /////---------- Impl ----------/////
    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::parse_format_data()
    {
        buf::TestAccess access(fmtstream);
        buf::TestManip manip(fmtstream);

        executor.data.has_spec = true;
        while (buf::Access(fmtstream).is_end_of_string() == false && buf::FMTParamsManip(fmtstream).is_end_of_parameter() == false)
        {
            manip.ignore_every_spaces();

            if (access.IsUpperCase())
                { SF_TRY(parse_format_data_base()); }
            else if (!access.IsLowerCase())
                { SF_TRY(parse_format_dataSpecial()); }
            else
                { SF_TRY(parse_format_dataCustom()); }

            buf::FMTParamsManip(fmtstream).param_go_to(',');
            buf::TestManip(fmtstream).ignore_one_of(',');
        }
        return {};
    }


    template <typename TChar>
    [[nodiscard]] std::expected<std::int32_t, FMTResult> BasicContext<TChar>::GetFormatIndex_Number()
    {
        std::int32_t index = -1;
        SF_TRY(buf::ReadManip(fmtstream).fast_read_integer(index));

        if (buf::TestAccess(fmtstream).is_equal_to(':') || buf::TestAccess(fmtstream).is_equal_to('}'))
        {
            if (index >= 0 && index < args_interface.size())
                { return index; }
        }

        return std::unexpected(FMTResult::Context_ArgumentIndexResolution);
    }
    template <typename TChar>
    [[nodiscard]] std::expected<std::int32_t, FMTResult> BasicContext<TChar>::GetFormatIndex_Name()
    {
        std::int32_t index = SF_TRY(args_interface.get_index_of_current_named_arg(fmtstream));
        if (buf::TestAccess(fmtstream).is_equal_to(':') || buf::TestAccess(fmtstream).is_equal_to('}'))
        {
            if (index >= 0 && index < args_interface.size())
                { return index; }
        }

        return std::unexpected(FMTResult::Context_ArgumentIndexResolution);
    }
    template <typename TChar>
    [[nodiscard]] std::expected<std::int32_t, FMTResult> BasicContext<TChar>::GetFormatIndex_SubIndex()
    {
        buf::TestAccess access(fmtstream);
        buf::TestManip manip(fmtstream);

        if (access.is_equal_to('{'))
        {
            SF_TRY(buf::Manip(fmtstream).forward());
            std::int32_t recIndex = SF_TRY(GetFormatIndex());
            if (access.is_equal_to('}') && recIndex >= 0 && recIndex < args_interface.size())
            {
                SF_TRY(buf::Manip(fmtstream).forward());
                manip.ignore_every_spaces();
                if (access.is_equal_to(':', '}'))
                {
                    std::int32_t finalRecIndex = (std::int32_t)SF_TRY(args_interface.get_int_at(recIndex));
                    if (finalRecIndex >= 0 && finalRecIndex < args_interface.size())
                        return finalRecIndex;
                }
            }
        }
        return std::unexpected(FMTResult::Context_ArgumentIndexResolution);
    }

    template <typename TChar>
    [[nodiscard]] std::expected<std::int32_t, FMTResult> BasicContext<TChar>::GetFormatIndex()
    {
        buf::TestAccess access(fmtstream);

        // I : if there is no number specified : ':' or '}'
        if (access.is_equal_to(':') || access.is_equal_to('}'))
            if (values_index < args_interface.size())
                { return values_index++; }

        // II: A number(idx)
        if (access.is_a_digit())
        {
            return SF_FORWARD(GetFormatIndex_Number());
        }

        // III : A name
        if (access.IsLowerCase() || access.IsUpperCase())
        {
            return SF_FORWARD(GetFormatIndex_Name());
        }

        // VI : { which is a idx to an argument
        if (access.is_equal_to('{'))
        {
            const TChar* oldPos = fmtstream.current_pos;
            std::expected<std::int32_t, FMTResult> res = GetFormatIndex_SubIndex();
            if (res.has_value() == false && res.error() == FMTResult::Context_ArgumentIndexResolution)
            {
                fmtstream.current_pos = oldPos;
                return std::unexpected(FMTResult::Context_ArgumentIndexResolution);
            }
            return SF_FORWARD(res);
        }

        return std::unexpected(FMTResult::Context_ArgumentIndexResolution);
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::ParseVariable(std::int32_t formatIdx)
    {
        detail::FormatData<TChar> saveFormatData = executor.data;
        executor.data = detail::FormatData<TChar>{};
        detail::TextProperties::Properties saveTextProperties = executor.TextManager.save();

        if (buf::TestAccess(fmtstream).is_equal_to(':', '{'))
        {
            SF_TRY(buf::Manip(fmtstream).forward());
            SF_TRY(parse_format_data());
        }

        SF_TRY(args_interface.run_type_at(formatIdx));

        if (executor.data.keep_new_style == false)
            { SF_TRY(executor.TextManager.reload(saveTextProperties)); }

        executor.data = saveFormatData;

        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::parse()
    {
        buf::Manip(fmtstream).forward();  // Ignore {

        if (buf::TestAccess(fmtstream).IsUpperCase())
        {
            SF_TRY(parse_format_data());
            return buf::FMTParamsManip(fmtstream).param_go_to_forward(); // Ignore }
        }

        auto formatIdx = GetFormatIndex();
        if (formatIdx.has_value())
        {
            if (formatIdx.value() >= 0 && formatIdx.value() < args_interface.size())
            {
                SF_TRY(ParseVariable(formatIdx.value()));
                return buf::FMTParamsManip(fmtstream).param_go_to_forward(); // Ignore }
            }
        }

        SF_TRY(executor.exec_raw_string("{"));
        return {};
    }
}
