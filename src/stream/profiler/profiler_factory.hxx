#pragma once

#include "profiler.hxx"

#include <filesystem>

namespace stream::profiler {
    class ProfilerFactory {
    public:
        static void to_json(Profiler& profiler, std::filesystem::path path = "");
    };
}  // namespace stream::profiler
