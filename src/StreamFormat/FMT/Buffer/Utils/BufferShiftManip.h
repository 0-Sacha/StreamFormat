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
        inline void WriteShiftCenterBegin(Detail::ShiftInfo& shift)
        {
            if (shift.Type == Detail::ShiftInfo::ShiftType::CenterRight || shift.Type == Detail::ShiftInfo::ShiftType::CenterLeft)
            {
                std::int32_t shift_ = shift.Size / 2;
                if (shift.Type == Detail::ShiftInfo::ShiftType::CenterLeft) shift_ = (shift.Size + 1) / 2;
                BufferOutManip(Buffer).Pushback(shift.Print.Before, shift.Size - shift_);
                shift.Size = shift_;
            }
        }

        inline void WriteShiftCenterEnd(Detail::ShiftInfo& shift)
        {
            if (shift.Type == Detail::ShiftInfo::ShiftType::CenterRight || shift.Type == Detail::ShiftInfo::ShiftType::CenterLeft)
                BufferOutManip(Buffer).Pushback(shift.Print.After, shift.Size);
        }

        inline void WriteShiftRightAll(Detail::ShiftInfo& shift)
        {
            if (shift.Type == Detail::ShiftInfo::ShiftType::Right)
                BufferOutManip(Buffer).Pushback(shift.Print.Before, shift.Size);
        }

        inline void WriteShiftLeftAll(Detail::ShiftInfo& shift)
        {
            if (shift.Type == Detail::ShiftInfo::ShiftType::Left)
                BufferOutManip(Buffer).Pushback(shift.Print.After, shift.Size);
        }

        inline void WriteShiftBegin(Detail::ShiftInfo& shift)
        {
            WriteShiftCenterBegin(shift);
            WriteShiftRightAll(shift);
        }

        inline void WriteShiftEnd(Detail::ShiftInfo& shift)
        {
            WriteShiftLeftAll(shift);
            WriteShiftCenterEnd(shift);
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
        void SkipShiftBeginSpace(Detail::ShiftInfo& shift)
        {
            if (shift.Print.BeforeIsADigit() == false) return;
            if (shift.Type == Detail::ShiftInfo::ShiftType::Right || shift.Type == Detail::ShiftInfo::ShiftType::CenterLeft || shift.Type == Detail::ShiftInfo::ShiftType::CenterRight)
                while (Buffer.Get() == ' ')
                {
                    BufferManip(Buffer).Forward();
                    --shift.Size;
                }
        }

        void SkipShiftEnd(Detail::ShiftInfo& shift)
        {
            if (shift.Type == Detail::ShiftInfo::ShiftType::Left || shift.Type == Detail::ShiftInfo::ShiftType::CenterLeft || shift.Type == Detail::ShiftInfo::ShiftType::CenterRight)
                while (Buffer.Get() == ' ' && shift.Size > 0)
                {
                    BufferManip(Buffer).Forward();
                    --shift.Size;
                }
        }
    };
}
