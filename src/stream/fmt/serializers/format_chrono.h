#pragma once

#include "stream/fmt/buffer/buffer_test_manip.h"
#include "stream/fmt/buffer/buffer_write_manip.h"
#include "stream/fmt/buffer/buffer_read_manip.h"
#include "stream/fmt/buffer/FMTBufferWriteManip.h"

#include "stream/fmt/context/formatter_executor/basic_formatter_executor.h"

#include <chrono>

namespace stream::fmt::detail
{
    enum class TimePrintMode : std::uint8_t
    {
        FullTime,
        Mod,
        Sub,
    };

    template <typename Clock, typename Duration, typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> WriteSubTime_(const std::chrono::time_point<Clock, Duration>& value, BufferInfoView<TChar>& pattern, FMTBufferOutInfo<TChar>& buffer, TimePrintMode mode)
    {
        ShiftInfo shift;
        shift.Type = detail::ShiftInfo::ShiftType::Right;
        shift.Print = detail::ShiftInfo::ShiftPrint('0', ' ');
        shift.Size = 0;
        (void)BufferReadManip(pattern).FastReadInteger(shift.Size);

        if (mode == TimePrintMode::Mod && shift.Size < 0)
            shift.Size = 3;

        if (BufferTestAccess(pattern).IsSame("ns", 2))
        {
            SF_TRY(BufferManip(pattern).Forward());
            std::uint32_t ns = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::nanoseconds>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                ns = ns % 1000;
            SF_TRY(FMTBufferWriteManip(buffer).WriteInteger(static_cast<uint32_t>(ns) % 1000, shift));
        }
        else if (BufferTestAccess(pattern).IsSame("us", 2))
        {
            SF_TRY(BufferManip(pattern).Forward());
            std::uint32_t us = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::microseconds>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                us = us % 1000;
            else if (mode == TimePrintMode::Sub)
                us = us / 1000;
            SF_TRY(FMTBufferWriteManip(buffer).WriteInteger(static_cast<uint32_t>(us) % 1000, shift));
        }
        else if (BufferTestAccess(pattern).IsSame("ms", 2))
        {
            SF_TRY(BufferManip(pattern).Forward());
            std::uint32_t ms = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::milliseconds>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                ms = ms % 1000;
            else if (mode == TimePrintMode::Sub)
                ms = ms / 1000000;
            SF_TRY(FMTBufferWriteManip(buffer).WriteInteger(static_cast<uint32_t>(ms) % 1000, shift));
        }
        else if (BufferTestAccess(pattern).IsEqualTo('s'))
        {
            SF_TRY(BufferManip(pattern).Forward());
            std::uint32_t sec = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::seconds>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                sec = sec % 60;
            else if (mode == TimePrintMode::Sub)
                sec = sec / 1000000000;
            SF_TRY(FMTBufferWriteManip(buffer).WriteInteger(static_cast<uint32_t>(sec) % 1000, shift));
        }
        else if (BufferTestAccess(pattern).IsEqualTo('m'))
        {
            SF_TRY(BufferManip(pattern).Forward());
            std::uint32_t min = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::minutes>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                min = min % 60;
            SF_TRY(FMTBufferWriteManip(buffer).WriteInteger(static_cast<uint32_t>(min) % 1000, shift));
        }
        else if (BufferTestAccess(pattern).IsEqualTo('h'))
        {
            SF_TRY(BufferManip(pattern).Forward());
            std::uint32_t min = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::hours>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                min = min % 24;
            SF_TRY(FMTBufferWriteManip(buffer).WriteInteger(static_cast<uint32_t>(min) % 1000, shift));
        }

        return {};
    }

    template <typename Clock, typename Duration, typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> WriteTime(const std::chrono::time_point<Clock, Duration>& value, BufferInfoView<TChar> pattern, FMTBufferOutInfo<TChar>& buffer)
    {
        auto view = SF_TRY(BufferTestManip(pattern).ViewExec(
            [&] -> std::expected<void, FMTResult> { FMTBufferParamsManip(pattern).ParamGoTo('%', '#', '/'); return {}; }
        ));
        SF_TRY(BufferWriteManip(buffer).FastWriteString(view));

        while (!BufferAccess(pattern).IsEndOfString())
        {
            TimePrintMode mode;
            if (BufferTestAccess(pattern).IsEqualTo('%'))
                mode = TimePrintMode::Mod;
            else if (BufferTestAccess(pattern).IsEqualTo('#'))
                mode = TimePrintMode::FullTime;
            else if (BufferTestAccess(pattern).IsEqualTo('/'))
                mode = TimePrintMode::Sub;
            
            SF_TRY(BufferManip(pattern).Forward());
            SF_TRY(WriteSubTime_(value, pattern, buffer, mode));

            auto view = SF_TRY(BufferTestManip(pattern).ViewExec(
                [&] -> std::expected<void, FMTResult> { FMTBufferParamsManip(pattern).ParamGoTo('%', '#', '/'); return {}; }
            ));
            SF_TRY(BufferWriteManip(buffer).FastWriteString(view));
        }

        return {};
    }
}

namespace stream::fmt
{
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::chrono::time_point<T>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::chrono::time_point<T>& t, FormatterExecutor& executor)
        {
            return detail::WriteTime(t, detail::BufferInfoView(executor.Data.Specifiers.GetAsText("pattern", "%h:%m:%s.%ms")), executor.buffer_out);
        }
    };

    template <typename Rep, typename Period, typename FormatterExecutor>
    struct FormatterType<std::chrono::duration<Rep, Period>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::chrono::duration<Rep, Period>& t, FormatterExecutor& executor)
        {
            if (executor.Data.Specifiers.Has("pattern"))
            {
                return detail::WriteTime(
                    std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<Rep, Period>>(t),
                    detail::BufferInfoView(executor.Data.Specifiers.GetAsText("pattern", "%h:%m:%s.%ms")),
                    executor.buffer_out
                );
            }
            SF_TRY(detail::BufferWriteManip(executor.buffer_out).FastWriteInteger(t.count()));

            if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::seconds>)
                { SF_TRY(detail::BufferOutManip(executor.buffer_out).Pushback('s')); }
            else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::minutes>)
                { SF_TRY(detail::BufferOutManip(executor.buffer_out).Pushback('m')); }
            else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::hours>)
                { SF_TRY(detail::BufferOutManip(executor.buffer_out).Pushback('h')); }
            else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::milliseconds>)
                { SF_TRY(detail::BufferOutManip(executor.buffer_out).Pushback('m', 's')); }
            else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::microseconds>)
                { SF_TRY(detail::BufferOutManip(executor.buffer_out).Pushback('u', 's')); }
            else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::nanoseconds>)
                { SF_TRY(detail::BufferOutManip(executor.buffer_out).Pushback('n', 's')); }
                
            return {};
        }
    };
}
