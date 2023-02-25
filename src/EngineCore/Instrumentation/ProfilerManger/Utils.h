#pragma once

#include "AllEvents.h"

namespace EngineCore::Instrumentation
{
    class Profiler;

    class ScopeProfile : public DurationEvent
    {
    public:
        ScopeProfile(Profiler& profiler, const std::string& name, const std::string& category)
            : DurationEvent(name, category)
            , m_Profiler(profiler)
        { Start(); }

		ScopeProfile(Profiler& profiler, std::string&& name, std::string&& category)
			: DurationEvent(std::move(name), std::move(category))
			, m_Profiler(profiler)
		{ Start(); }

        ~ScopeProfile();
    
    private:
        Profiler& m_Profiler;
    };
}
