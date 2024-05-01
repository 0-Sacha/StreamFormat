#pragma once

#include "Profiler.h"

#include <filesystem>

namespace ProjectCore::ProfilerManager
{
    class ProfilerFactory
    {
    public:
        static void ToJson(Profiler& profiler, std::filesystem::path path = "");
    };
}
