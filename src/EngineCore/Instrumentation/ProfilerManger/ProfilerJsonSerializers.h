#pragma once

#include "EngineCore/Json/Json.h"
#include "ProfilerFactory.h"

namespace EngineCore::JSON
{
	template <>
	struct JsonSerializer<Instrumentation::Profiler>
    {
		static inline void Dump(const Instrumentation::Profiler& t, Detail::JsonFormatter& formatter)
        {
			auto intermediate = formatter.GetStructIntermediate();
			intermediate.Dump("displayTimeUnit", "us");
			intermediate.Dump("traceEvents", t.Events);
        }

		static inline void Load(Instrumentation::Profiler& t, Detail::JsonParser& parser)
		{
			auto intermediate = parser.GetStructIntermediate();
			intermediate.Load("traceEvents", t.Events);
		}
    };

	template <>
	struct JsonSerializer<Instrumentation::Event>
    {
		static inline void Dump(const Instrumentation::Event& t, Detail::JsonFormatter& formatter)
        {
			auto intermediate = formatter.GetStructIntermediate();
			intermediate.Dump("name", t.Name);
			intermediate.Dump("cat", t.Category);
			intermediate.Dump("ph", t.Type);
			intermediate.Dump("pid", t.PID);
			intermediate.Dump("tid", t.TID);
			intermediate.Dump("ts", t.TimeOfEvent);
			intermediate.Dump("dur", t.Duration);
			intermediate.Dump("id", t.Id);
			if (t.Data != nullptr)
				intermediate.Dump("args", *t.Data);
        }

		static inline void Load(Instrumentation::Event& t, Detail::JsonParser& parser)
		{
			auto intermediate = parser.GetStructIntermediate();
			intermediate.Load("name", t.Name);
			intermediate.Load("cat", t.Category);
			intermediate.Load("ph", t.Type);
			intermediate.Load("pid", t.PID);
			intermediate.Load("tid", t.TID);
			intermediate.Load("ts", t.TimeOfEvent);
			intermediate.Load("dur", t.Duration);
			intermediate.Load("id", t.Id);
			intermediate.Load("args", *t.Data);
		}
    };

	template <>
	struct JsonSerializer<Instrumentation::EventType>
    {
		static inline void Dump(const Instrumentation::EventType& t, Detail::JsonFormatter& formatter)
        {
            formatter.Dump(static_cast<char>(t));
        }

		static inline void Load(Instrumentation::EventType& t, Detail::JsonParser& parser)
		{
            parser.Load(reinterpret_cast<char&>(t));
		}
    };

	template <>
	struct JsonSerializer<Instrumentation::EventData>
    {
		static inline void Dump(const Instrumentation::EventData& t, Detail::JsonFormatter& formatter)
        {
			t.ToJson(formatter);
        }

		static inline void Load(Instrumentation::EventData& t, Detail::JsonParser& parser)
		{
			t.FromJson(parser);
		}
    };
}
