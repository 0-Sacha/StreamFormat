#pragma once

#include "StreamFormat/FMT/Buffer/BasicBuffer.h"
#include "StreamFormat/FMT/Buffer/BufferOutManager/BasicBufferOutManager.h"

namespace StreamFormat::FMT::Detail
{
    template <typename CharBuffer>
    class BasicBufferOut : public BasicBuffer<CharBuffer>
    {
    protected:
        using Base = BasicBuffer<CharBuffer>;
        using Base::m_Buffer;
        using Base::m_BufferEnd;
        using Base::m_CurrentPos;

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

    public:
        // using Base::CanMoveForward;
        // using Base::CanMoveForwardThrow;
        using Base::CanMoveBackward;
        using Base::CanMoveBackwardThrow;

        using Base::IsNotOutOfBound;
        using Base::IsNotOutOfBoundThrow;
        using Base::IsEnd;
        using Base::IsEndThrow;

        // using Base::Forward;
        using Base::ForwardNoCheck;
        // using Base::ForwardNoThrow;
        using Base::Backward;
        using Base::BackwardNoCheck;
        using Base::BackwardNoThrow;
        // using Base::Reserve;

        using Base::Get;
        // using Base::GetAndForward;
        using Base::GetAndForwardNoCheck;
        using Base::GetAndBackward;
        using Base::GetAndBackwardNoCheck;
        // using Base::GetNext;
        using Base::GetNextNoCheck;
        using Base::GetPrev;
        using Base::GetPrevNoCheck;

    public:
        static constexpr char UPPER_HEX[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
        static constexpr char LOWER_HEX[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    protected:
        BasicBufferOutManager<CharBuffer>* m_BufferOutManager;

    public:
        inline BasicBufferOutManager<CharBuffer>*       GetBufferOutManagerPtr() noexcept { return m_BufferOutManager; }
        inline const BasicBufferOutManager<CharBuffer>* GetBufferOutManagerPtr() const noexcept { return m_BufferOutManager; }

        inline BasicBufferOutManager<CharBuffer>&       GetBufferOutManager() noexcept { return *m_BufferOutManager; }
        inline const BasicBufferOutManager<CharBuffer>& GetBufferOutManager() const noexcept { return *m_BufferOutManager; }

    public:
        BasicBufferOut() noexcept
            : Base()
            , m_BufferOutManager(nullptr)
        {}

        BasicBufferOut(BasicBufferOutManager<CharBuffer>& bufferOutManager)
            : Base()
            , m_BufferOutManager(&bufferOutManager)
        {
            m_BufferOutManager->BeginContext();
            SetBuffer(m_BufferOutManager->GetBuffer(), m_BufferOutManager->GetBufferSize());
            SetBufferCurrentPos(m_BufferOutManager->GetBuffer());
        }

        ~BasicBufferOut() noexcept override = default;

    public:
        void SetBufferOutManager(BasicBufferOutManager<CharBuffer>& bufferOutManager)
        {
            m_BufferOutManager = &bufferOutManager;
            if (m_BufferOutManager == nullptr) throw Detail::FMTShouldNotEndHere{};

            m_BufferOutManager->BeginContext();
            SetBuffer(m_BufferOutManager->GetBuffer(), m_BufferOutManager->GetBufferSize());
            SetBufferCurrentPos(m_BufferOutManager->GetBuffer());
        }

        void EndContext() { m_BufferOutManager->EndContext(GetBufferCurrentSize()); }

    public:
        // TODO : need to have throw version od those to have secure call
        template <typename T>
        void FastWriteInt(T i);
        template <typename T>
        void FastWriteUInt(T i);
        template <typename T>
        void FastWriteFloat(T i, FloatPrecision floatPrecision = FloatPrecision{});

        template <typename T>
        void FastWriteIntAsBin(T i, DigitSize digitSize = DigitSize::DEFAULT, bool prefix = true);
        template <typename T>
        void FastWriteIntAsHex(T i, DigitSize digitSize = DigitSize::DEFAULT, bool prefix = true, Detail::PrintStyle uppercase = PrintStyle::Nothing);
        template <typename T>
        void FastWriteIntAsOct(T i, DigitSize digitSize = DigitSize::DEFAULT, bool prefix = true);

        template <typename CharStr>
        void FastWriteCharPtr(const CharStr* str, std::size_t size);

        template <typename CharStr>
        inline void FastWriteCharPtrNSize(const CharStr* str)
        {
            FastWriteStringView(std::basic_string_view<CharStr>(str));
        }
        template <typename CharStr, std::size_t SIZE>
        inline void FastWriteCharArray(const CharStr (&str)[SIZE])
        {
            FastWriteCharPtr(str, str[SIZE - 1] == 0 ? SIZE - 1 : SIZE);
        }
        template <typename CharStr>
        inline void FastWriteCharBound(const CharStr* begin, const CharStr* end)
        {
            FastWriteCharPtr(begin, static_cast<std::size_t>(end - begin));
        }
        template <typename CharStr>
        inline void FastWriteStringView(const std::basic_string_view<CharStr>& str)
        {
            FastWriteCharPtr(str.data(), str.size());
        }
        template <typename CharStr>
        inline void FastWriteString(const std::basic_string<CharStr>& str)
        {
            FastWriteCharPtr(str.data(), str.size());
        }

    protected:
        template <typename T>
        static DataType GetNumberOfDigitDec(T value);

    public:
        bool AddSize(const std::size_t count)
        {
            if (m_BufferOutManager == nullptr) throw Detail::FMTShouldNotEndHere{};
            if (m_CurrentPos > m_BufferEnd) throw Detail::FMTBufferError{};
            std::size_t currentSize = GetBufferCurrentSize();
            if (m_BufferOutManager->AddSize(count) == false) return false;
            SetBuffer(m_BufferOutManager->GetBuffer(), m_BufferOutManager->GetBufferSize());
            SetBufferCurrentPos(m_BufferOutManager->GetBuffer() + currentSize);
            return true;
        }

        inline bool CanMoveForward()
        {
            if (m_CurrentPos + 1 <= m_BufferEnd) return true;
            return AddSize(1);
        }
        inline bool CanMoveForward(const auto count)
        {
            if (m_CurrentPos + count <= m_BufferEnd) return true;
            return AddSize(static_cast<std::size_t>(count));
        }
        inline void CanMoveForwardThrow()
        {
            if (CanMoveForward()) return;
            throw FMTBufferFull{};
        }
        inline void CanMoveForwardThrow(const auto count)
        {
            if (CanMoveForward(count)) return;
            throw FMTBufferFull{};
        }

        inline void Forward()
        {
            CanMoveForwardThrow();
            ++m_CurrentPos;
        }
        inline void Forward(const auto count)
        {
            CanMoveForwardThrow(count);
            m_CurrentPos += count;
        }
        inline void ForwardNoThrow()
        {
            if (CanMoveForward()) ++m_CurrentPos;
        }
        inline void ForwardNoThrow(const auto count)
        {
            if (CanMoveForward(count)) m_CurrentPos += count;
        }
        inline CharBuffer GetAndForward()
        {
            CanMoveForwardThrow();
            return *m_CurrentPos++;
        }
        inline CharBuffer GetNext()
        {
            CanMoveForwardThrow();
            return *(m_CurrentPos + 1);
        }
        inline void Reserve(const auto count)
        {
            Forward(count);
            Backward();
        }

    public:
        inline void SetChar(const CharBuffer c) { *m_CurrentPos = c; }
        inline void PushBack(const CharBuffer c)
        {
            if (CanMoveForward()) *m_CurrentPos++ = c;
        }
        inline void PushReverse(const CharBuffer c)
        {
            if (CanMoveBackward()) *m_CurrentPos-- = c;
        }
        inline void PushBackNoCheck(const CharBuffer c) { *m_CurrentPos++ = c; }
        inline void PushReverseNoCheck(const CharBuffer c) { *m_CurrentPos-- = c; }
        inline void PushBack(const CharBuffer c, auto count)
        {
            if (CanMoveForward(count))
                while (count-- > 0)
                    PushBackNoCheck(c);
        }
        inline void PushReverse(const CharBuffer c, auto count)
        {
            if (CanMoveBackward(count))
                while (count-- > 0)
                    PushReverseNoCheck(c);
        }

        inline void PushBackEndChar() { PushBack('\0'); }
        inline void AddSpaces(const auto count) { PushBack(' ', count); }

    protected:
        template <typename... Rest>
        inline void PushBackSeqImpl(const CharBuffer c, const Rest... rest)
        {
            PushBackNoCheck(c);
            if constexpr (sizeof...(rest) > 0) PushBackSeqImpl(rest...);
        }

    public:
        template <typename... CharToPush>
        inline void PushBackSeq(const CharToPush... ele)
        {
            if (CanMoveForward(sizeof...(ele))) return PushBackSeqImpl(ele...);
        }

    public:
        template <typename Type, typename... Rest>
        inline void BasicWriteType(Type&& type, Rest&&... rest)
        {
            BasicWriteType(type);
            if constexpr (sizeof...(rest) > 0) BasicWriteType(std::forward<Rest>(rest)...);
        }

        template <typename T>
        requires Detail::AsSignedIntegerType<T>
        inline void BasicWriteType(const T i) { FastWriteInt(i); }
        template <typename T>
        requires Detail::AsUnsignedIntegerType<T>
        inline void BasicWriteType(const T i) { FastWriteUInt(i); }
        template <typename T>
        requires Detail::AsFloatType<T>
        inline void BasicWriteType(const T i) { FastWriteFloat(i); }
        template <typename T>
        requires Detail::AsCharType<T>
        inline void BasicWriteType(const T i) { PushBack(i); }
        template <typename T, std::size_t SIZE>
        requires Detail::AsCharType<T>
        inline void BasicWriteType(const T (&i)[SIZE]) { FastWriteCharArray(i); }
        template <typename T>
        requires Detail::AsCharType<T>
        inline void BasicWriteType(const std::basic_string_view<T>& i) { FastWriteString(i); }
    };
}

#include "Integer-inl.h"
#include "Internal-inl.h"
#include "String-inl.h"
