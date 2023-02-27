#pragma once

#include "EngineCore/Json/JsonSerializer.h"

#include <string>

namespace EngineCore::JSON
{
    template <>
	struct JsonSerializer<std::string>
    {
        static inline void Parse(std::string& t, Detail::JsonParser& parser) {
            JsonStringSerializer::LoadSTDString(t, parser);
        }
		static inline void Format(const std::string& t, Detail::JsonFormatter& formatter) {
            JsonStringSerializer::DumpSTDString(t, formatter);
        }
    };
}
