#pragma once

#include "FMT/Detail/Detail.h"

namespace EngineCore::FMT::Detail {

	template <typename CharBuffer>
	class BasicFormatterMemoryBuffer {

	public:
		using StringView = std::basic_string_view<Detail::GetBaseType<CharBuffer>>;

	protected:
		CharBuffer*			m_Buffer;
		CharBuffer*			m_CurrentPos;
		CharBuffer*			m_BufferEnd;			// Point to the end char of the format
		std::size_t			m_BufferSize;			// Do not count the end char

	protected:
		inline CharBuffer*			GetBuffer()											{ return m_Buffer; }
		inline const CharBuffer*	GetBuffer() const									{ return m_Buffer; }
		inline CharBuffer*			GetBufferCurrentPos()								{ return m_CurrentPos; }
		inline const CharBuffer*	GetBufferCurrentPos() const							{ return m_CurrentPos; }
		inline CharBuffer*			GetBufferEnd()										{ return m_BufferEnd; }
		inline const CharBuffer*	GetBufferEnd() const								{ return m_BufferEnd; }
		inline std::size_t			GetBufferSize() const								{ return m_BufferSize; }
		inline std::size_t			GetBufferSizeLeft() const							{ return m_BufferEnd - m_CurrentPos; }
		inline std::size_t			GetBufferCurrentSize() const						{ return m_CurrentPos - m_Buffer; }
		inline void					SetBufferCurrentPos(CharBuffer* const pos)			{ if (pos >= GetBuffer() && pos < GetBufferEnd()) m_CurrentPos = pos; }

	public:
		explicit BasicFormatterMemoryBuffer()
			: m_Buffer(nullptr)
			, m_CurrentPos(nullptr)
			, m_BufferEnd(nullptr)
			, m_BufferSize(0)
		{}

		explicit BasicFormatterMemoryBuffer(CharBuffer *const buffer, const std::size_t size)
			: m_Buffer(buffer)
			, m_CurrentPos(m_Buffer)
			, m_BufferEnd(m_Buffer + size)
			, m_BufferSize(size)
		{}

	public:
		void SetBuffer(CharBuffer *const buffer, const std::size_t size)
		{
 			m_Buffer = buffer;
			m_CurrentPos = buffer;
			m_BufferEnd = buffer + size;
			m_BufferSize = size;
		}

		void SetBuffer(const std::basic_string_view<Detail::GetBaseType<CharBuffer>>& buffer)		{ SetBuffer(buffer.data(), buffer.size()); }
		void SetCurrentPos(CharBuffer *const bufferCurrentPos)										{ m_CurrentPos = bufferCurrentPos; }

	public:
		// Format
		inline bool CanMoveForward() const							{ return m_CurrentPos + 1 < m_BufferEnd; }
		inline bool CanMoveForward(const std::size_t count) const	{ return m_CurrentPos + count < m_BufferEnd; }

		inline bool CanMoveBackward() const							{ return m_CurrentPos - 1 >= m_Buffer; }
		inline bool CanMoveBackward(const std::size_t count) const	{ return m_CurrentPos - count >= m_Buffer; }
		inline bool IsNotOutOfBound() const							{ return m_CurrentPos < m_Buffer || m_CurrentPos >= m_BufferEnd; }
		inline bool IsEnd() const									{ return m_CurrentPos >= m_BufferEnd; }

		inline void CanMoveForwardThrow() const							{ if (CanMoveForward())			return; throw FMTBufferFull(); }
		inline void CanMoveForwardThrow(const std::size_t count) const	{ if (CanMoveForward(count))	return; throw FMTBufferFull(); }
		inline void CanMoveBackwardThrow() const						{ if (CanMoveBackward())		return; throw FMTBufferIndexOutOfRange(); }
		inline void CanMoveBackwardThrow(const std::size_t count)		{ if (CanMoveBackward(count))	return; throw FMTBufferIndexOutOfRange(); }
		inline void IsNotOutOfBoundThrow() const						{ if (IsNotOutOfBound())		return; throw FMTBufferIndexOutOfRange(); }
		inline void IsEndThrow() const									{ if (IsEnd())					return; throw FMTBufferEnd(); }

		// Format base commands
		inline void Forward()										{ CanMoveForwardThrow(); ++m_CurrentPos; }
		inline void Forward(const std::size_t count)				{ CanMoveForwardThrow(count); m_CurrentPos += count; }
		inline void ForwardNoCheck()								{ ++m_CurrentPos; }
		inline void ForwardNoCheck(const std::size_t count)			{ m_CurrentPos += count; }
		inline void ForwardNoThrow()								{ if (CanMoveForward()) ++m_CurrentPos; }
		inline void ForwardNoThrow(const std::size_t count)			{ if (CanMoveForward(count)) m_CurrentPos += count; }

		inline void Backward()										{ CanMoveBackwardThrow(); --m_CurrentPos; }
		inline void Backward(const std::size_t count)				{ CanMoveBackwardThrow(count); m_CurrentPos -= count; }
		inline void BackwardNoCheck()								{ --m_CurrentPos; }
		inline void BackwardNoCheck(const std::size_t count)		{ m_CurrentPos -= count; }
		inline void BackwardNoThrow()								{ if (CanMoveBackward()) --m_CurrentPos; }
		inline void BackwardNoThrow(const std::size_t count)		{ if (CanMoveBackward(count)) m_CurrentPos -= count; }

		inline CharBuffer Get() const								{ return *m_CurrentPos; }
		inline CharBuffer GetAndForward()							{ CanMoveForwardThrow(); return *m_CurrentPos++; }
		inline CharBuffer GetAndForwardNoCheck()					{ return *m_CurrentPos++; }
		inline CharBuffer GetAndBackward()							{ CanMoveBackwardThrow(); return *m_CurrentPos--; }
		inline CharBuffer GetAndBackwardNoCheck()					{ return *m_CurrentPos--; }
		inline CharBuffer GetNext() const							{ CanMoveForwardThrow(); return *(m_CurrentPos + 1); }
		inline CharBuffer GetNextNoCheck() const					{ return *(m_CurrentPos + 1); }
		inline CharBuffer GetPrev() const							{ CanMoveBackwardThrow(); return *(m_CurrentPos - 1); }
		inline CharBuffer GetPrevNoCheck() const					{ return *(m_CurrentPos - 1); }
	};
}