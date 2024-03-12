#pragma once

#include "ProjectCore/Core/Core.h"
#include <chrono>

namespace ProjectCore::FMT::Detail
{
    class FormatterHandler
    {
    public:
        static void SetBeginTime()                                                                  { sm_TimeShift = std::chrono::high_resolution_clock::now(); }
        static void SetHoursShift(const std::chrono::hours& hoursShift) 							{ sm_HoursShift = hoursShift; }
        static const std::chrono::time_point<std::chrono::high_resolution_clock>& GetTimeShift()    { return sm_TimeShift; }
        static const std::chrono::hours& GetHoursShift()                                            { return sm_HoursShift; }

    private:
        FormatterHandler() = default;
        ~FormatterHandler() = default;
        FormatterHandler(const FormatterHandler& other) = delete;
        FormatterHandler(FormatterHandler&& other)        = delete;

    private:
        static inline std::chrono::time_point<std::chrono::high_resolution_clock>   sm_TimeShift;
        static inline std::chrono::hours 										    sm_HoursShift{};
    };
}

#define PROJECTCORE_FORMATTER_TIME_BEGIN()        ProjectCore::FMT::Detail::FormatterHandler::SetBeginTime()
#define PROJECTCORE_FORMATTER_SET_TIME_GTM(i)     ProjectCore::FMT::Detail::FormatterHandler::SetHoursShift(std::chrono::hours(i))
