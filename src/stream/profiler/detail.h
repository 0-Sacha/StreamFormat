#pragma once

#include <chrono>

namespace stream::profiler
{
    inline double get_microseconds()
    {
        return (double)std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() / 1000;
    }
};
