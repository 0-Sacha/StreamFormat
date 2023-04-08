#pragma once

#include "FMTBufferIn.h"

#include <cmath>

namespace ProjectCore::FMT::Detail
{
    template<typename CharBuffer>
    template<typename T>
    void FMTBufferIn<CharBuffer>::ReadInt(T& i, ShiftType st, ShiftSize shift, ShiftPrint sp) {
        T res = 0;

        SkipShiftBeginSpace(st, sp, shift);

        bool sign = IsEqualToForward('-'); 
        if (sign) --shift;
    
        IsADigitThrow();

        while (IsADigit()) {
            res = res * 10 + (GetAndForward() - '0');
            --shift;
        }

        SkipShiftEnd(st, sp, shift);

        if (shift > 0) throw FMTParseError();
        
        i = sign ? -res : res;
    }

    template<typename CharBuffer>
    template<typename T>
    void FMTBufferIn<CharBuffer>::ReadUInt(T& i, ShiftType st, ShiftSize shift, ShiftPrint sp) {
        T res = 0;

        SkipShiftBeginSpace(st, sp, shift);

        IsADigitThrow();

        while (IsADigit()) {
            res = res * 10 + (GetAndForward() - '0');
            --shift;
        }

        SkipShiftEnd(st, sp, shift);

        if (shift > 0) throw FMTParseError();

        i = res;
    }

    template<typename CharBuffer>
    template<typename T>
    void FMTBufferIn<CharBuffer>::ReadFloat(T& i, FloatPrecision floatPrecision, ShiftType st, ShiftSize shift, ShiftPrint sp) {
        typename Detail::TypesInfo::FloatDetail<T>::IntType iInt = 0;

        SkipShiftBeginSpace(st, sp, shift);

        bool sign = IsEqualToForward('-');
        if (sign) --shift;

        IsADigitThrow();

        while (IsADigit()) {
            iInt = iInt * 10 + (GetAndForward() - '0');
            --shift;
        }

        T dec = 0;
        T decIdx = 0.1f;

        if (IsEqualToForward('.') == false)
        {
            if (floatPrecision == 0 || floatPrecision.IsDefault())    
                return iInt;
            throw Detail::FMTParseError{};
        }
        --shift;
            
        if (floatPrecision.IsDefault())
        {
            while (IsADigit() && IsEnd() == false) {
                dec += (GetAndForward() - '0') * decIdx;
                decIdx *= 0.1f;
            --shift;
            }
        }
        else
        {
            ++floatPrecision;
            while (IsADigit() && --floatPrecision != 0) {
                dec += (GetAndForward() - '0') * decIdx;
                decIdx *= 0.1f;
            --shift;
            }
        }

        SkipShiftEnd(st, sp, shift);

        if (shift > 0) throw FMTParseError();

        sign ? i = -iInt - dec : i = iInt + dec;
    }

    //---------------------------------------------//
    //---------------------------------------------//
    //---------------------------------------------//

    template<typename CharBuffer>
    template<typename T>
    void FMTBufferIn<CharBuffer>::ReadIntAsBin(T& i, DigitSize digitSize, ShiftType st, ShiftSize shift, ShiftPrint sp, bool trueValue) {
        if (digitSize.IsDefault())
            digitSize = sizeof(T) * 8;

        shift -= digitSize;
        if (trueValue) shift -= 2;

        SkipShiftBeginSpace(st, sp, shift);
        
        if (trueValue) {
            Skip('0');
            Skip('b');
        }

        T res = 0;

        while (IsEqualTo('0', '1')) {
            res = res << 1;
            res += Get() - '0';
            Forward();
        }

        SkipShiftEnd(st, sp, shift);

        if (shift > 0) throw FMTParseError();

        i = res;
    }

    template<typename CharBuffer>
    template<typename T>
    void FMTBufferIn<CharBuffer>::ReadIntAsHex(T& i, DigitSize digitSize, ShiftType st, ShiftSize shift, ShiftPrint sp, bool trueValue, [[maybe_unused]] Detail::PrintStyle printStyle) {
        if (digitSize.IsDefault())
            digitSize = sizeof(T) * 2;

        shift -= digitSize;
        if (trueValue) shift -= 2;

        SkipShiftBeginSpace(st, sp, shift);

        if (trueValue) {
            Skip('0');
            Skip('x');
        }

        T res = 0;

        while (IsADigit() || (Get() >= 'A' && Get() <= 'F') || (Get() >= 'a' && Get() <= 'f')) {
            res = res << 4;
            if (IsADigit())                                res += Get() - '0';
            else if (Get() >= 'A' && Get() <= 'F')    res += Get() - 'A' + 10;
            else if (Get() >= 'a' && Get() <= 'f')    res += Get() - 'a' + 10;
            Forward();
        }

        SkipShiftEnd(st, sp, shift);

        if (shift > 0) throw FMTParseError();

        i = res;
    }

    template<typename CharBuffer>
    template<typename T>
    void FMTBufferIn<CharBuffer>::ReadIntAsOct(T& i, DigitSize digitSize, ShiftType st, ShiftSize shift, ShiftPrint sp, bool trueValue) {
        if (digitSize.IsDefault())
            digitSize = std::ceil(static_cast<float>(sizeof(T) * 8) / 3);

        shift -= digitSize;
        if (trueValue) shift -= 2;

        SkipShiftBeginSpace(st, sp, shift);

        if (trueValue) {
            Skip('0');
            Skip('o');
        }

        T res = 0;

        while (Get() >= '0' && Get() <= '8') {
            res = res << 3;
            res += Get() - '0';
            Forward();
        }

        SkipShiftEnd(st, sp, shift);

        if (shift > 0) throw FMTParseError();

        i = res;
    }
}
