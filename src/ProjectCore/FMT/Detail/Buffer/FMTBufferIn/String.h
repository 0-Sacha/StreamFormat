#pragma once

#include "FMTBufferIn.h"

namespace ProjectCore::FMT::Detail
{
    template<typename CharBuffer>
    template<typename CharStr>
    inline void FMTBufferIn<CharBuffer>::ReadCharPtr(const CharStr* str, std::size_t sizeContainer, std::size_t sizeToWrite, ShiftType st, ShiftSize shift, ShiftPrint sp)
    {
        // FIXME
        throw FMTImplError{};
    }

}
