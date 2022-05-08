#pragma once

#include <chrono>

namespace EngineCore::Fmt {

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

#define ENGINE_CORE_FORMATTER_TIME_BEGIN()	EngineCore::Fmt::FormatterHandler::SetBeginTime()

#define ENGINE_CORE_FORMATTER_SET_TIME_GTM(i) EngineCore::Fmt::FormatterHandler::SetHoursShift(std::chrono::hours(i))