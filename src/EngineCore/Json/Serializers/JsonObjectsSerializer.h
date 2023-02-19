#pragma once

#include "../JsonObjects.h"
#include "../JsonSerializer.h"

#include "STDSerializers/JSON_vector.h"
#include "STDSerializers/JSON_unordered_map.h"

namespace EngineCore::JSON
{
	template <>
	struct JsonSerializer<std::unique_ptr<JsonObject>>
	{
		static inline void Load(std::unique_ptr<JsonObject>& t, Detail::JsonParser& parser)
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

			t->Parse(parser);
		}

		static inline void Dump(const std::unique_ptr<JsonObject>& t, Detail::JsonFormatter& formatter)
		{
			t->Format(formatter);
		}
	};

    template <>
	struct JsonSerializer<JsonObject>
    {
		static inline void Dump(const JsonObject& t, Detail::JsonFormatter& formatter)
        {
            t.Format(formatter);
        }
    };

    template <>
	struct JsonSerializer<JsonStringObject>
    {
        static inline void Load(JsonStringObject& t, Detail::JsonParser& parser)
        {
            t.String.clear();
            JsonSerializer<Detail::ForwardAsJsonString<JsonStringObject>>::LoadSTDString(t.String, parser);
        }

		static inline void Dump(const JsonStringObject& t, Detail::JsonFormatter& formatter)
        {
            JsonSerializer<Detail::ForwardAsJsonString<JsonStringObject>>::DumpSTDString(t.String, formatter);
        }
    };

    template <>
	struct JsonSerializer<JsonNumberObject>
    {
        static inline void Load(JsonNumberObject& t, Detail::JsonParser& parser)
        {
            JsonSerializer<Detail::ForwardAsJsonNumber<JsonNumberObject>>::LoadFloat(t.Number, parser);
        }

		static inline void Dump(const JsonNumberObject& t, Detail::JsonFormatter& formatter)
        {
            JsonSerializer<Detail::ForwardAsJsonNumber<JsonNumberObject>>::DumpFloat(t.Number, formatter);
        }
    };

    template <>
	struct JsonSerializer<JsonBooleanObject>
    {
        static inline void Load(JsonBooleanObject& t, Detail::JsonParser& parser)
        {
            JsonSerializer<Detail::ForwardAsJsonBoolean<JsonBooleanObject>>::LoadBool(t.Boolean, parser);
        }

		static inline void Dump(const JsonBooleanObject& t, Detail::JsonFormatter& formatter)
        {
            JsonSerializer<Detail::ForwardAsJsonBoolean<JsonBooleanObject>>::DumpBool(t.Boolean, formatter);
        }
    };

    template <>
	struct JsonSerializer<JsonNullObject>
    {
        static inline void Load(JsonNullObject& t, Detail::JsonParser& parser)
        {
            JsonSerializer<Detail::ForwardAsJsonNull<JsonNullObject>>::LoadNull(parser);
        }

		static inline void Dump(const JsonNullObject& t, Detail::JsonFormatter& formatter)
        {
            JsonSerializer<Detail::ForwardAsJsonNull<JsonNullObject>>::DumpNull(formatter);
        }
    };

    template <>
	struct JsonSerializer<JsonStructObject>
    {
        static inline void Load(JsonStructObject& t, Detail::JsonParser& parser) {
            JsonSerializer<std::unordered_map<std::string, std::unique_ptr<JsonObject>>>::Load(t.Objects, parser);
        }
		static inline void Dump(const JsonStructObject& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<std::unordered_map<std::string, std::unique_ptr<JsonObject>>>::Dump(t.Objects, formatter);
        }
    };

    template <>
	struct JsonSerializer<JsonArrayObject>
    {
        static inline void Load(JsonArrayObject& t, Detail::JsonParser& parser) {
            JsonSerializer<std::vector<std::unique_ptr<JsonObject>>>::Load(t.Objects, parser);
        }
		static inline void Dump(const JsonArrayObject& t, Detail::JsonFormatter& formatter) {
            JsonSerializer<std::vector<std::unique_ptr<JsonObject>>>::Dump(t.Objects, formatter);
        }
    };
}
