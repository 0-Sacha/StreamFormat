#pragma once

#include "JsonFormatter.h"
#include "EngineCore/Json/JsonContext/JsonObjects/JsonObjects.h"

namespace EngineCore::JSON::Detail
{
    void JsonFormatter::DumpJsonObject(const Detail::JsonObject& object)
    {
       object.Format(*this);
    }
}
