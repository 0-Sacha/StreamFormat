#pragma once

#include "Detail.h"
#include "EventData.h"
#include "ProjectCore/Core/Core.h"
#include "ProjectCore/FMT.h"

#include <memory>
#include <string>
#include <thread>

// https://docs.google.com/document/d/1CvAClvFfyA5R-PhYUmn5OOQtYMH4h6I0nSsKchNAySU/preview

namespace ProjectCore::ProfilerManager
{
    int GetPid();

    enum class EventType : char
    {
        Unknow = '.',

        DurationBegin = 'B',
        DurationEnd   = 'E',

        AsyncStart   = 'b',
        AsyncInstant = 'n',
        AsyncEnd     = 'e',

        FlowStart = 's',
        FlowStep  = 't',
        FlowEnd   = 'f',

        ObjectCreated   = 'N',
        ObjectSnapshot  = 'O',
        ObjectDestroyed = 'D',

        MemoryDumpGlobal  = 'V',
        MemoryDumpProcess = 'v',

        Complete        = 'X',
        Instant         = 'i',
        Counter         = 'C',
        Sample          = 'P',
        MetaData        = 'M',
        Mark            = 'R',
        ClockSyncEvents = 'c',
        Context         = ','  // '(' ')'
    };

    struct EventInfo
    {
    public:
        EventInfo()
            : Name("Unknow")
            , Category("Unknow")
            , Type(EventType::Unknow)
            , Id(0)
            , TimeOfEvent(ProfilerManager::GetMicroseconds())
            , ThreadTimeOfEvent(0)
            , Duration(0)
            , PID(GetPid())
            , TID(std::hash<std::thread::id>{}(std::this_thread::get_id()))
            , Data(nullptr)
        {}

        EventInfo(const std::string& name, const std::string& category, EventType type, EventData* data = nullptr)
            : Name(name)
            , Category(category)
            , Type(type)
            , Id(0)
            , TimeOfEvent(ProfilerManager::GetMicroseconds())
            , ThreadTimeOfEvent(0)
            , Duration(0)
            , PID(GetPid())
            , TID(std::hash<std::thread::id>{}(std::this_thread::get_id()))
            , Data(data)
        {}

        EventInfo(std::string&& name, std::string&& category, EventType type, EventData* data = nullptr)
            : Name(std::move(name))
            , Category(std::move(category))
            , Type(type)
            , Id(0)
            , TimeOfEvent(ProfilerManager::GetMicroseconds())
            , ThreadTimeOfEvent(0)
            , Duration(0)
            , PID(GetPid())
            , TID(std::hash<std::thread::id>{}(std::this_thread::get_id()))
            , Data(data)
        {}

    public:
        std::string                Name;
        std::string                Category;
        EventType                  Type;
        std::size_t                Id;
        double                     TimeOfEvent, ThreadTimeOfEvent;
        double                     Duration;
        int                        PID;
        std::size_t                TID;
        std::shared_ptr<EventData> Data;
    };

    struct Event
    {
    public:
        Event() = default;

        Event(const std::string& name, const std::string& category, EventType type, EventData* data = nullptr)
            : Info(name, category, type, data)
        {}

        Event(std::string&& name, std::string&& category, EventType type, EventData* data = nullptr)
            : Info(std::move(name), std::move(category), type, data)
        {}

        virtual ~Event() = default;

    public:
        void Trigger() { Info.TimeOfEvent = ProfilerManager::GetMicroseconds(); }

    public:
        EventInfo Info;
    };
}

namespace ProjectCore::FMT
{
    template <typename FormatterContext>
    struct FormatterType<ProjectCore::ProfilerManager::EventType, FormatterContext>
    {
        static void Format(const ProjectCore::ProfilerManager::EventType& t, FormatterContext& context) { context.BufferOut().PushBack(static_cast<char>(t)); }
    };
}
