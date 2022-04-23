#pragma once

#include "BasicBuffer.h"

namespace EngineCore::Instrumentation::Fmt::Detail {

	template<typename CharBuffer>
	class BasicFormatterMemoryBufferIn : public BasicFormatterMemoryBuffer<const CharBuffer> {

	private:
		using Base = BasicFormatterMemoryBuffer<const CharBuffer>;
		using Base::m_Buffer;
		using Base::m_BufferEnd;
		using Base::m_BufferSize;
		using Base::m_CurrentPos;

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
		using CharBufferType = CharBuffer;

	public:
		inline const CharBuffer*	GetBuffer() const									{ return Base::GetBuffer(); }
		inline const CharBuffer*	GetBufferCurrentPos() const							{ return Base::GetBufferCurrentPos(); }
		inline const CharBuffer*	GetBufferEnd() const								{ return Base::GetBufferEnd(); }
		inline std::size_t			GetBufferSize() const								{ return Base::GetBufferSize(); }
		inline std::size_t			GetBufferCurrentSize() const						{ return Base::GetBufferCurrentSize(); }
		inline void					SetBufferCurrentPos(const CharBuffer* const pos)	{ Base::SetBufferCurrentPos(pos); }

	public:
		BasicFormatterMemoryBufferIn(const std::basic_string_view<CharBuffer> format)
			: Base(format) {}

	public:
		// TODO
		template <typename ChildBuffer>
		inline void UpdateFromChlidBuffer(ChildBuffer& childBuffer) { SetBufferCurrentPos(childBuffer.GetBufferCurrentPos()); }

	public:
		template<typename T> void FastReadInt	(T& i);
		template<typename T> void FastReadUInt	(T& i);
		template<typename T> void FastReadFloat	(T& i, FormatDataType floatPrecision = Detail::FLOAT_PRECISION_NOT_SPECIFIED);
		
		template<typename T> void BasicReadInt		(T& i, ShiftType st = ShiftType::Nothing, FormatDataType shift = Detail::SHIFT_NOT_SPECIFIED, ShiftPrint sp = ShiftPrint::Space);
		template<typename T> void BasicReadUInt		(T& i, ShiftType st = ShiftType::Nothing, FormatDataType shift = Detail::SHIFT_NOT_SPECIFIED, ShiftPrint sp = ShiftPrint::Space);
		template<typename T> void BasicReadFloat	(T& i, FormatDataType floatPrecision = Detail::FLOAT_PRECISION_NOT_SPECIFIED, ShiftType st = ShiftType::Nothing, FormatDataType shift = Detail::SHIFT_NOT_SPECIFIED, ShiftPrint sp = ShiftPrint::Space);
		
		template<typename T> void BasicReadIntAsBin	(T& i, FormatDataType digitSize = Detail::DIGIT_SIZE_NOT_SPECIFIED, ShiftType st = ShiftType::Nothing, FormatDataType shift = Detail::SHIFT_NOT_SPECIFIED, ShiftPrint sp = ShiftPrint::Space, bool trueValue = false);
		template<typename T> void BasicReadIntAsHex	(T& i, FormatDataType digitSize = Detail::DIGIT_SIZE_NOT_SPECIFIED, ShiftType st = ShiftType::Nothing, FormatDataType shift = Detail::SHIFT_NOT_SPECIFIED, ShiftPrint sp = ShiftPrint::Space, bool trueValue = false, Detail::PrintStyle valueDes = PrintStyle::Nothing);
		template<typename T> void BasicReadIntAsOct	(T& i, FormatDataType digitSize = Detail::DIGIT_SIZE_NOT_SPECIFIED, ShiftType st = ShiftType::Nothing, FormatDataType shift = Detail::SHIFT_NOT_SPECIFIED, ShiftPrint sp = ShiftPrint::Space, bool trueValue = false);


	public:
		template<typename T, typename FormatDataCharType> void ReadIntFormatData	(T& i, const FormatData<FormatDataCharType>& formatData);
		template<typename T, typename FormatDataCharType> void ReadUIntFormatData	(T& i, const FormatData<FormatDataCharType>& formatData);
		template<typename T, typename FormatDataCharType> void ReadFloatFormatData	(T& i, const FormatData<FormatDataCharType>& formatData);

	public:
		// Basic types
		template<typename T> bool BasicReadType(T& i) { return false; }

		inline void BasicReadType(std::int8_t& i)	{ return FastReadInt(i); 	}
		inline void BasicReadType(std::uint8_t& i)	{ return FastReadUInt(i); 	}
		inline void BasicReadType(std::int16_t& i)	{ return FastReadInt(i);	}
		inline void BasicReadType(std::uint16_t& i)	{ return FastReadUInt(i); 	}
		inline void BasicReadType(std::int32_t& i)	{ return FastReadInt(i);	}
		inline void BasicReadType(std::uint32_t& i)	{ return FastReadUInt(i); 	}
		inline void BasicReadType(std::int64_t& i)	{ return FastReadInt(i);	}
		inline void BasicReadType(std::uint64_t& i)	{ return FastReadUInt(i); 	}

		inline void BasicReadType(float& i)			{ return FastReadFloat(i);	}
		inline void BasicReadType(double& i)		{ return FastReadFloat(i);	}
		inline void BasicReadType(long double& i)	{ return FastReadFloat(i);	}

		inline void BasicReadType(char& i)		{ i = Base::GetAndForward(); return; }
		inline void BasicReadType(wchar_t& i)	{ i = Base::GetAndForward(); return; }
		inline void BasicReadType(char16_t& i)	{ i = Base::GetAndForward(); return; }
		inline void BasicReadType(char32_t& i)	{ i = Base::GetAndForward(); return; }

		template<std::size_t SIZE> inline void BasicReadType(char(&i)[SIZE])		{ /* TODO */ return; }
		template<std::size_t SIZE> inline void BasicReadType(wchar_t(&i)[SIZE])		{ /* TODO */ return; }
		template<std::size_t SIZE> inline void BasicReadType(char16_t(&i)[SIZE])	{ /* TODO */ return; }
		template<std::size_t SIZE> inline void BasicReadType(char32_t(&i)[SIZE])	{ /* TODO */ return; }

		template<typename CharType> inline bool BasicReadType(std::basic_string_view<CharType> i) { /* TODO */ return true; }

	public:
		// Format check
		inline bool IsEqualTo(const CharBuffer c) const				{ return Get() == c; }
		inline bool IsNotEqualTo(const CharBuffer c) const			{ return Get() != c; }
		inline bool IsEqualForward(const CharBuffer c)				{ if (IsEqualTo(c)) { Forward(); return true; } return false; }
		inline bool IsNotEqualForward(const CharBuffer c)			{ if (IsNotEqualTo(c)) { Forward(); return true; } return false; }
		template<typename ...CharToTest> inline bool IsEqualTo(const CharBuffer c, const CharToTest ...ele) const		{ return IsEqualTo(c) || IsEqualTo(ele...); }
		template<typename ...CharToTest> inline bool IsEqualForward(const CharToTest ...ele)							{ if (IsEqualTo(ele...)) { Forward(); return true; } return false; }
		template<typename ...CharToTest> inline bool IsNotEqualTo(const CharBuffer c, const CharToTest ...ele) const	{ return IsNotEqualTo(c) && IsNotEqualTo(ele...); }
		template<typename ...CharToTest> inline bool IsNotEqualForward(const CharToTest ...ele)							{ if (IsNotEqualTo(ele...)) { Forward(); return true; } return false; }
		// Auto throw variant
		template<typename ...CharToTest> inline void IsEqualToThrow(const CharBuffer c, const CharToTest ...ele) const		{ if (IsEqualTo(c, ele...)) return; throw FormatParseError(); }
		template<typename ...CharToTest> inline void IsEqualForwardThrow(const CharToTest ...ele)							{ if (IsEqualForward(ele...)) return; throw FormatParseError(); }
		template<typename ...CharToTest> inline void IsNotEqualToThrow(const CharBuffer c, const CharToTest ...ele) const	{ if (IsNotEqualTo(c, ele...)) return; throw FormatParseError(); }
		template<typename ...CharToTest> inline void IsNotEqualForwardThrow(const CharToTest ...ele)						{ if (IsNotEqualForward(ele...)) return; throw FormatParseError(); }
		
		
		// Format Next check
		inline bool NextIsEqualTo(const CharBuffer c) const			{ return GetNext() == c; }
		inline bool NextIsNotEqualTo(const CharBuffer c) const		{ return GetNext() != c; }
		inline bool NextIsEqualForward(const CharBuffer c)			{ Forward(); if (!IsEqualTo(c)) { BackwardNoCheck(); return false; } return true; }
		inline bool NextIsNotEqualForward(const CharBuffer c)		{ Forward(); if (!IsNotEqualTo(c)) { BackwardNoCheck(); return false; } return true; }
		template<typename ...CharToTest> inline bool NextIsEqualForward(const CharToTest ...ele)		{ Forward(); if (IsEqualTo(ele...)) { return true; } BackwardNoCheck(); return false; }
		template<typename ...CharToTest> inline bool NextIsEqualTo(const CharToTest ...ele) const		{ Forward(); if (IsEqualTo(ele...)) { BackwardNoCheck(); return true; } BackwardNoCheck(); return false; }
		template<typename ...CharToTest> inline bool NextIsNotEqualForward(const CharToTest ...ele)		{ Forward(); if (IsNotEqualTo(ele...)) { return true; } BackwardNoCheck(); return false; }
		template<typename ...CharToTest> inline bool NextIsNotEqualTo(const CharToTest ...ele) const	{ Forward(); if (IsNotEqualTo(ele...)) { BackwardNoCheck(); return true; } BackwardNoCheck(); return false; }
		// Auto throw variant
		template<typename ...CharToTest> inline void NextIsEqualToThrow(const CharBuffer c, const CharToTest ...ele) const		{ if (NextIsEqualTo(c, ele...)) return; throw FormatParseError(); }
		template<typename ...CharToTest> inline void NextIsEqualForwardThrow(const CharToTest ...ele)							{ if (NextIsEqualForward(ele...)) return; throw FormatParseError(); }
		template<typename ...CharToTest> inline void NextIsNotEqualToThrow(const CharBuffer c, const CharToTest ...ele) const	{ if (NextIsNotEqualTo(c, ele...)) return; throw FormatParseError(); }
		template<typename ...CharToTest> inline void NextIsNotEqualForwardThrow(const CharToTest ...ele)						{ if (NextIsNotEqualForward(ele...)) return; throw FormatParseError(); }


	public:
		template<typename CharToTest> bool NextIsANamedArgs(std::basic_string_view<CharToTest> sv) {
			const CharBuffer* const prevSubFormat = m_CurrentPos;
			if (NextIsSame(sv) && (IsEqualTo(':') || IsEqualTo('}'))) return true;
			m_CurrentPos = prevSubFormat;
			return false;
		}

		template<typename CharToTest> bool NextIsSame(std::basic_string_view<CharToTest> sv) {
			const CharToTest* str = sv.data();
			std::size_t size = sv.size();
			const CharBuffer* prevSubFormat = m_CurrentPos;		bool isSame = true;
			while (isSame && size-- != 0 && CanMoveForward())	isSame = GetAndForwardNoCheck() == *str++;
			if (isSame && size == 0)							isSame = false;
			if (!isSame)										m_CurrentPos = prevSubFormat;
			return isSame;
		}

		template<std::size_t SIZE, typename CharToTest>
		inline bool NextIsSame(const CharToTest(&data)[SIZE]) { return NextIsSame(std::basic_string_view<CharToTest>(data)); }

		inline bool IsLowerCase() const	{ return Get() >= 'a' && Get() <= 'z'; }
		inline bool IsUpperCase() const	{ return Get() >= 'A' && Get() <= 'Z'; }
		inline bool IsADigit() const	{ return Get() >= '0' && Get() <= '9'; }

		// Auto throw variant
		template<typename CharToTest> inline void NextIsANamedArgsThrow(std::basic_string_view<CharToTest> sv)		{ if (NextIsANamedArgs(sv)) return; throw FormatParseError(); }
		template<typename CharToTest> inline void NextIsSameThrow(std::basic_string_view<CharToTest> sv)			{ if (NextIsSame(sv)) return; throw FormatParseError(); }
		template<std::size_t SIZE, typename CharToTest> inline void NextIsSameThrow(const CharToTest(&data)[SIZE])	{ if (NextIsSame(data)) return; throw FormatParseError(); }

		inline void IsLowerCaseThrow() const	{ if (IsLowerCase()) return; throw FormatParseError(); }
		inline void IsUpperCaseThrow() const	{ if (IsUpperCase()) return; throw FormatParseError(); }
		inline void IsADigitThrow() const		{ if (IsADigit()) return; throw FormatParseError(); }

		// Format commands
	public:
		inline void IgnoreSpace()															{ while (IsEqualTo(' ') && CanMoveForward()) ForwardNoCheck(); }
		template<typename ...CharToTest> inline void GoTo(const CharToTest ...ele)			{ while (IsNotEqualTo(ele...) && CanMoveForward())	ForwardNoCheck(); }
		template<typename ...CharToTest> inline void GoToForward(const CharToTest ...ele)	{ while (IsNotEqualTo(ele...) && CanMoveForward())	ForwardNoCheck(); Forward(); }


		// Utils
	private:
		template<typename T>
		void SkipShiftBeginSpace(const Detail::ShiftType st, const Detail::ShiftPrint sp, T& shift) {
			if ((st == ShiftType::Right || st == ShiftType::Center) && sp == ShiftPrint::Space)
				while (Base::Get() == ' ') {
					Base::Forward();
					--shift;
				}
		}

		template<typename T>
		void SkipShiftEnd(const Detail::ShiftType st, const Detail::ShiftPrint sp, T& shift) {
			if (st == ShiftType::Left || st == ShiftType::Center)
				while (Base::Get() == ' ' && shift > 0) {
					Base::Forward();
					--shift;
				}
		}
	};

}