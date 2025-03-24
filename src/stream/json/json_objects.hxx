#pragma once

#include "detail.hxx"
#include "stream/fmt.hxx"

#include <concepts>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace stream::json::detail {
    class JsonParser;
    class JsonFormatter;
}  // namespace stream::json::detail

namespace stream::json {
    struct JsonObject {
    public:
        enum class ObjectType {
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
        JsonObject(ObjectType type) : type_(type) {}

        virtual ~JsonObject() = default;

    private:
        ObjectType type_ = ObjectType::Undefined;

    public:
        ObjectType get_type() {
            return type_;
        }

        JsonObject& operator[](const std::size_t index) {
            return get(index);
        }
        JsonObject& operator[](const std::string_view subObject) {
            return get(subObject);
        }

        virtual JsonObject& get(const std::size_t) {
            throw detail::JsonIndexingError{};
        }
        virtual JsonObject& get(const std::string_view) {
            throw detail::JsonIndexingError{};
        }

    public:
        template <typename T>
            requires std::is_base_of_v<JsonObject, T>
        T& as() {
            T* t = dynamic_cast<T*>(this);
            if (t == nullptr) throw detail::JsonCastError{};
            return *t;
        }
        template <typename T>
            requires std::is_base_of_v<JsonObject, T>
        const T& as() const {
            const T* t = dynamic_cast<const T*>(this);
            if (t == nullptr) throw detail::JsonCastError{};
            return *t;
        }

        template <typename T>
        T read() {
            T value;
            JsonObjectSerializer<T>::read_object(value, *this);
            return value;
        }

        template <typename T>
        void write(const T& t) {
            JsonObjectSerializer<T>::write_object(t, *this);
        }

        std::string to_string() {
            return fmt::format_string(*this);
        }

    public:
        virtual void ParserExecute(detail::JsonParser& parser)                = 0;
        virtual void FormatterExecute(detail::JsonFormatter& formatter) const = 0;
    };

    struct JsonStringObject final : public JsonObject {
        JsonStringObject() : JsonObject(ObjectType::String) {}
        JsonStringObject(const std::string_view value) : JsonObject(ObjectType::String), String(value) {}
        JsonStringObject(std::string&& value) : JsonObject(ObjectType::String), String(std::move(value)) {}
        ~JsonStringObject() override = default;

    public:
        std::string String;

    public:
        static std::unique_ptr<JsonObject> create() {
            return std::make_unique<JsonStringObject>();
        }
        static std::unique_ptr<JsonObject> create(const std::string_view value) {
            return std::make_unique<JsonStringObject>(value);
        }
        static std::unique_ptr<JsonObject> create(std::string&& value) {
            return std::make_unique<JsonStringObject>(std::move(value));
        }

    public:
        void ParserExecute(detail::JsonParser& parser) override;
        void FormatterExecute(detail::JsonFormatter& formatter) const override;
    };

    struct JsonNumberObject final : public JsonObject {
        JsonNumberObject(double value = 0.0) : JsonObject(ObjectType::Number), Number(value) {}
        ~JsonNumberObject() override = default;

    public:
        double Number;

    public:
        static std::unique_ptr<JsonObject> create(double value = 0.0) {
            return std::make_unique<JsonNumberObject>(value);
        }

    public:
        void ParserExecute(detail::JsonParser& parser) override;
        void FormatterExecute(detail::JsonFormatter& formatter) const override;
    };

    struct JsonBooleanObject final : public JsonObject {
        JsonBooleanObject(bool value = false) : JsonObject(ObjectType::Boolean), Boolean(value) {}
        ~JsonBooleanObject() override = default;

    public:
        bool Boolean;

    public:
        static std::unique_ptr<JsonObject> create(bool value = false) {
            return std::make_unique<JsonBooleanObject>(value);
        }

    public:
        void ParserExecute(detail::JsonParser& parser) override;
        void FormatterExecute(detail::JsonFormatter& formatter) const override;
    };

    struct JsonStructObject final : public JsonObject {
    public:
        JsonStructObject() : JsonObject(ObjectType::Struct) {}
        ~JsonStructObject() override = default;

    public:
        static std::unique_ptr<JsonObject> create() {
            return std::make_unique<JsonStructObject>();
        }

    public:
        std::unordered_map<std::string, std::unique_ptr<JsonObject>> Objects;

    public:
        void add(const std::string& name, std::unique_ptr<JsonObject>&& object) {
            Objects.insert({name, std::move(object)});
        }
        void add(std::string&& name, std::unique_ptr<JsonObject>&& object) {
            Objects.insert({std::move(name), std::move(object)});
        }
        JsonObject& get(const std::string_view subObject) override {
            try {
                return *Objects.at(std::string(subObject));
            } catch (...) {
                throw detail::JsonIndexingError{};
            }
        }

    public:
        void ParserExecute(detail::JsonParser& parser) override;
        void FormatterExecute(detail::JsonFormatter& formatter) const override;
    };

    struct JsonArrayObject final : public JsonObject {
    public:
        JsonArrayObject() : JsonObject(ObjectType::Array) {}
        ~JsonArrayObject() override = default;

    public:
        static std::unique_ptr<JsonObject> create() {
            return std::make_unique<JsonArrayObject>();
        }

    public:
        std::vector<std::unique_ptr<JsonObject>> Objects;

    public:
        void add(std::unique_ptr<JsonObject>&& object) {
            Objects.emplace_back(std::move(object));
        }
        JsonObject& get(const std::size_t index) override {
            return *Objects[index];
        }

    public:
        void ParserExecute(detail::JsonParser& parser) override;
        void FormatterExecute(detail::JsonFormatter& formatter) const override;
    };

    struct JsonNullObject final : public JsonObject {
    public:
        JsonNullObject() : JsonObject(ObjectType::Null) {}
        ~JsonNullObject() override = default;

    public:
        static std::unique_ptr<JsonObject> create() {
            return std::make_unique<JsonNullObject>();
        }

    public:
        void ParserExecute(detail::JsonParser& parser) override;
        void FormatterExecute(detail::JsonFormatter& formatter) const override;
    };
}  // namespace stream::json
