#pragma once

#include "BasicBufferOut.h"

namespace ProjectCore::FMT::Detail
{

    template<typename CharBuffer>
    template<typename CharStr>
    inline void BasicBufferOut<CharBuffer>::FastWriteCharPtr(const CharStr* str, std::size_t size) {
        if (CanMoveForward(size) == false)
            return FastWriteCharPtr(str, GetBufferRemainingSize());

        while (size-- != 0 && *str != 0)
            PushBackNoCheck(*str++);
    }

}
