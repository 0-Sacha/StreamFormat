#pragma once

#include "StreamFormat/FMT/Context/BasicContext/ITextPropertiesExecutor.h"
#include "StreamFormat/FMT/Detail/Detail.h"
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
