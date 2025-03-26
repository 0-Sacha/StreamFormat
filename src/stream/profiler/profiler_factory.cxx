#include "profiler_factory.hxx"
#include "profiler_json_serializers.hxx"

#include <fstream>

namespace stream::profiler {
    void ProfilerFactory::to_json(Profiler& profiler, std::filesystem::path path) {
        profiler.profiler_duration.stop();
        profiler.events[0] = profiler.profiler_duration.info;

        if (path == "") {
            path = std::string(profiler.name) + ".json";
        }

        std::ofstream                      file(path.string(), std::ios::out);
        json::FormatAsJson<Profiler> const format_profiler(profiler);
        fmt::file_print(file, format_profiler);
        file.close();
    }
}  // namespace stream::profiler
