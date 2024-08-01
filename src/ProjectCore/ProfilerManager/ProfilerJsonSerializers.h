#pragma once

#include "ProfilerFactory.h"
#include "ProjectCore/Json.h"

namespace ProjectCore::JSON
{
    template <>
    struct JsonSerializer<ProfilerManager::Profiler>
    {
        static inline void Format(const ProfilerManager::Profiler& t, Detail::JsonFormatter& formatter)
        {
            auto intermediate = formatter.GetStructIntermediate();
            intermediate.Format("displayTimeUnit", "us");
            intermediate.Format("traceEvents", t.Events);
        }

        static inline void Parse(ProfilerManager::Profiler& t, Detail::JsonParser& parser)
        {
            auto intermediate = parser.GetStructIntermediate();
            intermediate.Parse("traceEvents", t.Events);
        }
    };

    template <>
    struct JsonSerializer<ProfilerManager::EventType>
    {
        static inline void Format(const ProfilerManager::EventType& t, Detail::JsonFormatter& formatter) { formatter.Format(static_cast<char>(t)); }

        static inline void Parse(ProfilerManager::EventType& t, Detail::JsonParser& parser) { parser.Parse(reinterpret_cast<char&>(t)); }
    };

    template <>
    struct JsonSerializer<ProfilerManager::EventData>
    {
        static inline void Format(const ProfilerManager::EventData& t, Detail::JsonFormatter& formatter) { t.ToJson(formatter); }

        static inline void Parse(ProfilerManager::EventData& t, Detail::JsonParser& parser) { t.FromJson(parser); }
    };

    template <>
    struct JsonSerializer<ProfilerManager::EventInfo>
    {
        static inline void Format(const ProfilerManager::EventInfo& t, Detail::JsonFormatter& formatter)
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
            if (t.Data != nullptr) intermediate.Format("args", *t.Data);
        }

        static inline void Parse(ProfilerManager::EventInfo& t, Detail::JsonParser& parser)
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
    struct JsonSerializer<ProfilerManager::Event>
    {
        static inline void Format(const ProfilerManager::Event& t, Detail::JsonFormatter& formatter)
        {
            return JsonSerializer<ProfilerManager::EventInfo>::Format(t.Info, formatter);
        }

        static inline void Parse(ProfilerManager::Event& t, Detail::JsonParser& parser) { return JsonSerializer<ProfilerManager::EventInfo>::Parse(t.Info, parser); }
    };
}
