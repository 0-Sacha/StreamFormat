#pragma once

#include "BasicBufferIn.h"

namespace ProjectCore::FMT::Detail
{
    template<typename CharBuffer>
	template<typename CharPtr>
	void BasicBufferIn<CharBuffer>::FastReadCharPtr(CharPtr* str, std::size_t size)
    {
        if (CanMoveForward(size) == false)
            return FastReadCharPtr(str, GetBufferRemainingSize());

        // TODO : Opti with bigger types
        while (size-- != 0)
            *str++ = GetAndForward();
    }
}
