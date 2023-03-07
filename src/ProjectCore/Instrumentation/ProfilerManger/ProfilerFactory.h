#pragma once

#include "Profiler.h"

#include <filesystem>

namespace ProjectCore::Instrumentation
{
	class ProfilerFactory
	{
	public:
		static void ToJson(Profiler& profiler, std::filesystem::path path = "");
	};
}
