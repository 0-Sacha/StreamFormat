#pragma once

#include "BasicBufferIn.h"

namespace EngineCore::Instrumentation::FMT::Detail {
	template <typename CharFormat>
	class FormatterMemoryFormat : public BasicFormatterMemoryBufferIn<CharFormat> {

	protected:
		using Base = BasicFormatterMemoryBufferIn<CharFormat>;
		using Base::m_Buffer;
		using Base::m_BufferEnd;
		using Base::m_BufferSize;
		using Base::m_CurrentPos;

	public:
		using typename Base::StringView;
		using CharFormatType = CharFormat;

	public:
		using Base::GetBuffer;
		using Base::GetBufferCurrentPos;
		using Base::GetBufferEnd;
		using Base::GetBufferSize;
		using Base::GetBufferCurrentSize;
		using Base::SetBufferCurrentPos;

	public:
		using Base::CanMoveForward;
		using Base::CanMoveBackward;
		using Base::IsNotOutOfBound;

		using Base::IsEnd;

		using Base::CanMoveForwardThrow;
		using Base::CanMoveBackwardThrow;
		using Base::IsNotOutOfBoundThrow;
		using Base::IsEndThrow;

		using Base::Forward;
		using Base::ForwardNoCheck;
		using Base::Backward;
		using Base::BackwardNoCheck;

		using Base::Get;
		using Base::GetAndForward;
		using Base::GetAndForwardNoCheck;
		using Base::GetAndBackward;
		using Base::GetAndBackwardNoCheck;
		using Base::GetNext;
		using Base::GetNextNoCheck;

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
		using Base::IsEqualForward;
		using Base::IsNotEqualForward;
		using Base::IsEqualToThrow;
		using Base::IsNotEqualToThrow;
		using Base::IsEqualForwardThrow;
		using Base::IsNotEqualForwardThrow;

		using Base::NextIsEqualTo;
		using Base::NextIsNotEqualTo;
		using Base::NextIsEqualForward;
		using Base::NextIsNotEqualForward;
		using Base::NextIsEqualToThrow;
		using Base::NextIsNotEqualToThrow;
		using Base::NextIsEqualForwardThrow;
		using Base::NextIsNotEqualForwardThrow;

		using Base::IsLowerCase;
		using Base::IsUpperCase;
		using Base::IsADigit;
		using Base::IsLowerCaseThrow;
		using Base::IsUpperCaseThrow;
		using Base::IsADigitThrow;

		using Base::NextIsSame;
		using Base::NextIsSameThrow;

		using Base::NextIsANamedArgs;
		using Base::NextIsANamedArgsThrow;

		using Base::GetWordFromList;

		using Base::IgnoreSpace;
		using Base::GoTo;
		using Base::GoToForward;

	protected:
		using Base::SkipShiftBeginSpace;
		using Base::SkipShiftEnd;

	public:
		explicit FormatterMemoryFormat(const std::basic_string_view<CharFormat>& format)
			: BasicFormatterMemoryBufferIn<CharFormat>(format) {}

	public:
		template<typename T> bool ReadInt(T& t);
		template<typename T> bool ReadUInt(T& t);

	public:
		// Format commands in parameter (add check to '}' to avoid skip the end of the format specifier)
		template<typename ...CharToTest> inline void ParamGoTo(const CharToTest ...ele)			{ GoTo(ele..., '}'); }
		template<typename ...CharToTest> inline void ParamGoToForward(const CharToTest ...ele)	{ GoToForward(ele..., '}'); }

		inline bool IsEndOfParameter()		{ return IsEqualTo('}'); }
		inline void GoToEndOfParameter()	{ while (IsNotEqualTo('}') && CanMoveForward()) ForwardNoCheck(); }
		inline void GoOutOfParameter()		{ while (IsNotEqualTo('}') && CanMoveForward()) ForwardNoCheck(); Forward(); }
	};
}