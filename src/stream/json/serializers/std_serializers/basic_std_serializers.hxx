#pragma once

#include "stream/json/json_serializer.hxx"

#include <string>

namespace stream::json {
    template <>
    struct JsonSerializer<std::string> {
        static inline void parse(std::string& t, detail::JsonParser& parser) {
            JsonStringSerializer::ParseSTDString(t, parser);
        }
        static inline void format(const std::string& t, detail::JsonFormatter& formatter) {
            JsonStringSerializer::FormatSTDString(t, formatter);
        }
    };

    template <>
    struct JsonSerializer<std::string_view> {
        static inline void parse(std::string_view& t, detail::JsonParser& parser) {
            // TODO:
        }
        static inline void format(const std::string_view& t, detail::JsonFormatter& formatter) {
            JsonStringSerializer::FormatSTDString(t, formatter);
        }
    };
}  // namespace stream::json
