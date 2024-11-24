#pragma once

#include "StreamFormat/FMT/Context/BasicContext/ITextPropertiesExecutor.h"
#include "StreamFormat/FMT/Buffer/FMTBufferOutManip.h"
#include "StreamFormat/FMT/Context/FormatterExecutor/BasicFormatterExecutor.h"

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    class IFormatterTextPropertiesExecutor : public ITextPropertiesExecutor
    {
    public:
        ~IFormatterTextPropertiesExecutor() override = default;

        void LinkToExecutor(void* executor) override
        {
            Buffer = &reinterpret_cast<Context::BasicFormatterExecutor<TChar>*>(executor)->BufferOut;
        }

    protected:
        Detail::FMTBufferOutInfo<TChar>* Buffer{nullptr};
    };
}

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    class FormatterNOTextPropertiesExecutor final : public IFormatterTextPropertiesExecutor<TChar>
    {
    public:
        FormatterNOTextPropertiesExecutor() = default;
        ~FormatterNOTextPropertiesExecutor() override = default;

    public:
        [[nodiscard]] std::expected<void, FMTResult> AllPropertiesReset() override {}

    public:
        [[nodiscard]] std::expected<void, FMTResult> ResetColor() override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::BasicColorFG&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::BasicColorBG&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::BasicColor&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::Color24bFG&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::Color24bBG&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::Color24b&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::ColorCubeFG&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::ColorCubeBG&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteColor(const Detail::TextProperties::TextColor::ColorCube&) override {}

    public:
        [[nodiscard]] std::expected<void, FMTResult> ResetFront() override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteFront(const Detail::TextProperties::TextFront::FrontID&) override {}

    public:
        [[nodiscard]] std::expected<void, FMTResult> ResetStyle() override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Intensity&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Italic&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Underline&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::Color&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::ColorCube&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::Color24b&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Blink&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Inverted&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Ideogram&) override {}
        [[nodiscard]] std::expected<void, FMTResult> ExecuteStyle(const Detail::TextProperties::TextStyle::Script&) override {}
    };
}
