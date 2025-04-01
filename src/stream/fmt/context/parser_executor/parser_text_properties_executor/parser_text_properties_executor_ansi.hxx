#pragma once

#include "parser_text_properties_executor.hxx"

namespace stream::fmt::detail {
    template <typename TChar>
    class ParserANSITextPropertiesExecutor : public IParserTextPropertiesExecutor<TChar> {
    public:
        ParserANSITextPropertiesExecutor()           = default;
        ~ParserANSITextPropertiesExecutor() override = default;

        using IParserTextPropertiesExecutor<TChar>::buffer;

    public:
        void all_properties_reset() override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType('\033', '[', 0, 'm');*/
        }

    public:
        void reset_color() override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType('\033', '[', 39, ';', 49, 'm');*/
        }
        void execute_color(const detail::TextProperties::TextColor::BasicColorFG&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void execute_color(const detail::TextProperties::TextColor::BasicColorBG&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void execute_color(const detail::TextProperties::TextColor::BasicColor&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t.fg) , ';', static_cast<std::uint8_t>(t.bg), 'm');*/
        }
        void execute_color(const detail::TextProperties::TextColor::Color24bFG&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType("\033[38;2;", t.r, ';', t.g, ';', t.b, 'm');*/
        }
        void execute_color(const detail::TextProperties::TextColor::Color24bBG&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType("\033[48;2;", t.r, ';', t.g, ';', t.b, 'm');*/
        }
        void execute_color(const detail::TextProperties::TextColor::Color24b&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType("\033[38;2;", t.fg.r, ';', t.fg.g, ';', t.fg.b, "; 48; 2;", t.bg.r, ';', t.bg.g, ';', t.bg.b, 'm');*/
        }
        void execute_color(const detail::TextProperties::TextColor::ColorCubeFG&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType("\033[38;5;", t.get_color_ref(), 'm');*/
        }
        void execute_color(const detail::TextProperties::TextColor::ColorCubeBG&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType("\033[48;5;", t.get_color_ref(), 'm');*/
        }
        void execute_color(const detail::TextProperties::TextColor::ColorCube&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType("\033[48;5;", t.fg.get_color_ref(), ";48;5;", t.bg.get_color_ref(), 'm');*/
        }

    public:
        void reset_front() override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType('\033', '[', detail::TextProperties::TextFront::FrontID::DefaultFrontID, 'm');*/
        }
        void execute_front(const detail::TextProperties::TextFront::FrontID&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType('\033', '[', t.id, 'm');*/
        }

    public:
        void reset_style() override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType('\033', '[', 0, 'm');*/
        }
        void execute_style(const detail::TextProperties::TextStyle::Intensity&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void execute_style(const detail::TextProperties::TextStyle::Italic&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void execute_style(const detail::TextProperties::TextStyle::Underline&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void execute_style(const detail::TextProperties::TextStyle::UnderlineColor::Color&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType("\033[59m");*/
        }
        void execute_style(const detail::TextProperties::TextStyle::UnderlineColor::ColorCube&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType("\033[58;5;", t.get_color_ref(), 'm');*/
        }
        void execute_style(const detail::TextProperties::TextStyle::UnderlineColor::Color24b&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType("\033[58;2;", t.r, ';', t.g, ';', t.b, 'm');*/
        }
        void execute_style(const detail::TextProperties::TextStyle::Blink&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void execute_style(const detail::TextProperties::TextStyle::Inverted&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void execute_style(const detail::TextProperties::TextStyle::Ideogram&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
        void execute_style(const detail::TextProperties::TextStyle::Script&) override {
            throw std::runtime_error("fmt error: FunctionNotImpl");
            /*ReadManip(buffer).BasicReadType('\033', '[', static_cast<std::uint8_t>(t), 'm');*/
        }
    };
}  // namespace stream::fmt::detail
