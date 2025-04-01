#pragma once

#include <chrono>

namespace stream::profiler {
    inline std::chrono::nanoseconds get_nanoseconds() {
        return std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch();
    }
};  // namespace stream::profiler
