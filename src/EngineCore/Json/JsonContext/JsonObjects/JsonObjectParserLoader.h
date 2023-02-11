#pragma once

#include "JsonObjects.h"
#include "EngineCore/Json/JsonContext/JsonParser/JsonParser.h"

namespace EngineCore::JSON::Detail
{
    template <>
	struct JsonParserType<JsonObject>
    {
		inline static void Load(JsonObject&, JsonParser& parser) {}
	};

    template <>
	struct JsonParserType<JsonStringObject>
    {
		inline static void Load(JsonStringObject& stringObject, JsonParser& parser)
        {
            const char* begin = parser.GetBuffer().GetBufferCurrentPos();
            parser.GetBuffer().Skip('"');

            stringObject.String.clear();

            while(true)
            {
                const char* beginString = parser.GetBuffer().GetBufferCurrentPos();
                parser.GetBuffer().GoTo('"', '\\');
                const char* endString = parser.GetBuffer().GetBufferCurrentPos();
                stringObject.String.append(beginString, endString);

                if (parser.GetBuffer().IsEqualTo('"'))
                    break;
                
                parser.GetBuffer().Skip('\\');
                switch (parser.GetBuffer().Get())
                {
                    // TODO : Do all others escape char
                    case '"': stringObject.String.push_back('"'); break;
                    case 't': stringObject.String.push_back('\t'); break;
                    case 'r': stringObject.String.push_back('\r'); break;
                    case 'n': stringObject.String.push_back('\n'); break;
                    default: break;
                }
            }

            parser.GetBuffer().IsEqualToForward('"');
            const char* end = parser.GetBuffer().GetBufferCurrentPos();
            stringObject.Data = std::string_view(begin, end);
		}
	};

    template <>
	struct JsonParserType<JsonNumberObject>
    {
		inline static void Load(JsonNumberObject&, JsonParser& parser)
        {
		}
	};

    template <>
	struct JsonParserType<JsonBooleanObject>
    {
		inline static void Load(JsonBooleanObject&, JsonParser& parser)
        {
		}
	};

    template <>
	struct JsonParserType<JsonArrayObject>
    {
		inline static void Load(JsonArrayObject&, JsonParser& parser)
        {
		}
	};

    template <>
	struct JsonParserType<JsonNullObject>
    {
		inline static void Load(JsonNullObject&, JsonParser& parser)
        {
		}
	};
}
