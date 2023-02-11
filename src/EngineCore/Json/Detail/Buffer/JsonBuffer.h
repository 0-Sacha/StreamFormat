#pragma once

#include <memory>

namespace EngineCore::JSON::Detail
{
    class JsonBuffer
    {
    public:
        void Reserve(const std::size_t size)
        {
            m_Buffer.reset(new char[size + 1]);
            m_Buffer[size] = 0;
            m_Size = size;
        }

    public:
        char* GetBuffer() { return m_Buffer.get(); }
        const char* GetBuffer() const { return m_Buffer.get(); }
        std::size_t GetSize() const { return m_Size; }

    protected:
        std::unique_ptr<char[]> m_Buffer;
        std::size_t m_Size;
    }; 
}
