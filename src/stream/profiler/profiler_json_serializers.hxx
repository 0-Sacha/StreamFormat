#pragma once

#include "profiler_factory.h"
#include "stream/json.h"

namespace stream::json {
    template <>
    struct JsonSerializer<profiler::Profiler> {
        static inline void format(const profiler::Profiler& t, detail::JsonFormatter& formatter) {
            auto intermediate = formatter.get_struct_intermediate();
            intermediate.format("displayTimeUnit", "us");
            intermediate.format("traceEvents", t.events);
        }

        static inline void parse(profiler::Profiler& t, detail::JsonParser& parser) {
            auto intermediate = parser.get_struct_intermediate();
            intermediate.parse("traceEvents", t.events);
        }
    };

    template <>
    struct JsonSerializer<profiler::EventType> {
        static inline void format(const profiler::EventType& t, detail::JsonFormatter& formatter) {
            formatter.format(static_cast<char>(t));
        }

        static inline void parse(profiler::EventType& t, detail::JsonParser& parser) {
            parser.parse(reinterpret_cast<char&>(t));
        }
    };

    template <>
    struct JsonSerializer<profiler::EventData> {
        static inline void format(const profiler::EventData& t, detail::JsonFormatter& formatter) {
            t.to_json(formatter);
        }

        static inline void parse(profiler::EventData& t, detail::JsonParser& parser) {
            t.FromJson(parser);
        }
    };

    template <>
    struct JsonSerializer<profiler::EventInfo> {
        static inline void format(const profiler::EventInfo& t, detail::JsonFormatter& formatter) {
            auto intermediate = formatter.get_struct_intermediate();
            intermediate.format("name", t.name);
            intermediate.format("cat", t.category);
            intermediate.format("ph", t.type);
            intermediate.format("pid", t.pid);
            intermediate.format("tid", t.tid);
            intermediate.format("ts", t.time_of_event);
            intermediate.format("dur", t.duration);
            intermediate.format("id", t.id);
            if (t.data != nullptr) intermediate.format("args", *t.data);
        }

        static inline void parse(profiler::EventInfo& t, detail::JsonParser& parser) {
            auto intermediate = parser.get_struct_intermediate();
            intermediate.parse("name", t.name);
            intermediate.parse("cat", t.category);
            intermediate.parse("ph", t.type);
            intermediate.parse("pid", t.pid);
            intermediate.parse("tid", t.tid);
            intermediate.parse("ts", t.time_of_event);
            intermediate.parse("dur", t.duration);
            intermediate.parse("id", t.id);
            intermediate.parse("args", *t.data);
        }
    };

    template <>
    struct JsonSerializer<profiler::Event> {
        static inline void format(const profiler::Event& t, detail::JsonFormatter& formatter) {
            return JsonSerializer<profiler::EventInfo>::format(t.info, formatter);
        }

        static inline void parse(profiler::Event& t, detail::JsonParser& parser) {
            return JsonSerializer<profiler::EventInfo>::parse(t.info, parser);
        }
    };
}  // namespace stream::json
