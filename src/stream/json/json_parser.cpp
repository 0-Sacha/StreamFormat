#include "detail.h"

#include <string_view>
#include <unordered_map>
#include <vector>

#include "JsonSerializer.h"

namespace stream::JSON::detail
{
    void JsonParser::Intermediate::parse(detail::JsonParser& parser)
    {
        fmt::detail::BufferTestAccess access(parser.BufferIn);
        fmt::detail::BufferTestManip manip(parser.BufferIn);

        manip.IgnoreEveryBlanks();
        const char* begin = parser.BufferIn.CurrentPos;

        if (parser.IsJsonStringBegin())
        {
            manip.SkipOneOf('"').value();
            while (true)
            {
                manip.GoTo('"');
                if (fmt::detail::BufferTestAccess(parser.BufferIn).PrevIsNotEqualTo('\\'))
                    break;
            }
            manip.SkipOneOf('"').value();
        }
        else if (parser.IsJsonNumberBegin())
        {
            float k;
            JsonNumberSerializer::ParseFloat(k, parser);
        }
        else if (parser.IsJsonBooleanBegin())
        {
            bool k;
            JsonBooleanSerializer::ParseBool(k, parser);
        }
        else if (parser.IsJsonStructBegin())
        {
            JsonStructSerializer::LoadAllSubObjects<JsonParser::Intermediate>(*this, parser, [](JsonParser::Intermediate&, std::size_t, std::string&&, JsonParser& jsonParser) {
                JsonParser::Intermediate intermediate;
                intermediate.parse(jsonParser);
            });
        }
        else if (parser.IsJsonArrayBegin())
        {
            JsonArraySerializer::LoadAllSubObjects<JsonParser::Intermediate>(*this, parser, [](JsonParser::Intermediate&, std::size_t, JsonParser& jsonParser) {
                JsonParser::Intermediate intermediate;
                intermediate.parse(jsonParser);
            });
        }
        else if (parser.IsJsonNullBegin())
        {
            JsonNullSerializer::ParseNull(parser);
        }

        const char* end = parser.BufferIn.CurrentPos;
        Data            = std::string_view(begin, end);
    };

    void JsonParser::StructIntermediate::parse(detail::JsonParser& parser)
    {
        JsonStructSerializer::LoadAllSubObjects<JsonParser::StructIntermediate>(*this, parser,
                                                                                [](JsonParser::StructIntermediate& t, std::size_t, std::string&& name, JsonParser& jsonParser) {
                                                                                    JsonParser::Intermediate intermediate;
                                                                                    intermediate.parse(jsonParser);
                                                                                    t.Objects.insert({std::move(name), std::move(intermediate)});
                                                                                });
    };

    void JsonParser::ArrayIntermediate::parse(detail::JsonParser& parser)
    {
        JsonArraySerializer::LoadAllSubObjects<JsonParser::ArrayIntermediate>(*this, parser, [](JsonParser::ArrayIntermediate& t, std::size_t, JsonParser& jsonParser) {
            JsonParser::Intermediate intermediate;
            intermediate.parse(jsonParser);
            t.Objects.emplace_back(std::move(intermediate));
        });
    };
}
