#pragma once

#include "stream/fmt/context/basic_context/text_properties_executor.hxx"
#include "stream/fmt/buf/fmt_manip_io.hxx"
#include "stream/fmt/context/formatter_executor/basic_formatter_executor.hxx"

namespace stream::fmt::detail {
    template <typename TChar>
    class IFormatterTextPropertiesExecutor : public ITextPropertiesExecutor {
    public:
        ~IFormatterTextPropertiesExecutor() override = default;

        void link_to_executor(void* executor) override {
            buffer = &reinterpret_cast<context::BasicFormatterExecutor<TChar>*>(executor)->ostream;
        }

    protected:
        buf::FMTStreamIO<TChar>* buffer{nullptr};
    };
}  // namespace stream::fmt::detail

namespace stream::fmt::detail {
    template <typename TChar>
    class FormatterNOTextPropertiesExecutor final : public IFormatterTextPropertiesExecutor<TChar> {
    public:
        FormatterNOTextPropertiesExecutor()           = default;
        ~FormatterNOTextPropertiesExecutor() override = default;

    public:
        void all_properties_reset() override {}

    public:
        void reset_color() override {}
        void execute_color(const detail::TextProperties::TextColor::BasicColorFG&) override {}
        void execute_color(const detail::TextProperties::TextColor::BasicColorBG&) override {}
        void execute_color(const detail::TextProperties::TextColor::BasicColor&) override {}
        void execute_color(const detail::TextProperties::TextColor::Color24bFG&) override {}
        void execute_color(const detail::TextProperties::TextColor::Color24bBG&) override {}
        void execute_color(const detail::TextProperties::TextColor::Color24b&) override {}
        void execute_color(const detail::TextProperties::TextColor::ColorCubeFG&) override {}
        void execute_color(const detail::TextProperties::TextColor::ColorCubeBG&) override {}
        void execute_color(const detail::TextProperties::TextColor::ColorCube&) override {}

    public:
        void reset_front() override {}
        void execute_front(const detail::TextProperties::TextFront::FrontID&) override {}

    public:
        void reset_style() override {}
        void execute_style(const detail::TextProperties::TextStyle::Intensity&) override {}
        void execute_style(const detail::TextProperties::TextStyle::Italic&) override {}
        void execute_style(const detail::TextProperties::TextStyle::Underline&) override {}
        void execute_style(const detail::TextProperties::TextStyle::UnderlineColor::Color&) override {}
        void execute_style(const detail::TextProperties::TextStyle::UnderlineColor::ColorCube&) override {}
        void execute_style(const detail::TextProperties::TextStyle::UnderlineColor::Color24b&) override {}
        void execute_style(const detail::TextProperties::TextStyle::Blink&) override {}
        void execute_style(const detail::TextProperties::TextStyle::Inverted&) override {}
        void execute_style(const detail::TextProperties::TextStyle::Ideogram&) override {}
        void execute_style(const detail::TextProperties::TextStyle::Script&) override {}
    };
}  // namespace stream::fmt::detail
