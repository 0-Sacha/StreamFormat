#pragma once

#include "stream/fmt/context/basic_context/text_properties_executor.h"
#include "stream/fmt/detail/prelude.h"
#include "stream/fmt/context/ParserExecutor/BasicParserExecutor.h"

namespace stream::fmt::detail
{
    template <typename TChar>
    class IParserTextPropertiesExecutor : public ITextPropertiesExecutor
    {
    public:
        IParserTextPropertiesExecutor() = default;
        ~IParserTextPropertiesExecutor() override = default;

        void link_to_executor(void* executor) override
        {
            Buffer = &reinterpret_cast<Context::BasicParserExecutor<TChar>*>(executor)->BufferIn;
        }

    protected:
        BufferInfoView<TChar>* Buffer{nullptr};
    };
}

namespace stream::fmt::detail
{
    template <typename TChar>
    class ParserNOTextPropertiesExecutor : public IParserTextPropertiesExecutor<TChar>
    {
    public:
        ParserNOTextPropertiesExecutor() = default;
        ~ParserNOTextPropertiesExecutor() override = default;

        using IParserTextPropertiesExecutor<TChar>::Buffer;

    public:
        [[nodiscard]] std::expected<void, FMTResult> all_properties_reset() override { return {}; }

    public:
        [[nodiscard]] std::expected<void, FMTResult> reset_color() override {}
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::BasicColorFG&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::BasicColorBG&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::BasicColor&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::Color24bFG&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::Color24bBG&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::Color24b&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::ColorCubeFG&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::ColorCubeBG&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_color(const detail::TextProperties::TextColor::ColorCube&) override { return {}; }

    public:
        [[nodiscard]] std::expected<void, FMTResult> reset_front() override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteFront(const detail::TextProperties::TextFront::FrontID&) override { return {}; }

    public:
        [[nodiscard]] std::expected<void, FMTResult> ResetStyle() override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Intensity&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Italic&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Underline&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::UnderlineColor::Color&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::UnderlineColor::ColorCube&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::UnderlineColor::Color24b&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Blink&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Inverted&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Ideogram&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> execute_style(const detail::TextProperties::TextStyle::Script&) override { return {}; }
    };
}
