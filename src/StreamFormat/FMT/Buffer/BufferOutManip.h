#pragma once

#include "BufferInfo.h"
#include "BufferManip.h"

#include "BufferOutManager/BasicBufferOutManager.h"

namespace StreamFormat::FMT::Detail
{
    template <typename CharType>
    class BufferOutInfo : public BufferInfo<CharType>
    {
    public:
        using BufferInfo<CharType>::TChar;

        using BufferInfo<CharType>::Buffer;
        using BufferInfo<CharType>::CurrentPos;
        using BufferInfo<CharType>::BufferEnd;

        using BufferInfo<CharType>::Get;
        using BufferInfo<CharType>::Manip;
        
    public:
        BufferOutInfo(BasicBufferOutManager<CharType>& bufferOutManager) noexcept
            : BufferInfo<CharType>()
        {
            SetManager(bufferOutManager);
        }

    public:
        BasicBufferOutManager<CharType>* Manager;

    public:
        void SetManager(BasicBufferOutManager<CharType>& bufferOutManager)
        {
            Manager = &bufferOutManager;
            Manager->BeginContext();
            BufferManip(*this).Set(Manager->GetBuffer(), Manager->GetBufferSize());
        }
    };

    template <typename T>
    concept ConvertibleToBufferOutInfo = requires(T&& t)
    {
        BufferOutInfo(std::forward<T>(t));
    };

    template <typename TChar>
    class BufferOutManip
    {
    public:
        constexpr inline BufferOutManip(BufferOutInfo<TChar>& buffer) noexcept : Buffer(buffer) {}
    public:
        BufferOutInfo<TChar>& Buffer;

    public:
        void SetManager(BasicBufferOutManager<TChar>& bufferOutManager)
        {
            Buffer.SetManager(bufferOutManager);
        }

        void ComputeGeneratedSize() { Buffer.Manager->ComputeGeneratedSize(BufferAccess(Buffer).GetBufferCurrentSize()); }

    public:
        bool AddSize(const std::size_t count)
        {
            if (Buffer.Manager == nullptr) throw Detail::FMTShouldNotEndHere{};
            if (Buffer.CurrentPos > Buffer.BufferEnd) throw Detail::FMTParseError{};
            std::size_t currentSize = BufferAccess(Buffer).GetBufferCurrentSize();
            if (Buffer.Manager->AddSize(count) == false) return false;
            BufferManip(Buffer).Set(Buffer.Manager->GetBuffer(), Buffer.Manager->GetBufferSize());
            Buffer.CurrentPos = Buffer.Manager->GetBuffer() + currentSize;
            return true;
        }

        inline BufferManipResult Reserve(const std::size_t count = 1)
        {
            if (Buffer.CurrentPos + count <= Buffer.BufferEnd)
                return true;
            return AddSize(static_cast<std::size_t>(count));
        }

        inline BufferManipResult Forward(const std::size_t count = 1)
        {
            if (Reserve(count))
            {
                Buffer.CurrentPos += count;
                return true;
            }
            return false;
        }

    public:
        inline void SetChar(const TChar c) { *Buffer.CurrentPos = c; }
        inline BufferManipResult Pushback(const TChar c)
        {
            if (Reserve(1))
            {
                *Buffer.CurrentPos++ = c;
                return true;
            }
            return false;
        }
        inline BufferManipResult SetInverse(const TChar c)
        {
            if (BufferAccess(Buffer).CanMoveBackward(1))
            {
                *--Buffer.CurrentPos = c;
                return true;
            }
            return false;
        }
        inline void ForcePushback(const TChar c) { *Buffer.CurrentPos++ = c; }
        inline void ForceSetInverse(const TChar c) { *--Buffer.CurrentPos = c; }

    public:
        inline BufferManipResult Pushback(const TChar c, auto count)
        {
            if (Reserve(count))
            {
                while (count-- > 0)
                    ForcePushback(c);
                return true;
            }
            return false;
        }

    public:
        inline void AddSpaces(const auto count) { Pushback(' ', count); }

    protected:
        template <typename... Rest>
        inline void PushbackSeqImpl(const TChar c, const Rest... rest)
        {
            ForcePushback(c);
            if constexpr (sizeof...(rest) > 0) PushbackSeqImpl(rest...);
        }

    public:
        template <typename... CharToPush>
        inline BufferManipResult PushbackSeq(const CharToPush... ele)
        {
            if (Reserve(sizeof...(ele)))
            {
                PushbackSeqImpl(ele...);
                return true;
            }
            return false;
        }
    };
}
