#pragma once

#include <exception>
#include <functional>
#include <string_view>
#include <string>

namespace ProjectCore::JSON::Detail
{
    class JsonError : public std::exception
    {
    public:
        JsonError(std::string&& msg): m_What(std::move(msg)) {}
        JsonError(const std::string_view msg): m_What(msg) {}
        const char* what() const noexcept override { return m_What.c_str(); }
    protected:
        std::string m_What;
    };

    class JsonIndexingError : public JsonError
    {
    public:
        JsonIndexingError(std::string&& msg = ""): JsonError(std::string("JsonIndexingError") + std::move(msg)) {}
        JsonIndexingError(const std::string& msg): JsonError(std::string("JsonIndexingError") + msg) {}
    };
    class JsonTypeSerializerNotImpl : public JsonError
    {
    public:
        JsonTypeSerializerNotImpl(std::string&& msg = ""): JsonError(std::string("JsonTypeSerializerNotImpl") + std::move(msg)) {}
        JsonTypeSerializerNotImpl(const std::string& msg): JsonError(std::string("JsonTypeSerializerNotImpl") + msg) {}
    };
    class JsonGivenTypeError : public JsonError
    {
    public:
        JsonGivenTypeError(std::string&& msg = ""): JsonError(std::string("JsonGivenTypeError") + std::move(msg)) {}
        JsonGivenTypeError(const std::string& msg): JsonError(std::string("JsonGivenTypeError") + msg) {}
    };
    class JsonCastError : public JsonError
    {
    public:
        JsonCastError(std::string&& msg = ""): JsonError(std::string("JsonCastError") + std::move(msg)) {}
        JsonCastError(const std::string& msg): JsonError(std::string("JsonCastError") + msg) {}
    };
}

namespace ProjectCore::JSON
{
    template <typename T>
    struct JsonObjectSerializer;
    template <typename T>
    struct JsonSerializer;
}



