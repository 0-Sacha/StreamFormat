#pragma once

#include "ProjectCore/Json/Json.h"
#include "ProfilerFactory.h"

namespace ProjectCore::JSON
{
	template <>
	struct JsonSerializer<Instrumentation::Profiler>
    {
		static inline void Format(const Instrumentation::Profiler& t, Detail::JsonFormatter& formatter)
        {
			auto intermediate = formatter.GetStructIntermediate();
			intermediate.Format("displayTimeUnit", "us");
			intermediate.Format("traceEvents", t.Events);
        }

		static inline void Parse(Instrumentation::Profiler& t, Detail::JsonParser& parser)
		{
			auto intermediate = parser.GetStructIntermediate();
			intermediate.Parse("traceEvents", t.Events);
		}
    };

	template <>
	struct JsonSerializer<Instrumentation::Event>
    {
		static inline void Format(const Instrumentation::Event& t, Detail::JsonFormatter& formatter)
        {
			auto intermediate = formatter.GetStructIntermediate();
			intermediate.Format("name", t.Name);
			intermediate.Format("cat", t.Category);
			intermediate.Format("ph", t.Type);
			intermediate.Format("pid", t.PID);
			intermediate.Format("tid", t.TID);
			intermediate.Format("ts", t.TimeOfEvent);
			intermediate.Format("dur", t.Duration);
			intermediate.Format("id", t.Id);
			if (t.Data != nullptr)
				intermediate.Format("args", *t.Data);
        }

		static inline void Parse(Instrumentation::Event& t, Detail::JsonParser& parser)
		{
			auto intermediate = parser.GetStructIntermediate();
			intermediate.Parse("name", t.Name);
			intermediate.Parse("cat", t.Category);
			intermediate.Parse("ph", t.Type);
			intermediate.Parse("pid", t.PID);
			intermediate.Parse("tid", t.TID);
			intermediate.Parse("ts", t.TimeOfEvent);
			intermediate.Parse("dur", t.Duration);
			intermediate.Parse("id", t.Id);
			intermediate.Parse("args", *t.Data);
		}
    };

	template <>
	struct JsonSerializer<Instrumentation::EventType>
    {
		static inline void Format(const Instrumentation::EventType& t, Detail::JsonFormatter& formatter)
        {
            formatter.Format(static_cast<char>(t));
        }

		static inline void Parse(Instrumentation::EventType& t, Detail::JsonParser& parser)
		{
            parser.Parse(reinterpret_cast<char&>(t));
		}
    };

	template <>
	struct JsonSerializer<Instrumentation::EventData>
    {
		static inline void Format(const Instrumentation::EventData& t, Detail::JsonFormatter& formatter)
        {
			t.ToJson(formatter);
        }

		static inline void Parse(Instrumentation::EventData& t, Detail::JsonParser& parser)
		{
			t.FromJson(parser);
		}
    };
}
