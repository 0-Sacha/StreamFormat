#pragma once

#include "all_events.hxx"

namespace stream::profiler {
    class Profiler;

    class ScopeProfile : public DurationEvent {
    public:
        ScopeProfile(Profiler& profiler, const std::string& name, const std::string& category = "ScopeProfiler") : DurationEvent(name, category), profiler_(profiler) {
            start();
        }

        ScopeProfile(Profiler& profiler, std::string&& name, std::string&& category = "ScopeProfiler") : DurationEvent(std::move(name), std::move(category)), profiler_(profiler) {
            start();
        }

        ~ScopeProfile() override;

    private:
        Profiler& profiler_;
    };

    class ObjectTracker {
    public:
        ObjectTracker(Profiler& profiler, const std::string& name, const std::string& category = "Tracker");
        ObjectTracker(Profiler& profiler, std::string&& name, std::string&& category = "Tracker");
        virtual ~ObjectTracker();

    public:
        void snapshot();

    private:
        Profiler&   profiler_;
        std::string name_;
        std::string category_;
    };

    class EventCounter {
    public:
        EventCounter(Profiler& profiler, const std::string& name, const std::string& category = "EventCounter") : profiler_(profiler), name_(name), category_(category), idx_(0) {}

        EventCounter(Profiler& profiler, std::string&& name, std::string&& category = "EventCounter")
            : profiler_(profiler), name_(std::move(name)), category_(std::move(category)), idx_(0) {}

    public:
        void snapshot();

    private:
        Profiler&     profiler_;
        std::string   name_;
        std::string   category_;
        std::uint64_t idx_;
    };
}  // namespace stream::profiler
