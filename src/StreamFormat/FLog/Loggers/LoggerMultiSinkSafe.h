#pragma once

#include "LoggerMultiSinks.h"

namespace StreamFormat::FLog::Detail
{
    template <typename Severity, typename CharType>
    class BasicLoggerMultiSinkSafeImpl : public BasicLoggerMultiSinkImpl<Severity, CharType>
    {
    public:
        using Base = BasicLoggerMultiSinkImpl<Severity, CharType>;
        using Base::SetName;
        using Base::GetName;
        using Base::GetSinks;
        using Base::m_Name;
        using Base::m_Sinks;
        using Base::AddSink;

        using Base::m_StartTime;

        using typename Base::SeverityValueType;

    public:
        BasicLoggerMultiSinkSafeImpl()
            : Base()
        {}

        BasicLoggerMultiSinkSafeImpl(std::basic_string<CharType>&& name)
            : Base(std::forward<std::basic_string<CharType>>(name))
        {}

        ~BasicLoggerMultiSinkSafeImpl() override = default;

    public:
        template <typename Format = std::string_view, typename... Args>
        requires FMT::Detail::ConvertibleToBufferInfoView<Format>
        void Log(const SeverityValueType& severity, const Format& format, Args&&... args)
        {
            std::chrono::nanoseconds logTime = std::chrono::high_resolution_clock::now() - m_StartTime;

            // FIXME maybe add : name ; indent ???
            for (auto& sink : m_Sinks)
            {
                if (sink->NeedToLog(severity))
                {
                    FMT::Detail::DynamicBufferOutManager<CharType> managerPattern(256);
                    FMT::Detail::DynamicBufferOutManager<CharType> managerFormat(256);
                    auto formatPatternStr =
                        FMT::Detail::FormatInManager(managerPattern, false, std::string_view(sink->GetPattern(severity)), FORMAT_SV("time", logTime),
                                                           FORMAT_SV("name", FuturConcateNameAndSinkName(m_Name)), FORMAT_SV("data", FLog::AddIndentInFormat(format)));
                    auto formatFormatStr = FMT::Detail::FormatInManager(managerFormat, false, static_cast<std::string_view>(*formatPatternStr), std::forward<Args>(args)...,
                                                                              FORMAT_SV("sink", sink->GetName()), FORMAT_SV("color", severity));
                    sink->WriteToSink(static_cast<std::basic_string_view<CharType>>(*formatFormatStr));
                }
            }

            for (auto& sink : m_Sinks)
                if (sink->NeedToLog(severity)) sink->WaitUnitlFinishedToWrite();
        }

        template <typename T>
        void Log(const SeverityValueType& severity, T&& t)
        {
            std::chrono::nanoseconds logTime = std::chrono::high_resolution_clock::now() - m_StartTime;

            for (auto& sink : m_Sinks)
            {
                if (sink->NeedToLog(severity))
                {
                    FMT::Detail::DynamicBufferOutManager<CharType> manager(256);
                    auto formatBuffer = FMT::Detail::FormatInManager(manager, false, std::string_view(sink->GetPattern(severity)), FORMAT_SV("time", logTime),
                                                                           FORMAT_SV("name", ConcateNameAndSinkName(m_Name, sink->GetName())), FORMAT_SV("data", t));
                    sink->WriteToSink(static_cast<std::basic_string_view<CharType>>(*formatBuffer));
                }
            }

            for (auto& sink : m_Sinks)
                if (sink->NeedToLog(severity)) sink->WaitUnitlFinishedToWrite();
        }
    };
}
