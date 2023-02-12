#pragma once

#include "EngineCore/Json/Detail/Buffer/JsonFormatterBuffer.h"
#include "EngineCore/Json/JsonContext/JsonObjects/JsonObjects.h"

namespace EngineCore::JSON::Detail
{
    class JsonFormatter
    {
    public:
        JsonFormatter()
            : m_BufferManager(256)
            , m_Buffer(m_BufferManager)
        {}

    public:
        void DumpJsonObject(const Detail::JsonObject& object);

    public:
        JsonFormatterBuffer& GetBuffer() { return m_Buffer; }
        const JsonFormatterBuffer& GetBuffer() const { return m_Buffer; }

    protected:
        EngineCore::FMT::Detail::DynamicBufferManager<char> m_BufferManager;
        JsonFormatterBuffer m_Buffer;
    };
}
