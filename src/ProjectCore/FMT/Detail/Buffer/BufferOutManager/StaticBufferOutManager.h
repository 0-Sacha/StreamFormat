#pragma once

#include "BasicBufferOutManager.h"

namespace ProjectCore::FMT::Detail {

    template <typename CharType, std::size_t Count>
    class StaticBufferOutManager : public BasicBufferOutManager<CharType>
    {
    public:
        ~StaticBufferOutManager() override = default;
        
    public:
        CharType* GetBuffer() override { return m_Buffer; }
        const CharType* GetBuffer() const override { return m_Buffer; }
        std::size_t GetBufferSize() const override { return Count; }
    
    public:
        bool AddSize(const std::size_t) override { return false; }

    private:
        CharType m_Buffer[Count];
    };

}
