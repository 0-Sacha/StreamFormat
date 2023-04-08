#pragma once

#include "ProjectCore/FMT/Detail/Detail.h"

namespace ProjectCore::FMT::Detail
{
    template <typename CharBuffer>
    class BasicBuffer
    {
    public:
        using StringView = std::basic_string_view<Detail::GetBaseType<CharBuffer>>;

    protected:
        CharBuffer*            m_Buffer;
        CharBuffer*            m_CurrentPos;
        CharBuffer*            m_BufferEnd;            // Point to the end char of the format

    protected:
        inline CharBuffer*          GetBuffer() noexcept                            { return m_Buffer; }
        inline const CharBuffer*    GetBuffer() noexcept const                      { return m_Buffer; }
        inline CharBuffer*          GetBufferCurrentPos() noexcept                  { return m_CurrentPos; }
        inline const CharBuffer*    GetBufferCurrentPos() noexcept const            { return m_CurrentPos; }
        inline CharBuffer*          GetBufferEnd() noexcept                         { return m_BufferEnd; }
        inline const CharBuffer*    GetBufferEnd() noexcept const                   { return m_BufferEnd; }
        inline std::size_t          GetBufferSize() noexcept const                  { return static_cast<std::size_t>(m_BufferEnd - m_Buffer); }
        inline std::size_t          GetBufferSizeLeft() noexcept const              { return static_cast<std::size_t>(m_BufferEnd - m_CurrentPos); }
        inline std::size_t          GetBufferCurrentSize() noexcept const           { return static_cast<std::size_t>(m_CurrentPos - m_Buffer); }
        inline std::size_t          GetBufferRemainingSize() noexcept const         { return static_cast<std::size_t>(m_BufferEnd - m_CurrentPos); }
        
        inline void                 SetBufferCurrentPos(CharBuffer* const pos)      { if (pos >= GetBuffer() && pos <= GetBufferEnd()) m_CurrentPos = pos; }

    public:
        BasicBuffer() noexcept
            : m_Buffer(nullptr)
            , m_CurrentPos(nullptr)
            , m_BufferEnd(nullptr)
        {}

        BasicBuffer(CharBuffer *const buffer, const std::size_t size) noexcept
            : m_Buffer(buffer)
            , m_CurrentPos(m_Buffer)
            , m_BufferEnd(m_Buffer + size)
        {}

        virtual ~BasicBuffer() noexcept = default;

    public:
        template <typename OtherBuffer>
        void ReloadBuffer(OtherBuffer& buffer) noexcept
        {
            SetBuffer(buffer.GetBuffer(), buffer.GetBufferSize());
            SetBufferCurrentPos(buffer.GetBufferCurrentPos());
        }

        void SetBuffer(CharBuffer *const buffer, const std::size_t size) noexcept
        {
            m_Buffer = buffer;
            m_CurrentPos = buffer;
            m_BufferEnd = buffer + size;
        }

        void SetBuffer(const std::basic_string_view<Detail::GetBaseType<CharBuffer>>& buffer) noexcept
        {
            SetBuffer(buffer.data(), buffer.size());
        }

    public:
        // Format
        inline bool CanMoveForward() noexcept const                         { return m_CurrentPos + 1 <= m_BufferEnd; }
        inline bool CanMoveForward(const std::size_t count) noexcept const  { return m_CurrentPos + count <= m_BufferEnd; }

        inline bool CanMoveBackward() noexcept const                        { return m_CurrentPos - 1 >= m_Buffer; }
        inline bool CanMoveBackward(const std::size_t count) noexcept const { return m_CurrentPos - count >= m_Buffer; }
        inline bool IsNotOutOfBound() noexcept const                        { return m_CurrentPos < m_Buffer || m_CurrentPos >= m_BufferEnd; }
        inline bool IsEndSimple() noexcept const                            { return m_CurrentPos >= m_BufferEnd; }
        inline bool IsEnd() noexcept const                                  { return IsEndSimple() || Get() == 0; }

        inline void CanMoveForwardThrow() const                         { if (CanMoveForward())            return; throw FMTBufferFull{}; }
        inline void CanMoveForwardThrow(const std::size_t count) const  { if (CanMoveForward(count))    return; throw FMTBufferFull{}; }
        inline void CanMoveBackwardThrow() const                        { if (CanMoveBackward())        return; throw FMTBufferIndexOutOfRange{}; }
        inline void CanMoveBackwardThrow(const std::size_t count)       { if (CanMoveBackward(count))    return; throw FMTBufferIndexOutOfRange{}; }
        inline void IsNotOutOfBoundThrow() const                        { if (IsNotOutOfBound())        return; throw FMTBufferIndexOutOfRange{}; }
        inline void IsEndSimpleThrow() const                            { if (IsEndSimple())            return; throw FMTBufferEnd{}; }
        inline void IsEndThrow() const                                  { if (IsEnd())                    return; throw FMTBufferEnd{}; }

        // Format base commands
        inline void Forward()                                           { CanMoveForwardThrow(); ++m_CurrentPos; }
        inline void Forward(const std::size_t count)                    { CanMoveForwardThrow(count); m_CurrentPos += count; }
        inline void ForwardNoCheck() noexcept                           { ++m_CurrentPos; }
        inline void ForwardNoCheck(const std::size_t count) noexcept    { m_CurrentPos += count; }
        inline bool ForwardNoThrow() noexcept                           { if (CanMoveForward()) { ++m_CurrentPos; return true; } return false; }
        inline bool ForwardNoThrow(const std::size_t count) noexcept    { if (CanMoveForward(count)) { m_CurrentPos += count; return true; } return false; }

        inline void Backward()                                          { CanMoveBackwardThrow(); --m_CurrentPos; }
        inline void Backward(const std::size_t count)                   { CanMoveBackwardThrow(count); m_CurrentPos -= count; }
        inline void BackwardNoCheck() noexcept                          { --m_CurrentPos; }
        inline void BackwardNoCheck(const std::size_t count) noexcept   { m_CurrentPos -= count; }
        inline bool BackwardNoThrow() noexcept                          { if (CanMoveBackward()) { --m_CurrentPos; return true; } return false; }
        inline bool BackwardNoThrow(const std::size_t count) noexcept   { if (CanMoveBackward(count)) { m_CurrentPos -= count; return true; } return false; }

        inline void Reserve(const std::size_t count)            { Forward(count); Backward(); }

        inline CharBuffer Get() noexcept const                  { return *m_CurrentPos; }
        inline CharBuffer GetAndForward()                       { CanMoveForwardThrow(); return *m_CurrentPos++; }
        inline CharBuffer GetAndForwardNoCheck() noexcept       { return *m_CurrentPos++; }
        inline CharBuffer GetAndBackward()                      { CanMoveBackwardThrow(); return *m_CurrentPos--; }
        inline CharBuffer GetAndBackwardNoCheck() noexcept      { return *m_CurrentPos--; }
        inline CharBuffer GetNext() const                       { CanMoveForwardThrow(); return *(m_CurrentPos + 1); }
        inline CharBuffer GetNextNoCheck() noexcept const       { return *(m_CurrentPos + 1); }
        inline CharBuffer GetPrev() const                       { CanMoveBackwardThrow(); return *(m_CurrentPos - 1); }
        inline CharBuffer GetPrevNoCheck() noexcept const       { return *(m_CurrentPos - 1); }


        
    };
}
