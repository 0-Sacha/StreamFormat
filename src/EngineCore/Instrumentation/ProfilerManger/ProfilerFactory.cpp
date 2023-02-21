
#include "ProfilerFactory.h"
#include "EngineCore/Json/Json.h"

#include <fstream>

namespace EngineCore::JSON
{
	template <>
	struct JsonSerializer<Instrumentation::Profiler>
    {
		static inline void Dump(const Instrumentation::Profiler& t, Detail::JsonFormatter& formatter)
        {
			JsonSerializer<Detail::ForwardAsJsonStruct<Instrumentation::Profiler>>::DumpBegin(formatter);
			JsonSerializer<Detail::ForwardAsJsonStruct<Instrumentation::Profiler>>::DumpObject("displayTimeUnit", "us", 0, formatter);
			JsonSerializer<Detail::ForwardAsJsonStruct<Instrumentation::Profiler>>::DumpObject("traceEvents", t.Events, 1, formatter);
			JsonSerializer<Detail::ForwardAsJsonStruct<Instrumentation::Profiler>>::DumpEnd(formatter);
        }

		static inline void Load(Instrumentation::Profiler& t, Detail::JsonParser& parser) {};
    };

	template <>
	struct JsonSerializer<Instrumentation::Event>
    {
		static inline void Dump(const Instrumentation::Event& t, Detail::JsonFormatter& formatter)
        {
			JsonSerializer<Detail::ForwardAsJsonStruct<Instrumentation::Profiler>>::DumpBegin(formatter);
			JsonSerializer<Detail::ForwardAsJsonStruct<Instrumentation::Profiler>>::DumpObject("name", t.Name, 0, formatter);
			JsonSerializer<Detail::ForwardAsJsonStruct<Instrumentation::Profiler>>::DumpObject("cat", t.Category, 1, formatter);
			JsonSerializer<Detail::ForwardAsJsonStruct<Instrumentation::Profiler>>::DumpObject("ph", t.Type, 2, formatter);
			JsonSerializer<Detail::ForwardAsJsonStruct<Instrumentation::Profiler>>::DumpObject("pid", t.PID, 3, formatter);
			JsonSerializer<Detail::ForwardAsJsonStruct<Instrumentation::Profiler>>::DumpObject("tid", t.TID, 4, formatter);
			JsonSerializer<Detail::ForwardAsJsonStruct<Instrumentation::Profiler>>::DumpObject("ts", t.TimeOfEvent, 5, formatter);
			JsonSerializer<Detail::ForwardAsJsonStruct<Instrumentation::Profiler>>::DumpObject("dur", t.Duration, 5, formatter);
			JsonSerializer<Detail::ForwardAsJsonStruct<Instrumentation::Profiler>>::DumpObject("id", t.Id, 5, formatter);
			JsonSerializer<Detail::ForwardAsJsonStruct<Instrumentation::Profiler>>::DumpEnd(formatter);
        }

		static inline void Load(Instrumentation::Event& t, Detail::JsonParser& parser) {};
    };
}

namespace EngineCore::Instrumentation
{

	void ProfilerFactory::ToJson(Profiler& profiler, std::filesystem::path path)
	{
		profiler.GetProfilerProfile().Stop();

		if (path == "")
			path = std::filesystem::path(profiler.Name) / ".json";
		
		std::ofstream file(path.string(), std::ios::out);
		JSON::FormatAsJson<Profiler> formatProfiler(profiler);
		FMT::FilePrint(file, formatProfiler);
		file.close();
	}
}
