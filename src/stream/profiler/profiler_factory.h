#pragma once

#include "profiler.h"

#include <filesystem>

namespace stream::profiler
{
    class ProfilerFactory
    {
    public:
        static void to_json(Profiler& profiler, std::filesystem::path path = "");
    };
}
