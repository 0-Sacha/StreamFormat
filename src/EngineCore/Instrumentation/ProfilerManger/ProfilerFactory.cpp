
#include "ProfilerFactory.h"

#include <fstream>

namespace EngineCore::Instrumentation
{
	void ProfilerFactory::ToJson(Profiler& profiler, std::filesystem::path path)
	{
		profiler.GetProfilerProfile().Stop();

		if (path == "")
			path = std::filesystem::path(profiler.Name) / ".json";
		std::ofstream file(path.string(), std::ios::out);

		file << "{\n";
		file << "\"displayTimeUnit\": \"us\", \n";

		file << "\"traceEvents\":[\n";
		bool first = true;
		for (const Event& event : profiler.Events)
		{
			std::string_view newLine = ",\n";
			if (first == true)
			{
				newLine = "";
				first = false;
			}

			// TODO :  not handled : ThreadTimeOfEvent (tts), Data(args{})

			FMT::FilePrint(file,
							R"({0}{"name": "{1}", "cat": "{2}", "ph": "{3}", "pid": {4}, "tid": {5}, "ts":{6}, "dur":{7}, "id":{8}})",
							newLine,
							event.Name,
							event.Category,
							event.Type,
							event.PID,
							event.TID,
							event.TimeOfEvent,
							event.Duration,
							event.Id
						);
		}
		file << "]}";
		file.close();
	}
}
