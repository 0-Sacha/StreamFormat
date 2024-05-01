#pragma once

#include "BasicBufferOut.h"

namespace ProjectCore::FMT::Detail
{
    template <typename CharBuffer>
    template <typename T>
    DataType BasicBufferOut<CharBuffer>::GetNumberOfDigitDec(T value)
    {
        if constexpr (std::numeric_limits<T>::is_signed)
        {
            if (value < 0)    value = -value;
        }
        DataType nb = 0;
        while(true) {
            if (value < 10)         return nb + 1;
            else if(value < 100)    return nb + 2;
            else if (value < 1000)  return nb + 3;
            else if (value < 10000) return nb + 4;
            else {
                value /= static_cast<T>(10000);
                nb += 4;
            }
        }
    }
}
