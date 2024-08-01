#include "ProfilerEventCreator.h"
#include "Profiler.h"

namespace ProjectCore::ProfilerManager
{
    ScopeProfile::~ScopeProfile()
    {
        Stop();

        double millis = Info.Duration / 1000;
        double sec    = millis / 1000;

        if (sec > 1.5)
            m_Profiler.GetLogger().Trace("{} : {} seconds", Info.Name, sec);
        else if (millis > 5.0)
            m_Profiler.GetLogger().Trace("{} : {} ms", Info.Name, millis);
        else
            m_Profiler.GetLogger().Trace("{} : {} us", Info.Name, Info.Duration);

        m_Profiler.AddEvent(*this);
    }

    ObjectTracker::ObjectTracker(Profiler& profiler, const std::string& name, const std::string& category)
        : m_Profiler(profiler)
        , m_Name(name)
        , m_Category(category)
    {
        Event created(m_Name, m_Category, EventType::ObjectCreated);
        m_Profiler.AddEvent(created);
    }

    ObjectTracker::ObjectTracker(Profiler& profiler, std::string&& name, std::string&& category)
        : m_Profiler(profiler)
        , m_Name(std::move(name))
        , m_Category(std::move(category))
    {
        Event created(m_Name, m_Category, EventType::ObjectCreated);
        created.Info.Id = 10;
        m_Profiler.AddEvent(created);
    }

    ObjectTracker::~ObjectTracker()
    {
        Event destroyed(m_Name, m_Category, EventType::ObjectDestroyed);
        destroyed.Info.Id = 10;
        m_Profiler.AddEvent(destroyed);
    }

    void ObjectTracker::Snapshot()
    {
        Event snapshot(m_Name, m_Category, EventType::ObjectSnapshot);
        snapshot.Info.Id = 10;
        m_Profiler.AddEvent(snapshot);
    }

    void EventCounter::Snapshot()
    {
        m_Idx++;
        Event snapshot(m_Name, m_Category, EventType::Counter);
        m_Profiler.AddEvent(snapshot);
    }
}
