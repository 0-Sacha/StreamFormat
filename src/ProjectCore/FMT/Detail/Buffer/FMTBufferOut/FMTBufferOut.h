#pragma once

#include "ProjectCore/FMT/Detail/Buffer/BasicBufferOut/BasicBufferOut.h"

namespace ProjectCore::FMT::Detail {

	template <typename CharBuffer>
	class FMTBufferOut : public BasicBufferOut<CharBuffer> {
	protected:
		using Base = BasicBufferOut<CharBuffer>;
		using Base::m_Buffer;
		using Base::m_BufferEnd;
		using Base::m_BufferSize;
		using Base::m_CurrentPos;
		using Base::m_BufferOutManager;
		
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
		using Base::GetBufferRemainingSize;
		using Base::SetBufferCurrentPos;

		using Base::ReloadBuffer;
		using Base::SetBuffer;

		// using Base::SetBufferOutManager;
		using Base::GetBufferOutManager;

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
		using Base::FastWriteInt;
		using Base::FastWriteUInt;
    	using Base::FastWriteFloat;

		using Base::FastWriteCharPtr;
		using Base::FastWriteCharPtrNSize;
		using Base::FastWriteCharArray;
		using Base::FastWriteCharBound;
		using Base::FastWriteStringView;
		using Base::FastWriteString;

	public:
		using Base::BasicWriteType;

	protected:
		using Base::GetNumberOfDigitDec;

	public:
		using Base::AddSize;

		using Base::SetChar;
		using Base::PushBack;
		using Base::PushReverse;
		using Base::PushBackNoCheck;
		using Base::PushReverseNoCheck;

		using Base::PushBackEndChar;
		using Base::AddSpaces;

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
		FMTBufferOut(BasicBufferOutManager<CharBuffer>& BufferOutManager)
			: Base(BufferOutManager)
			, m_NoStride(0)
			, m_Indent(0)
		{}

		~FMTBufferOut() override = default;

	public:
		template<typename T> void WriteInt		(T i, ShiftType st = ShiftType::Default, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{});
		template<typename T> void WriteUInt		(T i, ShiftType st = ShiftType::Default, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{});
		template<typename T> void WriteFloat	(T i, FloatPrecision floatPrecision = FloatPrecision{}, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{});

		template<typename T> void WriteIntAsBin	(T i, DigitSize digitSize = DigitSize{}, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{}, bool trueValue = false);
		template<typename T> void WriteIntAsHex	(T i, DigitSize digitSize = DigitSize{}, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{}, bool trueValue = false, Detail::PrintStyle valueDes = PrintStyle::Nothing);
		template<typename T> void WriteIntAsOct	(T i, DigitSize digitSize = DigitSize{}, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{}, bool trueValue = false);

	public:
		template<typename T, typename FormatDataCharBuffer> void WriteIntFormatData		(T i, const FormatData<FormatDataCharBuffer>& formatData);
		template<typename T, typename FormatDataCharBuffer> void WriteUIntFormatData	(T i, const FormatData<FormatDataCharBuffer>& formatData);
		template<typename T, typename FormatDataCharBuffer> void WriteFloatFormatData	(T i, const FormatData<FormatDataCharBuffer>& formatData);

	public:
		template<typename CharStr>
		inline void WriteCharPtr(const CharStr* str, std::size_t size, ShiftType st = ShiftType::Default, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{});
		
		template<typename CharStr> 						inline void WriteCharPtrNSize(const CharStr* str, ShiftType st = ShiftType::Default, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{}) 						{ WriteStringView(std::basic_string_view<CharStr>(str), st, shift, sp); }
		template<typename CharStr, std::size_t SIZE>	inline void WriteCharArray(const CharStr(&str)[SIZE], ShiftType st = ShiftType::Default, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{})					{ WriteCharPtr(str, str[SIZE - 1] == 0 ? SIZE - 1 : SIZE, st, shift, sp); }
    	template<typename CharStr> 						inline void WriteCharBound(const CharStr* begin, const CharStr* end, ShiftType st = ShiftType::Default, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{}) 	{ WriteCharPtr(begin, end - begin,  st, shift, sp); }
		template<typename CharStr>						inline void WriteStringView(const std::basic_string_view<CharStr>& str, ShiftType st = ShiftType::Default, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{})	{ WriteCharPtr(str.data(), str.size(), st, shift, sp); }
		template<typename CharStr>						inline void WriteString(const std::basic_string<CharStr>& str, ShiftType st = ShiftType::Default, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{})			{ WriteCharPtr(str.data(), str.size(), st, shift, sp); }

	public:
		inline void NewLineIndent()								{ PushBack('\n'); PushBack(' ', m_Indent); }
		inline void SetCharCheckIndent(const CharBuffer c)		{ SetChar(c);  if (c == '\n') PushBack(' ', m_Indent); }
		inline void PushBackCheckIndent(const CharBuffer c)		{ PushBack(c);  if (c == '\n') PushBack(' ', m_Indent); }

		template<typename CharStr>
		inline void WriteIndentCharPtr(const CharStr* str, std::size_t size);

		template<typename CharStr> 						inline void WriteIndentCharPtrNSize(const CharStr* str) 						{ WriteIndentStringView(std::basic_string_view<CharStr>(str)); }
		template<typename CharStr, std::size_t SIZE>	inline void WriteIndentCharArray(const CharStr(&str)[SIZE])						{ WriteIndentCharPtr(str, str[SIZE - 1] == 0 ? SIZE - 1 : SIZE); }
    	template<typename CharStr> 						inline void WriteIndentCharBound(const CharStr* begin, const CharStr* end) 		{ WriteIndentCharPtr(begin, end - begin); }
		template<typename CharStr>						inline void WriteIndentStringView(const std::basic_string_view<CharStr>& str)	{ WriteIndentCharPtr(str.data(), str.size()); }
		template<typename CharStr>						inline void WriteIndentString(const std::basic_string<CharStr>& str)			{ WriteIndentCharPtr(str.data(), str.size()); }

	public:
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

#include "Integer.h"
#include "FromFormatData.h"
#include "String.h"
