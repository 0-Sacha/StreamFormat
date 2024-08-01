#pragma once

#include "StreamFormat/Core/Core.h"
#include "StreamFormat/FLog.h"

#include "AllEvents.h"
#include "Event.h"
#include "ProfilerEventCreator.h"

namespace StreamFormat::ProfilerManager
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
        inline StreamFormat::FLog::BasicLogger& GetLogger() { return Logger; }

    public:
        static Profiler& GetInstance()
        {
            static Profiler profiler("Profiler");
            return profiler;
        }

    public:
        std::string            Name;
        FLog::BasicLogger      Logger;
        DurationEvent          ProfilerDuration;
        std::vector<EventInfo> Events;
    };
}
