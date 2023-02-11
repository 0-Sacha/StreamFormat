#pragma once

#include "JsonParser.h"
#include "EngineCore/Json/JsonContext/JsonObjects/JsonObjectParserLoader.h"

namespace EngineCore::JSON::Detail
{
    std::unique_ptr<Detail::JsonObject> JsonParser::CreateJsonObject()
    {
        m_Buffer.GoToJsonObject();
        if (m_Buffer.IsJsonStringBegin())
        {
            JsonStringObject* stringObject = new JsonStringObject();
            JsonParserType<JsonStringObject>::Load(*stringObject, *this);
            return std::unique_ptr<Detail::JsonObject>(stringObject);
        }

        if (m_Buffer.IsJsonNumberBegin())
        {
            JsonNumberObject* numberObject = new JsonNumberObject();
            JsonParserType<JsonNumberObject>::Load(*numberObject, *this);
            return std::unique_ptr<Detail::JsonObject>(numberObject);
        }
    
        if (m_Buffer.IsJsonBooleanBegin())
        {
            JsonBooleanObject* booleanObject = new JsonBooleanObject();
            JsonParserType<JsonBooleanObject>::Load(*booleanObject, *this);
            return std::unique_ptr<Detail::JsonObject>(booleanObject);
        }

        if (m_Buffer.IsJsonStructBegin())
        {
            JsonStructObject* structObject = new JsonStructObject();
            JsonParserType<JsonStructObject>::Load(*structObject, *this);
            return std::unique_ptr<Detail::JsonObject>(structObject);
        }

        if (m_Buffer.IsJsonArrayBegin())
        {
            JsonArrayObject* arrayObject = new JsonArrayObject();
            JsonParserType<JsonArrayObject>::Load(*arrayObject, *this);
            return std::unique_ptr<Detail::JsonObject>(arrayObject);
        }

        if (m_Buffer.IsJsonNullBegin())
        {
            JsonNullObject* nullObject = new JsonNullObject();
            JsonParserType<JsonNullObject>::Load(*nullObject, *this);
            return std::unique_ptr<Detail::JsonObject>(nullObject);
        }

        return std::unique_ptr<Detail::JsonObject>(nullptr);
    }
}
