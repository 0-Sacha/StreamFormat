#pragma once

#include "BasicContext.h"

#include "StreamFormat/FMT/Buffer/BufferManip.h"
#include "StreamFormat/FMT/Buffer/BufferTestManip.h"
#include "StreamFormat/FMT/Buffer/BufferWriteManip.h"
#include "StreamFormat/FMT/Buffer/BufferReadManip.h"
#include "StreamFormat/FMT/Buffer/FMTBufferOutManip.h"
#include "StreamFormat/FMT/Buffer/FMTBufferReadManip.h"

namespace StreamFormat::FMT::Context
{
    template <typename TChar>
    std::basic_string_view<TChar> BasicContext<TChar>::ParseNextOverrideFormatData()
    {
        Detail::BufferTestAccess access(Format);
        Detail::BufferTestManip manip(Format);

        manip.SkipAllSpaces();
        Detail::FMTBufferParamsManip(Format).ParamGoTo('{', '=', ':');
        manip.SkipAllSpaces();
        manip.IsEqualToForward('=', ':');
        manip.SkipAllSpaces();
        Detail::FMTBufferParamsManip(Format).ParamGoTo('{');

        const TChar* begin = Format.CurrentPos;
        manip.IsEqualToForward('{').ThrowIfFailed();
        int scopes = 0;
        while (Detail::FMTBufferParamsManip(Format).IsEndOfParameter() == false || scopes > 0)
        {
            manip.GoTo('\'', '}', '{');
            if (manip.IsEqualToForward('\''))
                manip.GoToForward('\'');
            else if (manip.IsEqualToForward('{'))
                scopes++;
            else if (scopes > 0 && manip.IsEqualToForward('}'))
                scopes--;
        }
        manip.IsEqualToForward('}').ThrowIfFailed();
        const TChar* end = Format.CurrentPos;
        return std::basic_string_view<TChar>(begin, end - begin);
    }

    template <typename TChar>
    void BasicContext<TChar>::ParseFormatDataBase()
    {
        Detail::BufferTestManip manip(Format);

        if (manip.IsEqualToForward('C'))
            Executor.TextManager.ParseColor(*this);
        else if (manip.IsEqualToForward('S'))
            Executor.TextManager.ParseStyle(*this);
        else if (manip.IsEqualToForward('F'))
            Executor.TextManager.ParseFront(*this);

        else if (manip.IsEqualToForward('K'))
            Executor.Data.KeepNewStyle = true;

        else if (manip.IsEqualToForward('N'))
            Executor.Data.NextOverride = ParseNextOverrideFormatData();
    }

    template <typename TChar>
    void BasicContext<TChar>::ParseFormatDataSpecial_ShiftType(const Detail::ShiftInfo::ShiftType type)
    {
        Executor.Data.Shift.Type = type;
        FormatReadParameter(Executor.Data.Shift.Size, -1);
        if (Detail::BufferTestManip(Format).IsEqualToForward(':'))
        {
            Executor.Data.Shift.Print.Before = Detail::BufferManip(Format).ThrowIfFailed().GetAndForward();
            Executor.Data.Shift.Print.After  = Executor.Data.Shift.Print.Before;
            if (Detail::BufferTestManip(Format).IsEqualToForward('|'))
                Executor.Data.Shift.Print.After = Detail::BufferManip(Format).ThrowIfFailed().GetAndForward();
        }
    }

    template <typename TChar>
    void BasicContext<TChar>::ParseFormatDataSpecial()
    {
        Detail::BufferTestAccess access(Format);
        Detail::BufferTestManip manip(Format);

        if (manip.IsEqualToForward('{'))
        {
            std::int32_t formatIndex = 0;
            if (GetFormatIndex(formatIndex) == false) return;

            if ((Executor.Data.TestApply(ArgsInterface.template GetTypeAtIndex<Detail::FormatData<TChar>>(formatIndex)) ||
                 Executor.Data.TestApply(ArgsInterface.template GetTypeAtIndex<Detail::FormatSpecifier<TChar>>(formatIndex)) ||
                 Executor.Data.TestApply(ArgsInterface.template GetTypeAtIndex<Detail::IntegerPrintBase>(formatIndex)) ||
                 Executor.Data.TestApply(ArgsInterface.template GetTypeAtIndex<Detail::ShiftInfo>(formatIndex))) == false)
                throw Detail::FMTGivenTypeError{};
            manip.IsEqualToForward('}');
        }

        else if (manip.IsEqualToForward('.'))
            FormatReadParameter(Executor.Data.FloatPrecision, -1);

        else if (access.IsEqualTo('d', 'b', 'B', 'o', 'O', 'x', 'X'))
            Executor.Data.IntegerPrint = static_cast<Detail::IntegerPrintBase>(Detail::BufferManip(Format).ThrowIfFailed().GetAndForward());

        else if (manip.IsEqualToForward('#'))
            Executor.Data.PrefixSuffix = true;


        else if (manip.IsEqualToForward('>'))
            ParseFormatDataSpecial_ShiftType(Detail::ShiftInfo::ShiftType::Right);

        else if (manip.IsEqualToForward('<'))
            ParseFormatDataSpecial_ShiftType(Detail::ShiftInfo::ShiftType::Left);
            
        else if (manip.IsEqualToForward('^'))
        {
            if (manip.IsEqualToForward('<'))
                ParseFormatDataSpecial_ShiftType(Detail::ShiftInfo::ShiftType::CenterLeft);
            else
            {
                manip.IsEqualToForward('>');
                ParseFormatDataSpecial_ShiftType(Detail::ShiftInfo::ShiftType::CenterRight);
            }
        }
    }

    template <typename TChar>
    void BasicContext<TChar>::ParseFormatDataCustom()
    {
        Detail::BufferTestAccess access(Format);
        Detail::BufferTestManip manip(Format);

        std::basic_string_view<TChar> name = manip.ViewExec(
            [&]{Detail::FMTBufferParamsManip(Format).ParamGoTo(' ', '=', '\'', '{', ',');}
        );
        Detail::FMTBufferParamsManip(Format).ParamGoTo('=', '\'', '{', ',');
        manip.IsEqualToForward('=');
        manip.SkipAllSpaces();

        if (manip.IsEqualToForward('\''))
        {
            std::basic_string_view<TChar> value = Detail::BufferTestManip(Format).ViewUntil('\'');
            Executor.Data.Specifiers.Concat(Detail::FormatSpecifier{name, value});
        }
        else if (access.IsADigit())
        {
            std::int32_t value = 0;
            Detail::BufferReadManip(Format).FastReadInteger(value);
            Executor.Data.Specifiers.Concat(Detail::FormatSpecifier{name, value});
        }
        else if (manip.IsEqualToForward('{'))
        {
            std::int32_t idx = 0;
            GetFormatIndex(idx);
            // TODO / FIXME
            // Executor.Data.Specifiers.Concat(Detail::FormatSpecifier{name, GetTypeAtIndexAuto(idx)});
            manip.IsEqualToForward('}');
        }
        else if (access.IsEqualTo(',', '}'))
        {
            Executor.Data.Specifiers.Concat(Detail::FormatSpecifier{name});
        }
    }

    /////---------- Impl ----------/////
    template <typename TChar>
    void BasicContext<TChar>::ParseFormatData()
    {
        Detail::BufferTestAccess access(Format);
        Detail::BufferTestManip manip(Format);

        Executor.Data.HasSpec = true;
        while (Detail::BufferAccess(Format).IsEndOfString() == false && Detail::FMTBufferParamsManip(Format).IsEndOfParameter() == false)
        {
            manip.SkipAllSpaces();

            if (access.IsUpperCase())
                ParseFormatDataBase();
            else if (!access.IsLowerCase())
                ParseFormatDataSpecial();
            else
                ParseFormatDataCustom();

            Detail::FMTBufferParamsManip(Format).ParamGoTo(',');
            Detail::BufferTestManip(Format).IsEqualToForward(',');
        }
    }

    template <typename TChar>
    Detail::BufferManipResult BasicContext<TChar>::GetFormatIndex(std::int32_t& idx)
    {
        const TChar* mainSubFormat = Format.CurrentPos;

        Detail::BufferTestAccess access(Format);
        Detail::BufferTestManip manip(Format);

        // I : if there is no number specified : ':' or '}'
        if (access.IsEqualTo(':') || access.IsEqualTo('}'))
            if (ValuesIndex < ArgsInterface.Size())
            {
                idx = ValuesIndex++;
                return true;
            }

        // II: A number(idx)
        std::int32_t subIndex = -1;
        if (Detail::BufferReadManip(Format).FastReadInteger(subIndex))
            if (access.IsEqualTo(':') || access.IsEqualTo('}'))
                if (subIndex >= 0 && subIndex < ArgsInterface.Size())
                {
                    idx = subIndex;
                    return true;
                }
        Format.CurrentPos = mainSubFormat;

        // III : A name
        std::int32_t indexOfNamedArg = ArgsInterface.GetIndexOfCurrentNamedArg(Format);
        if (indexOfNamedArg >= 0 && indexOfNamedArg < ArgsInterface.Size())
        {
            idx = indexOfNamedArg;
            return true;
        }
        Format.CurrentPos = mainSubFormat;

        // VI : { which is a idx to an argument
        if (manip.IsEqualToForward('{'))
        {
            std::int32_t recIndex = -1;
            if (GetFormatIndex(recIndex) == false)
                return false;

            if (manip.IsEqualToForward('}') && recIndex >= 0 && recIndex < ArgsInterface.Size())
            {
                manip.SkipAllSpaces();
                if (access.IsEqualTo(':', '}'))
                {
                    std::int32_t finalRecIndex = ArgsInterface.GetFormatIndexAt(recIndex);
                    if (finalRecIndex >= 0 && finalRecIndex < ArgsInterface.Size())
                        return finalRecIndex;
                    return false;
                }
            }
        }
        Format.CurrentPos = mainSubFormat;
        return false;
    }

    template <typename TChar>
    void BasicContext<TChar>::ParseVariable(std::int32_t formatIdx)
    {
        Detail::FormatData<TChar> saveFormatData = Executor.Data;
        Executor.Data = Detail::FormatData<TChar>{};
        Detail::TextProperties::Properties saveTextProperties = Executor.TextManager.Save();

        if (Detail::BufferTestAccess(Format).IsEqualTo(':', '{'))
        {
            Detail::BufferManip(Format).Forward();
            ParseFormatData();
        }

        ArgsInterface.RunTypeAtIndex(formatIdx);

        if (Executor.Data.KeepNewStyle == false)
            Executor.TextManager.Reload(saveTextProperties);

        Executor.Data = saveFormatData;
    }

    template <typename TChar>
    bool BasicContext<TChar>::Parse()
    {
        Detail::BufferManip(Format).Forward();  // Skip {

        if (Detail::BufferTestAccess(Format).IsUpperCase())
        {
            ParseFormatData();
            Detail::FMTBufferParamsManip(Format).ParamGoToForward(); // Skip }
            return true;
        }

        std::int32_t formatIdx = -1;
        if (GetFormatIndex(formatIdx) && formatIdx >= 0 && formatIdx < ArgsInterface.Size())
        {
            ParseVariable(formatIdx);
            Detail::FMTBufferParamsManip(Format).ParamGoToForward(); // Skip }
            return true;
        }

        return false;
    }
}
