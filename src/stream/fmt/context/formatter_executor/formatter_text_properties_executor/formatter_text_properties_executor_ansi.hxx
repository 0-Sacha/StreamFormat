#pragma once

#include "formatter_text_properties_executor.hxx"
#include "stream/fmt/detail/indent_handlers.hxx"

namespace stream::fmt::detail {
    template <typename TChar>
    class FormatterTextPropertiesExecutorANSI final : public IFormatterTextPropertiesExecutor<TChar> {
    public:
        FormatterTextPropertiesExecutorANSI()           = default;
        ~FormatterTextPropertiesExecutorANSI() override = default;

        using IFormatterTextPropertiesExecutor<TChar>::buffer;

    public:
        void all_properties_reset() override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).fast_write_string_literal("\033[0m");
        }

    public:
        void reset_color() override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).fast_write_string_literal("\033[39;49m");
        }

        void execute_color(const TextProperties::TextColor::BasicColorFG& t) {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[", static_cast<std::uint8_t>(t), "m");
        }
        void execute_color(const TextProperties::TextColor::BasicColorBG& t) {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[", static_cast<std::uint8_t>(t), "m");
        }
        void execute_color(const detail::TextProperties::TextColor::BasicColor& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[", static_cast<std::uint8_t>(t.fg), ";", static_cast<std::uint8_t>(t.bg), "m");
        }
        void execute_color(const detail::TextProperties::TextColor::Color24bFG& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[38;2;", t.r, ";", t.g, ";", t.b, "m");
        }
        void execute_color(const detail::TextProperties::TextColor::Color24bBG& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[48;2;", t.r, ";", t.g, ";", t.b, "m");
        }
        void execute_color(const detail::TextProperties::TextColor::Color24b& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[38;2;", t.fg.r, ";", t.fg.g, ";", t.fg.b, "; 48; 2;", t.bg.r, ";", t.bg.g, ";", t.bg.b, "m");
        }
        void execute_color(const detail::TextProperties::TextColor::ColorCubeFG& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[38;5;", t.get_color_ref(), "m");
        }
        void execute_color(const detail::TextProperties::TextColor::ColorCubeBG& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[48;5;", t.get_color_ref(), "m");
        }
        void execute_color(const detail::TextProperties::TextColor::ColorCube& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[48;5;", t.fg.get_color_ref(), ";48;5;", t.bg.get_color_ref(), "m");
        }

    public:
        void reset_front() override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[", detail::TextProperties::TextFront::FrontID::DefaultFrontID, "m");
        }
        void execute_front(const detail::TextProperties::TextFront::FrontID& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[", t.id, "m");
        }

    public:
        void reset_style() override {
            // TODO
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).fast_write_string_literal("\033[0m");
        }
        void execute_style(const detail::TextProperties::TextStyle::Intensity& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[", static_cast<std::uint8_t>(t), "m");
        }
        void execute_style(const detail::TextProperties::TextStyle::Italic& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[", static_cast<std::uint8_t>(t), "m");
        }
        void execute_style(const detail::TextProperties::TextStyle::Underline& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[", static_cast<std::uint8_t>(t), "m");
        }
        void execute_style(const detail::TextProperties::TextStyle::UnderlineColor::Color&) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[59m");
        }
        void execute_style(const detail::TextProperties::TextStyle::UnderlineColor::ColorCube& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[58;5;", t.get_color_ref(), "m");
        }
        void execute_style(const detail::TextProperties::TextStyle::UnderlineColor::Color24b& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[58;2;", t.r, ";", t.g, ";", t.b, "m");
        }
        void execute_style(const detail::TextProperties::TextStyle::Blink& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[", static_cast<std::uint8_t>(t), "m");
        }
        void execute_style(const detail::TextProperties::TextStyle::Inverted& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[", static_cast<std::uint8_t>(t), "m");
        }
        void execute_style(const detail::TextProperties::TextStyle::Ideogram& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[", static_cast<std::uint8_t>(t), "m");
        }
        void execute_style(const detail::TextProperties::TextStyle::Script& t) override {
            NoStrideFunction no_stride(*buffer);
            return buf::WriteManip(*buffer).basic_write_type("\033[", static_cast<std::uint8_t>(t), "m");
        }
    };
}  // namespace stream::fmt::detail
