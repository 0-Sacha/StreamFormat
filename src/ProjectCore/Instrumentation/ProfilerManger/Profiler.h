#pragma once

#include "ProjectCore/Core/Core.h"
#include "LoggerManager/LoggerManager.h"

#include "Event.h"
#include "AllEvents.h"
#include "ProfilerEventCreator.h"

namespace ProjectCore::Instrumentation
{
	class Profiler
	{
	public:
		explicit Profiler(std::string&& name)
			: Name(name)
			, Logger(name)
		{
			Events.clear();
			Events.push_back(DurationEvent(name, "Profiler"));
			GetProfilerProfile().Start();
		}

		~Profiler() {}

	public:
		DurationEvent& GetProfilerProfile() 						{ return *reinterpret_cast<DurationEvent*>(&Events[0]); }
		void AddEvent(const Event& event) 							{ Events.push_back(event); }
		inline ProjectCore::LoggerManager::BasicLogger& GetLogger() { return Logger; }

	public:
		static Profiler& GetInstance()								{ static Profiler profiler("Profiler"); return profiler; }

	public:
		std::string Name;
		LoggerManager::BasicLogger Logger;
		std::vector<Event> Events;
	};
}
