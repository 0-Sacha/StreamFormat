#pragma once

#include "stream/fmt/buffer/buffer_info.h"
#include "stream/fmt/buffer/buffer_out_manip.h"

namespace stream::fmt::detail
{
    template <typename TChar>
    class BufferShiftWriteManip
    {
    public:
        BufferShiftWriteManip(BufferOutInfo<TChar>& buffer) : Buffer(buffer) {}
    public:
        BufferOutInfo<TChar>& Buffer;

    public:
        [[nodiscard]] inline std::expected<void, FMTResult> WriteShiftCenterBegin(detail::ShiftInfo& shift)
        {
            if (shift.Type == detail::ShiftInfo::ShiftType::CenterRight || shift.Type == detail::ShiftInfo::ShiftType::CenterLeft)
            {
                std::int32_t shift_ = shift.Size / 2;
                if (shift.Type == detail::ShiftInfo::ShiftType::CenterLeft) shift_ = (shift.Size + 1) / 2;
                SF_TRY(BufferOutManip(buffer).Pushback(shift.Print.Before, shift.Size - shift_));
                shift.Size = shift_;
            }

            return {};
        }

        [[nodiscard]] inline std::expected<void, FMTResult> WriteShiftCenterEnd(detail::ShiftInfo& shift)
        {
            if (shift.Type == detail::ShiftInfo::ShiftType::CenterRight || shift.Type == detail::ShiftInfo::ShiftType::CenterLeft)
                return BufferOutManip(buffer).Pushback(shift.Print.After, shift.Size);
            return {};
        }

        [[nodiscard]] inline std::expected<void, FMTResult> WriteShiftRightAll(detail::ShiftInfo& shift)
        {
            if (shift.Type == detail::ShiftInfo::ShiftType::Right)
                return BufferOutManip(buffer).Pushback(shift.Print.Before, shift.Size);
            return {};
        }

        [[nodiscard]] inline std::expected<void, FMTResult> WriteShiftLeftAll(detail::ShiftInfo& shift)
        {
            if (shift.Type == detail::ShiftInfo::ShiftType::Left)
                return BufferOutManip(buffer).Pushback(shift.Print.After, shift.Size);
            return {};
        }

        [[nodiscard]] inline std::expected<void, FMTResult> WriteShiftBegin(detail::ShiftInfo& shift)
        {
            SF_TRY(WriteShiftCenterBegin(shift));
            return WriteShiftRightAll(shift);
        }

        [[nodiscard]] inline std::expected<void, FMTResult> WriteShiftEnd(detail::ShiftInfo& shift)
        {
            SF_TRY(WriteShiftLeftAll(shift));
            return WriteShiftCenterEnd(shift);
        }
    };

    template <typename TChar>
    class BufferShiftReadManip
    {
    public:
        BufferShiftReadManip(BufferInfo<TChar>& buffer) : Buffer(buffer) {}
    public:
        BufferInfo<TChar>& Buffer;

    public:
        [[nodiscard]] std::expected<void, FMTResult> IgnoreShiftBeginSpace(detail::ShiftInfo& shift)
        {
            if (shift.Print.BeforeIsADigit() == false)
                return {};
            if (shift.Type == detail::ShiftInfo::ShiftType::Right || shift.Type == detail::ShiftInfo::ShiftType::CenterLeft || shift.Type == detail::ShiftInfo::ShiftType::CenterRight)
            {

                while (Buffer.Get() == ' ')
                {
                    SF_TRY(BufferManip(buffer).Forward());
                    --shift.Size;
                }
            }
            return {};
        }

        [[nodiscard]] std::expected<void, FMTResult> IgnoreShiftEnd(detail::ShiftInfo& shift)
        {
            if (shift.Type == detail::ShiftInfo::ShiftType::Left || shift.Type == detail::ShiftInfo::ShiftType::CenterLeft || shift.Type == detail::ShiftInfo::ShiftType::CenterRight)
            {
                while (Buffer.Get() == ' ' && shift.Size > 0)
                {
                    SF_TRY(BufferManip(buffer).Forward());
                    --shift.Size;
                }
            }
            return {};
        }
    };
}
