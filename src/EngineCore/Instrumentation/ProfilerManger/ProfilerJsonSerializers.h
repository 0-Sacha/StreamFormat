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
			JsonStructSerializer::DumpBegin(formatter);
			JsonStructSerializer::DumpObject("displayTimeUnit", "us", 0, formatter);
			JsonStructSerializer::DumpObject("traceEvents", t.Events, 1, formatter);
			JsonStructSerializer::DumpEnd(formatter);
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
			JsonStructSerializer::DumpBegin(formatter);
			JsonStructSerializer::DumpObject("name", t.Name, 0, formatter);
			JsonStructSerializer::DumpObject("cat", t.Category, 1, formatter);
			JsonStructSerializer::DumpObject("ph", t.Type, 2, formatter);
			JsonStructSerializer::DumpObject("pid", t.PID, 3, formatter);
			JsonStructSerializer::DumpObject("tid", t.TID, 4, formatter);
			JsonStructSerializer::DumpObject("ts", t.TimeOfEvent, 5, formatter);
			JsonStructSerializer::DumpObject("dur", t.Duration, 6, formatter);
			JsonStructSerializer::DumpObject("id", t.Id, 7, formatter);
			JsonStructSerializer::DumpEnd(formatter);
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
}
