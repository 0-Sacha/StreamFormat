#pragma once

#include "../json_objects.hxx"
#include "../json_serializer.hxx"

#include "std_serializers/json_unordered_map.hxx"
#include "std_serializers/json_vector.hxx"

#include <map>

namespace stream::json {
    template <>
    struct JsonSerializer<std::unique_ptr<JsonObject>> {
        static inline void parse(std::unique_ptr<JsonObject>& t, detail::JsonParser& parser) {
            fmt::buf::TestManip(parser.istream).IgnoreEveryBlanks();
            if (parser.is_json_string_begin())
                t = std::make_unique<JsonStringObject>();
            else if (parser.is_json_number_begin())
                t = std::make_unique<JsonNumberObject>();
            else if (parser.is_json_boolean_begin())
                t = std::make_unique<JsonBooleanObject>();
            else if (parser.is_json_struct_begin())
                t = std::make_unique<JsonStructObject>();
            else if (parser.is_json_array_begin())
                t = std::make_unique<JsonArrayObject>();
            else if (parser.is_json_null_begin())
                t = std::make_unique<JsonNullObject>();

            t->ParserExecute(parser);
        }

        static inline void format(const std::unique_ptr<JsonObject>& t, detail::JsonFormatter& formatter) {
            t->FormatterExecute(formatter);
        }
    };

    template <>
    struct JsonSerializer<JsonObject> {
        static inline void format(const JsonObject& t, detail::JsonFormatter& formatter) {
            t.FormatterExecute(formatter);
        }
    };

    template <>
    struct JsonSerializer<JsonStringObject> {
        static inline void parse(JsonStringObject& t, detail::JsonParser& parser) {
            t.String.clear();
            JsonStringSerializer::ParseSTDString(t.String, parser);
        }

        static inline void format(const JsonStringObject& t, detail::JsonFormatter& formatter) {
            JsonStringSerializer::FormatSTDString(t.String, formatter);
        }
    };

    template <>
    struct JsonSerializer<JsonNumberObject> {
        static inline void parse(JsonNumberObject& t, detail::JsonParser& parser) {
            JsonNumberSerializer::ParseFloat(t.Number, parser);
        }

        static inline void format(const JsonNumberObject& t, detail::JsonFormatter& formatter) {
            JsonNumberSerializer::FormatFloat(t.Number, formatter);
        }
    };

    template <>
    struct JsonSerializer<JsonBooleanObject> {
        static inline void parse(JsonBooleanObject& t, detail::JsonParser& parser) {
            JsonBooleanSerializer::ParseBool(t.Boolean, parser);
        }

        static inline void format(const JsonBooleanObject& t, detail::JsonFormatter& formatter) {
            JsonBooleanSerializer::FormatBool(t.Boolean, formatter);
        }
    };

    template <>
    struct JsonSerializer<JsonNullObject> {
        static inline void parse(JsonNullObject&, detail::JsonParser& parser) {
            JsonNullSerializer::ParseNull(parser);
        }

        static inline void format(const JsonNullObject&, detail::JsonFormatter& formatter) {
            JsonNullSerializer::FormatNull(formatter);
        }
    };

    template <>
    struct JsonSerializer<JsonStructObject> {
        static inline void parse(JsonStructObject& t, detail::JsonParser& parser) {
            parser.parse(t.Objects);
        }
        static inline void format(const JsonStructObject& t, detail::JsonFormatter& formatter) {
            if (formatter.settings.ordered_struct == false) {
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
    struct JsonSerializer<JsonArrayObject> {
        static inline void parse(JsonArrayObject& t, detail::JsonParser& parser) {
            parser.parse(t.Objects);
        }
        static inline void format(const JsonArrayObject& t, detail::JsonFormatter& formatter) {
            formatter.format(t.Objects);
        }
    };
}  // namespace stream::json
