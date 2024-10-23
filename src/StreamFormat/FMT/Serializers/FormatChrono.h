#pragma once

#include "StreamFormat/FMT/Buffer/BufferTestManip.h"
#include "StreamFormat/FMT/Buffer/BufferWriteManip.h"
#include "StreamFormat/FMT/Buffer/BufferReadManip.h"
#include "StreamFormat/FMT/Buffer/FMTBufferWriteManip.h"

#include "StreamFormat/FMT/Context/FormatterExecutor/BasicFormatterExecutor.h"

#include <chrono>

namespace StreamFormat::FMT::Detail
{
    enum class TimePrintMode : std::uint8_t
    {
        FullTime,
        Mod,
        Sub,
    };

    template <typename Clock, typename Duration, typename TChar>
    BufferManipResult WriteSubTime_(const std::chrono::time_point<Clock, Duration>& value, BufferInfoView<TChar>& pattern, FMTBufferOutInfo<TChar>& buffer, TimePrintMode mode)
    {
        ShiftInfo shift;
        shift.Type = Detail::ShiftInfo::ShiftType::Right;
        shift.Print = Detail::ShiftInfo::ShiftPrint('0', ' ');
        BufferReadManip(pattern).FastReadInteger(shift.Size);

        if (mode == TimePrintMode::Mod && shift.Size < 0)
            shift.Size = 3;

        if (BufferTestManip(pattern).IsSameForward("ns", 2))
        {
            std::uint32_t ns = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::nanoseconds>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                ns = ns % 1000;
            FMTBufferWriteManip(buffer).WriteInteger(static_cast<uint32_t>(ns) % 1000, shift);
        }
        else if (BufferTestManip(pattern).IsSameForward("us", 2))
        {
            std::uint32_t us = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::microseconds>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                us = us % 1000;
            else if (mode == TimePrintMode::Sub)
                us = us / 1000;
            FMTBufferWriteManip(buffer).WriteInteger(static_cast<uint32_t>(us) % 1000, shift);
        }
        else if (BufferTestManip(pattern).IsSameForward("ms", 2))
        {
            std::uint32_t ms = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::milliseconds>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                ms = ms % 1000;
            else if (mode == TimePrintMode::Sub)
                ms = ms / 1000000;
            FMTBufferWriteManip(buffer).WriteInteger(static_cast<uint32_t>(ms) % 1000, shift);
        }
        else if (BufferTestManip(pattern).IsEqualToForward('s'))
        {
            std::uint32_t sec = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::seconds>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                sec = sec % 60;
            else if (mode == TimePrintMode::Sub)
                sec = sec / 1000000000;
            FMTBufferWriteManip(buffer).WriteInteger(static_cast<uint32_t>(sec) % 1000, shift);
        }
        else if (BufferTestManip(pattern).IsEqualToForward('m'))
        {
            std::uint32_t min = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::minutes>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                min = min % 60;
            FMTBufferWriteManip(buffer).WriteInteger(static_cast<uint32_t>(min) % 1000, shift);
        }
        else if (BufferTestManip(pattern).IsEqualToForward('h'))
        {
            std::uint32_t min = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::hours>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                min = min % 24;
            FMTBufferWriteManip(buffer).WriteInteger(static_cast<uint32_t>(min) % 1000, shift);
        }

        return true;
    }

    template <typename Clock, typename Duration, typename TChar>
    BufferManipResult WriteTime(const std::chrono::time_point<Clock, Duration>& value, BufferInfoView<TChar> pattern, FMTBufferOutInfo<TChar>& buffer)
    {
        BufferWriteManip(buffer).FastWriteString(
            BufferTestManip(pattern).ViewExec(
                [&]{FMTBufferParamsManip(pattern).ParamGoTo('%', '#', '/'); }
            )
        );

        while (!BufferAccess(pattern).IsEndOfString())
        {
            TimePrintMode mode;
            if (BufferTestManip(pattern).IsEqualToForward('%'))
                mode = TimePrintMode::Mod;
            else if (BufferTestManip(pattern).IsEqualToForward('#'))
                mode = TimePrintMode::FullTime;
            else if (BufferTestManip(pattern).IsEqualToForward('/'))
                mode = TimePrintMode::Sub;
            
            WriteSubTime_(value, pattern, buffer, mode);

            BufferWriteManip(buffer).FastWriteString(
                BufferTestManip(pattern).ViewExec(
                    [&]{FMTBufferParamsManip(pattern).ParamGoTo('%', '#', '/'); }
                )
            );
        }

        return true;
    }
}

namespace StreamFormat::FMT
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::chrono::time_point<T>, FormatterExecutor>
    {
        static void Format(const std::chrono::time_point<T>& t, FormatterExecutor& executor)
        {
            Detail::WriteTime(t, Detail::BufferInfoView(executor.Data.Specifiers.GetAsText("pattern", "%h:%m:%s.%ms")), executor.BufferOut);
        }
    };

    template <typename Rep, typename Period, typename FormatterExecutor>
    struct FormatterType<std::chrono::duration<Rep, Period>, FormatterExecutor>
    {
        static void Format(const std::chrono::duration<Rep, Period>& t, FormatterExecutor& executor)
        {
            if (executor.Data.Specifiers.Has("pattern"))
            {
                Detail::WriteTime(
                    std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<Rep, Period>>(t),
                    Detail::BufferInfoView(executor.Data.Specifiers.GetAsText("pattern", "%h:%m:%s.%ms")),
                    executor.BufferOut
                );
                return;
            }
            Detail::BufferWriteManip(executor.BufferOut).FastWriteInteger(t.count());

            if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::seconds>)
                Detail::BufferOutManip(executor.BufferOut).Pushback('s');
            else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::minutes>)
                Detail::BufferOutManip(executor.BufferOut).Pushback('m');
            else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::hours>)
                Detail::BufferOutManip(executor.BufferOut).Pushback('h');
            else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::milliseconds>)
                Detail::BufferOutManip(executor.BufferOut).Pushback('m', 's');
            else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::microseconds>)
                Detail::BufferOutManip(executor.BufferOut).Pushback('u', 's');
            else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::nanoseconds>)
                Detail::BufferOutManip(executor.BufferOut).Pushback('n', 's');
        }
    };
}
