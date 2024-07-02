#pragma once

#include "FMTBufferOut.h"

namespace ProjectCore::FMT::Detail
{
    template <typename CharBuffer>
    template <typename CharStr>
    inline void FMTBufferOut<CharBuffer>::WriteCharPtr(const CharStr* str, std::size_t size, ShiftType st, ShiftSize shift, ShiftPrint sp)
    {
        if (CanMoveForward(std::max(static_cast<std::size_t>(shift.Value), size)) == false) return WriteCharPtr(str, GetBufferRemainingSize(), st, shift, sp);

        if (static_cast<std::size_t>(shift) > size)
        {
            shift -= static_cast<Detail::DataType>(size);

            PrintShiftBegin(st, sp, shift);

            FastWriteCharPtr(str, size);

            PrintShiftEnd(st, sp, shift);
        }
        else
        {
            FastWriteCharPtr(str, size);
        }
    }

    template <typename CharBuffer>
    template <typename CharStr>
    inline void FMTBufferOut<CharBuffer>::WriteIndentCharPtr(const CharStr* str, std::size_t size)
    {
        while (size > 0)
        {
            const CharStr* const begin = str;
            while (size > 0 && *str != '\n')
            {
                ++str, --size;
            }
            const CharStr* const end = str;

            FastWriteCharBound(begin, end);

            if (size > 0 && *str == '\n')
            {
                NewLineIndent();
                ++str;
                --size;
            }
        }
    }
}
