#pragma once

#include "BasicBuffer.h"

namespace EngineCore::Instrumentation::FMT::Detail {

	template <typename CharBuffer>
	class BasicFormatterMemoryBufferOutCopy;

	template <typename CharBuffer>
	class BasicFormatterMemoryBufferOut : public BasicFormatterMemoryBuffer<CharBuffer> {

	private:
		using Base = BasicFormatterMemoryBuffer<CharBuffer>;
		using Base::m_Buffer;
		using Base::m_BufferEnd;
		using Base::m_BufferSize;
		using Base::m_CurrentPos;
		using Base::m_NoStride;

	public:
		using CharBufferType = CharBuffer;

		using Base::GetBuffer;
		using Base::GetBufferCurrentPos;
		using Base::GetBufferEnd;
		using Base::GetBufferSize;
		using Base::GetBufferCurrentSize;
		using Base::SetBufferCurrentPos;

		using Base::GetNoStride;
		using Base::AddNoStride;

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

		static constexpr std::size_t	DEFAULT_BEGIN_SIZE	= 512;
		static constexpr std::size_t	GROW_UP_BUFFER_SIZE = 2;
		static constexpr bool			DEBUG_RESIZE		= true;

		static constexpr char			UPPER_HEX[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
		static constexpr char			LOWER_HEX[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	
	private:
		bool				m_BufferAutoResize;
		bool				m_FreeOnDestructor;

	public:
		inline CharBuffer*			GetBuffer()									{ return Base::GetBuffer(); }
		inline const CharBuffer*	GetBuffer() const							{ return Base::GetBuffer(); }
		inline CharBuffer*			GetBufferCurrentPos()						{ return Base::GetBufferCurrentPos(); }
		inline const CharBuffer*	GetBufferCurrentPos() const					{ return Base::GetBufferCurrentPos(); }
		inline CharBuffer*			GetBufferEnd() 								{ return Base::GetBufferEnd(); }
		inline const CharBuffer*	GetBufferEnd() const						{ return Base::GetBufferEnd()(); }
		inline std::size_t			GetBufferSize() const						{ return Base::GetBufferSize(); }
		inline std::size_t			GetBufferCurrentSize() const				{ return Base::GetBufferCurrentSize(); }
		inline void					SetBufferCurrentPos(CharBuffer* const pos)	{ Base::SetBufferCurrentPos(pos); }

		inline bool					BufferIsAutoResize()						{ return m_BufferAutoResize; }

	private:
		friend BasicFormatterMemoryBufferOutCopy<CharBuffer>;
		inline void					DoNotFreeOnDestructor()					{ m_FreeOnDestructor = false; }

	public:
		BasicFormatterMemoryBufferOut(CharBuffer* const buffer, const std::size_t bufferSize)
			: BasicFormatterMemoryBuffer<CharBuffer>(buffer, bufferSize)
			, m_BufferAutoResize(false)
			, m_FreeOnDestructor(false)
		{
			PushEndCharToTheEnd();
		}

		BasicFormatterMemoryBufferOut(const std::size_t beginSize = DEFAULT_BEGIN_SIZE)
			: BasicFormatterMemoryBuffer<CharBuffer>(new CharBuffer[beginSize], beginSize)
			, m_BufferAutoResize(true)
			, m_FreeOnDestructor(true)
		{
			PushEndCharToTheEnd();
		}

		~BasicFormatterMemoryBufferOut() {
			if (m_FreeOnDestructor)
				delete[] m_Buffer;
		}

		template <typename ParentBuffer>
		explicit BasicFormatterMemoryBufferOut(ParentBuffer& parentBuffer)
			: BasicFormatterMemoryBuffer<CharBuffer>(parentBuffer.GetBuffer(), parentBuffer.GetBufferCurrentPos(), parentBuffer.GetBufferEnd(), parentBuffer.GetBufferSize(), parentBuffer.GetNoStride())
			, m_BufferAutoResize(parentBuffer.BufferIsAutoResize())
			, m_FreeOnDestructor(false) {}

	public:
		template <typename ChildBuffer>
		inline void UpdateFromChildBuffer(ChildBuffer& childBuffer) { SetBufferCurrentPos(childBuffer.GetBufferCurrentPos()); m_NoStride = childBuffer.GetNoStride(); }

	public:
		template<typename T> void FastWriteInt	(T i);
		template<typename T> void FastWriteUInt	(T i);
		template<typename T> void FastWriteFloat(T i, FormatDataType floatPrecision = Detail::FLOAT_PRECISION_NOT_SPECIFIED);

		template<typename T> void BasicWriteInt		(T i, ShiftType st = ShiftType::Default, FormatDataType shift = Detail::SHIFT_NOT_SPECIFIED, ShiftPrint sp = ShiftPrint::Default);
		template<typename T> void BasicWriteUInt	(T i, ShiftType st = ShiftType::Default, FormatDataType shift = Detail::SHIFT_NOT_SPECIFIED, ShiftPrint sp = ShiftPrint::Default);
		template<typename T> void BasicWriteFloat	(T i, FormatDataType floatPrecision = Detail::FLOAT_PRECISION_NOT_SPECIFIED, ShiftType st = ShiftType::Nothing, FormatDataType shift = Detail::SHIFT_NOT_SPECIFIED, ShiftPrint sp = ShiftPrint::Space);

		template<typename T> void BasicWriteIntAsBin	(T i, FormatDataType digitSize = Detail::DIGIT_SIZE_NOT_SPECIFIED, ShiftType st = ShiftType::Nothing, FormatDataType shift = Detail::SHIFT_NOT_SPECIFIED, ShiftPrint sp = ShiftPrint::Space, bool trueValue = false);
		template<typename T> void BasicWriteIntAsHex	(T i, FormatDataType digitSize = Detail::DIGIT_SIZE_NOT_SPECIFIED, ShiftType st = ShiftType::Nothing, FormatDataType shift = Detail::SHIFT_NOT_SPECIFIED, ShiftPrint sp = ShiftPrint::Space, bool trueValue = false, Detail::PrintStyle valueDes = PrintStyle::Nothing);
		template<typename T> void BasicWriteIntAsOct	(T i, FormatDataType digitSize = Detail::DIGIT_SIZE_NOT_SPECIFIED, ShiftType st = ShiftType::Nothing, FormatDataType shift = Detail::SHIFT_NOT_SPECIFIED, ShiftPrint sp = ShiftPrint::Space, bool trueValue = false);


	public:
		template<typename T, typename FormatDataCharType> void WriteIntFormatData	(T i, const FormatData<FormatDataCharType>& formatData);
		template<typename T, typename FormatDataCharType> void WriteUIntFormatData	(T i, const FormatData<FormatDataCharType>& formatData);
		template<typename T, typename FormatDataCharType> void WriteFloatFormatData	(T i, const FormatData<FormatDataCharType>& formatData);

	public:
		// Basic types
		template<typename T> void BasicWriteType(T i) {}

		inline void BasicWriteType(const std::int8_t i)		{ FastWriteInt(i); }
		inline void BasicWriteType(const std::uint8_t i)	{ FastWriteUInt(i); }
		inline void BasicWriteType(const std::int16_t i)	{ FastWriteInt(i); }
		inline void BasicWriteType(const std::uint16_t i)	{ FastWriteUInt(i); }
		inline void BasicWriteType(const std::int32_t i)	{ FastWriteInt(i); }
		inline void BasicWriteType(const std::uint32_t i)	{ FastWriteUInt(i); }
		inline void BasicWriteType(const std::int64_t i)	{ FastWriteInt(i); }
		inline void BasicWriteType(const std::uint64_t i)	{ FastWriteUInt(i); }

		inline void BasicWriteType(const float i)		{ FastWriteFloat(i); }
		inline void BasicWriteType(const double i)		{ FastWriteFloat(i); }
		inline void BasicWriteType(const long double i) { FastWriteFloat(i); }

		inline void BasicWriteType(const char i)		{ PushBack(i); }
		inline void BasicWriteType(const wchar_t i)		{ PushBack(i); }
		inline void BasicWriteType(const char16_t i)	{ PushBack(i); }
		inline void BasicWriteType(const char32_t i)	{ PushBack(i); }

		template<std::size_t SIZE> inline void BasicWriteType(const char (&i)[SIZE])		{ WriteCharArray(i); }
		template<std::size_t SIZE> inline void BasicWriteType(const wchar_t (&i)[SIZE])		{ WriteCharArray(i); }
		template<std::size_t SIZE> inline void BasicWriteType(const char16_t (&i)[SIZE])	{ WriteCharArray(i); }
		template<std::size_t SIZE> inline void BasicWriteType(const char32_t (&i)[SIZE])	{ WriteCharArray(i); }

		template<typename CharType> inline void BasicWriteType(const std::basic_string_view<CharType>& i) { WriteStringView(i); }

	public:
		inline bool CanMoveForward()									{ if (m_CurrentPos < m_BufferEnd)			return true; return CheckResize(); }
		inline bool CanMoveForward(const std::size_t count) 			{ if (m_CurrentPos + count <= m_BufferEnd)	return true; return CheckResize(count); }

		inline bool CheckResize(const std::size_t addToBufferSize = 0) {
			if (!m_BufferAutoResize)	return false;
			return						AddToBufferSize(addToBufferSize);
		}

		bool AddToBufferSize(const std::size_t addToBufferSize = 0) {
			const std::size_t targetBufferSize = addToBufferSize + m_BufferSize;

			const std::size_t step = m_CurrentPos - m_Buffer;

			const CharBuffer* oldBuffer = m_Buffer;
			const std::size_t oldSize = m_BufferSize;
			
			while(m_BufferSize < targetBufferSize)
				m_BufferSize *= GROW_UP_BUFFER_SIZE;

			m_Buffer = new CharBuffer[m_BufferSize];
			if (m_Buffer == nullptr) return false;

			m_CurrentPos = m_Buffer + step;
			m_BufferEnd = m_Buffer + m_BufferSize;

			std::memcpy(m_Buffer, oldBuffer, oldSize);

			delete[] oldBuffer;

			if constexpr (DEBUG_RESIZE)
				std::cout << "Resize from " << oldSize << " to " << m_BufferSize << std::endl;

			return true;
		}

		/////---------- Buffer Commands ----------/////
		inline void Set(const CharBuffer c)								{ *m_CurrentPos = c; }
		inline void PushBack(const CharBuffer c)						{ if (CanMoveForward()) *m_CurrentPos++ = c; }
		inline void PushReverse(const CharBuffer c)						{ if (CanMoveBackward()) *m_CurrentPos-- = c; }
		inline void PushBackNoCheck(const CharBuffer c)					{ *m_CurrentPos++ = c; }
		inline void PushReverseNoCheck(const CharBuffer c)				{ *m_CurrentPos-- = c; }

		inline void PushBack(const CharBuffer c, std::size_t count)			{ if (CanMoveForward(count)) while (count-- > 0) PushBackNoCheck(c); }
		inline void PushReverse(const CharBuffer c, std::size_t count)		{ if (CanMoveBackward(count)) while (count-- > 0) PushReverseNoCheck(c); }

		inline void PushEndChar()										{ PushBack('\0'); }
		inline void PushEndCharToTheEnd() 								{ *(m_BufferEnd - 1) = 0; }
		inline void AddSpaces(const std::size_t count)					{ for (std::size_t i = count; i > 0 && CanMoveForward(); --i) PushBackNoCheck(' '); }

		template<typename CharStr, std::size_t SIZE>	inline void WriteCharArray(const CharStr(&str)[SIZE])					{ WriteCharPt(str, SIZE); }
		template<typename CharStr>						inline void WriteStringView(const std::basic_string_view<CharStr>& str)	{ WriteCharPt(str.data(), str.size()); }
		template<typename CharStr>	inline void WriteCharPt(const CharStr* str)						{ while (*str != 0) PushBack(*str++); }
		template<typename CharStr>	inline void WriteCharPt(const CharStr* str, std::size_t size)	{
			if (CanMoveForward(size))
				while (size-- != 0 && *str != 0)
					PushBackNoCheck(*str++);
		}


		/////---------- Buffer Commands Indent ----------/////
		inline void SetIndent(const CharBuffer c, const std::size_t indent)								{ Set(c);  if (c == '\n') PushBack(' ', indent); }
		inline void PushBackIndent(const CharBuffer c, const std::size_t indent)						{ PushBack(c);  if (c == '\n') PushBack(' ', indent); }

		template<typename CharStr>	inline void WriteCharPtIndent(const CharStr* str, const std::size_t indent) {
			while (*str != 0)
			{
				if (*str == '\n')
				{
					PushBack('\n');
					PushBack(' ', indent);
				}
				else
					PushBack(*str++);
			}
		}
		template<typename CharStr>	inline void WriteCharPtIndent(const CharStr* str, std::size_t size, const std::size_t indent) {
			if (CanMoveForward(size))
				while (size-- != 0 && *str != 0)
				{
					if (*str == '\n')
					{
						PushBack('\n');
						PushBack(' ', indent);
					}
					else
						PushBackNoCheck(*str++);
				}
		}

		// Utils
	private:
		template<typename T>
		static inline FormatDataType GetNumberOfDigitDec(T value) {
			if constexpr (std::numeric_limits<T>::is_signed) {
				if (value < 0)	value = -value;
			}
			FormatDataType nb = 0;
			while(true) {
				if (value < 10)
					return nb + 1;
				else if(value < 100)
					return nb + 2;
				else if (value < 1000)
					return nb + 3;
				else if (value < 10000)
					return nb + 4;
				else {
					value /= (T)10000;
					nb += 4;
				}
			}
		}
		
		// Shift
		template<typename T>
		inline void PrintShift(Detail::ShiftPrint sp, T shift) {
			if (sp == Detail::ShiftPrint::Space)		{ while (shift-- > 0) PushBack(' '); }
			else if (sp == Detail::ShiftPrint::Zeros)	{ while (shift-- > 0) PushBack('0'); }
		}

		template<typename T>
		inline void PrintShiftCenterBegin(const Detail::ShiftType st, const Detail::ShiftPrint sp, T& shift) {
			if(st == Detail::ShiftType::Center)
			{
				FormatDataType shift_ = shift / 2;
				PrintShift(Detail::ShiftPrint::Space, shift - shift_);
				shift = shift_;
			}
		}

		template<typename T>
		inline void PrintShiftCenterEnd(const Detail::ShiftType st, const Detail::ShiftPrint sp, const T shift) {
			if (st == Detail::ShiftType::Center)
				PrintShift(Detail::ShiftPrint::Space, shift);
		}

		template<typename T>
		inline void PrintShiftRight(const Detail::ShiftType st, const Detail::ShiftPrint sp, const T shift) {
			if (st == Detail::ShiftType::Right)
				PrintShift(sp, shift);
		}

		template<typename T>
		inline void PrintShiftLeft(const Detail::ShiftType st, const Detail::ShiftPrint sp, const T shift) {
			if (st == Detail::ShiftType::Left)
				PrintShift(sp, shift);
		}

		template<typename T>
		inline void PrintShiftBegin(const Detail::ShiftType st, const Detail::ShiftPrint sp, T& shift) {
			PrintShiftCenterBegin(st, sp, shift);
			PrintShiftRight(st, sp, shift);
		}

		template<typename T>
		inline void PrintShiftEnd(const Detail::ShiftType st, const Detail::ShiftPrint sp, T& shift) {
			PrintShiftLeft(st, sp, shift);
			PrintShiftCenterEnd(st, sp, shift);
		}
	};


	template <typename CharBuffer>
	class BasicFormatterMemoryBufferOutCopy {
	public:
		BasicFormatterMemoryBufferOutCopy(BasicFormatterMemoryBufferOut<CharBuffer>& bufferOut)
			: m_Buffer(bufferOut.GetBuffer())
			, m_Size(bufferOut.GetBufferCurrentSize())
			, m_FreeOnDestructor(true)
		{
			bufferOut.DoNotFreeOnDestructor();
		}

		BasicFormatterMemoryBufferOutCopy(BasicFormatterMemoryBufferOutCopy<CharBuffer>& bufferOutCopy)
			: m_Buffer(bufferOutCopy.GetBuffer())
			, m_Size(bufferOutCopy.GetSize())
			, m_FreeOnDestructor(true)
		{
			bufferOutCopy.DoNotFreeOnDestructor();
		}

		~BasicFormatterMemoryBufferOutCopy() {
			if (m_FreeOnDestructor)
				delete[] m_Buffer;
		}

		operator std::basic_string_view<CharBuffer>() {
			return std::basic_string_view<CharBuffer>(m_Buffer, m_Size);
		}


	public:
		inline const CharBuffer*	GetBuffer() const		{ return m_Buffer; }
		inline std::size_t			GetSize() const			{ return m_Size; }

		inline void DoNotFreeOnDestructor() {
			m_FreeOnDestructor = false;
		}

	private:
		const CharBuffer* const m_Buffer;
		const std::size_t		m_Size;

		bool					m_FreeOnDestructor;
	};
}

