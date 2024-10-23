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
        void AllPropertiesReset() override {}

    public:
        void ResetColor() override {}
        void ExecuteColor(const Detail::TextProperties::TextColor::BasicColorFG&) override {}
        void ExecuteColor(const Detail::TextProperties::TextColor::BasicColorBG&) override {}
        void ExecuteColor(const Detail::TextProperties::TextColor::BasicColor&) override {}
        void ExecuteColor(const Detail::TextProperties::TextColor::Color24bFG&) override {}
        void ExecuteColor(const Detail::TextProperties::TextColor::Color24bBG&) override {}
        void ExecuteColor(const Detail::TextProperties::TextColor::Color24b&) override {}
        void ExecuteColor(const Detail::TextProperties::TextColor::ColorCubeFG&) override {}
        void ExecuteColor(const Detail::TextProperties::TextColor::ColorCubeBG&) override {}
        void ExecuteColor(const Detail::TextProperties::TextColor::ColorCube&) override {}

    public:
        void ResetFront() override {}
        void ExecuteFront(const Detail::TextProperties::TextFront::FrontID&) override {}

    public:
        void ResetStyle() override {}
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Intensity&) override {}
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Italic&) override {}
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Underline&) override {}
        void ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::Color&) override {}
        void ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::ColorCube&) override {}
        void ExecuteStyle(const Detail::TextProperties::TextStyle::UnderlineColor::Color24b&) override {}
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Blink&) override {}
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Inverted&) override {}
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Ideogram&) override {}
        void ExecuteStyle(const Detail::TextProperties::TextStyle::Script&) override {}
    };
}
