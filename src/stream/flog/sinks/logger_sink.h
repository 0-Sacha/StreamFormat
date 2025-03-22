#pragma once

#include "stream/flog/detail/detail.h"

#include <future>

namespace stream::flog::detail
{
    enum class AsyncSink
    {
        Sync,
        Async
    };

    template <typename Severity, typename CharType>
    class BasicLoggerSink
    {
    public:
        using PatternType          = std::basic_string<CharType>;
        using PatternTransfertType = std::basic_string_view<CharType>;
        using NameType             = std::basic_string<CharType>;
        using BufferType           = std::basic_string_view<CharType>;

        using SeverityValueType = typename Severity::Value;

    public:
        BasicLoggerSink(NameType&& name)
            : Name(std::forward<NameType>(name))
            , IsAsync(AsyncSink::Sync)
        {}

        BasicLoggerSink(NameType&& name, AsyncSink isAsync)
            : Name(std::forward<NameType>(name))
            , IsAsync(isAsync)
        {}

        virtual ~BasicLoggerSink() = default;

    public:
        NameType                           Name    = "";
        PatternType                        Pattern = "[{time:pattern='%h:%m:%s:%ms'}] {name} >> {data}";
        SeverityValueType                  SinkSeverity{SeverityValueType::DefaultSeverity};
        typename Severity::PatternOverride SeverityPatternOverride;
        AsyncSink                          IsAsync;

    protected:
        std::future<void> m_AsyncWaiter;

    public:
        bool NeedToLog(const SeverityValueType& severity) { return severity >= SinkSeverity; }
        void WriteToSink(const SeverityValueType& severity, const BufferType& bufferToPrint)
        {
            if (NeedToLog(severity))
                WriteToSink(bufferToPrint);
        }

    public:
        PatternTransfertType get_pattern(const typename Severity::Value& severity) const
        {
            PatternTransfertType customPattern = SeverityPatternOverride.get_pattern(severity);
            if (customPattern.data() == nullptr || customPattern.size() == 0) return Pattern;
            return customPattern;
        }

    protected:
        virtual void WriteImpl(const BufferType& bufferToPrint) = 0;

    public:
        void WriteToSinkSync(const BufferType& bufferToPrint) { WriteImpl(bufferToPrint); }
        void WriteToSinkAsync(const BufferType& bufferToPrint)
        {
            m_AsyncWaiter = std::async(std::launch::async, &BasicLoggerSink<Severity, CharType>::WriteToSinkSync, this, bufferToPrint);
        }

        void WriteToSink(const BufferType& bufferToPrint)
        {
            if (IsAsync == AsyncSink::Sync)
                WriteToSinkSync(bufferToPrint);
            else
                WriteToSinkAsync(bufferToPrint);
        }

    public:
        void WaitUnitlFinishedToWrite()
        {
            if (IsAsync == AsyncSink::Async) return m_AsyncWaiter.get();
        }

        [[nodiscard]] std::expected<void, fmt::FMTResult> FormatAndWriteToSinkSync(PatternTransfertType pattern, const std::chrono::nanoseconds& logTime, const NameType& loggerName, const BufferType& formatBuffer)
        {
            fmt::detail::DynamicBufferOutManager<CharType> manager(256);
            auto formatPatternStr = SF_TRY(fmt::detail::FormatInManager(manager, false, pattern, FORMAT_SV("time", logTime), FORMAT_SV("name", ConcateNameAndSinkName(loggerName, Name)),
                                                                             FORMAT_SV("data", formatBuffer)));
            BufferType buffer(*formatPatternStr);
            WriteToSinkSync(buffer);
            return {};
        }

        [[nodiscard]] std::expected<void, fmt::FMTResult> FormatAndWriteToSinkAsync(PatternTransfertType pattern, const std::chrono::nanoseconds& logTime, const NameType& loggerName, const BufferType& formatBuffer)
        {
            // TODO
            m_AsyncWaiter = std::async(std::launch::async, &BasicLoggerSink<Severity, CharType>::FormatAndWriteToSinkSync, this, pattern, logTime, loggerName, formatBuffer);
            return {};
        }

        [[nodiscard]] std::expected<void, fmt::FMTResult> FormatAndWriteToSink(PatternTransfertType pattern, const std::chrono::nanoseconds& logTime, const NameType& loggerName, const BufferType& formatBuffer)
        {
            if (IsAsync == AsyncSink::Sync)
                return FormatAndWriteToSinkSync(pattern, logTime, loggerName, formatBuffer);
            return FormatAndWriteToSinkAsync(pattern, logTime, loggerName, formatBuffer);
        }
    };
}
