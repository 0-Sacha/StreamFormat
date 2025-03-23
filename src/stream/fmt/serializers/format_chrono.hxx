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
    [[nodiscard]] std::expected<void, FMTResult> write_sub_time_(const std::chrono::time_point<Clock, Duration>& value, buf::StreamView<TChar>& pattern,
                                                                 buf::FMTStreamIO<TChar>& buffer, TimePrintMode mode) {
        ShiftInfo shift;
        shift.type  = detail::ShiftInfo::ShiftType::Right;
        shift.print = detail::ShiftInfo::ShiftPrint('0', ' ');
        shift.size  = 0;
        (void)buf::ReadManip(pattern).fast_read_integer(shift.size);

        if (mode == TimePrintMode::Mod && shift.size < 0) shift.size = 3;

        if (buf::TestAccess(pattern).is_same("ns", 2)) {
            SF_VERIFY(buf::Manip(pattern).forward(2));
            std::uint32_t ns = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::nanoseconds>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod) ns = ns % 1000;
            SF_VERIFY(buf::FMTWriteManip(buffer).write_integer(static_cast<uint32_t>(ns) % 1000, shift));
        } else if (buf::TestAccess(pattern).is_same("us", 2)) {
            SF_VERIFY(buf::Manip(pattern).forward(2));
            std::uint32_t us = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::microseconds>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                us = us % 1000;
            else if (mode == TimePrintMode::Sub)
                us = us / 1000;
            SF_VERIFY(buf::FMTWriteManip(buffer).write_integer(static_cast<uint32_t>(us) % 1000, shift));
        } else if (buf::TestAccess(pattern).is_same("ms", 2)) {
            SF_VERIFY(buf::Manip(pattern).forward(2));
            std::uint32_t ms = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::milliseconds>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                ms = ms % 1000;
            else if (mode == TimePrintMode::Sub)
                ms = ms / 1000000;
            SF_VERIFY(buf::FMTWriteManip(buffer).write_integer(static_cast<uint32_t>(ms) % 1000, shift));
        } else if (buf::TestAccess(pattern).is_equal_to('s')) {
            SF_VERIFY(buf::Manip(pattern).forward());
            std::uint32_t sec = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::seconds>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod)
                sec = sec % 60;
            else if (mode == TimePrintMode::Sub)
                sec = sec / 1000000000;
            SF_VERIFY(buf::FMTWriteManip(buffer).write_integer(static_cast<uint32_t>(sec) % 1000, shift));
        } else if (buf::TestAccess(pattern).is_equal_to('m')) {
            SF_VERIFY(buf::Manip(pattern).forward());
            std::uint32_t min = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::minutes>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod) min = min % 60;
            SF_VERIFY(buf::FMTWriteManip(buffer).write_integer(static_cast<uint32_t>(min) % 1000, shift));
        } else if (buf::TestAccess(pattern).is_equal_to('h')) {
            SF_VERIFY(buf::Manip(pattern).forward());
            std::uint32_t min = static_cast<std::uint32_t>(std::chrono::time_point_cast<std::chrono::hours>(value).time_since_epoch().count());
            if (mode == TimePrintMode::Mod) min = min % 24;
            SF_VERIFY(buf::FMTWriteManip(buffer).write_integer(static_cast<uint32_t>(min) % 1000, shift));
        }

        return {};
    }

    template <typename Clock, typename Duration, typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> WriteTime(const std::chrono::time_point<Clock, Duration>& value, buf::StreamView<TChar> pattern, buf::FMTStreamIO<TChar>& buffer) {
        auto view = SF_TRY(buf::TestManip(pattern).ViewExec([&] -> std::expected<void, FMTResult> {
            buf::FMTParamsManip(pattern).param_go_to('%', '#', '/');
            return {};
        }));
        SF_VERIFY(buf::WriteManip(buffer).fast_write_string(view));

        while (!buf::Access(pattern).is_end_of_string()) {
            TimePrintMode mode;
            if (buf::TestAccess(pattern).is_equal_to('%'))
                mode = TimePrintMode::Mod;
            else if (buf::TestAccess(pattern).is_equal_to('#'))
                mode = TimePrintMode::FullTime;
            else if (buf::TestAccess(pattern).is_equal_to('/'))
                mode = TimePrintMode::Sub;

            SF_VERIFY(buf::Manip(pattern).forward());
            SF_VERIFY(write_sub_time_(value, pattern, buffer, mode));

            auto view = SF_TRY(buf::TestManip(pattern).ViewExec([&] -> std::expected<void, FMTResult> {
                buf::FMTParamsManip(pattern).param_go_to('%', '#', '/');
                return {};
            }));
            SF_VERIFY(buf::WriteManip(buffer).fast_write_string(view));
        }

        return {};
    }
}  // namespace stream::fmt::detail

namespace stream::fmt {
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::chrono::time_point<T>, FormatterExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::chrono::time_point<T>& t, FormatterExecutor& executor) {
            return detail::WriteTime(t, buf::StreamView(executor.data.specifiers.get_as_text("pattern", "%h:%m:%s.%ms")), executor.ostream);
        }
    };

    template <typename Rep, typename Period, typename FormatterExecutor>
    struct FormatterType<std::chrono::duration<Rep, Period>, FormatterExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::chrono::duration<Rep, Period>& t, FormatterExecutor& executor) {
            if (executor.data.specifiers.has("pattern")) {
                return detail::WriteTime(std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<Rep, Period>>(t),
                                         buf::StreamView(executor.data.specifiers.get_as_text("pattern", "%h:%m:%s.%ms")), executor.ostream);
            }
            SF_VERIFY(buf::WriteManip(executor.ostream).fast_write_integer(t.count()));

            if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::seconds>) {
                SF_VERIFY(buf::ManipIO(executor.ostream).pushback('s'));
            } else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::minutes>) {
                SF_VERIFY(buf::ManipIO(executor.ostream).pushback('m'));
            } else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::hours>) {
                SF_VERIFY(buf::ManipIO(executor.ostream).pushback('h'));
            } else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::milliseconds>) {
                SF_VERIFY(buf::ManipIO(executor.ostream).pushback('m', 's'));
            } else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::microseconds>) {
                SF_VERIFY(buf::ManipIO(executor.ostream).pushback('u', 's'));
            } else if constexpr (std::is_same_v<std::chrono::duration<Rep, Period>, std::chrono::nanoseconds>) {
                SF_VERIFY(buf::ManipIO(executor.ostream).pushback('n', 's'));
            }

            return {};
        }
    };
}  // namespace stream::fmt
