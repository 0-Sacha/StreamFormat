#pragma once

#include <chrono>

namespace EngineCore::Instrumentation
{
    inline double GetMicroseconds()
	{
		return (double)std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() / 1000;
	}
};
