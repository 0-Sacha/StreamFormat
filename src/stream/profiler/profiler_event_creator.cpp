#include "profiler_event_creator.h"
#include "profiler.h"

namespace stream::profiler
{
    ScopeProfile::~ScopeProfile()
    {
        stop();

        double millis = info.Duration / 1000;
        double sec    = millis / 1000;

        if (sec > 1.5)
            profiler_.get_logger().trace("{} : {} seconds", info.name, sec);
        else if (millis > 5.0)
            profiler_.get_logger().trace("{} : {} ms", info.name, millis);
        else
            profiler_.get_logger().trace("{} : {} us", info.name, info.Duration);

        profiler_.add_event(*this);
    }

    ObjectTracker::ObjectTracker(Profiler& profiler, const std::string& name, const std::string& category)
        : profiler_(profiler)
        , name_(name)
        , category_(category)
    {
        Event created(name_, category_, EventType::Objectcreated);
        profiler_.add_event(created);
    }

    ObjectTracker::ObjectTracker(Profiler& profiler, std::string&& name, std::string&& category)
        : profiler_(profiler)
        , name_(std::move(name))
        , category_(std::move(category))
    {
        Event created(name_, category_, EventType::Objectcreated);
        created.info.Id = 10;
        profiler_.add_event(created);
    }

    ObjectTracker::~ObjectTracker()
    {
        Event destroyed(name_, category_, EventType::ObjectDestroyed);
        destroyed.info.Id = 10;
        profiler_.add_event(destroyed);
    }

    void ObjectTracker::snapshot()
    {
        Event snapshot(name_, category_, EventType::Objectsnapshot);
        snapshot.info.Id = 10;
        profiler_.add_event(snapshot);
    }

    void EventCounter::snapshot()
    {
        idx_++;
        Event snapshot(name_, category_, EventType::Counter);
        profiler_.add_event(snapshot);
    }
}
