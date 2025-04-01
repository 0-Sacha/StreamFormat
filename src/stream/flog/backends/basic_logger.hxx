#pragma once

#include "stream/flog/detail/detail.hxx"
#include "stream/fmt/serializers/format_chrono.hxx"

#include <chrono>
#include <iostream>

namespace stream::flog::detail {
    template <typename Severity>
    class BasicLoggerImpl {
    public:
        using SeverityValueType = typename Severity::Value;

    public:
        BasicLoggerImpl() : name_("logger_"), severity_(Severity::Value::DefaultSeverity), stream_(std::cout), start_time_(std::chrono::high_resolution_clock::now()) {
            reset_pattern();
        }

        explicit BasicLoggerImpl(const std::string_view& name, typename Severity::Value severity = Severity::Value::DefaultSeverity, std::ostream& stream = std::cout)
            : name_(name),
              severity_(severity),
              stream_(stream),
              pre_format_stream_io_manager_(64),
              full_format_stream_io_manager_(64),
              start_time_(std::chrono::high_resolution_clock::now()) {
            reset_pattern();
        }
        explicit BasicLoggerImpl(const std::string_view& name, const std::string_view& format, typename Severity::Value severity = Severity::Value::DefaultSeverity,
                                 std::ostream& stream = std::cout)
            : name_(name),
              severity_(severity),
              stream_(stream),
              pre_format_stream_io_manager_(64),
              full_format_stream_io_manager_(64),
              start_time_(std::chrono::high_resolution_clock::now()) {
            set_pattern(format);
        }

        virtual ~BasicLoggerImpl() = default;

    public:
        void set_severity(const SeverityValueType& severity) {
            severity_ = severity;
        }
        void set_name(std::string name) {
            name_ = std::move(name);
        }
        void set_real_pattern(std::string pattern) {
            pattern_ = std::move(pattern);
        }
        void set_pattern(std::string_view pattern) {
            pattern_ = "{color}";
            pattern_ += pattern;
        }
        void reset_pattern() {
            set_pattern("[{logtime:pattern='default'}] {name} >> {data}");
        }

    private:
        std::string                            name_;
        SeverityValueType                      severity_;
        std::ostream&                          stream_;
        std::string                            pattern_;
        fmt::buf::DynamicStreamIOManager<char> pre_format_stream_io_manager_;
        fmt::buf::DynamicStreamIOManager<char> full_format_stream_io_manager_;

        std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;

    public:
        void NewLine() {
            stream_.write("\n", 1);
        }

        template <typename Format = std::string_view, typename... Args>
            requires fmt::buf::convertible_to_buffer_info_view<Format>
        void log(const SeverityValueType& severity, Format&& format, Args&&... args) {
            if (severity < severity_) return;

            std::chrono::nanoseconds log_time = std::chrono::high_resolution_clock::now() - start_time_;

            fmt::detail::format_in_manager(pre_format_stream_io_manager_, false, fmt::buf::StreamView<char>(pattern_), FORMAT_SV("logtime", log_time), FORMAT_SV("name", name_),
                                           FORMAT_SV("data", flog::AddIndentInFormat(format)));

            fmt::detail::format_in_manager(full_format_stream_io_manager_, true, pre_format_stream_io_manager_.get_last_generated_buffer_info_view(), std::forward<Args>(args)...,
                                           FORMAT_SV("color", severity));
            stream_.write(full_format_stream_io_manager_.get_buffer(), static_cast<std::streamsize>(full_format_stream_io_manager_.get_last_generated_data_size()));
            stream_.flush();
        }

        template <typename T>
        void log(const SeverityValueType& severity, T&& t) {
            if (severity < severity_) return;

            std::chrono::nanoseconds log_time = std::chrono::high_resolution_clock::now() - start_time_;

            fmt::detail::format_in_manager(full_format_stream_io_manager_, true, fmt::buf::StreamView<char>(pattern_), FORMAT_SV("data", t), FORMAT_SV("color", severity),
                                           FORMAT_SV("logtime", log_time), FORMAT_SV("name", name_));
            stream_.write(full_format_stream_io_manager_.get_buffer(), static_cast<std::streamsize>(full_format_stream_io_manager_.get_last_generated_data_size()));
            stream_.flush();
        }
    };
}  // namespace stream::flog::detail
