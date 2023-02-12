#pragma once

#include "JsonParser.h"

namespace EngineCore::JSON::Detail
{
    std::unique_ptr<Detail::JsonObject> JsonParser::LoadJsonObject()
    {
        m_Buffer.GoToJsonObject();
        if (m_Buffer.IsJsonStringBegin())
        {
            std::unique_ptr<Detail::JsonObject> stringObject = std::make_unique<JsonStringObject>();
            stringObject->Parse(*this);
        }

        if (m_Buffer.IsJsonNumberBegin())
        {
            std::unique_ptr<Detail::JsonObject> numberObject = std::make_unique<JsonNumberObject>();
            numberObject->Parse(*this);
        }
    
        if (m_Buffer.IsJsonBooleanBegin())
        {
            std::unique_ptr<Detail::JsonObject> booleanObject = std::make_unique<JsonBooleanObject>();
            booleanObject->Parse(*this);
        }

        if (m_Buffer.IsJsonStructBegin())
        {
            std::unique_ptr<Detail::JsonObject> structObject = std::make_unique<JsonStructObject>();
            structObject->Parse(*this);
        }

        if (m_Buffer.IsJsonArrayBegin())
        {
            std::unique_ptr<Detail::JsonObject> arrayObject = std::make_unique<JsonArrayObject>();
            arrayObject->Parse(*this);
        }

        if (m_Buffer.IsJsonNullBegin())
        {
            std::unique_ptr<Detail::JsonObject> nullObject = std::make_unique<JsonNullObject>();
            nullObject->Parse(*this);
        }

        return std::unique_ptr<Detail::JsonObject>(nullptr);
    }
}
