#pragma once

#include "stream/fmt/buf/test_manip.hxx"
#include "stream/fmt/buf/write_manip.hxx"
#include "stream/fmt/buf/read_manip.hxx"
#include "stream/fmt/buf/fmt_write_manip.hxx"

#include "stream/fmt/context/formatter_executor/basic_formatter_executor.hxx"

#include <chrono>

namespace stream::fmt::detail {
    enum class TimePrintMode : std::uint8_t {
        FullTime,
        Mod,
        Sub,
    };

    template <typename Clock, typename Duration, typename TChar>
    void write_sub_time_(const std::chrono::time_point<Clock, Duration>& value, buf::StreamView<TChar>& pattern, buf::FMTStreamIO<TChar>& buffer, TimePrintMode mode) {
        ShiftInfo shift;
        shift.type  = detail::ShiftInfo::ShiftType::Right;
        shift.print = detail::ShiftInfo::ShiftPrint('0', ' ');
        shift.size  = 0;
        if (buf::TestAccess(pattern).is_a_digit()) {
            buf::ReadManip(pattern).fast_read_integer(shift.size);
        }

        if (mode == TimePrintMode::Mod && shift.size < 0) shift.size = 3;

        if (buf::TestAccess(pattern).is_same("ns", 2)) {
            buf::Manip(pattern).forward(2);
            std::uint32_t ns = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::nanoseconds>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod) ns = ns % 1000;
            buf::FMTWriteManip(buffer).write_integer(static_cast<uint32_t>(ns) % 1000, shift);
        } else if (buf::TestAccess(pattern).is_same("us", 2)) {
            buf::Manip(pattern).forward(2);
            std::uint32_t us = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::microseconds>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                us = us % 1000;
            else if (mode == TimePrintMode::Sub)
                us = us / 1000;
            buf::FMTWriteManip(buffer).write_integer(static_cast<uint32_t>(us) % 1000, shift);
        } else if (buf::TestAccess(pattern).is_same("ms", 2)) {
            buf::Manip(pattern).forward(2);
            std::uint32_t ms = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::milliseconds>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                ms = ms % 1000;
            else if (mode == TimePrintMode::Sub)
                ms = ms / 1000000;
            buf::FMTWriteManip(buffer).write_integer(static_cast<uint32_t>(ms) % 1000, shift);
        } else if (buf::TestAccess(pattern).is_equal_to('s')) {
            buf::Manip(pattern).forward();
            std::uint32_t sec = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::seconds>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                sec = sec % 60;
            else if (mode == TimePrintMode::Sub)
                sec = sec / 1000000000;
            buf::FMTWriteManip(buffer).write_integer(static_cast<uint32_t>(sec) % 1000, shift);
        } else if (buf::TestAccess(pattern).is_equal_to('m')) {
            buf::Manip(pattern).forward();
            std::uint32_t min = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::minutes>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod) min = min % 60;
            buf::FMTWriteManip(buffer).write_integer(static_cast<uint32_t>(min) % 1000, shift);
        } else if (buf::TestAccess(pattern).is_equal_to('h')) {
            buf::Manip(pattern).forward();
            std::uint32_t hours = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::hours>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod) hours = hours % 24;
            buf::FMTWriteManip(buffer).write_integer(static_cast<uint32_t>(hours) % 1000, shift);
        }
    }

    template <typename Clock, typename Duration, typename TChar>
    void write_time(const std::chrono::time_point<Clock, Duration>& value, buf::StreamView<TChar> pattern, buf::FMTStreamIO<TChar>& buffer) {
        if (buf::TestAccess(pattern).is_same("default", true) == true) {
            buf::Manip(pattern).reload("%2h:%2m:%2s:%3ms");
        }

        auto view = buf::TestManip(pattern).view_exec([&] { buf::FMTParamsManip(pattern).param_go_to('%', '#', '/'); });
        buf::WriteManip(buffer).fast_write_string(view);

        while (!pattern.is_end_of_string()) {
            TimePrintMode mode;
            if (buf::TestAccess(pattern).is_equal_to('%'))
                mode = TimePrintMode::Mod;
            else if (buf::TestAccess(pattern).is_equal_to('#'))
                mode = TimePrintMode::FullTime;
            else if (buf::TestAccess(pattern).is_equal_to('/'))
                mode = TimePrintMode::Sub;

            buf::Manip(pattern).forward();
            write_sub_time_(value, pattern, buffer, mode);

            auto view = buf::TestManip(pattern).view_exec([&] { buf::FMTParamsManip(pattern).param_go_to('%', '#', '/'); });
            buf::WriteManip(buffer).fast_write_string(view);
        }
    }
}  // namespace stream::fmt::detail

namespace stream::fmt {
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::chrono::time_point<T>, FormatterExecutor> {
        static inline void format(const std::chrono::time_point<T>& t, FormatterExecutor& executor) {
            return detail::write_time(t, buf::StreamView(executor.data.specifiers.get_as_text("pattern", "default")), executor.ostream);
        }
    };

    template <typename Rep, typename Period, typename FormatterExecutor>
    struct FormatterType<std::chrono::duration<Rep, Period>, FormatterExecutor> {
        static inline void format(const std::chrono::duration<Rep, Period>& t, FormatterExecutor& executor) {
            if (executor.data.specifiers.has("pattern")) {
                return detail::write_time(std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<Rep, Period>>(t),
                                          buf::StreamView(executor.data.specifiers.get_as_text("pattern", "default")), executor.ostream);
            }
            buf::WriteManip(executor.ostream).fast_write_integer(t.count());

            if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::seconds>) {
                buf::ManipIO(executor.ostream).pushback('s');
            } else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::minutes>) {
                buf::ManipIO(executor.ostream).pushback('m');
            } else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::hours>) {
                buf::ManipIO(executor.ostream).pushback('h');
            } else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::milliseconds>) {
                buf::ManipIO(executor.ostream).pushback('m', 's');
            } else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::microseconds>) {
                buf::ManipIO(executor.ostream).pushback('u', 's');
            } else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::nanoseconds>) {
                buf::ManipIO(executor.ostream).pushback('n', 's');
            }
        }
    };
}  // namespace stream::fmt
