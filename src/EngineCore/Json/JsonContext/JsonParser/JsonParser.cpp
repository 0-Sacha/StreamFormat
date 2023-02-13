#pragma once

#include "JsonParser.h"

namespace EngineCore::JSON::Detail
{
    std::unique_ptr<Detail::JsonObject> JsonParser::LoadJsonObject()
    {
        m_BufferIn.GoToJsonObject();
        if (m_BufferIn.IsJsonStringBegin())
        {
            std::unique_ptr<Detail::JsonObject> stringObject = std::make_unique<JsonStringObject>();
            stringObject->Parse(*this);
            return stringObject;
        }

        if (m_BufferIn.IsJsonNumberBegin())
        {
            std::unique_ptr<Detail::JsonObject> numberObject = std::make_unique<JsonNumberObject>();
            numberObject->Parse(*this);
            return numberObject;
        }
    
        if (m_BufferIn.IsJsonBooleanBegin())
        {
            std::unique_ptr<Detail::JsonObject> booleanObject = std::make_unique<JsonBooleanObject>();
            booleanObject->Parse(*this);
            return booleanObject;
        }

        if (m_BufferIn.IsJsonStructBegin())
        {
            std::unique_ptr<Detail::JsonObject> structObject = std::make_unique<JsonStructObject>();
            structObject->Parse(*this);
            return structObject;
        }

        if (m_BufferIn.IsJsonArrayBegin())
        {
            std::unique_ptr<Detail::JsonObject> arrayObject = std::make_unique<JsonArrayObject>();
            arrayObject->Parse(*this);
            return arrayObject;
        }

        if (m_BufferIn.IsJsonNullBegin())
        {
            std::unique_ptr<Detail::JsonObject> nullObject = std::make_unique<JsonNullObject>();
            nullObject->Parse(*this);
            return nullObject;
        }

        return std::unique_ptr<Detail::JsonObject>(nullptr);
    }
}
