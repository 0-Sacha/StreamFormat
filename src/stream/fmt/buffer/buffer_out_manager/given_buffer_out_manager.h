#pragma once

#include "basic_buffer_out_manager.h"

namespace stream::fmt::detail
{
    template <typename CharType>
    class GivenBufferOutManager : public BasicBufferOutManager<CharType>
    {
    public:
        template <std::size_t SIZE>
        GivenBufferOutManager(CharType (&buffer)[SIZE])
            : m_Buffer(buffer)
            , m_BufferSize(SIZE)
        {}

        GivenBufferOutManager(CharType* buffer, std::size_t bufferSize)
            : m_Buffer(buffer)
            , m_BufferSize(bufferSize)
        {}

        ~GivenBufferOutManager() override = default;

        GivenBufferOutManager(GivenBufferOutManager&) = delete;
        GivenBufferOutManager& operator=(GivenBufferOutManager&) = delete;

    public:
        CharType*       GetBuffer() override { return m_Buffer; }
        const CharType* GetBuffer() const override { return m_Buffer; }
        std::size_t     GetBufferSize() const override { return m_BufferSize; }

    public:
        [[nodiscard]] std::expected<void, FMTResult> AddSize(const std::size_t /* count */) override
        {
            return std::unexpected(FMTResult::Manager_StaticMemory);
        }

    private:
        CharType*   m_Buffer;
        std::size_t m_BufferSize;
    };
}
