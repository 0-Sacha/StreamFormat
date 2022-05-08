#pragma once

#include "EngineCore/Core.h"
#include <chrono>

namespace EngineCore::Instrumentation::Fmt {

	class FormatterHandler {

	public:
		static FormatterHandler& GetInstance();

	public:
		static void SetBeginTime()																	{ GetInstance().m_TimeShift = std::chrono::high_resolution_clock::now(); }
		static void SetHoursShift(const std::chrono::hours& hoursShift)								{ GetInstance().m_HoursShift = hoursShift; }
		static const std::chrono::time_point<std::chrono::high_resolution_clock>& GetTimeShift()	{ return GetInstance().m_TimeShift; }
		static const std::chrono::hours& GetHoursShift()											{ return GetInstance().m_HoursShift; }

	private:
		FormatterHandler() = default;
		~FormatterHandler() = default;

		FormatterHandler(const FormatterHandler& other) = delete;

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_TimeShift;
		std::chrono::hours m_HoursShift{};
	};
}

#define ENGINECORE_FORMATTER_TIME_BEGIN()	EngineCore::Instrumentation::Fmt::FormatterHandler::SetBeginTime()

#define ENGINECORE_FORMATTER_SET_TIME_GTM(i) EngineCore::Instrumentation::Fmt::FormatterHandler::SetHoursShift(std::chrono::hours(i))