#include "profiler_event_creator.hxx"
#include "profiler.hxx"

namespace stream::profiler {
    ScopeProfile::~ScopeProfile() {
        stop();

        std::chrono::microseconds       us      = std::chrono::duration_cast<std::chrono::microseconds>(info.duration);
        std::chrono::milliseconds const millis  = std::chrono::duration_cast<std::chrono::milliseconds>(info.duration);
        std::chrono::seconds const      seconds = std::chrono::duration_cast<std::chrono::seconds>(info.duration);

        if (seconds.count() > 1.5)
            profiler_.get_logger().trace("{} : {} seconds", info.name, seconds.count());
        else if (millis.count() > 5.0)
            profiler_.get_logger().trace("{} : {} ms", info.name, millis.count());
        else
            profiler_.get_logger().trace("{} : {} us", info.name, us.count());

        profiler_.add_event(*this);
    }

    ObjectTracker::ObjectTracker(Profiler& profiler, const std::string& name, const std::string& category) : profiler_(profiler), name_(name), category_(category) {
        Event const created(name_, category_, EventType::Objectcreated);
        profiler_.add_event(created);
    }

    ObjectTracker::ObjectTracker(Profiler& profiler, std::string&& name, std::string&& category) : profiler_(profiler), name_(std::move(name)), category_(std::move(category)) {
        Event created(name_, category_, EventType::Objectcreated);
        created.info.id = 10;
        profiler_.add_event(created);
    }

    ObjectTracker::~ObjectTracker() {
        Event destroyed(name_, category_, EventType::ObjectDestroyed);
        destroyed.info.id = 10;
        profiler_.add_event(destroyed);
    }

    void ObjectTracker::snapshot() {
        Event snapshot(name_, category_, EventType::Objectsnapshot);
        snapshot.info.id = 10;
        profiler_.add_event(snapshot);
    }

    void EventCounter::snapshot() {
        idx_++;
        Event const snapshot(name_, category_, EventType::Counter);
        profiler_.add_event(snapshot);
    }
}  // namespace stream::profiler
