#pragma once

#include "stream/fmt/context/basic_context/text_properties_executor.hxx"
#include "stream/fmt/detail/prelude.hxx"
#include "stream/fmt/context/parser_executor/basic_parser_executor.hxx"

namespace stream::fmt::detail {
    template <typename TChar>
    class IParserTextPropertiesExecutor : public ITextPropertiesExecutor {
    public:
        IParserTextPropertiesExecutor()           = default;
        ~IParserTextPropertiesExecutor() override = default;

        void link_to_executor(void* executor) override {
            buffer = &reinterpret_cast<context::BasicParserExecutor<TChar>*>(executor)->istream;
        }

    protected:
        buf::StreamView<TChar>* buffer{nullptr};
    };
}  // namespace stream::fmt::detail

namespace stream::fmt::detail {
    template <typename TChar>
    class ParserNOTextPropertiesExecutor : public IParserTextPropertiesExecutor<TChar> {
    public:
        ParserNOTextPropertiesExecutor()           = default;
        ~ParserNOTextPropertiesExecutor() override = default;

        using IParserTextPropertiesExecutor<TChar>::buffer;

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
