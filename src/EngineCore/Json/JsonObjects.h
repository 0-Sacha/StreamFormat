#pragma once

#include "Detail.h"

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <concepts>


namespace EngineCore::JSON::Detail
{
    class JsonParser;
    class JsonFormatter;
}

namespace EngineCore::JSON
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
        JsonObject(ObjectType type) : m_Type(type) {}
    
    private:
        ObjectType m_Type = ObjectType::Undefined;

    public:
        ObjectType GetType() { return m_Type; }

        JsonObject& operator[](const std::size_t index)         { return Get(index); }
        JsonObject& operator[](const std::string& subObject)    { return Get(subObject); }

        virtual JsonObject& Get(const std::size_t index)        { throw JsonIndexingError{}; }
        virtual JsonObject& Get(const std::string& subObject)   { throw JsonIndexingError{}; }

    public:
        template <typename T>
        requires std::is_base_of_v<JsonObject, T>
        T& As()   { return *dynamic_cast<T*>(this); }

    public:
        virtual void Parse(Detail::JsonParser& parser) = 0;
        virtual void Format(Detail::JsonFormatter& formatter) const = 0;
    };

    struct JsonStringObject final : public JsonObject
    {
        JsonStringObject() : JsonObject(ObjectType::String) {}
        std::string String;

    public:
        void Parse(Detail::JsonParser& parser) override;
        void Format(Detail::JsonFormatter& formatter) const override;
    };

    struct JsonNumberObject final : public JsonObject
    {
        JsonNumberObject() : JsonObject(ObjectType::Number) {}
        double Number;

    public:
        void Parse(Detail::JsonParser& parser) override;
        void Format(Detail::JsonFormatter& formatter) const override;
    };

    struct JsonBooleanObject final : public JsonObject
    {
        JsonBooleanObject() : JsonObject(ObjectType::Boolean) {}
        bool Boolean;

    public:
        void Parse(Detail::JsonParser& parser) override;
        void Format(Detail::JsonFormatter& formatter) const override;
    };

    struct JsonStructObject final : public JsonObject
    {
        JsonStructObject() : JsonObject(ObjectType::Struct) {}
        std::unordered_map<std::string, std::unique_ptr<JsonObject>> Objects;

        JsonObject& Get(const std::string& subObject) override
        {
            try {
                return *Objects.at(subObject);
            }
            catch(...)
            {
                throw JsonIndexingError{};
            }
        }

    public:
        void Parse(Detail::JsonParser& parser) override;
        void Format(Detail::JsonFormatter& formatter) const override;
    };

    struct JsonArrayObject final : public JsonObject
    {
        JsonArrayObject() : JsonObject(ObjectType::Array) {}
        std::vector<std::unique_ptr<JsonObject>> Objects;

        JsonObject& Get(const std::size_t index) override { return *Objects[index]; }

    public:
        void Parse(Detail::JsonParser& parser) override;
        void Format(Detail::JsonFormatter& formatter) const override;
    };

    struct JsonNullObject final : public JsonObject
    {
        JsonNullObject() : JsonObject(ObjectType::Null) {}
    
    public:
        void Parse(Detail::JsonParser& parser) override;
        void Format(Detail::JsonFormatter& formatter) const override;
    };
}
