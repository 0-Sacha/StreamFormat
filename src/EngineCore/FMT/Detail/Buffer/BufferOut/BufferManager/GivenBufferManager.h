#pragma once

#include "BasicBufferManager.h"

namespace EngineCore::FMT::Detail {

    template <typename CharType>
    class GivenBufferManager : public BasicBufferManager<CharType>
    {
        public:
            GivenBufferManager(CharType* buffer, std::size_t bufferSize)
                : m_Buffer(buffer)        
                , m_BufferSize(bufferSize)
            {}        

        public:
            CharType* GetBuffer() override { return m_Buffer; }
            const CharType* GetBuffer() const override { return m_Buffer; }
            std::size_t GetBufferSize() const override { return m_BufferSize; }
        
        public:
            bool AddSize(const std::size_t count) override { return false; }

        private:
            CharType* m_Buffer;
            std::size_t m_BufferSize;
    };

}
