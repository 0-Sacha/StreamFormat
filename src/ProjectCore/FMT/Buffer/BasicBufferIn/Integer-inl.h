#pragma once

#include "BasicBufferIn.h"

#include <cmath>

namespace ProjectCore::FMT::Detail
{
    template <typename CharBuffer>
    template <typename T>
    bool BasicBufferIn<CharBuffer>::FastReadInt(T& i) {
        T res = 0;

        bool sign = IsEqualToForward('-');
        if (!IsADigit())
            return false;

        while (IsADigit())
            res = res * static_cast<T>(10) + static_cast<T>(GetAndForward() - static_cast<CharBuffer>('0'));

        i = sign ? -res : res;
        return true;
    }

    template <typename CharBuffer>
    template <typename T>
    bool BasicBufferIn<CharBuffer>::FastReadUInt(T& i) {
        T res = (T)0;

        if(!IsADigit())
            return false;

        while (IsADigit())
            res = res * static_cast<T>(10) + static_cast<T>(GetAndForward() - static_cast<CharBuffer>('0'));

        i = res;
        return true;
    }

    template <typename CharBuffer>
    template <typename T>
    bool BasicBufferIn<CharBuffer>::FastReadFloat(T& i, FloatPrecision floatPrecision) {
        bool sign = IsEqualToForward('-');

        bool hasIntPart = false;
        if (IsNotEqualTo('.'))
        {
            hasIntPart = IsADigit();
            if (hasIntPart == false) return false;
            T res = 0;
            while (IsADigit())
                res = res * static_cast<T>(10) + static_cast<T>(GetAndForward() - static_cast<CharBuffer>('0'));
            i = sign ? -res : res;
        }

        if (IsEqualToForward('.') == false) return hasIntPart;

        if (floatPrecision.IsDefault() || floatPrecision == 0)
            while (IsADigit() && IsEnd() == false) ForwardNoCheck();
        else
        {
            while (IsADigit() && floatPrecision > 0 && IsEnd() == false)
            {
                ForwardNoCheck();
                floatPrecision--;
            }
        }
        BackwardNoCheck();

        T dec = (T)0;
        while (IsADigit())
        {
            dec += static_cast<T>(GetAndBackwardNoCheck() - '0');
            dec /= 10;
        }
        i += dec;
        return true;
    }
}
