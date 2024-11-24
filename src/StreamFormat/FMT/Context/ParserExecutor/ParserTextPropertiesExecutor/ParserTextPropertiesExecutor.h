#pragma once

#include "StreamFormat/FMT/Context/BasicContext/ITextPropertiesExecutor.h"
#include "StreamFormat/FMT/Detail/Prelude.h"
#include "StreamFormat/FMT/Context/ParserExecutor/BasicParserExecutor.h"

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    class IParserTextPropertiesExecutor : public ITextPropertiesExecutor
    {
    public:
        IParserTextPropertiesExecutor() = default;
        ~IParserTextPropertiesExecutor() override = default;

        void LinkToExecutor(void* executor) override
        {
            Buffer = &reinterpret_cast<Context::BasicParserExecutor<TChar>*>(executor)->BufferIn;
        }

    protected:
        BufferInfoView<TChar>* Buffer{nullptr};
    };
}

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    class ParserNOTextPropertiesExecutor : public IParserTextPropertiesExecutor<TChar>
    {
    public:
        ParserNOTextPropertiesExecutor() = default;
        ~ParserNOTextPropertiesExecutor() override = default;

        using IParserTextPropertiesExecutor<TChar>::Buffer;

    public:
        [[nodiscard]] std::expected<void, FMTResult> AllPropertiesReset() override { return {}; }

    public:
        [[nodiscard]] std::expected<void, FMTResult> ResetColor() override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::BasicColorFG&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::BasicColorBG&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::BasicColor&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::Color24bFG&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::Color24bBG&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::Color24b&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::ColorCubeFG&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::ColorCubeBG&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::ColorCube&) override { return {}; }

    public:
        [[nodiscard]] std::expected<void, FMTResult> ResetFront() override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteFront(const Detail::TextProperties::TextFront::FrontID&) override { return {}; }

    public:
        [[nodiscard]] std::expected<void, FMTResult> ResetStyle() override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Intensity&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Italic&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Underline&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::Color&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::ColorCube&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::Color24b&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Blink&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Inverted&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Ideogram&) override { return {}; }
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Script&) override { return {}; }
    };
}
