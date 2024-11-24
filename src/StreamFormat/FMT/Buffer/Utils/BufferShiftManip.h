#pragma once

#include "StreamFormat/FMT/Buffer/BufferInfo.h"
#include "StreamFormat/FMT/Buffer/BufferOutManip.h"

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    class BufferShiftWriteManip
    {
    public:
        BufferShiftWriteManip(BufferOutInfo<TChar>& buffer) : Buffer(buffer) {}
    public:
        BufferOutInfo<TChar>& Buffer;

    public:
        [[nodiscard]] inline std::expected<void, FMTResult> WriteShiftCenterBegin(Detail::ShiftInfo& shift)
        {
            if (shift.Type == Detail::ShiftInfo::ShiftType::CenterRight || shift.Type == Detail::ShiftInfo::ShiftType::CenterLeft)
            {
                std::int32_t shift_ = shift.Size / 2;
                if (shift.Type == Detail::ShiftInfo::ShiftType::CenterLeft) shift_ = (shift.Size + 1) / 2;
                SF_TRY(BufferOutManip(Buffer).Pushback(shift.Print.Before, shift.Size - shift_));
                shift.Size = shift_;
            }
        }

        [[nodiscard]] inline std::expected<void, FMTResult> WriteShiftCenterEnd(Detail::ShiftInfo& shift)
        {
            if (shift.Type == Detail::ShiftInfo::ShiftType::CenterRight || shift.Type == Detail::ShiftInfo::ShiftType::CenterLeft)
                return BufferOutManip(Buffer).Pushback(shift.Print.After, shift.Size);
        }

        [[nodiscard]] inline std::expected<void, FMTResult> WriteShiftRightAll(Detail::ShiftInfo& shift)
        {
            if (shift.Type == Detail::ShiftInfo::ShiftType::Right)
                return BufferOutManip(Buffer).Pushback(shift.Print.Before, shift.Size);
        }

        [[nodiscard]] inline std::expected<void, FMTResult> WriteShiftLeftAll(Detail::ShiftInfo& shift)
        {
            if (shift.Type == Detail::ShiftInfo::ShiftType::Left)
                return BufferOutManip(Buffer).Pushback(shift.Print.After, shift.Size);
        }

        [[nodiscard]] inline std::expected<void, FMTResult> WriteShiftBegin(Detail::ShiftInfo& shift)
        {
            SF_TRY(WriteShiftCenterBegin(shift));
            return WriteShiftRightAll(shift);
        }

        [[nodiscard]] inline std::expected<void, FMTResult> WriteShiftEnd(Detail::ShiftInfo& shift)
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
        [[nodiscard]] std::expected<void, FMTResult> SkipShiftBeginSpace(Detail::ShiftInfo& shift)
        {
            if (shift.Print.BeforeIsADigit() == false)
                return {};
            if (shift.Type == Detail::ShiftInfo::ShiftType::Right || shift.Type == Detail::ShiftInfo::ShiftType::CenterLeft || shift.Type == Detail::ShiftInfo::ShiftType::CenterRight)
                while (Buffer.Get() == ' ')
                {
                    SF_TRY(BufferManip(Buffer).Forward());
                    --shift.Size;
                }
        }

        [[nodiscard]] std::expected<void, FMTResult> SkipShiftEnd(Detail::ShiftInfo& shift)
        {
            if (shift.Type == Detail::ShiftInfo::ShiftType::Left || shift.Type == Detail::ShiftInfo::ShiftType::CenterLeft || shift.Type == Detail::ShiftInfo::ShiftType::CenterRight)
                while (Buffer.Get() == ' ' && shift.Size > 0)
                {
                    SF_TRY(BufferManip(Buffer).Forward());
                    --shift.Size;
                }
        }
    };
}
