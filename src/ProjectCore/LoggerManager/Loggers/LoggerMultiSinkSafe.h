#pragma once

#include "ProjectCore/LoggerManager/Detail/LoggerMultiSinks.h"

namespace ProjectCore::LoggerManager::Detail
{
    template <typename Severity, typename CharType>
    class BasicLoggerMultiSinkSafeImpl: public BasicLoggerMultiSinkImpl<Severity, CharType>
    {
    public:
        using Base = BasicLoggerMultiSinkImpl<Severity, CharType>;
        using Base::SetName;
        using Base::GetName;
        using Base::GetSinks;
        using Base::m_Name;
        using Base::m_Sinks;
        using Base::AddSink;
        using typename Base::SeverityValueType;

    public:
        BasicLoggerMultiSinkSafeImpl() : Base() {}
        
        BasicLoggerMultiSinkSafeImpl(std::basic_string<CharType>&& name)
            : Base(std::forward<std::basic_string<CharType>>(name))
        {}

        ~BasicLoggerMultiSinkSafeImpl() override = default;

    public:
        template<typename Format = std::string_view, typename ...Args>
        requires FMT::Detail::CanBeUseForFMTBufferIn<Format>
        void Log(const SeverityValueType& severity, const Format& format, Args&& ...args) {
            // FIXME maybe add : name ; indent ???
            for (auto& sink : m_Sinks)
            {
                if (sink->NeedToLog(severity))
                {
                    auto formatPatternStr = FMT::Detail::FormatAndGetBufferOut(std::string_view(sink->GetPattern(severity)), FORMAT_SV("name", m_Name), FORMAT_SV("data", LoggerManager::AddIndentInFormat(format)));
                    auto formatFormatStr = FMT::Detail::FormatAndGetBufferOut(static_cast<std::string_view>(*formatPatternStr), std::forward<Args>(args)..., FORMAT_SV("sink", sink->GetName()), FORMAT_SV("color", severity));
                    sink->WriteToSink(static_cast<std::basic_string_view<CharType>>(*formatFormatStr));
                }
            }

            for (auto& sink : m_Sinks)
                if (sink->NeedToLog(severity))
                    sink->WaitUnitlFinishedToWrite();
        }

        template<typename T>
        void Log(const SeverityValueType& severity, T&& t) {
            for (auto& sink : m_Sinks)
            {
                if (sink->NeedToLog(severity))
                {
                    auto formatBuffer = FMT::Detail::FormatAndGetBufferOut(std::string_view(sink->GetPattern(severity)), FORMAT_SV("name", ConcateNameAndSinkName(m_Name, sink->GetName())), FORMAT_SV("data", t));
                    sink->WriteToSink(static_cast<std::basic_string_view<CharType>>(*formatBuffer));
                }
            }
            
            for (auto& sink : m_Sinks)
                if (sink->NeedToLog(severity))
                    sink->WaitUnitlFinishedToWrite();
        }
    };
}
