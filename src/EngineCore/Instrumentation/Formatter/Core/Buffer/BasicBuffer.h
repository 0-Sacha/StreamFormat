#pragma once

#include "../Detail.h"

namespace EngineCore::Fmt::Detail {

	template <typename CharBuffer>
	class BasicFormatterMemoryBuffer {

	public:
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
		inline std::size_t			GetBufferCurrentSize() const						{ return m_CurrentPos - m_Buffer; }
		inline void					SetBufferCurrentPos(CharBuffer* const pos)			{ if (pos >= GetBuffer() && pos < GetBufferEnd()) m_CurrentPos = pos; }
		
	public:
		BasicFormatterMemoryBuffer(const std::basic_string_view<typename std::remove_const<CharBuffer>::type> buffer)
			: m_Buffer(buffer.data())
			, m_CurrentPos(buffer.data())
			, m_BufferEnd(buffer.data() + buffer.size())
			, m_BufferSize(buffer.size()) {}

		BasicFormatterMemoryBuffer(CharBuffer *const buffer, const std::size_t size)
			: m_Buffer(buffer)
			, m_CurrentPos(m_Buffer)
			, m_BufferEnd(m_Buffer + size)
			, m_BufferSize(size) {}
		
		BasicFormatterMemoryBuffer(CharBuffer* const buffer, CharBuffer* const bufferCurrentPos, CharBuffer* const bufferEnd, const std::size_t size)
			: m_Buffer(buffer)
			, m_CurrentPos(bufferCurrentPos)
			, m_BufferEnd(m_Buffer + size)
			, m_BufferSize(size) {}

	public:
		// Format
		inline bool CanMoveForward() const							{ return m_CurrentPos < m_BufferEnd; }
		inline bool CanMoveBackward() const							{ return m_CurrentPos > m_Buffer; }
		inline bool CanMoveForward(const std::size_t count) const	{ return m_CurrentPos + count <= m_BufferEnd; }
		inline bool CanMoveBackward(const std::size_t count) const	{ return m_CurrentPos + count >= m_Buffer; }
		inline bool IsNotOutOfBound() const							{ return !CanMoveForward() || !CanMoveBackward(); }
		inline bool IsEnd() const									{ return m_CurrentPos >= m_BufferEnd; }

		inline void CanMoveForwardThrow()								{ if (!CanMoveForward())	throw FormatBufferFull(); }
		inline void CanMoveForwardThrow(const std::size_t count)		{ if (!CanMoveForward())	throw FormatBufferFull(); }
		inline void CanMoveBackwardThrow() const						{ if (!CanMoveBackward())	throw FormatBufferIndex(); }
		inline void CanMoveBackwardThrow(const std::size_t count)		{ if (!CanMoveBackward())	throw FormatBufferIndex(); }
		inline void IsNotOutOfBoundThrow() const						{ if (!IsNotOutOfBound())	throw FormatBufferIndex(); }
		inline void IsEndThrow() const									{ if (!IsEnd())				throw FormatBufferEnd(); }

		// Format base commands
		inline void Forward()										{ if (CanMoveForward()) ++m_CurrentPos; }
		inline void ForwardNoCheck()								{ ++m_CurrentPos; }
		inline void Backward()										{ if (CanMoveBackward()) --m_CurrentPos; }
		inline void BackwardNoCheck()								{ --m_CurrentPos; }
		template<typename Int> inline void Forward(const Int size)	{ m_CurrentPos += size; if (!CanMoveForward()) m_CurrentPos = m_BufferEnd; }
		template<typename Int> inline void Backward(const Int size) { m_CurrentPos -= size; if (!CanMoveBackward()) m_CurrentPos = m_Buffer; }

		inline CharBuffer Get() const								{ return *m_CurrentPos; }
		inline CharBuffer GetAndForward()							{ return CanMoveForward() ? *m_CurrentPos++ : '\0'; }
		inline CharBuffer GetAndForwardNoCheck()					{ return *m_CurrentPos++; }
		inline CharBuffer GetAndBackward()							{ return CanMoveBackward() ? *m_CurrentPos-- : '\0'; }
		inline CharBuffer GetAndBackwardNoCheck()					{ return *m_CurrentPos--; }
		inline CharBuffer GetNext() const							{ return CanMoveForward() ? *(m_CurrentPos + 1) : '\0'; }
		inline CharBuffer GetNextNoCheck() const					{ return *(m_CurrentPos + 1); }
	};
}