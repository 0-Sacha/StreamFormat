#pragma once

#include "event.h"

namespace stream::profiler
{
    class DurationEvent : public Event
    {
    public:
        DurationEvent(const std::string& name, const std::string& category = "DurationEvent")
            : Event(name, category, EventType::Complete)
        {}

        DurationEvent(std::string&& name, std::string&& category = "DurationEvent")
            : Event(std::move(name), std::move(category), EventType::Complete)
        {}

        ~DurationEvent() override = default;

    public:
        void start() { trigger(); }
        void Stop() { info.Duration = profiler::get_microseconds() - info.TimeOfEvent; }
    };

    class SampleEvent : public Event
    {
    public:
        SampleEvent(const std::string& name, const std::string& category = "SampleEvent")
            : Event(name, category, EventType::Sample)
        {}

        SampleEvent(std::string&& name, std::string&& category)
            : Event(std::move(name), std::move(category), EventType::Sample)
        {}

        ~SampleEvent() override = default;
    };
}
