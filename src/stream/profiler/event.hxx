#pragma once

#include "detail.hxx"
#include "event_data.hxx"
#include "stream/core/prelude.hxx"
#include "stream/fmt.hxx"

#include <memory>
#include <string>
#include <thread>
#include <chrono>

// https://docs.google.com/document/d/1CvAClvFfyA5R-PhYUmn5OOQtYMH4h6I0nSsKchNAySU/preview

namespace stream::profiler {
    int get_pid();

    enum class EventType : char {
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

    struct EventInfo {
    public:
        EventInfo()
            : name("Unknow"),
              category("Unknow"),
              type(EventType::Unknow),
              id(0),
              time_of_event(profiler::get_nanoseconds()),
              duration(0),
              pid(get_pid()),
              tid(std::hash<std::thread::id>{}(std::this_thread::get_id())),
              data(nullptr) {}

        EventInfo(const std::string& name, const std::string& category, EventType type, EventData* data = nullptr)
            : name(name),
              category(category),
              type(type),
              id(0),
              time_of_event(profiler::get_nanoseconds()),
              duration(0),
              pid(get_pid()),
              tid(std::hash<std::thread::id>{}(std::this_thread::get_id())),
              data(data) {}

        EventInfo(std::string&& name, std::string&& category, EventType type, EventData* data = nullptr)
            : name(std::move(name)),
              category(std::move(category)),
              type(type),
              id(0),
              time_of_event(profiler::get_nanoseconds()),
              duration(0),
              pid(get_pid()),
              tid(std::hash<std::thread::id>{}(std::this_thread::get_id())),
              data(data) {}

    public:
        std::string                name;
        std::string                category;
        EventType                  type;
        std::size_t                id;
        std::chrono::nanoseconds   time_of_event;
        std::chrono::nanoseconds   duration;
        int                        pid;
        std::size_t                tid;
        std::shared_ptr<EventData> data;
    };

    struct Event {
    public:
        Event() = default;

        Event(const std::string& name, const std::string& category, EventType type, EventData* data = nullptr) : info(name, category, type, data) {}

        Event(std::string&& name, std::string&& category, EventType type, EventData* data = nullptr) : info(std::move(name), std::move(category), type, data) {}

        virtual ~Event() = default;

    public:
        void trigger() {
            info.time_of_event = profiler::get_nanoseconds();
        }

    public:
        EventInfo info;
    };
}  // namespace stream::profiler

namespace stream::fmt {
    template <typename FormatterExecutor>
    struct FormatterType<stream::profiler::EventType, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(const stream::profiler::EventType& t, FormatterExecutor& executor) {
            return executor.ostream.pushback(static_cast<char>(t));
        }
    };
}  // namespace stream::fmt
