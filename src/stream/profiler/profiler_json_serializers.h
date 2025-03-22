#pragma once

#include "ProfilerFactory.h"
#include "stream/Json.h"

namespace stream::JSON
{
    template <>
    struct JsonSerializer<ProfilerManager::Profiler>
    {
        static inline void format(const ProfilerManager::Profiler& t, detail::JsonFormatter& formatter)
        {
            auto intermediate = formatter.GetStructIntermediate();
            intermediate.format("displayTimeUnit", "us");
            intermediate.format("traceEvents", t.Events);
        }

        static inline void parse(ProfilerManager::Profiler& t, detail::JsonParser& parser)
        {
            auto intermediate = parser.GetStructIntermediate();
            intermediate.parse("traceEvents", t.Events);
        }
    };

    template <>
    struct JsonSerializer<ProfilerManager::EventType>
    {
        static inline void format(const ProfilerManager::EventType& t, detail::JsonFormatter& formatter) { formatter.format(static_cast<char>(t)); }

        static inline void parse(ProfilerManager::EventType& t, detail::JsonParser& parser) { parser.parse(reinterpret_cast<char&>(t)); }
    };

    template <>
    struct JsonSerializer<ProfilerManager::EventData>
    {
        static inline void format(const ProfilerManager::EventData& t, detail::JsonFormatter& formatter) { t.ToJson(formatter); }

        static inline void parse(ProfilerManager::EventData& t, detail::JsonParser& parser) { t.FromJson(parser); }
    };

    template <>
    struct JsonSerializer<ProfilerManager::EventInfo>
    {
        static inline void format(const ProfilerManager::EventInfo& t, detail::JsonFormatter& formatter)
        {
            auto intermediate = formatter.GetStructIntermediate();
            intermediate.format("name", t.Name);
            intermediate.format("cat", t.Category);
            intermediate.format("ph", t.Type);
            intermediate.format("pid", t.PID);
            intermediate.format("tid", t.TID);
            intermediate.format("ts", t.TimeOfEvent);
            intermediate.format("dur", t.Duration);
            intermediate.format("id", t.Id);
            if (t.Data != nullptr) intermediate.format("args", *t.Data);
        }

        static inline void parse(ProfilerManager::EventInfo& t, detail::JsonParser& parser)
        {
            auto intermediate = parser.GetStructIntermediate();
            intermediate.parse("name", t.Name);
            intermediate.parse("cat", t.Category);
            intermediate.parse("ph", t.Type);
            intermediate.parse("pid", t.PID);
            intermediate.parse("tid", t.TID);
            intermediate.parse("ts", t.TimeOfEvent);
            intermediate.parse("dur", t.Duration);
            intermediate.parse("id", t.Id);
            intermediate.parse("args", *t.Data);
        }
    };

    template <>
    struct JsonSerializer<ProfilerManager::Event>
    {
        static inline void format(const ProfilerManager::Event& t, detail::JsonFormatter& formatter)
        {
            return JsonSerializer<ProfilerManager::EventInfo>::format(t.Info, formatter);
        }

        static inline void parse(ProfilerManager::Event& t, detail::JsonParser& parser) { return JsonSerializer<ProfilerManager::EventInfo>::parse(t.Info, parser); }
    };
}
