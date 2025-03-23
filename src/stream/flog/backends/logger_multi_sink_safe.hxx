#pragma once

#include "logger_multi_sink.hxx"

namespace stream::flog::detail {
    template <typename Severity, typename CharType>
    class BasicLoggerMultiSinkSafeImpl : public BasicLoggerMultiSinkImpl<Severity, CharType> {
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
        BasicLoggerMultiSinkSafeImpl() : Base() {}

        BasicLoggerMultiSinkSafeImpl(std::basic_string<CharType>&& name) : Base(std::forward<std::basic_string<CharType>>(name)) {}

        ~BasicLoggerMultiSinkSafeImpl() override = default;

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

            // FIXME maybe add : name ; indent ???
            for (auto& sink : sinks_) {
                if (sink->need_to_log(severity)) {
                    fmt::buf::DynamicStreamIOManager<CharType> manager_pattern(256);
                    fmt::buf::DynamicStreamIOManager<CharType> manager_format(256);

                    auto format_pattern_str =
                        fmt::detail::format_in_manager(manager_pattern, false, std::string_view(sink->get_pattern(severity)), FORMAT_SV("time", logTime),
                                                       FORMAT_SV("name", FutureConcatNameAndSinkName(name_)), FORMAT_SV("data", flog::AddIndentInFormat(format)));
                    if (format_pattern_str.has_value() == false) return std::unexpected(format_pattern_str.error());
                    auto format_format_str = fmt::detail::format_in_manager(manager_format, false, static_cast<std::string_view>(*format_pattern_str.value()),
                                                                            std::forward<Args>(args)..., FORMAT_SV("sink", sink->get_name()), FORMAT_SV("color", severity));
                    if (format_format_str.has_value() == false) return std::unexpected(format_format_str.error());
                    SF_VERIFY(sink->WriteToSink(static_cast<std::basic_string_view<CharType>>(*format_format_str.value())));
                }
            }

            await(severity);
            return {};
        }

        template <typename T>
        [[nodiscard]] std::expected<void, fmt::FMTResult> log(const SeverityValueType& severity, T&& t) {
            std::chrono::nanoseconds logTime = std::chrono::high_resolution_clock::now() - start_time_;

            for (auto& sink : sinks_) {
                if (sink->need_to_log(severity)) {
                    fmt::buf::DynamicStreamIOManager<CharType> manager(256);
                    auto format_buffer = fmt::detail::format_in_manager(manager, false, std::string_view(sink->get_pattern(severity)), FORMAT_SV("time", logTime),
                                                                        FORMAT_SV("name", ConcatNameAndSinkName(name_, sink->get_name())), FORMAT_SV("data", t));
                    if (format_buffer.has_value() == false) return std::unexpected(format_buffer.error());
                    SF_VERIFY(sink->WriteToSink(static_cast<std::basic_string_view<CharType>>(*format_buffer.value())));
                }
            }

            await(severity);
            return {};
        }
    };
}  // namespace stream::flog::detail
