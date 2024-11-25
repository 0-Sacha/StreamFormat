#pragma once

#include "BasicBufferOutManager.h"

#include <cstring>
#include <iostream>
#include <memory>

namespace StreamFormat::FMT::Detail
{
    template <typename CharType>
    class DynamicBufferOutManager : public BasicBufferOutManager<CharType>
    {
    public:
        DynamicBufferOutManager(std::size_t beginSize = DEFAULT_BEGIN_SIZE)
            : m_BufferSize(beginSize)
        {}

        ~DynamicBufferOutManager() override = default;
        DynamicBufferOutManager(DynamicBufferOutManager&) = delete;
        DynamicBufferOutManager& operator=(DynamicBufferOutManager&) = delete;
    
    public:
        static constexpr std::size_t DEFAULT_BEGIN_SIZE  = 128;
        static constexpr std::size_t GROW_UP_BUFFER_SIZE = 2;
        static constexpr bool        DEBUG_RESIZE        = false;

    public:
        CharType*       GetBuffer() override { return m_Buffer.get(); }
        const CharType* GetBuffer() const override { return m_Buffer.get(); }
        std::size_t     GetBufferSize() const override { if (m_Buffer == nullptr) return 0; return m_BufferSize; }

    public:
        [[nodiscard]] std::expected<void, FMTResult> BeginContextImpl() final
        {
            if (m_Buffer != nullptr)
                return {};

            CharType* alloc = new CharType[m_BufferSize];
            if (alloc == nullptr)
                return std::unexpected(FMTResult::Manager_AllocationFailed);
            m_Buffer.reset(alloc);
            return {};
        }

        [[nodiscard]] std::expected<void, FMTResult> AddSize(const std::size_t count) override { return Resize(count + m_BufferSize); }
        [[nodiscard]] std::expected<void, FMTResult> Resize(const std::size_t targetBufferSize);

    protected:
        std::unique_ptr<CharType[]> m_Buffer = nullptr;
        std::size_t                 m_BufferSize = 0;
    };

    template <typename CharType>
    class ShrinkDynamicBufferOutManager : public DynamicBufferOutManager<CharType>
    {
    public:
        using Base = DynamicBufferOutManager<CharType>;
        using Base::DEFAULT_BEGIN_SIZE;
        using Base::GROW_UP_BUFFER_SIZE;
        using Base::DEBUG_RESIZE;

        using Base::GetBuffer;
        using Base::GetBufferSize;
        using Base::Resize;

        using Base::m_Buffer;
        using Base::m_BufferSize;

        static constexpr float MEAN_SIZE_OVERFLOW = 4.2f;
        static constexpr float MEAN_SIZE_RESIZE   = 1.4f;
        static constexpr float MEAN_CALCFACT_OLD  = 5;
        static constexpr float MEAN_CALCFACT_LAST = 1;

    public:
        ShrinkDynamicBufferOutManager(std::size_t beginSize = DEFAULT_BEGIN_SIZE)
            : Base(beginSize)
            , m_MeanGeneratedSize(beginSize)
        {}
        ~ShrinkDynamicBufferOutManager() override = default;
        ShrinkDynamicBufferOutManager(ShrinkDynamicBufferOutManager&) = delete;
        ShrinkDynamicBufferOutManager& operator=(ShrinkDynamicBufferOutManager&) = delete;

    protected:
        void ComputeGeneratedSizeImpl(std::size_t totalGeneratedLength) override
        {
            // WTF
            m_MeanGeneratedSize = (m_MeanGeneratedSize * MEAN_CALCFACT_OLD + totalGeneratedLength * MEAN_CALCFACT_LAST) / (MEAN_CALCFACT_OLD + MEAN_CALCFACT_LAST);
        }

    public:
        [[nodiscard]] std::expected<void, FMTResult> ShrinkIfNeeded()
        {
            if (m_BufferSize > static_cast<std::size_t>(m_MeanGeneratedSize * MEAN_SIZE_OVERFLOW))
                return Resize(static_cast<std::size_t>(m_MeanGeneratedSize * MEAN_SIZE_RESIZE));
            return {};
        }

    private:
        std::size_t m_MeanGeneratedSize = 0;
    };

    template <typename CharType>
    [[nodiscard]] std::expected<void, FMTResult> DynamicBufferOutManager<CharType>::Resize(const std::size_t targetBufferSize)
    {
        std::size_t newBufferSize = targetBufferSize;

        if (m_BufferSize < targetBufferSize)
        {
            newBufferSize = m_BufferSize;
            while (newBufferSize < targetBufferSize)
                newBufferSize *= GROW_UP_BUFFER_SIZE;
        }

        CharType* newBuffer = new CharType[newBufferSize];
        if (newBuffer == nullptr)
            return std::unexpected(FMTResult::Manager_AllocationFailed);

        std::memcpy(newBuffer, m_Buffer.get(), std::min(newBufferSize, m_BufferSize));

        if constexpr (DEBUG_RESIZE) std::cout << "Resize from " << m_BufferSize << " to " << newBufferSize << std::endl;

        m_Buffer.reset(newBuffer);
        m_BufferSize = newBufferSize;

        return {};
    }
}
