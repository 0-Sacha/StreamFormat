#pragma once

#include <exception>
#include <functional>
#include <string>
#include <string_view>

namespace stream::json::detail {
    class JsonError : public std::exception {
    public:
        JsonError(std::string&& msg) : what_(std::move(msg)) {}
        JsonError(const std::string_view msg) : what_(msg) {}
        const char* what() const noexcept override {
            return what_.c_str();
        }

    protected:
        std::string what_;
    };

    class JsonIndexingError : public JsonError {
    public:
        JsonIndexingError(std::string msg = "") : JsonError(std::string("JsonIndexingError") + std::move(msg)) {}
    };
    class JsonTypeSerializerNotImpl : public JsonError {
    public:
        JsonTypeSerializerNotImpl(std::string msg = "") : JsonError(std::string("JsonTypeSerializerNotImpl") + std::move(msg)) {}
    };
    class JsonGivenTypeError : public JsonError {
    public:
        JsonGivenTypeError(std::string msg = "") : JsonError(std::string("JsonGivenTypeError") + std::move(msg)) {}
    };
    class JsonCastError : public JsonError {
    public:
        JsonCastError(std::string msg = "") : JsonError(std::string("JsonCastError") + std::move(msg)) {}
    };
}  // namespace stream::json::detail

namespace stream::json {
    template <typename T>
    struct JsonObjectSerializer;
    template <typename T>
    struct JsonSerializer;
}  // namespace stream::json
