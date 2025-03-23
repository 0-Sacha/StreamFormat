#pragma once

#include "profiler_factory.h"
#include "stream/json.h"

namespace stream::json
{
    template <>
    struct JsonSerializer<profiler::Profiler>
    {
        static inline void format(const profiler::Profiler& t, detail::JsonFormatter& formatter)
        {
            auto intermediate = formatter.get_struct_intermediate();
            intermediate.format("displayTimeUnit", "us");
            intermediate.format("traceEvents", t.events);
        }

        static inline void parse(profiler::Profiler& t, detail::JsonParser& parser)
        {
            auto intermediate = parser.get_struct_intermediate();
            intermediate.parse("traceEvents", t.events);
        }
    };

    template <>
    struct JsonSerializer<profiler::EventType>
    {
        static inline void format(const profiler::EventType& t, detail::JsonFormatter& formatter) { formatter.format(static_cast<char>(t)); }

        static inline void parse(profiler::EventType& t, detail::JsonParser& parser) { parser.parse(reinterpret_cast<char&>(t)); }
    };

    template <>
    struct JsonSerializer<profiler::EventData>
    {
        static inline void format(const profiler::EventData& t, detail::JsonFormatter& formatter) { t.ToJson(formatter); }

        static inline void parse(profiler::EventData& t, detail::JsonParser& parser) { t.FromJson(parser); }
    };

    template <>
    struct JsonSerializer<profiler::EventInfo>
    {
        static inline void format(const profiler::EventInfo& t, detail::JsonFormatter& formatter)
        {
            auto intermediate = formatter.get_struct_intermediate();
            intermediate.format("name", t.name);
            intermediate.format("cat", t.Category);
            intermediate.format("ph", t.type);
            intermediate.format("pid", t.PID);
            intermediate.format("tid", t.TID);
            intermediate.format("ts", t.TimeOfEvent);
            intermediate.format("dur", t.Duration);
            intermediate.format("id", t.Id);
            if (t.data != nullptr) intermediate.format("args", *t.data);
        }

        static inline void parse(profiler::EventInfo& t, detail::JsonParser& parser)
        {
            auto intermediate = parser.get_struct_intermediate();
            intermediate.parse("name", t.name);
            intermediate.parse("cat", t.Category);
            intermediate.parse("ph", t.type);
            intermediate.parse("pid", t.PID);
            intermediate.parse("tid", t.TID);
            intermediate.parse("ts", t.TimeOfEvent);
            intermediate.parse("dur", t.Duration);
            intermediate.parse("id", t.Id);
            intermediate.parse("args", *t.data);
        }
    };

    template <>
    struct JsonSerializer<profiler::Event>
    {
        static inline void format(const profiler::Event& t, detail::JsonFormatter& formatter)
        {
            return JsonSerializer<profiler::EventInfo>::format(t.info, formatter);
        }

        static inline void parse(profiler::Event& t, detail::JsonParser& parser) { return JsonSerializer<profiler::EventInfo>::parse(t.info, parser); }
    };
}
