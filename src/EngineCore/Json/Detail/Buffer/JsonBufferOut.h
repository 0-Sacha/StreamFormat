#pragma once

#include "EngineCore/FMT/Detail/Buffer/BasicBufferOut/BasicBufferOut.h"
#include "EngineCore/FMT/Detail/Buffer/BasicBufferOut/Utils/BufferOutUtils.h"

namespace EngineCore::JSON::Detail
{
    class JsonBufferOut : public EngineCore::FMT::Detail::BasicBufferOut<char>
    {
	protected:
		using Base = EngineCore::FMT::Detail::BasicBufferOut<char>;
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

    public:
		JsonBufferOut()
			: Base()
		{}

        JsonBufferOut(FMT::Detail::BasicBufferManager<char>& bufferManager)
			: Base(bufferManager)
		{}
    };
}
