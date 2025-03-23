#pragma once

#include "stream/core/prelude.h"
#include "stream/flog.h"

#include "all_events.h"
#include "event.h"
#include "profiler_event_creator.h"

namespace stream::profiler
{
    class Profiler
    {
    public:
        explicit Profiler(std::string&& name)
            : name(name)
            , logger(name)
            , profiler_duration(name)
        {
            events.clear();
            events.push_back(EventInfo{});
            profiler_duration.start();
        }

        ~Profiler() {}

    public:
        void                                   add_event(const Event& event) { add_event_info(event.info); }
        void                                   add_event_info(const EventInfo& eventInfo) { events.push_back(eventInfo); }
        inline stream::flog::BasicLogger& get_logger() { return logger; }

    public:
        static Profiler& get_instance()
        {
            static Profiler profiler("profiler");
            return profiler;
        }

    public:
        std::string            name;
        flog::BasicLogger      logger;
        DurationEvent          profiler_duration;
        std::vector<EventInfo> events;
    };
}
