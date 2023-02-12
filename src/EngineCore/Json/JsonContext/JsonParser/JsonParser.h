#pragma once

#include "EngineCore/Json/Detail/Buffer/JsonBuffer.h"
#include "EngineCore/Json/Detail/Buffer/JsonParserBuffer.h"

#include "EngineCore/Json/JsonContext/JsonObjects/JsonObjects.h"

namespace EngineCore::JSON::Detail
{
    class JsonParser
    {
    public:
        std::unique_ptr<Detail::JsonObject> LoadJsonObject();

    public:
        JsonParserBuffer& GetBuffer() { return m_Buffer; }
        const JsonParserBuffer& GetBuffer() const { return m_Buffer; }

    protected:
        JsonParserBuffer m_Buffer;
    };
}
