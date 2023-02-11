#pragma once

#include "EngineCore//Json/Detail/Buffer/JsonBuffer.h"
#include "JsonParser/JsonParser.h"
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
        void ReloadParser()     { m_Parser.GetBuffer().SetBuffer(m_Buffer.GetBuffer(), m_Buffer.GetSize()); }
        void LoadObjects()      { m_Objects = m_Parser.CreateJsonObject(); }

    public:
        std::unique_ptr<Detail::JsonObject>&  GetObjectsPtr()                       { return m_Objects; };
        const std::unique_ptr<Detail::JsonObject>&  GetObjectsPtr() const           { return m_Objects; };
        Detail::JsonObject&  GetObjects()                                           { return *m_Objects; };
        const Detail::JsonObject&  GetObjects() const                               { return *m_Objects; };

		Detail::JsonBuffer& GetBuffer()                                             { return m_Buffer; };
		const Detail::JsonBuffer& GetBuffer() const                                 { return m_Buffer; };
        Detail::JsonParser&  GetParser()                                            { return m_Parser; };
        const Detail::JsonParser&  GetParser() const                                { return m_Parser; };

    protected:
        std::unique_ptr<Detail::JsonObject> m_Objects;
        Detail::JsonBuffer m_Buffer;
        Detail::JsonParser m_Parser;
    };
}
