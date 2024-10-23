#pragma once

#include "LoggerMultiSinks.h"

namespace StreamFormat::FLog::Detail
{
    template <typename Severity, typename CharType>
    class BasicLoggerMultiSinkFastImpl : public BasicLoggerMultiSinkImpl<Severity, CharType>
    {
    public:
        using Base = BasicLoggerMultiSinkImpl<Severity, CharType>;
        using Base::SetName;
        using Base::GetName;
        using Base::GetSinks;
        using Base::AddSink;
        using Base::m_Name;
        using Base::m_Sinks;

        using Base::m_StartTime;

        using typename Base::SeverityValueType;

    public:
        BasicLoggerMultiSinkFastImpl()
            : Base()
        {}

        BasicLoggerMultiSinkFastImpl(std::basic_string<CharType>&& name)
            : Base(std::forward<std::basic_string<CharType>>(name))
        {}

        ~BasicLoggerMultiSinkFastImpl() override = default;

    public:
        template <typename Format = std::string_view, typename... Args>
        requires FMT::Detail::ConvertibleToBufferInfoView<Format>
        void Log(const SeverityValueType& severity, const Format& format, Args&&... args)
        {
            std::chrono::nanoseconds logTime = std::chrono::high_resolution_clock::now() - m_StartTime;

            FMT::Detail::DynamicBufferOutManager<CharType> manager(256);
            auto formatBuffer = FMT::Detail::FormatInManager(manager, false, format, std::forward<Args>(args)...);
            for (auto& sink : m_Sinks)
                if (sink->NeedToLog(severity))
                    sink->FormatAndWriteToSink(sink->GetPattern(severity), logTime, m_Name, static_cast<std::basic_string_view<CharType>>(*formatBuffer));

            for (auto& sink : m_Sinks)
                if (sink->NeedToLog(severity)) sink->WaitUnitlFinishedToWrite();
        }

        template <typename T>
        void Log(const SeverityValueType& severity, T&& t)
        {
            std::chrono::nanoseconds logTime = std::chrono::high_resolution_clock::now() - m_StartTime;

            FMT::Detail::DynamicBufferOutManager<CharType> manager(256);
            auto formatBuffer = FMT::Detail::FormatInManager(manager, false, std::forward<T>(t));
            for (auto& sink : m_Sinks)
                if (sink->NeedToLog(severity))
                    sink->FormatAndWriteToSink(sink->GetPattern(severity), logTime, m_Name, static_cast<std::basic_string_view<CharType>>(*formatBuffer));

            for (auto& sink : m_Sinks)
                if (sink->NeedToLog(severity)) sink->WaitUnitlFinishedToWrite();
        }
    };
}
