#include "detail.hxx"

#include <string_view>
#include <unordered_map>
#include <vector>

#include "json_serializer.hxx"

namespace stream::json::detail {
    void JsonParser::Intermediate::parse(detail::JsonParser& parser) {
        const fmt::buf::TestAccess access(parser.istream);
        fmt::buf::TestManip        manip(parser.istream);

        manip.IgnoreEveryBlanks();
        const char* const begin = parser.istream.current_pos;

        if (parser.is_json_string_begin()) {
            manip.skip_one_of('"');
            while (true) {
                manip.GoTo('"');
                if (fmt::buf::Access(parser.istream).get_prev_force() != '\\') break;
            }
            manip.skip_one_of('"');
        } else if (parser.is_json_number_begin()) {
            float k;
            JsonNumberSerializer::ParseFloat(k, parser);
        } else if (parser.is_json_boolean_begin()) {
            bool k;
            JsonBooleanSerializer::ParseBool(k, parser);
        } else if (parser.is_json_struct_begin()) {
            JsonStructSerializer::LoadAllSubObjects<JsonParser::Intermediate>(*this, parser, [](JsonParser::Intermediate&, std::size_t, std::string&&, JsonParser& json_parser) {
                JsonParser::Intermediate intermediate;
                intermediate.parse(json_parser);
            });
        } else if (parser.is_json_array_begin()) {
            JsonArraySerializer::LoadAllSubObjects<JsonParser::Intermediate>(*this, parser, [](JsonParser::Intermediate&, std::size_t, JsonParser& json_parser) {
                JsonParser::Intermediate intermediate;
                intermediate.parse(json_parser);
            });
        } else if (parser.is_json_null_begin()) {
            JsonNullSerializer::ParseNull(parser);
        }

        const char* const end = parser.istream.current_pos;
        data                  = std::string_view(begin, end);
    };

    void JsonParser::StructIntermediate::parse(detail::JsonParser& parser) {
        JsonStructSerializer::LoadAllSubObjects<JsonParser::StructIntermediate>(*this, parser,
                                                                                [](JsonParser::StructIntermediate& t, std::size_t, std::string&& name, JsonParser& json_parser) {
            JsonParser::Intermediate intermediate;
            intermediate.parse(json_parser);
            t.Objects.insert({std::move(name), std::move(intermediate)});
        });
    };

    void JsonParser::ArrayIntermediate::parse(detail::JsonParser& parser) {
        JsonArraySerializer::LoadAllSubObjects<JsonParser::ArrayIntermediate>(*this, parser, [](JsonParser::ArrayIntermediate& t, std::size_t, JsonParser& json_parser) {
            JsonParser::Intermediate intermediate;
            intermediate.parse(json_parser);
            t.Objects.emplace_back(std::move(intermediate));
        });
    };
}  // namespace stream::json::detail
