#pragma once

#include "EngineCore/FMT/Detail/Buffer/BufferIn/BufferIn.h"

namespace EngineCore::JSON::Detail
{
    class JsonParserBuffer : public EngineCore::FMT::Detail::BasicFormatterMemoryBufferIn<char>
    {
    protected:
        using Base = EngineCore::FMT::Detail::BasicFormatterMemoryBufferIn<char>;
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
		using Base::SetBufferCurrentPos;

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

		using Base::IgnoreSpace;
		using Base::GoTo;
		using Base::GoToForward;

	protected:
		using Base::SkipShiftBeginSpace;
		using Base::SkipShiftEnd;
        
    public:
        explicit JsonParserBuffer()
            : Base()
        {}

		template <std::size_t SIZE>
		explicit JsonParserBuffer(const char (&format)[SIZE])
			: Base(format, SIZE) {}

		explicit JsonParserBuffer(const std::string_view& format)
			: Base(format.data(), format.size()) {}

 		explicit JsonParserBuffer(const char* const buffer, const std::size_t bufferSize)
            : Base(buffer, bufferSize)
        {}

    public:
        inline bool IsJsonObjectBegin() const		{ return IsEqualTo('{', '[', '"') || IsADigit() || IsSame("null", 4); }
        
		inline bool IsJsonStringBegin() const		{ return IsEqualTo('"'); }
        inline bool IsJsonNumberBegin() const		{ return IsADigit(); }
        inline bool IsJsonBooleanBegin() const		{ return IsSame("true", 4) || IsSame("false", 5); }
        inline bool IsJsonStructBegin() const		{ return IsEqualTo('{'); }
        inline bool IsJsonArrayBegin() const		{ return IsEqualTo('['); }
        inline bool IsJsonNullBegin() const			{ return IsSame("null", 4); }
    
	public:
        inline void GoToJsonObject()
		{
			while(IsJsonObjectBegin() == false && IsEnd() == false)
				Forward();
		}
    };
}
