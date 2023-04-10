#pragma once

#include "BasicBufferOut.h"

#include <cmath>

namespace ProjectCore::FMT::Detail
{
    template<typename CharBuffer>
    template<typename T>
    void BasicBufferOut<CharBuffer>::FastWriteInt(T i) {
        if (i == 0) { PushBack('0'); return; }
        if (i < 0)  { PushBack('-'); i = -i; }

        DataType nbDigit = GetNumberOfDigitDec(i);
        Reserve(nbDigit);
        while (i > 0) { PushReverseNoCheck(i % 10 + '0'); i /= 10; }
        Forward(nbDigit + 1);
    }

    template<typename CharBuffer>
    template<typename T>
    void BasicBufferOut<CharBuffer>::FastWriteUInt(T i) {
        if (i == 0) { PushBack('0'); return; }

        DataType nbDigit = GetNumberOfDigitDec(i);
        Reserve(nbDigit);
        while (i > 0) { PushReverseNoCheck(i % 10 + '0'); i /= 10; }
        Forward(nbDigit + 1);
    }

    template<typename CharBuffer>
    template<typename T>
    void BasicBufferOut<CharBuffer>::FastWriteFloat(T i, FloatPrecision nbDecimal) {
        FastWriteInt<typename Detail::TypesInfo::FloatDetail<T>::IntType>(static_cast<typename Detail::TypesInfo::FloatDetail<T>::IntType>(i));
        PushBack('.');
        if (i < 0)    i = -i;
        i = i - static_cast<T>(static_cast<typename Detail::TypesInfo::FloatDetail<T>::IntType>(i));

        nbDecimal.SetToBasicSizeIfDefault();

        while (nbDecimal-- != 0) {
            CharBuffer intPart = static_cast<CharBuffer>(i *= 10);
            PushBack(intPart + '0');
            i -= intPart;
        }
    }

    template<typename CharBuffer>
    template<typename T>
    void BasicBufferOut<CharBuffer>::FastWriteIntAsBin(T i, DigitSize digitSize, bool prefix) {
        bool removeLeading0 = digitSize.IsDefault();

        if (digitSize.Value == DigitSize::MAX_DIGIT_SIZE || digitSize.IsDefault())
            digitSize = static_cast<DigitSize::ValueType>(sizeof(T) * 8);

        if (removeLeading0)
        {
            DataType lastPosWithData = 0;
            DataType k = digitSize + 1;
            T cpyI = i;
            while (--k != 0) {
                if ((cpyI & 1) != 0) lastPosWithData = k;
                cpyI = cpyI >> 1;
            }
            digitSize -= lastPosWithData;
        }

        if (prefix)
        {
            PushBack('0');
            PushBack('b');
        }

        Reserve(digitSize);
        DataType k = digitSize + 1;
        while (--k != 0) {
            if (i & 1)  PushReverseNoCheck('1');
            else        PushReverseNoCheck('0');
            i = i >> 1;
        }
        Forward(digitSize + 1);
        
    }

    template<typename CharBuffer>
    template<typename T>
    void BasicBufferOut<CharBuffer>::FastWriteIntAsHex(T i, DigitSize digitSize, bool prefix, Detail::PrintStyle uppercase) {
        bool removeLeading0 = digitSize.IsDefault();

        if (digitSize.Value == DigitSize::MAX_DIGIT_SIZE || digitSize.IsDefault())
            digitSize = static_cast<DigitSize::ValueType>(sizeof(T) * 2);

        if (removeLeading0)
        {
            DataType lastPosWithData = 0;
            DataType k = digitSize + 1;
            T cpyI = i;
            while (--k != 0) {
                if ((cpyI & 0b1111) != 0) lastPosWithData = k;
                cpyI = cpyI >> 4;
            }
            digitSize -= lastPosWithData;
        }

        if (prefix)
        {
            PushBack('0');
            PushBack('x');
        }

        // Print value
        Reserve(digitSize);
        DataType k = digitSize + 1;
        if (uppercase == PrintStyle::LowerCase)
            while (--k != 0) { PushReverseNoCheck(LOWER_HEX[i & 0b1111]); i = i >> 4; }
        else
            while (--k != 0) { PushReverseNoCheck(UPPER_HEX[i & 0b1111]); i = i >> 4; }
        Forward(digitSize + 1);
    }

    template<typename CharBuffer>
    template<typename T>
    void BasicBufferOut<CharBuffer>::FastWriteIntAsOct(T i, DigitSize digitSize, bool prefix) {
        bool removeLeading0 = digitSize.IsDefault();

        if (digitSize.Value == DigitSize::MAX_DIGIT_SIZE || digitSize.IsDefault())
            digitSize = static_cast<DigitSize::ValueType>(std::ceil(static_cast<float>(sizeof(T) * 8) / 3));

        if (prefix)
        {
            PushBack('0');
            PushBack('o');
        }

        if (removeLeading0)
        {
            DataType lastPosWithData = 0;
            DataType k = digitSize + 1;
            T cpyI = i;
            while (--k != 0) {
                if ((cpyI & 0b111) != 0) lastPosWithData = k;
                cpyI = cpyI >> 3;
            }
            digitSize -= lastPosWithData;
        }

        // Print value
        Reserve(digitSize);
        DataType k = digitSize + 1;
        while (--k != 0) { PushReverseNoCheck((i & 0b111) + '0'); i = i >> 3; }
        Forward(digitSize + 1);
    }
}
