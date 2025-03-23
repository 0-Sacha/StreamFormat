#pragma once

#include "detail.h"
#include "event_data.h"
#include "stream/core/prelude.h"
#include "stream/fmt.h"

#include <memory>
#include <string>
#include <thread>

// https://docs.google.com/document/d/1CvAClvFfyA5R-PhYUmn5OOQtYMH4h6I0nSsKchNAySU/preview

namespace stream::profiler
{
    int GetPid();

    enum class EventType : char
    {
        Unknow = '.',

        DurationBegin = 'b',
        DurationEnd   = 'E',

        AsyncStart   = 'b',
        AsyncInstant = 'n',
        AsyncEnd     = 'e',

        FlowStart = 's',
        FlowStep  = 't',
        FlowEnd   = 'f',

        Objectcreated   = 'N',
        Objectsnapshot  = 'O',
        ObjectDestroyed = 'D',

        MemoryDumpGlobal  = 'V',
        MemoryDumpProcess = 'v',

        Complete        = 'X',
        Instant         = 'i',
        Counter         = 'C',
        Sample          = 'P',
        MetaData        = 'M',
        Mark            = 'r',
        ClockSyncEvents = 'c',
        Context         = ','  // '(' ')'
    };

    struct EventInfo
    {
    public:
        EventInfo()
            : name("Unknow")
            , Category("Unknow")
            , type(EventType::Unknow)
            , Id(0)
            , TimeOfEvent(profiler::get_microseconds())
            , ThreadTimeOfEvent(0)
            , Duration(0)
            , PID(GetPid())
            , TID(std::hash<std::thread::id>{}(std::this_thread::get_id()))
            , data(nullptr)
        {}

        EventInfo(const std::string& name, const std::string& category, EventType type, EventData* data = nullptr)
            : name(name)
            , Category(category)
            , type(type)
            , Id(0)
            , TimeOfEvent(profiler::get_microseconds())
            , ThreadTimeOfEvent(0)
            , Duration(0)
            , PID(GetPid())
            , TID(std::hash<std::thread::id>{}(std::this_thread::get_id()))
            , data(data)
        {}

        EventInfo(std::string&& name, std::string&& category, EventType type, EventData* data = nullptr)
            : name(std::move(name))
            , Category(std::move(category))
            , type(type)
            , Id(0)
            , TimeOfEvent(profiler::get_microseconds())
            , ThreadTimeOfEvent(0)
            , Duration(0)
            , PID(GetPid())
            , TID(std::hash<std::thread::id>{}(std::this_thread::get_id()))
            , data(data)
        {}

    public:
        std::string                name;
        std::string                Category;
        EventType                  type;
        std::size_t                Id;
        double                     TimeOfEvent, ThreadTimeOfEvent;
        double                     Duration;
        int                        PID;
        std::size_t                TID;
        std::shared_ptr<EventData> data;
    };

    struct Event
    {
    public:
        Event() = default;

        Event(const std::string& name, const std::string& category, EventType type, EventData* data = nullptr)
            : info(name, category, type, data)
        {}

        Event(std::string&& name, std::string&& category, EventType type, EventData* data = nullptr)
            : info(std::move(name), std::move(category), type, data)
        {}

        virtual ~Event() = default;

    public:
        void trigger() { info.TimeOfEvent = profiler::get_microseconds(); }

    public:
        EventInfo info;
    };
}

namespace stream::fmt
{
    template <typename FormatterExecutor>
    struct FormatterType<stream::profiler::EventType, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const stream::profiler::EventType& t, FormatterExecutor& executor)
            { return executor.ostream.pushback(static_cast<char>(t)); }
    };
}
