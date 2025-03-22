#include "JsonFormatter.h"

#include "JsonSerializer.h"

namespace stream::JSON::detail
{
    inline JsonFormatter::StructIntermediate::StructIntermediate(JsonFormatter& formatter)
        : Formatter(formatter)
        , Idx(0)
    {
        JsonStructSerializer::FormatBegin(Formatter);
    }
    inline JsonFormatter::StructIntermediate::~StructIntermediate()
    {
        JsonStructSerializer::FormatEnd(Formatter);
    }
    template <typename T>
    inline void JsonFormatter::StructIntermediate::format(const std::string_view name, const T& t)
    {
        JsonStructSerializer::FormatObject(name, t, Idx++, Formatter);
    }

    inline JsonFormatter::ArrayIntermediate::ArrayIntermediate(JsonFormatter& formatter)
        : Formatter(formatter)
        , Idx(0)
    {
        JsonArraySerializer::FormatBegin(Formatter);
    }
    inline JsonFormatter::ArrayIntermediate::~ArrayIntermediate()
    {
        JsonArraySerializer::FormatEnd(Formatter);
    }
    template <typename T>
    inline void JsonFormatter::ArrayIntermediate::format(const T& t)
    {
        JsonArraySerializer::FormatObject(t, Idx++, Formatter);
    }
}
