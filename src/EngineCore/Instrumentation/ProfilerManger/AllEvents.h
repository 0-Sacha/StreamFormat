#pragma once

#include "Event.h"

namespace EngineCore::Instrumentation
{
    class DurationEvent : public Event
    {
    public:
		DurationEvent(const std::string& name, const std::string& category)
			: Event(name, category, EventType::Complete)
		{}

        DurationEvent(std::string&& name, std::string&& category)
            : Event(std::move(name), std::move(category), EventType::Complete)
        {}

    public:
        void Start()    { Trigger(); }
        void Stop()     { Duration = Instrumentation::GetMicroseconds() - TimeOfEvent; }
    };
}
