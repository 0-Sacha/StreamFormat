#pragma once

#include "EngineCore/Json/Detail/Buffer/JsonBuffer.h"
#include "EngineCore/Json/Detail/Buffer/JsonParserBuffer.h"

#include "EngineCore/Json/JsonContext/JsonObjects/JsonObjects.h"

namespace EngineCore::JSON::Detail
{
    class JsonParser
    {
    public:
        std::unique_ptr<Detail::JsonObject> CreateJsonObject();

    public:
        JsonParserBuffer& GetBuffer() { return m_Buffer; }
        const JsonParserBuffer& GetBuffer() const { return m_Buffer; }

    protected:
        JsonParserBuffer m_Buffer;
    };

    template<typename T>
	struct JsonParserType {
		static inline void Load(T& t, JsonParser& parser)
        {
            // TODO : error recovery for unknown types
		}
	};
}
