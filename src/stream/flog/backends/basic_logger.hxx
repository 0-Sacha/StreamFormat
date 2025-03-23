#pragma once

#include "stream/flog/detail/detail.h"
#include "stream/fmt/serializers/format_chrono.h"

#include <chrono>
#include <iostream>

namespace stream::flog::detail {
    template <typename Severity>
    class BasicLoggerImpl {
    public:
        using SeverityValueType = typename Severity::Value;

    public:
        BasicLoggerImpl() : name_("logger_"), m_Severity(Severity::Value::DefaultSeverity), m_Stream(std::cout), start_time_(std::chrono::high_resolution_clock::now()) {
            ResetPattern();
        }

        explicit BasicLoggerImpl(const std::string_view& name, typename Severity::Value severity = Severity::Value::DefaultSeverity, std::ostream& stream = std::cout)
            : name_(name),
              m_Severity(severity),
              m_Stream(stream),
              preFormatStreamIOManager(64),
              fullFormatStreamIOManager(64),
              start_time_(std::chrono::high_resolution_clock::now()) {
            ResetPattern();
        }
        explicit BasicLoggerImpl(const std::string_view& name, const std::string_view& format, typename Severity::Value severity = Severity::Value::DefaultSeverity,
                                 std::ostream& stream = std::cout)
            : name_(name),
              m_Severity(severity),
              m_Stream(stream),
              preFormatStreamIOManager(64),
              fullFormatStreamIOManager(64),
              start_time_(std::chrono::high_resolution_clock::now()) {
            SetPattern(format);
        }

        virtual ~BasicLoggerImpl() = default;

    public:
        void set_severity(const SeverityValueType& severity) {
            m_Severity = severity;
        }
        void set_name(const std::string& name) {
            name_ = name;
        }
        void set_name(std::string&& name) {
            name_ = std::move(name);
        }
        void SetRealPattern(std::string_view pattern) {
            m_Pattern = pattern;
        }
        void set_real_pattern_strmv(std::string&& pattern) {
            m_Pattern = std::move(pattern);
        }
        void SetPattern(std::string_view pattern) {
            m_Pattern = "{color}";
            m_Pattern += pattern;
        }
        void ResetPattern() {
            SetPattern("[{time:pattern='%h:%m:%s:%ms'}] {name} >> {data}");
        }

    private:
        std::string                            name_;
        SeverityValueType                      m_Severity;
        std::ostream&                          m_Stream;
        std::string                            m_Pattern;
        fmt::buf::DynamicStreamIOManager<char> preFormatStreamIOManager;
        fmt::buf::DynamicStreamIOManager<char> fullFormatStreamIOManager;

        std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;

    public:
        void NewLine() {
            m_Stream.write("\n", 1);
        }

        template <typename Format = std::string_view, typename... Args>
            requires fmt::buf::convertible_to_buffer_info_view<Format>
        [[nodiscard]] std::expected<void, fmt::FMTResult> log(const SeverityValueType& severity, Format&& format, Args&&... args) {
            if (severity < m_Severity) return {};

            std::chrono::nanoseconds logTime = std::chrono::high_resolution_clock::now() - start_time_;

            SF_TRY(fmt::detail::format_in_manager(preFormatStreamIOManager, false, fmt::buf::StreamView<char>(m_Pattern), FORMAT_SV("time", logTime), FORMAT_SV("name", name_),
                                                  FORMAT_SV("data", flog::AddIndentInFormat(format))));

            SF_TRY(fmt::detail::format_in_manager(fullFormatStreamIOManager, true, preFormatStreamIOManager.get_last_generated_buffer_info_view(), std::forward<Args>(args)...,
                                                  FORMAT_SV("color", severity)));
            m_Stream.write(fullFormatStreamIOManager.get_buffer(), static_cast<std::streamsize>(fullFormatStreamIOManager.get_last_generated_data_size()));
            m_Stream.flush();

            return {};
        }

        template <typename T>
        [[nodiscard]] std::expected<void, fmt::FMTResult> log(const SeverityValueType& severity, T&& t) {
            if (severity < m_Severity) return {};

            std::chrono::nanoseconds logTime = std::chrono::high_resolution_clock::now() - start_time_;

            SF_TRY(fmt::detail::format_in_manager(fullFormatStreamIOManager, true, fmt::buf::StreamView<char>(m_Pattern), FORMAT_SV("data", t), FORMAT_SV("color", severity),
                                                  FORMAT_SV("time", logTime), FORMAT_SV("name", name_)));
            m_Stream.write(fullFormatStreamIOManager.get_buffer(), static_cast<std::streamsize>(fullFormatStreamIOManager.get_last_generated_data_size()));
            m_Stream.flush();

            return {};
        }
    };
}  // namespace stream::flog::detail
