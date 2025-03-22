#pragma once

#include "LoggerMultiSinks.h"

namespace stream::flog::detail
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
        void Await(const SeverityValueType& severity)
        {
            for (auto& sink : m_Sinks)
                if (sink->NeedToLog(severity)) sink->WaitUnitlFinishedToWrite();
        }

    public:
        template <typename Format = std::string_view, typename... Args>
        requires fmt::detail::ConvertibleToBufferInfoView<Format>
        [[nodiscard]] std::expected<void, fmt::FMTResult> log(const SeverityValueType& severity, const Format& format, Args&&... args)
        {
            std::chrono::nanoseconds logTime = std::chrono::high_resolution_clock::now() - m_StartTime;

            fmt::detail::DynamicBufferOutManager<CharType> manager(256);
            auto formatBuffer = SF_TRY(fmt::detail::FormatInManager(manager, false, format, std::forward<Args>(args)...));
            for (auto& sink : m_Sinks)
                if (sink->NeedToLog(severity))
                    { SF_TRY(sink->FormatAndWriteToSink(sink->get_pattern(severity), logTime, m_Name, static_cast<std::basic_string_view<CharType>>(*formatBuffer))); }

            Await(severity);
            return {};
        }

        template <typename T>
        [[nodiscard]] std::expected<void, fmt::FMTResult> log(const SeverityValueType& severity, T&& t)
        {
            std::chrono::nanoseconds logTime = std::chrono::high_resolution_clock::now() - m_StartTime;

            fmt::detail::DynamicBufferOutManager<CharType> manager(256);
            auto formatBuffer = SF_TRY(fmt::detail::FormatInManager(manager, false, std::forward<T>(t)));
            for (auto& sink : m_Sinks)
                if (sink->NeedToLog(severity))
                    { SF_TRY(sink->FormatAndWriteToSink(sink->get_pattern(severity), logTime, m_Name, static_cast<std::basic_string_view<CharType>>(*formatBuffer))); }

            Await(severity);

            return {};
        }
    };
}
