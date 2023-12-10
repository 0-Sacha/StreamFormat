#pragma once

#include "ProjectCore/Core/Core.h"
#include "LoggerManager/LoggerManager.h"

#include "Event.h"
#include "AllEvents.h"
#include "ProfilerEventCreator.h"

namespace ProjectCore::Instrumentation
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
        void AddEvent(const Event& event)                           { AddEventInfo(event.Info); }
        void AddEventInfo(const EventInfo& eventInfo)               { Events.push_back(eventInfo); }
        inline ProjectCore::LoggerManager::BasicLogger& GetLogger() { return Logger; }

    public:
        static Profiler& GetInstance()                              { static Profiler profiler("Profiler"); return profiler; }

    public:
        std::string Name;
        LoggerManager::BasicLogger Logger;
        DurationEvent ProfilerDuration;
        std::vector<EventInfo> Events;
    };
}
