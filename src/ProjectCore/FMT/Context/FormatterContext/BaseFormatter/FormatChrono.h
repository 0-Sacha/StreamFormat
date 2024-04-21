#pragma once

#include "ProjectCore/FMT/Context/FormatterContext/BasicFormatterContext.h"
#include <chrono>

namespace ProjectCore::FMT::ChronoDetail
{
    template<typename Clock, typename Duration, typename PatternFormat, typename FormatterContext>
    void WriteSubTimeFull(const std::chrono::time_point<Clock, Duration>& value, PatternFormat& pattern, FormatterContext& context) {
        Detail::ShiftSize nbDigit{};
        pattern.FastReadUInt(nbDigit.Value);

        if (pattern.IsSameSeqForward('n', 's'))     return context.BufferOut().WriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::nanoseconds>(value).time_since_epoch().count()), Detail::ShiftType::Right, nbDigit, Detail::ShiftPrint_Zeros);
        if (pattern.IsSameSeqForward('u', 's'))     return context.BufferOut().WriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::microseconds>(value).time_since_epoch().count()), Detail::ShiftType::Right, nbDigit, Detail::ShiftPrint_Zeros);
        if (pattern.IsSameSeqForward('m', 's'))     return context.BufferOut().WriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::milliseconds>(value).time_since_epoch().count()), Detail::ShiftType::Right, nbDigit, Detail::ShiftPrint_Zeros);
        if (pattern.IsSameSeqForward('s'))          return context.BufferOut().WriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::seconds>(value).time_since_epoch().count()), Detail::ShiftType::Right, nbDigit, Detail::ShiftPrint_Zeros);
        if (pattern.IsSameSeqForward('m'))          return context.BufferOut().WriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::minutes>(value).time_since_epoch().count()), Detail::ShiftType::Right, nbDigit, Detail::ShiftPrint_Zeros);
        if (pattern.IsSameSeqForward('h'))          return context.BufferOut().WriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::hours>(value).time_since_epoch().count()), Detail::ShiftType::Right, nbDigit, Detail::ShiftPrint_Zeros);
    }

    template<typename Clock, typename Duration, typename PatternFormat, typename FormatterContext>
    void WriteSubTimeMod(const std::chrono::time_point<Clock, Duration>& value, PatternFormat& pattern, FormatterContext& context) {
        Detail::ShiftSize nbDigit;
        pattern.FastReadUInt(nbDigit.Value);
        bool isDefault = nbDigit.IsDefault();

        if (isDefault) nbDigit.Value = 3;
        if (pattern.IsSameSeqForward('n', 's'))     return context.BufferOut().WriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::nanoseconds>(value).time_since_epoch().count()    % 1000),     Detail::ShiftType::Right, nbDigit, Detail::ShiftPrint_Zeros);
        if (pattern.IsSameSeqForward('u', 's'))     return context.BufferOut().WriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::microseconds>(value).time_since_epoch().count()    % 1000), Detail::ShiftType::Right, nbDigit, Detail::ShiftPrint_Zeros);
        if (pattern.IsSameSeqForward('m', 's'))     return context.BufferOut().WriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::milliseconds>(value).time_since_epoch().count()    % 1000),     Detail::ShiftType::Right, nbDigit, Detail::ShiftPrint_Zeros);
        if (isDefault) nbDigit.Value = 2;
        if (pattern.IsSameSeqForward('s'))  return context.BufferOut().WriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::seconds>(value).time_since_epoch().count()        % 60),        Detail::ShiftType::Right, nbDigit, Detail::ShiftPrint_Zeros);
        if (pattern.IsSameSeqForward('m'))  return context.BufferOut().WriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::minutes>(value).time_since_epoch().count()        % 60),        Detail::ShiftType::Right, nbDigit, Detail::ShiftPrint_Zeros);
        if (pattern.IsSameSeqForward('h'))  return context.BufferOut().WriteUInt(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::hours>(value).time_since_epoch().count()            % 24),        Detail::ShiftType::Right, nbDigit, Detail::ShiftPrint_Zeros);
    }

    template<typename Clock, typename Duration, typename PatternFormat, typename FormatterContext>
    void WriteSubTimeSub([[maybe_unused]] const std::chrono::time_point<Clock, Duration>& value, [[maybe_unused]] PatternFormat& pattern, [[maybe_unused]] FormatterContext& context)  {
        Detail::ShiftSize nbDigit{};
        pattern.ReadUInt(nbDigit.Value);
        
        Detail::FloatPrecision nbDecimal{};
        if (pattern.IsEqualToForward('.'))
            pattern.ReadUInt(nbDecimal.Value);

        if (pattern.IsSameSeqForward('u', 's'))     return context.BufferOut().WriteFloat(static_cast<float>(std::chrono::time_point_cast<std::chrono::nanoseconds>(value).time_since_epoch().count())        / 1000,         nbDecimal, Detail::ShiftType::Right, nbDigit.Value + 1 + nbDecimal.Value, Detail::ShiftPrint_Zeros);
        if (pattern.IsSameSeqForward('m', 's'))     return context.BufferOut().WriteFloat(static_cast<float>(std::chrono::time_point_cast<std::chrono::nanoseconds>(value).time_since_epoch().count())        / 1000000,         nbDecimal, Detail::ShiftType::Right, nbDigit.Value + 1 + nbDecimal.Value, Detail::ShiftPrint_Zeros);
        if (pattern.IsSameSeqForward('s'))          return context.BufferOut().WriteFloat(static_cast<float>(std::chrono::time_point_cast<std::chrono::nanoseconds>(value).time_since_epoch().count())        / 1000000000,    nbDecimal, Detail::ShiftType::Right, nbDigit.Value + 1 + nbDecimal.Value, Detail::ShiftPrint_Zeros);
    }

    template<typename Clock, typename Duration, typename FormatterContext>
    bool WriteTime(const std::chrono::time_point<Clock, Duration>& value, FormatterContext& context, bool useDefaultPattern = true) {
        auto patternPtr = context.GetFormatData().GetSpecifierOnlyText("pattern");
        if (patternPtr == nullptr && useDefaultPattern == false)
            return false;

        std::basic_string_view<typename FormatterContext::CharFormatType> patternStr = "%h:%m:%s.%ms";
        
        if (patternPtr != nullptr)
            patternStr = patternPtr->ValueAsText;

        Detail::FMTFormatBuffer pattern(patternStr.data(), patternStr.size());
        context.BufferOut().FastWriteStringView(pattern.ParamGoToAndGetStr('%', '#', '/'));
        while (!pattern.IsEnd()) {

            if (pattern.IsEqualToForward('%'))        WriteSubTimeMod(value, pattern, context);
            else if (pattern.IsEqualToForward('#'))    WriteSubTimeFull(value, pattern, context);
            else if (pattern.IsEqualToForward('/'))    WriteSubTimeSub(value, pattern, context);

            context.BufferOut().FastWriteStringView(pattern.ParamGoToAndGetStr('%', '#', '/'));
        }

        return true;
    }
}


namespace ProjectCore::FMT
{
    template<typename FormatterContext>
    struct FormatterType<std::chrono::time_point<std::chrono::high_resolution_clock>, FormatterContext>
    {
        static void Format(const std::chrono::time_point<std::chrono::high_resolution_clock>& t, FormatterContext& context) {
            ChronoDetail::WriteTime(t, context);
        }
    };

#ifdef UTILITIES_COMPILER_MSVC
    template<typename FormatterContext>
    struct FormatterType<std::chrono::time_point<std::chrono::system_clock>, FormatterContext>
    {
        static void Format(const std::chrono::time_point<std::chrono::system_clock>& t, FormatterContext& context) {
            ChronoDetail::WriteTime(t, context);
        }
    };
#endif

    template<typename FormatterContext>
    struct FormatterType<std::chrono::seconds, FormatterContext>
    {
        static void Format(const std::chrono::seconds& t, FormatterContext& context) {
            std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::seconds> time(t);
            if (!ChronoDetail::WriteTime<std::chrono::high_resolution_clock, std::chrono::seconds>(time, context)) {
                context.BufferOut().BasicWriteType(t.count());
                context.BufferOut().PushBack('s');
            }
        }
    };

    template<typename FormatterContext>
    struct FormatterType<std::chrono::minutes, FormatterContext>
    {
        static void Format(const std::chrono::minutes& t, FormatterContext& context) {
            std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::minutes> time(t);
            if (!ChronoDetail::WriteTime<std::chrono::high_resolution_clock, std::chrono::minutes>(time, context)) {
                context.BufferOut().BasicWriteType(t.count());
                context.BufferOut().PushBack('m');
            }
        }
    };

    template<typename FormatterContext>
    struct FormatterType<std::chrono::hours, FormatterContext>
    {
        static void Format(const std::chrono::hours& t, FormatterContext& context) {
            std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::hours> time(t);
            if (!ChronoDetail::WriteTime<std::chrono::high_resolution_clock, std::chrono::hours>(time, context)) {
                context.BufferOut().BasicWriteType(t.count());
                context.BufferOut().PushBack('h');
            }
        }
    };

    template<typename FormatterContext>
    struct FormatterType<std::chrono::milliseconds, FormatterContext>
    {
        static void Format(const std::chrono::milliseconds& t, FormatterContext& context) {
            std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::milliseconds> time(t);
            if (!ChronoDetail::WriteTime<std::chrono::high_resolution_clock, std::chrono::milliseconds>(time, context)) {
                context.BufferOut().BasicWriteType(t.count());
                context.BufferOut().PushBack('m');
                context.BufferOut().PushBack('s');
            }
        }
    };

    template<typename FormatterContext>
    struct FormatterType<std::chrono::microseconds, FormatterContext>
    {
        static void Format(const std::chrono::microseconds& t, FormatterContext& context) {
            std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::microseconds> time(t);
            if (!ChronoDetail::WriteTime<std::chrono::high_resolution_clock, std::chrono::microseconds>(time, context)) {
                context.BufferOut().BasicWriteType(t.count());
                context.BufferOut().PushBack('u');
                context.BufferOut().PushBack('s');
            }
        }
    };

    template<typename FormatterContext>
    struct FormatterType<std::chrono::nanoseconds, FormatterContext>
    {
        static void Format(const std::chrono::nanoseconds& t, FormatterContext& context) {
            std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> time(t);
            if (!ChronoDetail::WriteTime<std::chrono::high_resolution_clock, std::chrono::nanoseconds>(time, context)) {
                context.BufferOut().BasicWriteType(t.count());
                context.BufferOut().PushBack('n');
                context.BufferOut().PushBack('s');
            }
        }
    };
}
