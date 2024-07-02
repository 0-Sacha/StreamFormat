#pragma once

#include "FMTBufferIn.h"

namespace ProjectCore::FMT::Detail
{
    template <typename CharBuffer>
    template <typename CharStr>
    inline void FMTBufferIn<CharBuffer>::ReadCharPtr([[maybe_unused]] const CharStr* str, [[maybe_unused]] std::size_t sizeContainer, [[maybe_unused]] std::size_t sizeToWrite,
                                                     [[maybe_unused]] ShiftType st, [[maybe_unused]] ShiftSize shift, [[maybe_unused]] ShiftPrint sp)
    {
        // FIXME
        // TODO
        throw FMTImplError{};
    }
}
