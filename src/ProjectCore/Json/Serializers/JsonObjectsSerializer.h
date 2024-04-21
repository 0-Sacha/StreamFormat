#pragma once

#include "../JsonObjects.h"
#include "../JsonSerializer.h"

#include "STDSerializers/JSON_vector.h"
#include "STDSerializers/JSON_unordered_map.h"

#include <map>

namespace ProjectCore::JSON
{
    template <>
    struct JsonSerializer<std::unique_ptr<JsonObject>>
    {
        static inline void Parse(std::unique_ptr<JsonObject>& t, Detail::JsonParser& parser)
        {
            parser.BufferIn().IgnoreAllBlanks();
            if (parser.IsJsonStringBegin())
                t = std::make_unique<JsonStringObject>();
            else if (parser.IsJsonNumberBegin())
                t = std::make_unique<JsonNumberObject>();
            else if (parser.IsJsonBooleanBegin())
                t = std::make_unique<JsonBooleanObject>();
            else if (parser.IsJsonStructBegin())
                t = std::make_unique<JsonStructObject>();
            else if (parser.IsJsonArrayBegin())
                t = std::make_unique<JsonArrayObject>();
            else if (parser.IsJsonNullBegin())
                t = std::make_unique<JsonNullObject>();

            t->ParserExecute(parser);
        }

        static inline void Format(const std::unique_ptr<JsonObject>& t, Detail::JsonFormatter& formatter)
        {
            t->FormatterExecute(formatter);
        }
    };

    template <>
    struct JsonSerializer<JsonObject>
    {
        static inline void Format(const JsonObject& t, Detail::JsonFormatter& formatter)
        {
            t.FormatterExecute(formatter);
        }
    };

    template <>
    struct JsonSerializer<JsonStringObject>
    {
        static inline void Parse(JsonStringObject& t, Detail::JsonParser& parser)
        {
            t.String.clear();
            JsonStringSerializer::ParseSTDString(t.String, parser);
        }

        static inline void Format(const JsonStringObject& t, Detail::JsonFormatter& formatter)
        {
            JsonStringSerializer::FormatSTDString(t.String, formatter);
        }
    };

    template <>
    struct JsonSerializer<JsonNumberObject>
    {
        static inline void Parse(JsonNumberObject& t, Detail::JsonParser& parser)
        {
            JsonNumberSerializer::ParseFloat(t.Number, parser);
        }

        static inline void Format(const JsonNumberObject& t, Detail::JsonFormatter& formatter)
        {
            JsonNumberSerializer::FormatFloat(t.Number, formatter);
        }
    };

    template <>
    struct JsonSerializer<JsonBooleanObject>
    {
        static inline void Parse(JsonBooleanObject& t, Detail::JsonParser& parser)
        {
            JsonBooleanSerializer::ParseBool(t.Boolean, parser);
        }

        static inline void Format(const JsonBooleanObject& t, Detail::JsonFormatter& formatter)
        {
            JsonBooleanSerializer::FormatBool(t.Boolean, formatter);
        }
    };

    template <>
    struct JsonSerializer<JsonNullObject>
    {
        static inline void Parse(JsonNullObject&, Detail::JsonParser& parser)
        {
            JsonNullSerializer::ParseNull(parser);
        }

        static inline void Format(const JsonNullObject&, Detail::JsonFormatter& formatter)
        {
            JsonNullSerializer::FormatNull(formatter);
        }
    };

    template <>
    struct JsonSerializer<JsonStructObject>
    {
        static inline void Parse(JsonStructObject& t, Detail::JsonParser& parser) {
            parser.Parse(t.Objects);
        }
        static inline void Format(const JsonStructObject& t, Detail::JsonFormatter& formatter) {
            if (formatter.Settings().OrderedStruct == false)
            {
                formatter.Format(t.Objects);
                return;
            }

            std::map<std::string_view, JsonObject*> objectsOrdered;
            for (auto& [name, objects] : t.Objects)
                objectsOrdered.insert({ name, objects.get()});
            formatter.Format(objectsOrdered);
        }
    };

    template <>
    struct JsonSerializer<JsonArrayObject>
    {
        static inline void Parse(JsonArrayObject& t, Detail::JsonParser& parser) {
            parser.Parse(t.Objects);
        }
        static inline void Format(const JsonArrayObject& t, Detail::JsonFormatter& formatter) {
            formatter.Format(t.Objects);
        }
    };
}
