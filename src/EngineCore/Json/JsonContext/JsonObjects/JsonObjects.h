#pragma once

#include "EngineCore/Json/JsonContext/JsonParser/JsonParser.h"

#include <string_view>
#include <unordered_map>
#include <vector>

namespace EngineCore::JSON::Detail
{
    struct JsonObject
    {
    public:
        enum class ObjectType
        {
            String,
            Number,
            Boolean,
            Struct,
            Array,
            Null,
            Undefined
        };

    public:
        JsonObject() {}
        JsonObject(ObjectType type) : Type(type) {}
    
    public:
        ObjectType Type = ObjectType::Undefined;
        std::string_view Data;
    };

    struct JsonStringObject : public JsonObject
    {
        JsonStringObject() : JsonObject(ObjectType::String) {}
        std::string String;
    };

    struct JsonNumberObject : public JsonObject
    {
        JsonNumberObject() : JsonObject(ObjectType::Number) {}
        double NumberAsDouble;
        std::intmax_t NumberAsInt;
        std::uintmax_t NumberAsUInt;
    };

    struct JsonBooleanObject : public JsonObject
    {
        JsonBooleanObject() : JsonObject(ObjectType::Boolean) {}
        bool Boolean;
    };

    struct JsonStructObject : public JsonObject
    {
        JsonStructObject() : JsonObject(ObjectType::Struct) {}
        std::unordered_map<std::string_view, JsonObject> Objects;
    };

    struct JsonArrayObject : public JsonObject
    {
        JsonArrayObject() : JsonObject(ObjectType::Array) {}
        std::vector<JsonObject> Objects;
    };

    struct JsonNullObject : public JsonObject
    {
        JsonNullObject() : JsonObject(ObjectType::Null) {}
    };
}
