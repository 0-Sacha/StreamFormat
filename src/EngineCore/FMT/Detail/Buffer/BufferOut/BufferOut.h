#pragma once

#include "FMT/Detail/Buffer/BasicBuffer.h"
#include "BufferManager/DynamicBufferManager.h"
#include "BufferManager/StaticBufferManager.h"
#include "BufferManager/GivenBufferManager.h"

namespace EngineCore::FMT::Detail {

	template <typename CharBuffer>
	class BasicFormatterMemoryBufferOut : public BasicFormatterMemoryBuffer<CharBuffer> {
	protected:
		using Base = BasicFormatterMemoryBuffer<CharBuffer>;
		using Base::m_Buffer;
		using Base::m_BufferEnd;
		using Base::m_BufferSize;
		using Base::m_CurrentPos;
		using Base::m_ParentBuffer;

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

		using Base::SetBuffer;
		using Base::SetCurrentPos;

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
		using Base::ForwardNoThrow;
		using Base::ForwardNoCheckNoThrow;
		using Base::BackwardNoThrow;
		using Base::BackwardNoCheckNoThrow;

		using Base::Get;
		using Base::GetAndForward;
		using Base::GetAndForwardNoCheck;
		using Base::GetAndBackward;
		using Base::GetAndBackwardNoCheck;
		using Base::GetNext;
		using Base::GetNextNoCheck;

		using Base::UpdateFromChlid;

	public:
		static constexpr char			UPPER_HEX[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
		static constexpr char			LOWER_HEX[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	
	private:
		BasicBufferManager<CharBuffer>& m_BufferManager;
		std::size_t 					m_NoStride;
		std::size_t 					m_Indent;

	public:
		inline BasicBufferManager<CharBuffer>& GetBufferManager() 				{ return m_BufferManager; }
		inline const BasicBufferManager<CharBuffer>& GetBufferManager() const 	{ return m_BufferManager; }

		inline std::size_t GetNoStride() const					{ return m_NoStride; }
		inline void AddNoStride(const std::size_t noStride)		{ m_NoStride += noStride; }

		inline std::size_t GetIndent() const					{ return m_Indent; }
		inline void SetIndent(const std::size_t indent) 		{ m_Indent = indent; }
		inline void AddIndent(const std::size_t indent) 		{ m_Indent += indent; }
		inline void RemoveIndent(const std::size_t indent) 		{ m_Indent -= indent; }
		void SetIndent() 										{ m_Indent = GetBufferCurrentSize() - GetNoStride(); }

	public:
		BasicFormatterMemoryBufferOut(BasicBufferManager<CharBuffer>& bufferManager)
			: Base()
			, m_BufferManager(bufferManager)
			, m_NoStride(0)
			, m_Indent(0)
		{
			m_BufferManager.BeginContext();
			SetBuffer(m_BufferManager.GetBuffer(), m_BufferManager.GetBufferSize());
			SetCurrentPos(m_BufferManager.GetBuffer());
		}

		template <typename ParentBuffer>
		explicit BasicFormatterMemoryBufferOut(ParentBuffer& parentBuffer)
			: Base()
			, m_BufferManager(parentBuffer.GetBufferManager())
			, m_NoStride(parentBuffer.GetNoStride())
			, m_Indent(parentBuffer.GetIndent())
		{
			SetParentBufferForUpdate(&parentBuffer);
			SetBuffer(m_BufferManager.GetBuffer(), m_BufferManager.GetBufferSize());
			SetCurrentPos(parentBuffer.GetBufferCurrentPos());
		}

		~BasicFormatterMemoryBufferOut()
		{
			PushEndChar();

			// This must be, but this do not compile : BasicFormatterMemoryBuffer<CharBuffer>::BasicFormatterMemoryBuffer<CharBuffer>();
			UpdateFromChlid();

			// if not a child
			if (m_ParentBuffer == nullptr)
				m_BufferManager.EndContext(GetBufferCurrentSize() - 1);
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
		template<typename T, typename FormatDataCharBuffer> void WriteIntFormatData	(T i, const FormatData<FormatDataCharBuffer>& formatData);
		template<typename T, typename FormatDataCharBuffer> void WriteUIntFormatData	(T i, const FormatData<FormatDataCharBuffer>& formatData);
		template<typename T, typename FormatDataCharBuffer> void WriteFloatFormatData	(T i, const FormatData<FormatDataCharBuffer>& formatData);

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
		virtual bool RecoveryFunction(const std::size_t count) { return AddSize(count); }

		bool AddSize(const std::size_t count)
		{
			if (m_CurrentPos >= m_BufferEnd)
				std::cout << "Issue, out of bound" << std::endl;
			std::size_t currentSize = GetBufferCurrentSize();
			if (m_BufferManager.AddSize(count) == false)
				return false;
			SetBuffer(m_BufferManager.GetBuffer(), m_BufferManager.GetBufferSize());
			SetBufferCurrentPos(m_BufferManager.GetBuffer() + currentSize);
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
			if(st == Detail::ShiftType::CenterRight || st == Detail::ShiftType::CenterLeft)
			{
				DataType shift_ = shift / 2;
				if (st == Detail::ShiftType::CenterLeft)
					shift_ = (shift + 1) / 2;
				PushBack(sp.Before, shift - shift_);
				shift = shift_;
			}
		}

		template<typename T>
		inline void PrintShiftCenterEnd(const Detail::ShiftType st, const Detail::ShiftPrint sp, const T shift) {
			if (st == Detail::ShiftType::CenterRight || st == Detail::ShiftType::CenterLeft)
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
}