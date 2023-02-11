#pragma once

#include "EngineCore/Json/Json.h"
#include <filesystem>

namespace EngineCore::JSON
{
    class JsonFactory
    {
    public:
        static JsonContext FromPath(const std::filesystem::path& path);
        static void SaveToPath(JsonContext& json, const std::filesystem::path& path);
    };
}
