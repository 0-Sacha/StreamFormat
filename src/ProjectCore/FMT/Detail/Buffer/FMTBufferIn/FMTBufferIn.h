#pragma once

#include "ProjectCore/FMT/Detail/Buffer/BasicBufferIn/BasicBufferIn.h"

namespace ProjectCore::FMT::Detail
{
    template<typename CharBuffer>
    class FMTBufferIn : public BasicBufferIn<CharBuffer>
    {
    protected:
        using Base = ProjectCore::FMT::Detail::BasicBufferIn<CharBuffer>;
		using Base::m_Buffer;
		using Base::m_BufferEnd;
		using Base::m_CurrentPos;

	public:
		using typename Base::StringView;

	public:
		using Base::GetBuffer;
		using Base::GetBufferCurrentPos;
		using Base::GetBufferEnd;
		using Base::GetBufferSize;
		using Base::GetBufferCurrentSize;
		using Base::GetBufferRemainingSize;
		using Base::SetBufferCurrentPos;

		using Base::ReloadBuffer;
		using Base::SetBuffer;

	public:
		using Base::CanMoveForward;
		using Base::CanMoveForwardThrow;
		using Base::CanMoveBackward;
		using Base::CanMoveBackwardThrow;
		using Base::IsNotOutOfBound;
		using Base::IsNotOutOfBoundThrow;
		using Base::IsEnd;
		using Base::IsEndThrow;

		using Base::Forward;
		using Base::ForwardNoCheck;
		using Base::ForwardNoThrow;
		using Base::Backward;
		using Base::BackwardNoCheck;
		using Base::BackwardNoThrow;
		using Base::Reserve;

		using Base::Get;
		using Base::GetAndForward;
		using Base::GetAndForwardNoCheck;
		using Base::GetAndBackward;
		using Base::GetAndBackwardNoCheck;
		using Base::GetNext;
		using Base::GetNextNoCheck;
		using Base::GetPrev;
		using Base::GetPrevNoCheck;

	public:
		using Base::FastReadInt;
		using Base::FastReadUInt;
		using Base::FastReadFloat;

		using Base::FastReadCharPtr;
		using Base::FastReadCharArray;
		using Base::FastReadCharBound;

		using Base::FastReadCharPtrGlobber;
		using Base::FastReadCharArrayGlobber;
		using Base::FastReadCharBoundGlobber;
		using Base::FastReadCharPtrRegex;
		using Base::FastReadCharArrayRegex;
		using Base::FastReadCharBoundRegex;

		using Base::BasicReadType;

	public:
		using Base::IsEqualTo;
		using Base::IsNotEqualTo;
		using Base::IsEqualToForward;
		using Base::IsNotEqualForward;
		using Base::IsEqualToThrow;
		using Base::IsNotEqualToThrow;
		using Base::IsEqualToForwardThrow;
		using Base::Skip;
		using Base::IsNotEqualForwardThrow;

		using Base::NextIsEqualTo;
		using Base::NextIsNotEqualTo;
		using Base::NextIsEqualToForward;
		using Base::NextIsNotEqualForward;
		using Base::NextIsEqualToThrow;
		using Base::NextIsNotEqualToThrow;
		using Base::NextIsEqualToForwardThrow;
		using Base::NextIsNotEqualForwardThrow;

		using Base::PrevIsEqualTo;
		using Base::PrevIsNotEqualTo;
		using Base::PrevIsEqualToThrow;
		using Base::PrevIsNotEqualToThrow;

		using Base::IsLowerCase;
		using Base::IsUpperCase;
		using Base::IsADigit;
		using Base::IsLowerCaseForward;
		using Base::IsUpperCaseForward;
		using Base::IsADigitForward;
		using Base::IsLowerCaseThrow;
		using Base::IsUpperCaseThrow;
		using Base::IsADigitThrow;
		using Base::IsLowerCaseForwardThrow;
		using Base::IsUpperCaseForwardThrow;
		using Base::IsADigitForwardThrow;


		using Base::IsSameSeq;
		using Base::IsSameSeqForward;
		using Base::IsSameSeqThrow;
		using Base::IsSameSeqForwardThrow;
		using Base::IsSame;
		using Base::IsSameForward;
		using Base::IsSameThrow;
		using Base::IsSameForwardThrow;

		using Base::GetWordFromList;

		using Base::Ignore;
		using Base::IgnoreAll;
		using Base::GoTo;
		using Base::GoToForward;

		using Base::IsBlank;
		using Base::IsBlankForward;
		using Base::IsBlankThrow;
		using Base::IsBlankForwardThrow;

		using Base::IgnoreBlank;
		using Base::IgnoreSpace;
		using Base::IgnoreAllBlanks;
		using Base::IgnoreAllSpaces;

	public:
        FMTBufferIn() 													: Base() {}
        FMTBufferIn(const BufferInProperties<CharBuffer>& properties) 	: Base(properties) {}

		FMTBufferIn(const CharBuffer* const buffer, const std::size_t bufferSize)
            : Base(buffer, bufferSize)
        {}

        ~FMTBufferIn() override = default;

	public:
        template<typename T> void BasicReadInt		(T& i, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{});
        template<typename T> void BasicReadUInt		(T& i, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{});
        template<typename T> void BasicReadFloat	(T& i, FloatPrecision floatPrecision = FloatPrecision{}, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{});
        
        template<typename T> void BasicReadIntAsBin	(T& i, DigitSize digitSize = DigitSize{}, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{}, bool trueValue = false);
        template<typename T> void BasicReadIntAsHex	(T& i, DigitSize digitSize = DigitSize{}, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{}, bool trueValue = false, Detail::PrintStyle valueDes = PrintStyle::Nothing);
        template<typename T> void BasicReadIntAsOct	(T& i, DigitSize digitSize = DigitSize{}, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{}, bool trueValue = false);

    public:
        template<typename T, typename FormatDataCharType> void ReadIntFormatData	(T& i, const FormatData<FormatDataCharType>& formatData);
        template<typename T, typename FormatDataCharType> void ReadUIntFormatData	(T& i, const FormatData<FormatDataCharType>& formatData);
        template<typename T, typename FormatDataCharType> void ReadFloatFormatData	(T& i, const FormatData<FormatDataCharType>& formatData);

    protected:
        template<typename T>
        void SkipShiftBeginSpace(const Detail::ShiftType st, const Detail::ShiftPrint sp, T& shift) {
            if (sp.BeforeIsADigit() == false)
                return;
            if (st == ShiftType::Right || st == ShiftType::CenterLeft || st == ShiftType::CenterRight)
                while (Base::Get() == ' ') {
                    Base::Forward();
                    --shift;
                }
        }

        template<typename T>
        void SkipShiftEnd(const Detail::ShiftType st, const Detail::ShiftPrint sp, T& shift) {
            if (st == ShiftType::Left || st == ShiftType::CenterLeft || st == ShiftType::CenterRight)
                while (Base::Get() == ' ' && shift > 0) {
                    Base::Forward();
                    --shift;
                }
        }
    };
}

#include "Integer.h"
#include "FromFormatData.h"
