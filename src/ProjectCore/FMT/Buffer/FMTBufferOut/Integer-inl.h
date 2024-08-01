#pragma once

#include "FMTBufferOut.h"

#include <cmath>

namespace ProjectCore::FMT::Detail
{
    template <typename CharBuffer>
    template <typename T>
    void FMTBufferOut<CharBuffer>::WriteInt(T i, ShiftType st, ShiftSize shift, ShiftPrint sp)
    {
        sp.ValidateForNumber();

        DataType nbDigit = GetNumberOfDigitDec(i);

        shift -= nbDigit;
        if (i < 0) --shift;

        if (shift <= 0) return FastWriteInt(i);

        if (!sp.BeforeIsADigit()) PrintShiftBegin(st, sp, shift);
        if (i < 0)
        {
            PushBack('-');
            i = -i;
        }
        if (sp.BeforeIsADigit()) PrintShiftRightAll(st, sp, shift);

        if (i == 0)
            PushBack('0');
        else
        {
            Reserve(nbDigit);
            DataType nbDigit_ = nbDigit;
            while (nbDigit_ > 0)
            {
                PushReverseNoCheck(i % 10 + '0');
                i /= 10;
                nbDigit_--;
            }
            Forward(nbDigit + 1);
        }

        PrintShiftEnd(st, sp, shift);
    }

    template <typename CharBuffer>
    template <typename T>
    void FMTBufferOut<CharBuffer>::WriteUInt(T i, ShiftType st, ShiftSize shift, ShiftPrint sp)
    {
        sp.ValidateForNumber();

        DataType nbDigit = GetNumberOfDigitDec(i);
        shift -= nbDigit;

        if (shift <= 0) return FastWriteUInt(i);

        PrintShiftBegin(st, sp, shift);

        if (i == 0)
            PushBack('0');
        else
        {
            Reserve(nbDigit);
            DataType nbDigit_ = nbDigit;
            while (nbDigit_ > 0)
            {
                PushReverseNoCheck(i % 10 + '0');
                i /= 10;
                nbDigit_--;
            }
            Forward(nbDigit + 1);
        }

        PrintShiftEnd(st, sp, shift);
    }

    template <typename CharBuffer>
    template <typename T>
    void FMTBufferOut<CharBuffer>::WriteFloat(T i, FloatPrecision nbDecimal, ShiftType st, ShiftSize shift, ShiftPrint sp)
    {
        sp.ValidateForNumber();

        DataType nbDigit = GetNumberOfDigitDec(std::trunc(i));
        nbDecimal.SetToBasicSizeIfDefault();

        shift -= nbDigit + nbDecimal + 1;
        if (i < 0) --shift;

        if (shift <= 0) return FastWriteFloat(i, nbDecimal);

        if (!sp.BeforeIsADigit()) PrintShiftBegin(st, sp, shift);
        if (i < 0)
        {
            PushBack('-');
            i = -i;
        }
        if (sp.BeforeIsADigit()) PrintShiftRightAll(st, sp, shift);

        T k = std::trunc(i);
        if (k == 0)
            PushBack('0');
        else
        {
            Reserve(nbDigit);
            DataType nbDigit_ = nbDigit;
            while (nbDigit_ > 0)
            {
                PushReverseNoCheck(char(std::fmod(i, 10)) + '0');
                k /= 10;
                nbDigit_--;
            }
            Forward(nbDigit + 1);
        }

        PushBack('.');
        i -= k;
        while (nbDecimal-- != 0)
        {
            T decimal = std::trunc(i *= 10);
            PushBack((char)decimal + '0');
            i -= decimal;
        }

        PrintShiftEnd(st, sp, shift);
    }

    //---------------------------------------------//
    //---------------------------------------------//
    //---------------------------------------------//

    template <typename CharBuffer>
    template <typename T>
    void FMTBufferOut<CharBuffer>::WriteIntAsBin(T i, DigitSize digitSize, ShiftType st, ShiftSize shift, ShiftPrint sp, bool prefix)
    {
        sp.ValidateForNumber();

        bool removeLeading0 = digitSize.IsDefault();

        if (digitSize.Value == DigitSize::MAX_DIGIT_SIZE || digitSize.IsDefault()) digitSize = static_cast<DigitSize::ValueType>(sizeof(T) * 8);

        if (removeLeading0)
        {
            DataType lastPosWithData = 0;
            DataType k               = digitSize + 1;
            T        cpyI            = i;
            while (--k != 0)
            {
                if (cpyI & 1) lastPosWithData = k;
                cpyI = cpyI >> 1;
            }
            digitSize -= lastPosWithData;
        }

        shift -= digitSize;
        if (prefix) shift -= 2;
        if (shift < 0) shift = 0;

        if (!sp.BeforeIsADigit()) PrintShiftBegin(st, sp, shift);
        if (prefix)
        {
            PushBack('0');
            PushBack('b');
        }
        if (sp.BeforeIsADigit()) PrintShiftBegin(st, sp, shift);

        // Print value
        Reserve(digitSize);
        DataType k = digitSize + 1;
        while (--k != 0)
        {
            if (i & 1)
                PushReverseNoCheck('1');
            else
                PushReverseNoCheck('0');
            i = i >> 1;
        }
        Forward(digitSize + 1);

        PrintShiftEnd(st, sp, shift);
    }

    template <typename CharBuffer>
    template <typename T>
    void FMTBufferOut<CharBuffer>::WriteIntAsHex(T i, DigitSize digitSize, ShiftType st, ShiftSize shift, ShiftPrint sp, bool prefix, Detail::PrintStyle uppercase)
    {
        sp.ValidateForNumber();

        bool removeLeading0 = digitSize.IsDefault();

        if (digitSize.Value == DigitSize::MAX_DIGIT_SIZE || digitSize.IsDefault()) digitSize = static_cast<DigitSize::ValueType>(sizeof(T) * 2);

        if (removeLeading0)
        {
            DataType lastPosWithData = 0;
            DataType k               = digitSize + 1;
            T        cpyI            = i;
            while (--k != 0)
            {
                if ((cpyI & 0b1111) != 0) lastPosWithData = k;
                cpyI = cpyI >> 4;
            }
            digitSize -= lastPosWithData;
        }

        shift -= digitSize;
        if (prefix) shift -= 2;
        if (shift < 0) shift = 0;

        if (!sp.BeforeIsADigit()) PrintShiftBegin(st, sp, shift);
        if (prefix)
        {
            PushBack('0');
            PushBack('x');
        }
        if (sp.BeforeIsADigit()) PrintShiftBegin(st, sp, shift);

        // Print value
        Reserve(digitSize);
        DataType k = digitSize + 1;
        if (uppercase == PrintStyle::LowerCase)
            while (--k != 0)
            {
                PushReverseNoCheck(LOWER_HEX[i & 0b1111]);
                i = i >> 4;
            }
        else
            while (--k != 0)
            {
                PushReverseNoCheck(UPPER_HEX[i & 0b1111]);
                i = i >> 4;
            }
        Forward(digitSize + 1);

        PrintShiftEnd(st, sp, shift);
    }

    template <typename CharBuffer>
    template <typename T>
    void FMTBufferOut<CharBuffer>::WriteIntAsOct(T i, DigitSize digitSize, ShiftType st, ShiftSize shift, ShiftPrint sp, bool prefix)
    {
        sp.ValidateForNumber();

        bool removeLeading0 = digitSize.IsDefault();

        if (digitSize.Value == DigitSize::MAX_DIGIT_SIZE || digitSize.IsDefault()) digitSize = static_cast<DigitSize::ValueType>(std::ceil(static_cast<float>(sizeof(T) * 8) / 3));

        if (removeLeading0)
        {
            DataType lastPosWithData = 0;
            DataType k               = digitSize + 1;
            T        cpyI            = i;
            while (--k != 0)
            {
                if ((cpyI & 0b111) != 0) lastPosWithData = k;
                cpyI = cpyI >> 4;
            }
            digitSize -= lastPosWithData;
        }

        shift -= digitSize;
        if (prefix) shift -= 2;
        if (shift < 0) shift = 0;

        if (!sp.BeforeIsADigit()) PrintShiftBegin(st, sp, shift);
        if (prefix)
        {
            PushBack('0');
            PushBack('o');
        }
        if (sp.BeforeIsADigit()) PrintShiftBegin(st, sp, shift);

        // Print value
        Reserve(digitSize);
        DataType k = digitSize + 1;
        while (--k != 0)
        {
            PushReverseNoCheck((i & 0b111) + '0');
            i = i >> 3;
        }
        Forward(digitSize + 1);

        PrintShiftEnd(st, sp, shift);
    }
}
