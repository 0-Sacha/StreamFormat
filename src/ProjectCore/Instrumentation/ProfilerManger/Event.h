#pragma once

#include "ProjectCore/Core/Core.h"
#include "ProjectCore/FMT/FMT.h"
#include "EventData.h"
#include "Detail.h"

#include <string>
#include <memory>

#ifdef PROJECTCORE_PLATFORM_LINUX
    #include <sys/types.h>
    #include <unistd.h>
#endif

// https://docs.google.com/document/d/1CvAClvFfyA5R-PhYUmn5OOQtYMH4h6I0nSsKchNAySU/preview

namespace ProjectCore::Instrumentation
{
    enum class EventType : char
    {
        DurationBegin = 'B',
        DurationEnd = 'E',

        AsyncStart = 'b',
        AsyncInstant = 'n',
        AsyncEnd = 'e',

        FlowStart = 's',
        FlowStep = 't',
        FlowEnd = 'f',
        
        ObjectCreated = 'N',
        ObjectSnapshot = 'O',
        ObjectDestroyed = 'D',
        
        MemoryDumpGlobal = 'V',
        MemoryDumpProcess = 'v',
 
        Complete = 'X',
        Instant = 'i',
        Counter = 'C',
        Sample = 'P',
        MetaData = 'M',
        Mark = 'R',
        ClockSyncEvents = 'c',
        Context = ',' // '(' ')'
    };

	struct Event
	{
	public:
	    Event() = default;
        
	    Event(const std::string& name, const std::string& category, EventType type, EventData* data = nullptr)
            : Name(name)
            , Category(category)
            , Type(type)
            , Id(0)
            , TimeOfEvent(Instrumentation::GetMicroseconds())
            , ThreadTimeOfEvent(0)
            , Duration(0)
#ifdef PROJECTCORE_COMPILER_VS
            , PID(_getpid())
#else
            , PID(getpid())
#endif
            , TID(std::hash<std::thread::id>{}(std::this_thread::get_id()))
            , Data(data)
        {}

		Event(std::string&& name, std::string&& category, EventType type, EventData* data = nullptr)
			: Name(std::move(name))
			, Category(std::move(category))
			, Type(type)
			, Id(0)
			, TimeOfEvent(Instrumentation::GetMicroseconds())
			, ThreadTimeOfEvent(0)
			, Duration(0)
#ifdef PROJECTCORE_COMPILER_VS
            , PID(_getpid())
#else
            , PID(getpid())
#endif
			, TID(std::hash<std::thread::id>{}(std::this_thread::get_id()))
			, Data(data)
		{}

		~Event() {}

	public:
        void Trigger() { TimeOfEvent = Instrumentation::GetMicroseconds(); }

	public:
		std::string Name;
		std::string Category;
        EventType Type;
        std::size_t Id;
		double TimeOfEvent, ThreadTimeOfEvent;
		double Duration;
		std::size_t PID, TID;
        std::shared_ptr<EventData> Data;
	};
}

namespace ProjectCore::FMT
{
	template<typename FormatterContext>
	struct FormatterType<ProjectCore::Instrumentation::EventType, FormatterContext>
	{
		static void Format(const ProjectCore::Instrumentation::EventType& t, FormatterContext& context) {
            context.BufferOut().PushBack(static_cast<char>(t));
		}
	};
}
