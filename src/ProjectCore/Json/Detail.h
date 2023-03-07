#pragma once

#include <exception>

namespace ProjectCore::JSON
{
    class JsonError : public std::exception {};
    class JsonIndexingError : public JsonError {};
    class JsonTypeSerializerNotImpl : public JsonError {};
    class JsonGivenTypeError : public JsonError {};
}

