#pragma once

#include "EngineCore/FMT/Detail/Buffer/BasicBufferIn/BasicBufferIn.h"
#include "EngineCore/FMT/Detail/Buffer/BasicBufferIn/Utils/BufferInUtils.h"

namespace EngineCore::JSON::Detail
{
    class JsonBufferIn : public EngineCore::FMT::Detail::BasicBufferIn<char>
    {
    protected:
        using Base = EngineCore::FMT::Detail::BasicBufferIn<char>;
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

    public:
        explicit JsonBufferIn() : Base() {}

		template <std::size_t SIZE>
		explicit JsonBufferIn(const char (&format)[SIZE])								: Base(format, SIZE) {}
		explicit JsonBufferIn(const std::string_view& format)							: Base(format.data(), format.size()) {}
 		explicit JsonBufferIn(const char* const buffer, const std::size_t bufferSize)	: Base(buffer, bufferSize) {}

    public:
		inline bool IsJsonStringBegin() const		{ return IsEqualTo('"'); }
        inline bool IsJsonNumberBegin() const		{ return IsADigit() || IsEqualTo('.'); }
        inline bool IsJsonBooleanBegin() const		{ return IsEqualTo('t', 'f'); }
        inline bool IsJsonStructBegin() const		{ return IsEqualTo('{'); }
        inline bool IsJsonArrayBegin() const		{ return IsEqualTo('['); }
        inline bool IsJsonNullBegin() const			{ return IsEqualTo('n'); }
    
        inline bool IsJsonObjectBegin() const		{ return IsJsonStringBegin() || IsJsonNumberBegin() || IsJsonBooleanBegin() || IsJsonStructBegin() || IsJsonArrayBegin() || IsJsonNullBegin(); }

	public:
        inline void GoToJsonObject()
		{
			while(IsJsonObjectBegin() == false && IsEnd() == false)
				Forward();
		}
    };
}
