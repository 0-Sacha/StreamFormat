#pragma once

#include "ProjectCore/Json/JsonSerializer.h"

#include <string>

namespace ProjectCore::JSON
{
    template <>
    struct JsonSerializer<std::string>
    {
        static inline void Parse(std::string& t, Detail::JsonParser& parser) {
            JsonStringSerializer::ParseSTDString(t, parser);
        }
        static inline void Format(const std::string& t, Detail::JsonFormatter& formatter) {
            JsonStringSerializer::FormatSTDString(t, formatter);
        }
    };

    template <>
    struct JsonSerializer<std::string_view>
    {
        static inline void Parse(std::string_view& t, Detail::JsonParser& parser) {
            // TODO:
        }
        static inline void Format(const std::string_view& t, Detail::JsonFormatter& formatter) {
            JsonStringSerializer::FormatSTDString(t, formatter);
        }
    };
}
