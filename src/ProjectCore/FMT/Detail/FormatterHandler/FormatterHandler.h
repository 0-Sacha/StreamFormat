#pragma once

#include "ProjectCore/Core/Core.h"
#include <chrono>

namespace ProjectCore::FMT::Detail {

	class FormatterHandler {

	public:
		static FormatterHandler& GetInstance();

	public:
		static void SetBeginTime()																	{ GetInstance().m_TimeShift = std::chrono::high_resolution_clock::now(); }
		static void SetHoursShift(const std::chrono::hours& hoursShift)								{ GetInstance().m_HoursShift = hoursShift; }
		static const std::chrono::time_point<std::chrono::high_resolution_clock>& GetTimeShift()	{ return GetInstance().m_TimeShift; }
		static const std::chrono::hours& GetHoursShift()											{ return GetInstance().m_HoursShift; }

	private:
		FormatterHandler()
			: m_TimeShift(std::chrono::high_resolution_clock::now())
			, m_HoursShift{}
		{}

		~FormatterHandler() = default;
		FormatterHandler(const FormatterHandler& other) = delete;
		FormatterHandler(FormatterHandler&& other)		= delete;

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_TimeShift;
		std::chrono::hours											m_HoursShift{};
	};
}

#define PROJECTCORE_FORMATTER_TIME_BEGIN()		ProjectCore::FMT::Detail::FormatterHandler::SetBeginTime()
#define PROJECTCORE_FORMATTER_SET_TIME_GTM(i) 	ProjectCore::FMT::Detail::FormatterHandler::SetHoursShift(std::chrono::hours(i))
