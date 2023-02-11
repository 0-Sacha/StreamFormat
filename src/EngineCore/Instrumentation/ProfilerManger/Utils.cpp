#include "Utils.h"
#include "Profiler.h"

namespace EngineCore::Instrumentation
{
    ScopeProfile::~ScopeProfile()
    {
        Stop();
        
		double millis = Duration / 1000;
		double sec = Duration / 1000;

		if (sec > 1.5f)				m_Profiler.GetLogger().Trace("{} : {} seconds", Name, sec);
		else if (millis > 5.0f)		m_Profiler.GetLogger().Trace("{} : {} ms", Name, millis);
		else						m_Profiler.GetLogger().Trace("{} : {} us", Name, Duration);

        m_Profiler.AddEvent(*this);
    }
}
