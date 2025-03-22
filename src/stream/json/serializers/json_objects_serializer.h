#pragma once

#include "../JsonObjects.h"
#include "../JsonSerializer.h"

#include "STDSerializers/JSON_unordered_map.h"
#include "STDSerializers/JSON_vector.h"

#include <map>

namespace stream::JSON
{
    template <>
    struct JsonSerializer<std::unique_ptr<JsonObject>>
    {
        static inline void parse(std::unique_ptr<JsonObject>& t, detail::JsonParser& parser)
        {
            fmt::detail::BufferTestManip(parser.BufferIn).IgnoreEveryBlanks();
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

        static inline void format(const std::unique_ptr<JsonObject>& t, detail::JsonFormatter& formatter) { t->FormatterExecute(formatter); }
    };

    template <>
    struct JsonSerializer<JsonObject>
    {
        static inline void format(const JsonObject& t, detail::JsonFormatter& formatter) { t.FormatterExecute(formatter); }
    };

    template <>
    struct JsonSerializer<JsonStringObject>
    {
        static inline void parse(JsonStringObject& t, detail::JsonParser& parser)
        {
            t.String.clear();
            JsonStringSerializer::ParseSTDString(t.String, parser);
        }

        static inline void format(const JsonStringObject& t, detail::JsonFormatter& formatter) { JsonStringSerializer::FormatSTDString(t.String, formatter); }
    };

    template <>
    struct JsonSerializer<JsonNumberObject>
    {
        static inline void parse(JsonNumberObject& t, detail::JsonParser& parser) { JsonNumberSerializer::ParseFloat(t.Number, parser); }

        static inline void format(const JsonNumberObject& t, detail::JsonFormatter& formatter) { JsonNumberSerializer::FormatFloat(t.Number, formatter); }
    };

    template <>
    struct JsonSerializer<JsonBooleanObject>
    {
        static inline void parse(JsonBooleanObject& t, detail::JsonParser& parser) { JsonBooleanSerializer::ParseBool(t.Boolean, parser); }

        static inline void format(const JsonBooleanObject& t, detail::JsonFormatter& formatter) { JsonBooleanSerializer::FormatBool(t.Boolean, formatter); }
    };

    template <>
    struct JsonSerializer<JsonNullObject>
    {
        static inline void parse(JsonNullObject&, detail::JsonParser& parser) { JsonNullSerializer::ParseNull(parser); }

        static inline void format(const JsonNullObject&, detail::JsonFormatter& formatter) { JsonNullSerializer::FormatNull(formatter); }
    };

    template <>
    struct JsonSerializer<JsonStructObject>
    {
        static inline void parse(JsonStructObject& t, detail::JsonParser& parser) { parser.parse(t.Objects); }
        static inline void format(const JsonStructObject& t, detail::JsonFormatter& formatter)
        {
            if (formatter.Settings.OrderedStruct == false)
            {
                formatter.format(t.Objects);
                return;
            }

            std::map<std::string_view, JsonObject*> objectsOrdered;
            for (auto& [name, objects] : t.Objects)
                objectsOrdered.insert({name, objects.get()});
            formatter.format(objectsOrdered);
        }
    };

    template <>
    struct JsonSerializer<JsonArrayObject>
    {
        static inline void parse(JsonArrayObject& t, detail::JsonParser& parser) { parser.parse(t.Objects); }
        static inline void format(const JsonArrayObject& t, detail::JsonFormatter& formatter) { formatter.format(t.Objects); }
    };
}
