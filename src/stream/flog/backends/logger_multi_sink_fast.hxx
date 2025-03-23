#pragma once

#include "logger_multi_sink.hxx"

namespace stream::flog::detail {
    template <typename Severity, typename CharType>
    class BasicLoggerMultiSinkFastImpl : public BasicLoggerMultiSinkImpl<Severity, CharType> {
    public:
        using Base = BasicLoggerMultiSinkImpl<Severity, CharType>;
        using Base::add_sink;
        using Base::get_name;
        using Base::get_sinks;
        using Base::name_;
        using Base::set_name;
        using Base::sinks_;

        using Base::start_time_;

        using typename Base::SeverityValueType;

    public:
        BasicLoggerMultiSinkFastImpl() : Base() {}

        BasicLoggerMultiSinkFastImpl(std::basic_string<CharType>&& name) : Base(std::forward<std::basic_string<CharType>>(name)) {}

        ~BasicLoggerMultiSinkFastImpl() override = default;

    public:
        void await(const SeverityValueType& severity) {
            for (auto& sink : sinks_)
                if (sink->need_to_log(severity)) sink->wait_until_finished_to_write();
        }

    public:
        template <typename Format = std::string_view, typename... Args>
            requires fmt::buf::convertible_to_buffer_info_view<Format>
        [[nodiscard]] std::expected<void, fmt::FMTResult> log(const SeverityValueType& severity, const Format& format, Args&&... args) {
            std::chrono::nanoseconds logTime = std::chrono::high_resolution_clock::now() - start_time_;

            fmt::buf::DynamicStreamIOManager<CharType> manager(256);
            auto                                       formatBuffer = SF_TRY(fmt::detail::format_in_manager(manager, false, format, std::forward<Args>(args)...));
            for (auto& sink : sinks_)
                if (sink->need_to_log(severity)) {
                    SF_TRY(sink->format_and_write_to_sink(sink->get_pattern(severity), logTime, name_, static_cast<std::basic_string_view<CharType>>(*formatBuffer)));
                }

            await(severity);
            return {};
        }

        template <typename T>
        [[nodiscard]] std::expected<void, fmt::FMTResult> log(const SeverityValueType& severity, T&& t) {
            std::chrono::nanoseconds logTime = std::chrono::high_resolution_clock::now() - start_time_;

            fmt::buf::DynamicStreamIOManager<CharType> manager(256);
            auto                                       formatBuffer = SF_TRY(fmt::detail::format_in_manager(manager, false, std::forward<T>(t)));
            for (auto& sink : sinks_)
                if (sink->need_to_log(severity)) {
                    SF_TRY(sink->format_and_write_to_sink(sink->get_pattern(severity), logTime, name_, static_cast<std::basic_string_view<CharType>>(*formatBuffer)));
                }

            await(severity);

            return {};
        }
    };
}  // namespace stream::flog::detail
