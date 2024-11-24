#pragma once

#include "BasicBufferOutManager.h"

namespace StreamFormat::FMT::Detail
{
    template <typename CharType, std::size_t Count>
    class StaticBufferOutManager : public BasicBufferOutManager<CharType>
    {
    public:
        ~StaticBufferOutManager() override = default;
        StaticBufferOutManager(StaticBufferOutManager&) = delete;
        StaticBufferOutManager& operator=(StaticBufferOutManager&) = delete;

    public:
        CharType*       GetBuffer() override { return m_Buffer; }
        const CharType* GetBuffer() const override { return m_Buffer; }
        std::size_t     GetBufferSize() const override { return Count; }

    public:
        [[nodiscard]] std::expected<void, BufferManagerError> AddSize(const std::size_t) override
        {
            return std::unexpected(BufferManagerError::StaticMemoryManager);
        }

    private:
        CharType m_Buffer[Count];
    };
}
