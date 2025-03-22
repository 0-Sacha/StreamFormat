#pragma once

#include "stream/fmt/context/basic_context/text_properties_executor.h"
#include "stream/fmt/buffer/fmt_buffer_out_manip.h"
#include "stream/fmt/context/formatter_executor/basic_formatter_executor.h"

namespace stream::fmt::detail
{
    template <typename TChar>
    class IFormatterTextPropertiesExecutor : public ITextPropertiesExecutor
    {
    public:
        ~IFormatterTextPropertiesExecutor() override = default;

        void link_to_executor(void* executor) override
        {
            Buffer = &reinterpret_cast<Context::BasicFormatterExecutor<TChar>*>(executor)->BufferOut;
        }

    protected:
        detail::FMTBufferOutInfo<TChar>* Buffer{nullptr};
    };
}

namespace stream::fmt::detail
{
    template <typename TChar>
    class FormatterNOTextPropertiesExecutor final : public IFormatterTextPropertiesExecutor<TChar>
    {
    public:
        FormatterNOTextPropertiesExecutor() = default;
        ~FormatterNOTextPropertiesExecutor() override = default;

    public:
        [[nodiscard]] std::expected<void, FMTResult> all_properties_reset() override {}

    public:
        [[nodiscard]] std::expected<void, FMTResult> reset_color() override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::BasicColorFG&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::BasicColorBG&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::BasicColor&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::Color24bFG&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::Color24bBG&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::Color24b&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::ColorCubeFG&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::ColorCubeBG&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::ColorCube&) override {}

    public:
        [[nodiscard]] std::expected<void, FMTResult> reset_front() override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteFront(const detail::TextProperties::TextFront::FrontID&) override {}

    public:
        [[nodiscard]] std::expected<void, FMTResult> ResetStyle() override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Intensity&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Italic&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Underline&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::UnderlineColor::Color&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::UnderlineColor::ColorCube&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::UnderlineColor::Color24b&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Blink&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Inverted&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Ideogram&) override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Script&) override {}
    };
}
