#pragma once

#include "StreamFormat/FMT/Context/BasicContext/ITextPropertiesExecutor.h"
#include "StreamFormat/FMT/Detail/Detail.h"

namespace StreamFormat::FMT::Detail
{
    template <typename BufferOutType>
    class IFormatterTextPropertiesExecutor : public ITextPropertiesExecutor
    {
    public:
        ~IFormatterTextPropertiesExecutor() override = default;

    public:
        void SetBuffer(BufferOutType* buffer) { m_Buffer = buffer; }

    protected:
        BufferOutType* m_Buffer{nullptr};
    };
}

namespace StreamFormat::FMT::Detail
{
    template <typename BufferOutType>
    class FormatterNOTextPropertiesExecutor final : public IFormatterTextPropertiesExecutor<BufferOutType>
    {
    public:
        ~FormatterNOTextPropertiesExecutor() override = default;

    public:
        using Base = IFormatterTextPropertiesExecutor<BufferOutType>;
        using Base::SetBuffer;

    protected:
        using Base::m_Buffer;

    public:
        void AllPropertiesReset() override {}

    public:
        void ResetColor() override {}
        void ExecuteColor(const TextProperties::TextColor::BasicColorFG&) override {}
        void ExecuteColor(const TextProperties::TextColor::BasicColorBG&) override {}
        void ExecuteColor(const TextProperties::TextColor::BasicColor&) override {}
        void ExecuteColor(const TextProperties::TextColor::Color24bFG&) override {}
        void ExecuteColor(const TextProperties::TextColor::Color24bBG&) override {}
        void ExecuteColor(const TextProperties::TextColor::Color24b&) override {}
        void ExecuteColor(const TextProperties::TextColor::ColorCubeFG&) override {}
        void ExecuteColor(const TextProperties::TextColor::ColorCubeBG&) override {}
        void ExecuteColor(const TextProperties::TextColor::ColorCube&) override {}

    public:
        void ResetFront() override {}
        void ExecuteFront(const TextProperties::TextFront::FrontID&) override {}

    public:
        void ResetStyle() override {}
        void ExecuteStyle(const TextProperties::TextStyle::Intensity&) override {}
        void ExecuteStyle(const TextProperties::TextStyle::Italic&) override {}
        void ExecuteStyle(const TextProperties::TextStyle::Underline&) override {}
        void ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::Color&) override {}
        void ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::ColorCube&) override {}
        void ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::Color24b&) override {}
        void ExecuteStyle(const TextProperties::TextStyle::Blink&) override {}
        void ExecuteStyle(const TextProperties::TextStyle::Inverted&) override {}
        void ExecuteStyle(const TextProperties::TextStyle::Ideogram&) override {}
        void ExecuteStyle(const TextProperties::TextStyle::Script&) override {}
    };
}
