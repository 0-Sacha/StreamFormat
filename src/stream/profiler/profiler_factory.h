#pragma once

#include "Profiler.h"

#include <filesystem>

namespace stream::ProfilerManager
{
    class ProfilerFactory
    {
    public:
        static void ToJson(Profiler& profiler, std::filesystem::path path = "");
    };
}
