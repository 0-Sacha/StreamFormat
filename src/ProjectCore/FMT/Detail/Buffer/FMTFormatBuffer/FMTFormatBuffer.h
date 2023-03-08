#pragma once

#include "ProjectCore/FMT/Detail/Buffer/FMTBufferIn/FMTBufferIn.h"

namespace ProjectCore::FMT::Detail {
	template <typename CharFormat>
	class FMTFormatBuffer : public FMTBufferIn<CharFormat> {

	protected:
		using Base = FMTBufferIn<CharFormat>;
		using Base::m_Buffer;
		using Base::m_BufferEnd;
		using Base::m_BufferSize;
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

		using Base::BasicReadInt;
		using Base::BasicReadUInt;
		using Base::BasicReadFloat;

		using Base::BasicReadIntAsBin;
		using Base::BasicReadIntAsHex;
		using Base::BasicReadIntAsOct;

		using Base::ReadIntFormatData;
		using Base::ReadUIntFormatData;
		using Base::ReadFloatFormatData;

		using Base::BasicReadType;

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


	protected:
		using Base::SkipShiftBeginSpace;
		using Base::SkipShiftEnd;

	public:
	    FMTFormatBuffer() 													: Base() {}
        FMTFormatBuffer(const BufferInProperties<CharFormat>& properties) 	: Base(properties) {}

		FMTFormatBuffer(const CharFormat* const buffer, const std::size_t bufferSize)
            : Base(buffer, bufferSize)
        {}

		~FMTFormatBuffer() override = default;
		
	public:
		template<typename T> bool ReadInt(T& t);
		template<typename T> bool ReadUInt(T& t);

	public:
		// Format commands in parameter (add check to '}' to avoid skip the end of the format specifier)
		template<typename ...CharToTest> inline void ParamGoTo(const CharToTest ...ele)			{ GoTo(ele..., '}'); }
		template<typename ...CharToTest> inline void ParamGoToForward(const CharToTest ...ele)	{ GoToForward(ele..., '}'); }

		template<typename ...CharToTest> inline void GoToNextParamOr(const CharToTest ...ele)			{ GoTo(ele..., '{'); }
		template<typename ...CharToTest> inline void GoToNextParamOrForward(const CharToTest ...ele)	{ GoToForward(ele..., '{'); }

		inline bool IsBeginOfParameter()		{ return IsEqualTo('{'); }
		inline void GoToBeginOfParameter()		{ while (IsNotEqualTo('{') && CanMoveForward()) ForwardNoCheck(); }
		inline void GoAfterBeginOfParameter()	{ while (IsNotEqualTo('{') && CanMoveForward()) ForwardNoCheck(); Forward(); }

		inline bool IsEndOfParameter()		{ return IsEqualTo('}'); }
		inline void GoToEndOfParameter()	{ while (IsNotEqualTo('}') && CanMoveForward()) ForwardNoCheck(); }
		inline void GoOutOfParameter()		{ while (IsNotEqualTo('}') && CanMoveForward()) ForwardNoCheck(); Forward(); }

	public:
		// TODO Better way || way to verbous
		template<typename ...CharToTest>
        StringView ParamGoToAndGetStr(const CharToTest ...args)
        {
            const CharFormat* begin = GetBufferCurrentPos();
            ParamGoTo(args...);
            const CharFormat* end = GetBufferCurrentPos();
            return StringView(begin, end); 
        }

		template<typename ...CharToTest>
        StringView ParamGoToForwardAndGetStr(const CharToTest ...args)
        {
            const CharFormat* begin = GetBufferCurrentPos();
            ParamGoToForward(args...);
            const CharFormat* end = GetBufferCurrentPos();
            return StringView(begin, end); 
        }

	public:
		template<typename CharToTest> bool NextIsANamedArgs(const std::basic_string_view<CharToTest>& sv) {
            const CharToTest* const prevSubFormat = m_CurrentPos;
            if (IsSameForward(sv) && (IsEqualTo(':') || IsEqualTo('}'))) return true;
            m_CurrentPos = prevSubFormat;
            return false;
        }
	};
}

#include "Integer.h"
