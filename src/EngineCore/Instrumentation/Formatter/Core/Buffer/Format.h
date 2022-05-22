#pragma once

#include "BasicBufferIn.h"

namespace EngineCore::Instrumentation::FMT::Detail {
	template <typename CharFormat>
	class FormatterMemoryFormat : public BasicFormatterMemoryBufferIn<CharFormat> {

	private:
		using Base = BasicFormatterMemoryBuffer<const CharBuffer>;
		using Base::m_Buffer;
		using Base::m_BufferEnd;
		using Base::m_BufferSize;
		using Base::m_CurrentPos;

	public:
		using Base::StringView;
		using Base::CharBuffer;

	public:
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
		using CharFormatType = CharFormat;

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