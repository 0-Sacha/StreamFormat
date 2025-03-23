#include "profiler_factory.h"
#include "profiler_json_serializers.h"

#include <fstream>

namespace stream::profiler
{
    void ProfilerFactory::ToJson(Profiler& profiler, std::filesystem::path path)
    {
        profiler.profiler_duration.Stop();
        profiler.events[0] = profiler.profiler_duration.info;

        if (path == "") path = std::string(profiler.name) + ".json";

        std::ofstream file(path.string(), std::ios::out);
        json::FormatAsJson<Profiler> format_profiler(profiler);
        fmt::file_print(file, format_profiler).value();
        file.close();
    }
}
