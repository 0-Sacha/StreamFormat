#pragma once

#include "EngineCore/Json/JsonSerializer.h"

#include <string>

namespace EngineCore::JSON
{
    template <>
	struct JsonSerializer<std::string>
    {
        static inline void Load(std::string& t, Detail::JsonParser& parser) {
            JsonStringSerializer::LoadSTDString(t, parser);
        }
		static inline void Dump(const std::string& t, Detail::JsonFormatter& formatter) {
            JsonStringSerializer::DumpSTDString(t, formatter);
        }
    };
}
