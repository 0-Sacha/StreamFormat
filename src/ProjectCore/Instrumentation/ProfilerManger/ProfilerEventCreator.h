#pragma once

#include "AllEvents.h"

namespace ProjectCore::Instrumentation
{
    class Profiler;

    class ScopeProfile : public DurationEvent
    {
    public:
        ScopeProfile(Profiler& profiler, const std::string& name, const std::string& category = "ScopeProfiler")
            : DurationEvent(name, category)
            , m_Profiler(profiler)
        { Start(); }

		ScopeProfile(Profiler& profiler, std::string&& name, std::string&& category = "ScopeProfiler")
			: DurationEvent(std::move(name), std::move(category))
			, m_Profiler(profiler)
		{ Start(); }

        ~ScopeProfile();
    
    private:
        Profiler& m_Profiler;
    };

    class ObjectTracker
    {
    public:
		ObjectTracker(Profiler& profiler, const std::string& name, const std::string& category = "Tracker");
		ObjectTracker(Profiler& profiler, std::string&& name, std::string&& category = "Tracker");
        ~ObjectTracker();

    public:
        void Snapshot();

    private:
        Profiler& m_Profiler;
        std::string m_Name;
        std::string m_Category;
    };

    class EventCounter
    {
    public:
		EventCounter(Profiler& profiler, const std::string& name, const std::string& category = "EventCounter")
            : m_Profiler(profiler)
            , m_Name(name)
            , m_Category(category)
            , m_Idx(0)
        {}

		EventCounter(Profiler& profiler, std::string&& name, std::string&& category = "EventCounter")
            : m_Profiler(profiler)
            , m_Name(std::move(name))
            , m_Category(std::move(category))
            , m_Idx(0)
        {}

    public:
        void Snapshot();

    private:
        Profiler& m_Profiler;
        std::string m_Name;
        std::string m_Category;
        std::uint64_t m_Idx;
    };
}
