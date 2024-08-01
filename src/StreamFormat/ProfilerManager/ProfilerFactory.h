#pragma once

#include "Profiler.h"

#include <filesystem>

namespace StreamFormat::ProfilerManager
{
    class ProfilerFactory
    {
    public:
        static void ToJson(Profiler& profiler, std::filesystem::path path = "");
    };
}
