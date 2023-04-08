#include "ProfilerFactory.h"
#include "ProfilerJsonSerializers.h"

#include <fstream>

namespace ProjectCore::Instrumentation
{
    void ProfilerFactory::ToJson(Profiler& profiler, std::filesystem::path path)
    {
        profiler.GetProfilerProfile().Stop();

        if (path == "")
            path = std::string(profiler.Name) + ".json";
        
        std::ofstream file(path.string(), std::ios::out);
        JSON::FormatAsJson<Profiler> formatProfiler(profiler);
        FMT::FilePrint(file, formatProfiler);
        file.close();
    }
}
