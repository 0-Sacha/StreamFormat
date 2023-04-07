#pragma once

#include "Detail.h"

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <concepts>


namespace ProjectCore::JSON::Detail
{
    class JsonParser;
    class JsonFormatter;
}

namespace ProjectCore::JSON
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

        virtual ~JsonObject() = default;
    
    private:
        ObjectType m_Type = ObjectType::Undefined;

    public:
        ObjectType GetType() { return m_Type; }

        JsonObject& operator[](const std::size_t index)         { return Get(index); }
        JsonObject& operator[](const std::string& subObject)    { return Get(subObject); }

        virtual JsonObject& Get(const std::size_t)    { throw JsonIndexingError{}; }
        virtual JsonObject& Get(const std::string&)   { throw JsonIndexingError{}; }

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
		JsonStringObject(const std::string& value) : JsonObject(ObjectType::String), String(value) {}
		JsonStringObject(std::string&& value) : JsonObject(ObjectType::String), String(std::move(value)) {}
        ~JsonStringObject() override = default;

	public:
        std::string String;

	public:
		static std::unique_ptr<JsonObject> Create() { return std::make_unique<JsonStringObject>(); }
		static std::unique_ptr<JsonObject> Create(const std::string& value) { return std::make_unique<JsonStringObject>(value); }
		static std::unique_ptr<JsonObject> Create(std::string&& value) { return std::make_unique<JsonStringObject>(std::move(value)); }

	public:
        void Parse(Detail::JsonParser& parser) override;
        void Format(Detail::JsonFormatter& formatter) const override;
    };

    struct JsonNumberObject final : public JsonObject
    {
        JsonNumberObject(double value = 0.0) : JsonObject(ObjectType::Number), Number(value) {}
        ~JsonNumberObject() override = default;

	public:
        double Number;

	public:
        static std::unique_ptr<JsonObject> Create(double value = 0.0) { return std::make_unique<JsonNumberObject>(value); }

    public:
        void Parse(Detail::JsonParser& parser) override;
        void Format(Detail::JsonFormatter& formatter) const override;
    };

    struct JsonBooleanObject final : public JsonObject
    {
		JsonBooleanObject(bool value = false) : JsonObject(ObjectType::Boolean), Boolean(value) {}
        ~JsonBooleanObject() override = default;

	public:
        bool Boolean;

	public:
        static std::unique_ptr<JsonObject> Create(bool value = false) { return std::make_unique<JsonBooleanObject>(value); }

    public:
        void Parse(Detail::JsonParser& parser) override;
        void Format(Detail::JsonFormatter& formatter) const override;
    };

    struct JsonStructObject final : public JsonObject
    {
	public:
		JsonStructObject() : JsonObject(ObjectType::Struct) {}
        ~JsonStructObject() override = default;

	public:
        static std::unique_ptr<JsonObject> Create() { return std::make_unique<JsonStructObject>(); }

	public:
		std::unordered_map<std::string, std::unique_ptr<JsonObject>> Objects;

	public:
		void Add(const std::string& name, std::unique_ptr<JsonObject>&& object) { Objects.insert({ name, std::move(object) }); }
		void Add(std::string&& name, std::unique_ptr<JsonObject>&& object) { Objects.insert({ std::move(name), std::move(object) }); }
		JsonObject& Get(const std::string& subObject) override
        {
            try
            {
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
	public:
		JsonArrayObject() : JsonObject(ObjectType::Array) {}
        ~JsonArrayObject() override = default;

	public:
        static std::unique_ptr<JsonObject> Create() { return std::make_unique<JsonArrayObject>(); }

	public:
		std::vector<std::unique_ptr<JsonObject>> Objects;

	public:
		void Add(std::unique_ptr<JsonObject>&& object) { Objects.emplace_back(std::move(object)); }
		JsonObject& Get(const std::size_t index) override { return *Objects[index]; }

    public:
        void Parse(Detail::JsonParser& parser) override;
        void Format(Detail::JsonFormatter& formatter) const override;
    };

    struct JsonNullObject final : public JsonObject
    {
	public:
		JsonNullObject() : JsonObject(ObjectType::Null) {}
        ~JsonNullObject() override = default;

	public:
		static std::unique_ptr<JsonObject> Create() { return std::make_unique<JsonNullObject>(); }
    
    public:
        void Parse(Detail::JsonParser& parser) override;
        void Format(Detail::JsonFormatter& formatter) const override;
    };
}
