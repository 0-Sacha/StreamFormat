#pragma once

#include "EngineCore/FMT/Detail/Buffer/BasicBufferOut/BasicBufferOut.h"

namespace EngineCore::FMT::Detail {

	template <typename CharBuffer>
	class FMTBufferOut : public BasicBufferOut<CharBuffer> {
	protected:
		using Base = BasicBufferOut<CharBuffer>;
		using Base::m_Buffer;
		using Base::m_BufferEnd;
		using Base::m_BufferSize;
		using Base::m_CurrentPos;
		using Base::m_BufferManager;
		
        using Base::UPPER_HEX;
		using Base::LOWER_HEX;

	public:
		using typename Base::StringView;

	public:
		using Base::GetBuffer;
		using Base::GetBufferCurrentPos;
		using Base::GetBufferEnd;
		using Base::GetBufferSize;
		using Base::GetBufferCurrentSize;
		using Base::SetBufferCurrentPos;

		using Base::ReloadBuffer;
		using Base::SetBuffer;

		// using Base::SetBufferManager;

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
		using Base::GetBufferManager;

		using Base::FastWriteInt;
		using Base::FastWriteUInt;
    	using Base::FastWriteFloat;

		using Base::BasicWriteType;

		using Base::AddSize;

		using Base::SetChar;
		using Base::PushBack;
		using Base::PushReverse;
		using Base::PushBackNoCheck;
		using Base::PushReverseNoCheck;

		using Base::PushEndChar;
		using Base::AddSpaces;
		using Base::WriteCharArray;
		using Base::WriteStringView;
		using Base::WriteCharPtr;
		using Base::Append;

		using Base::GetNumberOfDigitDec;

	private:
		std::size_t 					m_NoStride;
		std::size_t 					m_Indent;

	public:
		inline std::size_t GetNoStride() const					{ return m_NoStride; }
		inline void AddNoStride(const std::size_t noStride)		{ m_NoStride += noStride; }

		inline std::size_t GetIndent() const					{ return m_Indent; }
		inline void SetIndent(const std::size_t indent) 		{ m_Indent = indent; }
		inline void AddIndent(const std::size_t indent) 		{ m_Indent += indent; }
		inline void RemoveIndent(const std::size_t indent) 		{ m_Indent -= indent; }
		void SetIndent() 										{ m_Indent = GetBufferCurrentSize() - GetNoStride(); }

	public:
		FMTBufferOut(BasicBufferManager<CharBuffer>& bufferManager)
			: Base(bufferManager)
			, m_NoStride(0)
			, m_Indent(0)
		{}

	public:
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
		
		// Shift
	public:
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

#include "Integer.h"
#include "FromFormatData.h"
