#pragma once

#include "stream/core/prelude.h"
#include "stream/flog.h"

#include "AllEvents.h"
#include "Event.h"
#include "ProfilerEventCreator.h"

namespace stream::ProfilerManager
{
    class Profiler
    {
    public:
        explicit Profiler(std::string&& name)
            : Name(name)
            , Logger(name)
            , ProfilerDuration(name)
        {
            Events.clear();
            Events.push_back(EventInfo{});
            ProfilerDuration.Start();
        }

        ~Profiler() {}

    public:
        void                                   AddEvent(const Event& event) { AddEventInfo(event.Info); }
        void                                   AddEventInfo(const EventInfo& eventInfo) { Events.push_back(eventInfo); }
        inline stream::flog::BasicLogger& GetLogger() { return Logger; }

    public:
        static Profiler& GetInstance()
        {
            static Profiler profiler("Profiler");
            return profiler;
        }

    public:
        std::string            Name;
        flog::BasicLogger      Logger;
        DurationEvent          ProfilerDuration;
        std::vector<EventInfo> Events;
    };
}
