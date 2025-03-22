#pragma once

#include "basic_context.h"

#include "stream/fmt/buffer/buffer_manip.h"
#include "stream/fmt/buffer/buffer_test_manip.h"
#include "stream/fmt/buffer/buffer_write_manip.h"
#include "stream/fmt/buffer/buffer_read_manip.h"
#include "stream/fmt/buffer/fmt_buffer_out_manip.h"
#include "stream/fmt/buffer/FMTBufferReadManip.h"

namespace stream::fmt::context
{
    template <typename TChar>
    [[nodiscard]] std::expected<std::basic_string_view<TChar>, FMTResult> BasicContext<TChar>::ParseNextOverrideFormatData()
    {
        // TODO: check that function
        detail::BufferTestAccess access(Format);
        detail::BufferTestManip manip(Format);

        manip.IgnoreEverySpaces();
        detail::FMTBufferParamsManip(Format).ParamGoTo('{', '=', ':');
        manip.IgnoreEverySpaces();
        manip.IgnoreOneOf('=', ':');
        manip.IgnoreEverySpaces();
        detail::FMTBufferParamsManip(Format).ParamGoTo('{');

        const TChar* begin = Format.CurrentPos;
        SF_TRY(manip.SkipOneOf('{'));
        int scopes = 0;
        while (detail::FMTBufferParamsManip(Format).IsEndOfParameter() == false || scopes > 0)
        {
            manip.GoTo('\'', '}', '{');
            if (access.IsEqualTo('\''))
            {
                SF_TRY(detail::BufferManip(Format).Forward());
                manip.GoToForward('\'');
            }
            else if (access.IsEqualTo('{'))
            {
                SF_TRY(detail::BufferManip(Format).Forward());
                scopes++;
            }
            else if (scopes > 0 && access.IsEqualTo('}'))
            {
                SF_TRY(detail::BufferManip(Format).Forward());
                scopes--;
            }
        }
        manip.SkipOneOf('}');
        const TChar* end = Format.CurrentPos;
        return std::basic_string_view<TChar>(begin, end - begin);
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::ParseFormatDataBase()
    {
        detail::BufferTestAccess access(Format);

        if (access.IsEqualTo('C'))
        {
            SF_TRY(detail::BufferManip(Format).Forward());
            SF_TRY(Executor.TextManager.ParseColor(*this));
        }
        else if (access.IsEqualTo('S'))
        {
            SF_TRY(detail::BufferManip(Format).Forward());
            SF_TRY(Executor.TextManager.ParseStyle(*this));
        }
        else if (access.IsEqualTo('F'))
        {
            SF_TRY(detail::BufferManip(Format).Forward());
            SF_TRY(Executor.TextManager.ParseFront(*this));
        }

        else if (access.IsEqualTo('K'))
        {
            SF_TRY(detail::BufferManip(Format).Forward());
            Executor.Data.KeepNewStyle = true;
        }

        else if (access.IsEqualTo('N'))
        {
            SF_TRY(detail::BufferManip(Format).Forward());
            Executor.Data.NextOverride = SF_TRY(ParseNextOverrideFormatData());
        }
        
        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::ParseFormatDataSpecial_ShiftType(const detail::ShiftInfo::ShiftType type)
    {
        Executor.Data.Shift.Type = type;
        Executor.Data.Shift.Size = SF_TRY(FormatReadParameter(-1));
        if (detail::BufferTestAccess(Format).IsEqualTo(':'))
        {
            SF_TRY(detail::BufferManip(Format).Forward());
            Executor.Data.Shift.Print.Before = SF_TRY(detail::BufferManip(Format).GetAndForward());
            Executor.Data.Shift.Print.After  = Executor.Data.Shift.Print.Before;
            if (detail::BufferTestAccess(Format).IsEqualTo('|'))
            {
                SF_TRY(detail::BufferManip(Format).Forward());
                Executor.Data.Shift.Print.After = SF_TRY(detail::BufferManip(Format).GetAndForward());
            }
        }
        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::ParseFormatDataSpecial()
    {
        detail::BufferTestAccess access(Format);
        detail::BufferTestManip manip(Format);

        if (access.IsEqualTo('{'))
        {
            SF_TRY(detail::BufferManip(Format).Forward());
            std::int32_t formatIndex = SF_TRY(GetFormatIndex());
            bool ableToApply = false;
            
            auto applyFormatData = SF_TRY(ArgsInterface.template GetTypeAt<detail::FormatData<TChar>>(formatIndex));
            ableToApply |= Executor.Data.TestApply(applyFormatData);
            auto applyFormatSpecifier = SF_TRY(ArgsInterface.template GetTypeAt<detail::FormatSpecifier<TChar>>(formatIndex));
            ableToApply |= Executor.Data.TestApply(applyFormatSpecifier);
            auto applyIntegerPrintBase = SF_TRY(ArgsInterface.template GetTypeAt<detail::IntegerPrintBase>(formatIndex));
            ableToApply |= Executor.Data.TestApply(applyIntegerPrintBase);
            auto applyShiftInfo = SF_TRY(ArgsInterface.template GetTypeAt<detail::ShiftInfo>(formatIndex));
            ableToApply |= Executor.Data.TestApply(applyShiftInfo);

            if (not ableToApply)
                { return std::unexpected(FMTResult::Context_CannotApplyType); }
            SF_TRY(manip.SkipOneOf('}'));
        }

        else if (access.IsEqualTo('.'))
        {
            SF_TRY(detail::BufferManip(Format).Forward());
            Executor.Data.FloatPrecision = SF_TRY(FormatReadParameter(-1));
        }

        else if (access.IsEqualTo('d', 'b', 'B', 'o', 'O', 'x', 'X'))
        {
            auto get = SF_TRY(detail::BufferManip(Format).GetAndForward());
            Executor.Data.IntegerPrint = static_cast<detail::IntegerPrintBase>(get);
        }

        else if (access.IsEqualTo('#'))
        {
            SF_TRY(detail::BufferManip(Format).Forward());
            Executor.Data.PrefixSuffix = true;
        }

        else if (access.IsEqualTo('>'))
        {
            SF_TRY(detail::BufferManip(Format).Forward());
            SF_TRY(ParseFormatDataSpecial_ShiftType(detail::ShiftInfo::ShiftType::Right));
        }
        else if (access.IsEqualTo('<'))
        {
            SF_TRY(detail::BufferManip(Format).Forward());
            SF_TRY(ParseFormatDataSpecial_ShiftType(detail::ShiftInfo::ShiftType::Left));
        }
        else if (access.IsEqualTo('^'))
        {
            SF_TRY(detail::BufferManip(Format).Forward());
            if (access.IsEqualTo('<'))
            {
                SF_TRY(detail::BufferManip(Format).Forward());
                SF_TRY(ParseFormatDataSpecial_ShiftType(detail::ShiftInfo::ShiftType::CenterLeft));
            }
            else
            {
                manip.IgnoreOneOf('>');
                SF_TRY(ParseFormatDataSpecial_ShiftType(detail::ShiftInfo::ShiftType::CenterRight));
            }
        }

        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::ParseFormatDataCustom()
    {
        detail::BufferTestAccess access(Format);
        detail::BufferTestManip manip(Format);

        std::basic_string_view<TChar> name = SF_TRY(manip.ViewExec(
            [&] -> std::expected<void, FMTResult> { detail::FMTBufferParamsManip(Format).ParamGoTo(' ', '=', '\'', '{', ','); return {}; }
        ));
        detail::FMTBufferParamsManip(Format).ParamGoTo('=', '\'', '{', ',');
        manip.IgnoreOneOf('=');
        manip.IgnoreEverySpaces();

        if (access.IsEqualTo('\''))
        {
            SF_TRY(detail::BufferManip(Format).Forward());
            std::basic_string_view<TChar> value = SF_TRY(detail::BufferTestManip(Format).ViewUntil('\''));
            SF_TRY(Executor.Data.Specifiers.Concat(detail::FormatSpecifier{name, value}));
        }
        else if (access.IsADigit())
        {
            std::int32_t value = 0;
            SF_TRY(detail::BufferReadManip(Format).FastReadInteger(value));
            SF_TRY(Executor.Data.Specifiers.Concat(detail::FormatSpecifier{name, value}));
        }
        else if (access.IsEqualTo('{'))
        {
            SF_TRY(detail::BufferManip(Format).Forward());
            std::int32_t idx = SF_TRY(GetFormatIndex());
            // TODO / FIXME
            // Executor.Data.Specifiers.Concat(detail::FormatSpecifier{name, GetTypeAtIndexAuto(idx)});
            SF_TRY(manip.SkipOneOf('}'));
        }
        else if (access.IsEqualTo(',', '}'))
        {
            SF_TRY(Executor.Data.Specifiers.Concat(detail::FormatSpecifier{name}));
        }

        return {};
    }

    /////---------- Impl ----------/////
    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::ParseFormatData()
    {
        detail::BufferTestAccess access(Format);
        detail::BufferTestManip manip(Format);

        Executor.Data.HasSpec = true;
        while (detail::BufferAccess(Format).IsEndOfString() == false && detail::FMTBufferParamsManip(Format).IsEndOfParameter() == false)
        {
            manip.IgnoreEverySpaces();

            if (access.IsUpperCase())
                { SF_TRY(ParseFormatDataBase()); }
            else if (!access.IsLowerCase())
                { SF_TRY(ParseFormatDataSpecial()); }
            else
                { SF_TRY(ParseFormatDataCustom()); }

            detail::FMTBufferParamsManip(Format).ParamGoTo(',');
            detail::BufferTestManip(Format).IgnoreOneOf(',');
        }
        return {};
    }


    template <typename TChar>
    [[nodiscard]] std::expected<std::int32_t, FMTResult> BasicContext<TChar>::GetFormatIndex_Number()
    {
        std::int32_t index = -1;
        SF_TRY(detail::BufferReadManip(Format).FastReadInteger(index));

        if (detail::BufferTestAccess(Format).IsEqualTo(':') || detail::BufferTestAccess(Format).IsEqualTo('}'))
        {
            if (index >= 0 && index < ArgsInterface.Size())
                { return index; }
        }

        return std::unexpected(FMTResult::Context_ArgumentIndexResolution);
    }
    template <typename TChar>
    [[nodiscard]] std::expected<std::int32_t, FMTResult> BasicContext<TChar>::GetFormatIndex_Name()
    {
        std::int32_t index = SF_TRY(ArgsInterface.GetIndexOfCurrentNamedArg(Format));
        if (detail::BufferTestAccess(Format).IsEqualTo(':') || detail::BufferTestAccess(Format).IsEqualTo('}'))
        {
            if (index >= 0 && index < ArgsInterface.Size())
                { return index; }
        }

        return std::unexpected(FMTResult::Context_ArgumentIndexResolution);
    }
    template <typename TChar>
    [[nodiscard]] std::expected<std::int32_t, FMTResult> BasicContext<TChar>::GetFormatIndex_SubIndex()
    {
        detail::BufferTestAccess access(Format);
        detail::BufferTestManip manip(Format);

        if (access.IsEqualTo('{'))
        {
            SF_TRY(detail::BufferManip(Format).Forward());
            std::int32_t recIndex = SF_TRY(GetFormatIndex());
            if (access.IsEqualTo('}') && recIndex >= 0 && recIndex < ArgsInterface.Size())
            {
                SF_TRY(detail::BufferManip(Format).Forward());
                manip.IgnoreEverySpaces();
                if (access.IsEqualTo(':', '}'))
                {
                    std::int32_t finalRecIndex = (std::int32_t)SF_TRY(ArgsInterface.GetIntAt(recIndex));
                    if (finalRecIndex >= 0 && finalRecIndex < ArgsInterface.Size())
                        return finalRecIndex;
                }
            }
        }
        return std::unexpected(FMTResult::Context_ArgumentIndexResolution);
    }

    template <typename TChar>
    [[nodiscard]] std::expected<std::int32_t, FMTResult> BasicContext<TChar>::GetFormatIndex()
    {
        detail::BufferTestAccess access(Format);

        // I : if there is no number specified : ':' or '}'
        if (access.IsEqualTo(':') || access.IsEqualTo('}'))
            if (ValuesIndex < ArgsInterface.Size())
                { return ValuesIndex++; }

        // II: A number(idx)
        if (access.IsADigit())
        {
            return SF_FORWARD(GetFormatIndex_Number());
        }

        // III : A name
        if (access.IsLowerCase() || access.IsUpperCase())
        {
            return SF_FORWARD(GetFormatIndex_Name());
        }

        // VI : { which is a idx to an argument
        if (access.IsEqualTo('{'))
        {
            const TChar* oldPos = Format.CurrentPos;
            std::expected<std::int32_t, FMTResult> res = GetFormatIndex_SubIndex();
            if (res.has_value() == false && res.error() == FMTResult::Context_ArgumentIndexResolution)
            {
                Format.CurrentPos = oldPos;
                return std::unexpected(FMTResult::Context_ArgumentIndexResolution);
            }
            return SF_FORWARD(res);
        }

        return std::unexpected(FMTResult::Context_ArgumentIndexResolution);
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::ParseVariable(std::int32_t formatIdx)
    {
        detail::FormatData<TChar> saveFormatData = Executor.Data;
        Executor.Data = detail::FormatData<TChar>{};
        detail::TextProperties::Properties saveTextProperties = Executor.TextManager.Save();

        if (detail::BufferTestAccess(Format).IsEqualTo(':', '{'))
        {
            SF_TRY(detail::BufferManip(Format).Forward());
            SF_TRY(ParseFormatData());
        }

        SF_TRY(ArgsInterface.RunTypeAtIndex(formatIdx));

        if (Executor.Data.KeepNewStyle == false)
            { SF_TRY(Executor.TextManager.Reload(saveTextProperties)); }

        Executor.Data = saveFormatData;

        return {};
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicContext<TChar>::parse()
    {
        detail::BufferManip(Format).Forward();  // Ignore {

        if (detail::BufferTestAccess(Format).IsUpperCase())
        {
            SF_TRY(ParseFormatData());
            return detail::FMTBufferParamsManip(Format).ParamGoToForward(); // Ignore }
        }

        auto formatIdx = GetFormatIndex();
        if (formatIdx.has_value())
        {
            if (formatIdx.value() >= 0 && formatIdx.value() < ArgsInterface.Size())
            {
                SF_TRY(ParseVariable(formatIdx.value()));
                return detail::FMTBufferParamsManip(Format).ParamGoToForward(); // Ignore }
            }
        }

        SF_TRY(Executor.ExecRawString("{"));
        return {};
    }
}
