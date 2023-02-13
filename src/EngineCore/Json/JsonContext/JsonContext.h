#pragma once

#include "EngineCore//Json/Detail/Buffer/JsonMemoryBuffer.h"
#include "JsonParser/JsonParser.h"
#include "JsonFormatter/JsonFormatter.h"
#include "JsonObjects/JsonObjects.h"

#include <string>
#include <memory>
#include <unordered_map>

namespace EngineCore::JSON
{
    class JsonContext
    {
    public:
        JsonContext() {}

    public:
        void ReloadFromBuffer()
        {
            Detail::JsonParser parser(m_Buffer.GetBuffer(), m_Buffer.GetSize());
            m_Objects = parser.LoadJsonObject();
        }

    public:
        std::unique_ptr<Detail::JsonObject>&  GetObjectsPtr()                       { return m_Objects; };
        const std::unique_ptr<Detail::JsonObject>&  GetObjectsPtr() const           { return m_Objects; };
        Detail::JsonObject&  GetObjects()                                           { return *m_Objects; };
        const Detail::JsonObject&  GetObjects() const                               { return *m_Objects; };

		Detail::JsonMemoryBuffer& GetBuffer()                                             { return m_Buffer; };
		const Detail::JsonMemoryBuffer& GetBuffer() const                                 { return m_Buffer; };

    protected:
        std::unique_ptr<Detail::JsonObject> m_Objects;
        Detail::JsonMemoryBuffer m_Buffer;
    };
}
