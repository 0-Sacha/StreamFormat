#pragma once

#include "profiler.h"

#include <filesystem>

namespace stream::profiler
{
    class ProfilerFactory
    {
    public:
        static void ToJson(Profiler& profiler, std::filesystem::path path = "");
    };
}
