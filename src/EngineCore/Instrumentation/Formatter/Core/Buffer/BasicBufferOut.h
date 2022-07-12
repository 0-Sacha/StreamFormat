#pragma once

#include "BasicBuffer.h"

namespace EngineCore::FMT::Detail {

	template <typename CharBuffer>
	class BasicFormatterMemoryBufferOutCopy;

	template <typename CharBuffer>
	class BasicFormatterMemoryBufferOut : public BasicFormatterMemoryBuffer<CharBuffer> {

	protected:
		using Base = BasicFormatterMemoryBuffer<CharBuffer>;
		using Base::m_Buffer;
		using Base::m_BufferEnd;
		using Base::m_BufferSize;
		using Base::m_CurrentPos;

	public:
		using typename Base::StringView;

	public:
		using CharBufferType = CharBuffer;

		using Base::GetBuffer;
		using Base::GetBufferCurrentPos;
		using Base::GetBufferEnd;
		using Base::GetBufferSize;
		using Base::GetBufferCurrentSize;
		using Base::SetBufferCurrentPos;
		using Base::SetParentBufferForUpdate;

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

		using Base::UpdateFromChlid;

	public:
		static constexpr std::size_t	DEFAULT_BEGIN_SIZE	= 512;
		static constexpr std::size_t	GROW_UP_BUFFER_SIZE = 2;
		static constexpr bool			DEBUG_RESIZE		= true;

		static constexpr char			UPPER_HEX[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
		static constexpr char			LOWER_HEX[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	
	private:
		bool				m_BufferAutoResize;
		bool				m_FreeOnDestructor;

		std::size_t 		m_NoStride;
		std::size_t 		m_Indent;

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


		inline std::size_t GetNoStride() const					{ return m_NoStride; }
		inline void AddNoStride(const std::size_t noStride)		{ m_NoStride += noStride; }

		inline std::size_t GetIndent() const					{ return m_Indent; }
		inline void SetIndent(const std::size_t indent) 		{ m_Indent = indent; }
		inline void AddIndent(const std::size_t indent) 		{ m_Indent += indent; }
		void SetIndent() 										{ m_Indent = GetBufferCurrentSize() - GetNoStride(); }

	private:
		friend BasicFormatterMemoryBufferOutCopy<CharBuffer>;
		inline void					DoNotFreeOnDestructor()					{ m_FreeOnDestructor = false; }

	public:
		BasicFormatterMemoryBufferOut(CharBuffer* const buffer, const std::size_t bufferSize)
			: Base(buffer, bufferSize)
			, m_BufferAutoResize(false)
			, m_FreeOnDestructor(false)
			, m_NoStride(0)
			, m_Indent(0)
		{
			PushEndCharToTheEnd();
		}

		BasicFormatterMemoryBufferOut(const std::size_t beginSize = DEFAULT_BEGIN_SIZE)
			: Base(new CharBuffer[beginSize], beginSize)
			, m_BufferAutoResize(true)
			, m_FreeOnDestructor(true)
			, m_NoStride(0)
			, m_Indent(0)
		{
			PushEndCharToTheEnd();
		}

		template <typename ParentBuffer>
		explicit BasicFormatterMemoryBufferOut(ParentBuffer& parentBuffer)
			: Base(parentBuffer.GetBuffer(), parentBuffer.GetBufferCurrentPos(), parentBuffer.GetBufferEnd(), parentBuffer.GetBufferSize())
		{
			SetParentBufferForUpdate(&parentBuffer);
		}

		~BasicFormatterMemoryBufferOut() {
			// Should call the destructo but doesn't compile : BasicFormatterMemoryBuffer<CharBuffer>::~BasicFormatterMemoryBuffer();
			UpdateFromChlid();

			if (m_FreeOnDestructor)
				delete[] m_Buffer;
		}

	public:
		template<typename T> void FastWriteInt	(T i);
		template<typename T> void FastWriteUInt	(T i);
		template<typename T> void FastWriteFloat(T i, FloatPrecision floatPrecision = FloatPrecision{});

		template<typename T> void BasicWriteInt		(T i, ShiftType st = ShiftType::Default, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{});
		template<typename T> void BasicWriteUInt	(T i, ShiftType st = ShiftType::Default, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{});
		template<typename T> void BasicWriteFloat	(T i, FloatPrecision floatPrecision = FloatPrecision{}, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{});

		template<typename T> void BasicWriteIntAsBin	(T i, DigitSize digitSize = DigitSize{}, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{}, bool trueValue = false);
		template<typename T> void BasicWriteIntAsHex	(T i, DigitSize digitSize = DigitSize{}, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{}, bool trueValue = false, Detail::PrintStyle valueDes = PrintStyle::Nothing);
		template<typename T> void BasicWriteIntAsOct	(T i, DigitSize digitSize = DigitSize{}, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{}, bool trueValue = false);


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
		inline void SetChar(const CharBuffer c)							{ *m_CurrentPos = c; }
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
		inline void NewLineIndent()											{ PushBack('\n'); PushBack(' ', m_Indent); }

		inline void SetCharIndent(const CharBuffer c)						{ SetChar(c);  if (c == '\n') PushBack(' ', m_Indent); }
		inline void PushBackIndent(const CharBuffer c)						{ PushBack(c);  if (c == '\n') PushBack(' ', m_Indent); }

		template<typename CharStr>	inline void WriteCharPtIndent(const CharStr* str) {
			while (*str != 0)
			{
				if (*str == '\n')
				{
					PushBack('\n');
					PushBack(' ', m_Indent);
				}
				else
					PushBack(*str++);
			}
		}
		template<typename CharStr>	inline void WriteCharPtIndent(const CharStr* str, std::size_t size) {
			if (CanMoveForward(size))
				while (size-- != 0 && *str != 0)
				{
					if (*str == '\n')
					{
						PushBack('\n');
						PushBack(' ', m_Indent);
					}
					else
						PushBackNoCheck(*str++);
				}
		}

		// Utils
	private:
		template<typename T>
		static inline DataType GetNumberOfDigitDec(T value) {
			if constexpr (std::numeric_limits<T>::is_signed) {
				if (value < 0)	value = -value;
			}
			DataType nb = 0;
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
		inline void PrintShiftCenterBegin(const Detail::ShiftType st, const Detail::ShiftPrint sp, T& shift) {
			if(st == Detail::ShiftType::Center)
			{
				DataType shift_ = shift / 2;
				PushBack(sp.Before, shift - shift_);
				shift = shift_;
			}
		}

		template<typename T>
		inline void PrintShiftCenterEnd(const Detail::ShiftType st, const Detail::ShiftPrint sp, const T shift) {
			if (st == Detail::ShiftType::Center)
				PushBack(sp.After, shift);
		}

		template<typename T>
		inline void PrintShiftRightAll(const Detail::ShiftType st, const Detail::ShiftPrint sp, const T shift) {
			if (st == Detail::ShiftType::Right)
				PushBack(sp.Before, shift);
		}

		template<typename T>
		inline void PrintShiftLeftAll(const Detail::ShiftType st, const Detail::ShiftPrint sp, const T shift) {
			if (st == Detail::ShiftType::Left)
				PushBack(sp.After, shift);
		}

		template<typename T>
		inline void PrintShiftBegin(const Detail::ShiftType st, const Detail::ShiftPrint sp, T& shift) {
			PrintShiftCenterBegin(st, sp, shift);
			PrintShiftRightAll(st, sp, shift);
		}

		template<typename T>
		inline void PrintShiftEnd(const Detail::ShiftType st, const Detail::ShiftPrint sp, T& shift) {
			PrintShiftLeftAll(st, sp, shift);
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

		explicit BasicFormatterMemoryBufferOutCopy(BasicFormatterMemoryBufferOutCopy<CharBuffer>& bufferOutCopy)
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

