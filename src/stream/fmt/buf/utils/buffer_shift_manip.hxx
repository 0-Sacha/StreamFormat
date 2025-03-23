#pragma once

#include "stream/fmt/buf/stream.hxx"
#include "stream/fmt/buf/manip_io.hxx"

namespace stream::fmt::buf {
    template <typename TChar>
    class ShiftWriteManip {
    public:
        ShiftWriteManip(StreamIO<TChar>& buffer) : buffer(buffer) {}

    public:
        StreamIO<TChar>& buffer;

    public:
        [[nodiscard]] inline std::expected<void, FMTResult> WriteShiftCenterBegin(detail::ShiftInfo& shift) {
            if (shift.type == detail::ShiftInfo::ShiftType::CenterRight || shift.type == detail::ShiftInfo::ShiftType::CenterLeft) {
                std::int32_t shift_ = shift.size / 2;
                if (shift.type == detail::ShiftInfo::ShiftType::CenterLeft) shift_ = (shift.size + 1) / 2;
                SF_TRY(ManipIO(buffer).pushback(shift.print.before, shift.size - shift_));
                shift.size = shift_;
            }

            return {};
        }

        [[nodiscard]] inline std::expected<void, FMTResult> WriteShiftCenterEnd(detail::ShiftInfo& shift) {
            if (shift.type == detail::ShiftInfo::ShiftType::CenterRight || shift.type == detail::ShiftInfo::ShiftType::CenterLeft)
                return ManipIO(buffer).pushback(shift.print.after, shift.size);
            return {};
        }

        [[nodiscard]] inline std::expected<void, FMTResult> write_shift_right_all(detail::ShiftInfo& shift) {
            if (shift.type == detail::ShiftInfo::ShiftType::Right) return ManipIO(buffer).pushback(shift.print.before, shift.size);
            return {};
        }

        [[nodiscard]] inline std::expected<void, FMTResult> WriteShiftLeftAll(detail::ShiftInfo& shift) {
            if (shift.type == detail::ShiftInfo::ShiftType::Left) return ManipIO(buffer).pushback(shift.print.after, shift.size);
            return {};
        }

        [[nodiscard]] inline std::expected<void, FMTResult> write_shift_begin(detail::ShiftInfo& shift) {
            SF_TRY(WriteShiftCenterBegin(shift));
            return write_shift_right_all(shift);
        }

        [[nodiscard]] inline std::expected<void, FMTResult> write_shift_end(detail::ShiftInfo& shift) {
            SF_TRY(WriteShiftLeftAll(shift));
            return WriteShiftCenterEnd(shift);
        }
    };

    template <typename TChar>
    class ShiftReadManip {
    public:
        ShiftReadManip(Stream<TChar>& buffer) : buffer(buffer) {}

    public:
        Stream<TChar>& buffer;

    public:
        [[nodiscard]] std::expected<void, FMTResult> ignore_shift_begin_space(detail::ShiftInfo& shift) {
            if (shift.print.before_is_a_digit() == false) return {};
            if (shift.type == detail::ShiftInfo::ShiftType::Right || shift.type == detail::ShiftInfo::ShiftType::CenterLeft ||
                shift.type == detail::ShiftInfo::ShiftType::CenterRight) {
                while (buffer.get() == ' ') {
                    SF_TRY(Manip(buffer).forward());
                    --shift.size;
                }
            }
            return {};
        }

        [[nodiscard]] std::expected<void, FMTResult> ignore_shift_end(detail::ShiftInfo& shift) {
            if (shift.type == detail::ShiftInfo::ShiftType::Left || shift.type == detail::ShiftInfo::ShiftType::CenterLeft ||
                shift.type == detail::ShiftInfo::ShiftType::CenterRight) {
                while (buffer.get() == ' ' && shift.size > 0) {
                    SF_TRY(Manip(buffer).forward());
                    --shift.size;
                }
            }
            return {};
        }
    };
}  // namespace stream::fmt::buf
