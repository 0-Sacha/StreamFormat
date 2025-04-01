#pragma once

#include "stream/flog/detail/detail.hxx"
#include "stream/flog/sinks/logger_sink.hxx"

namespace stream::flog::detail {
    template <typename Severity, typename CharType>
    class BasicLoggerMultiSinkImpl {
    public:
        using SinkType          = BasicLoggerSink<Severity, CharType>;
        using SeverityValueType = typename Severity::Value;

    public:
        BasicLoggerMultiSinkImpl() : name_("logger_:{sink}"), start_time_(std::chrono::high_resolution_clock::now()) {}

        BasicLoggerMultiSinkImpl(std::basic_string<CharType>&& name)
            : name_(std::forward<std::basic_string<CharType>>(name)), start_time_(std::chrono::high_resolution_clock::now()) {}

        virtual ~BasicLoggerMultiSinkImpl() = default;

    public:
        void set_name(std::basic_string<CharType>&& name) {
            name_ = std::forward<std::basic_string<CharType>>(name);
        }

        std::basic_string<CharType>& get_name() {
            return name_;
        }
        std::vector<std::shared_ptr<SinkType>>& get_sinks() {
            return sinks_;
        }

    protected:
        std::basic_string<CharType>            name_;
        std::vector<std::shared_ptr<SinkType>> sinks_;

        std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;

    public:
        void add_sink(std::shared_ptr<SinkType> sink) {
            sinks_.pushback(sink);
        }

        template <typename T, typename... Args>
        void EmplaceSink(Args&&... args) {
            std::shared_ptr<T> sink = std::make_shared<T>(std::forward<Args>(args)...);
            add_sink(sink);
        }
    };
}  // namespace stream::flog::detail
