#pragma once

#include <exception>
#include <functional>
#include <string_view>
#include <string>

namespace ProjectCore::JSON::Detail
{
    class JsonError : public std::exception {};
    class JsonIndexingError : public JsonError {};
    class JsonTypeSerializerNotImpl : public JsonError {};
    class JsonGivenTypeError : public JsonError {};
    class JsonCastError : public JsonError {};
}

namespace ProjectCore::JSON
{
    template<typename T>
    struct JsonObjectSerializer;
    template<typename T>
    struct JsonSerializer;
}



