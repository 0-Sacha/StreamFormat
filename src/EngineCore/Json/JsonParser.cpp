#pragma once

#include "Detail.h"

#include <string_view>
#include <unordered_map>
#include <vector>

#include "JsonSerializer.h"

namespace EngineCore::JSON::Detail
{
	void JsonParser::Intermediate::Parse(Detail::JsonParser& parser)
	{
		parser.BufferIn().IgnoreAllBlanks();
        const char* begin = parser.BufferIn().GetBufferCurrentPos();

        if (parser.IsJsonStringBegin())
        {
            parser.BufferIn().Skip('"');
            while (true)
            {
                parser.BufferIn().GoTo('"');
                if (parser.BufferIn().PrevIsNotEqualTo('\\')) break;
            }
            parser.BufferIn().Skip('"');
        }
        else if (parser.IsJsonNumberBegin())
        {
            float k;
            JsonNumberSerializer::LoadFloat(k, parser);
        }
        else if (parser.IsJsonBooleanBegin())
        {
            bool k;
            JsonBooleanSerializer::LoadBool(k, parser);
        }
        else if (parser.IsJsonStructBegin())
        {
            JsonStructSerializer::LoadAllSubObjects<JsonParser::Intermediate>(*this, parser, [](JsonParser::Intermediate&, std::size_t, std::string&&, JsonParser& parser) {
                JsonParser::Intermediate intermediate;
                intermediate.Parse(parser);
            });
        }
        else if (parser.IsJsonArrayBegin())
        {
            JsonArraySerializer::LoadAllSubObjects<JsonParser::Intermediate>(*this, parser, [](JsonParser::Intermediate&, std::size_t, JsonParser& parser){
                JsonParser::Intermediate intermediate;
                intermediate.Parse(parser);
            });
        }
        else if (parser.IsJsonNullBegin())
        {
            JsonNullSerializer::LoadNull(parser);
        }
        
        const char* end = parser.BufferIn().GetBufferCurrentPos();
        Data = std::string_view(begin, end);
	};

	void JsonParser::StructIntermediate::Parse(Detail::JsonParser& parser)
	{
        JsonStructSerializer::LoadAllSubObjects<JsonParser::StructIntermediate>(*this, parser, [](JsonParser::StructIntermediate& t, std::size_t, std::string&& name, JsonParser& parser){
            JsonParser::Intermediate intermediate;
            intermediate.Parse(parser);
            t.Objects.insert({std::move(name), std::move(intermediate)});
        });
    };

	void JsonParser::ArrayIntermediate::Parse(Detail::JsonParser& parser)
	{
        JsonArraySerializer::LoadAllSubObjects<JsonParser::ArrayIntermediate>(*this, parser, [](JsonParser::ArrayIntermediate& t, std::size_t, JsonParser& parser){
            JsonParser::Intermediate intermediate;
            intermediate.Parse(parser);
            t.Objects.emplace_back(std::move(intermediate));
        });
    };
}
