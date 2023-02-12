#pragma once

#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>
#include <memory>

namespace EngineCore::JSON::Detail
{
    class JsonParser;
    class JsonFormatter;

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
    
    public:
        void Parse(JsonParser& parser);
        void Format(JsonFormatter& formatter) const;
    
    protected:
        virtual void ParseImpl(JsonParser& parser) = 0;
        virtual void FormatImpl(JsonFormatter& formatter) const = 0;
    };

    struct JsonStringObject final : public JsonObject
    {
        JsonStringObject() : JsonObject(ObjectType::String) {}
        std::string String;

    protected:
        void ParseImpl(JsonParser& parser) override;
        void FormatImpl(JsonFormatter& formatter) const override;
    };

    struct JsonNumberObject : public JsonObject
    {
        JsonNumberObject() : JsonObject(ObjectType::Number) {}
        double NumberAsDouble;
        std::intmax_t NumberAsInt;
        std::uintmax_t NumberAsUInt;

    protected:
        void ParseImpl(JsonParser& parser) override;
        void FormatImpl(JsonFormatter& formatter) const override;
    };

    struct JsonBooleanObject : public JsonObject
    {
        JsonBooleanObject() : JsonObject(ObjectType::Boolean) {}
        bool Boolean;

    protected:
        void ParseImpl(JsonParser& parser) override;
        void FormatImpl(JsonFormatter& formatter) const override;
    };

    struct JsonStructObject : public JsonObject
    {
        JsonStructObject() : JsonObject(ObjectType::Struct) {}
        std::unordered_map<std::string, std::unique_ptr<JsonObject>> Objects;

    protected:
        void ParseImpl(JsonParser& parser) override;
        void FormatImpl(JsonFormatter& formatter) const override;
    };

    struct JsonArrayObject : public JsonObject
    {
        JsonArrayObject() : JsonObject(ObjectType::Array) {}
        std::vector<std::unique_ptr<JsonObject>> Objects;

    protected:
        void ParseImpl(JsonParser& parser) override;
        void FormatImpl(JsonFormatter& formatter) const override;
    };

    struct JsonNullObject : public JsonObject
    {
        JsonNullObject() : JsonObject(ObjectType::Null) {}

    protected:
        void ParseImpl(JsonParser& parser) override;
        void FormatImpl(JsonFormatter& formatter) const override;
    };
}
