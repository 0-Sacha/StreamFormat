#pragma once

#include "stream/flog/detail/detail.hxx"

#include <future>

namespace stream::flog::detail {
    enum class AsyncSink {
        Sync,
        Async
    };

    template <typename Severity, typename CharType>
    class BasicLoggerSink {
    public:
        using PatternType         = std::basic_string<CharType>;
        using PatternTransferType = std::basic_string_view<CharType>;
        using NameType            = std::basic_string<CharType>;
        using BufferType          = std::basic_string_view<CharType>;

        using SeverityValueType = typename Severity::Value;

    public:
        BasicLoggerSink(NameType name) : name(std::move(name)), is_async(AsyncSink::Sync) {}
        BasicLoggerSink(NameType name, AsyncSink isAsync) : name(std::move(name)), is_async(isAsync) {}

        virtual ~BasicLoggerSink() = default;

    public:
        NameType                           name    = "";
        PatternType                        pattern = "[{logtime:pattern='default'}] {name} >> {data}";
        SeverityValueType                  sink_severity{SeverityValueType::DefaultSeverity};
        typename Severity::PatternOverride severity_pattern_override;
        AsyncSink                          is_async;

    protected:
        std::future<void> async_waiter_;

    public:
        bool need_to_log(const SeverityValueType& severity) {
            return severity >= sink_severity;
        }
        void WriteToSink(const SeverityValueType& severity, const BufferType& bufferToPrint) {
            if (need_to_log(severity)) WriteToSink(bufferToPrint);
        }

    public:
        PatternTransferType get_pattern(const typename Severity::Value& severity) const {
            PatternTransferType customPattern = severity_pattern_override.get_pattern(severity);
            if (customPattern.data() == nullptr || customPattern.size() == 0) return pattern;
            return customPattern;
        }

    protected:
        virtual void WriteImpl(const BufferType& bufferToPrint) = 0;

    public:
        void WriteToSinkSync(const BufferType& bufferToPrint) {
            WriteImpl(bufferToPrint);
        }
        void WriteToSinkAsync(const BufferType& bufferToPrint) {
            async_waiter_ = std::async(std::launch::async, &BasicLoggerSink<Severity, CharType>::WriteToSinkSync, this, bufferToPrint);
        }

        void WriteToSink(const BufferType& bufferToPrint) {
            if (is_async == AsyncSink::Sync)
                WriteToSinkSync(bufferToPrint);
            else
                WriteToSinkAsync(bufferToPrint);
        }

    public:
        void wait_until_finished_to_write() {
            if (is_async == AsyncSink::Async) return async_waiter_.get();
        }

        void FormatAndWriteToSinkSync(PatternTransferType pattern, const std::chrono::nanoseconds& log_time, const NameType& logger_name, const BufferType& format_buffer) {
            fmt::buf::DynamicStreamIOManager<CharType> manager(256);

            auto       format_pattern_str = fmt::detail::format_in_manager(manager, false, pattern, FORMAT_SV("logtime", log_time),
                                                                           FORMAT_SV("name", ConcatNameAndSinkName(logger_name, name)), FORMAT_SV("data", format_buffer));
            BufferType buffer(*format_pattern_str);
            WriteToSinkSync(buffer);
        }

        void FormatAndWriteToSinkAsync(PatternTransferType pattern, const std::chrono::nanoseconds& log_time, const NameType& logger_name, const BufferType& format_buffer) {
            // TODO
            async_waiter_ = std::async(std::launch::async, &BasicLoggerSink<Severity, CharType>::FormatAndWriteToSinkSync, this, pattern, log_time, logger_name, format_buffer);
        }

        void format_and_write_to_sink(PatternTransferType pattern, const std::chrono::nanoseconds& log_time, const NameType& logger_name, const BufferType& format_buffer) {
            if (is_async == AsyncSink::Sync) return FormatAndWriteToSinkSync(pattern, log_time, logger_name, format_buffer);
            return FormatAndWriteToSinkAsync(pattern, log_time, logger_name, format_buffer);
        }
    };
}  // namespace stream::flog::detail
