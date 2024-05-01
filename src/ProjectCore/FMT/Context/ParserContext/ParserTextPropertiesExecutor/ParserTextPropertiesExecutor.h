#pragma once 

#include "ProjectCore/FMT/Detail/Detail.h"
#include "ProjectCore/FMT/Context/BasicContext/ITextPropertiesExecutor.h"

namespace ProjectCore::FMT::Detail
{
    template <typename BufferInType>
    class IParserTextPropertiesExecutor : public ITextPropertiesExecutor
    {
    public:
        ~IParserTextPropertiesExecutor() override = default;
        
    public:
        void SetBuffer(BufferInType* buffer) { m_Buffer = buffer; }

    protected:
        BufferInType* m_Buffer;
    };
}

namespace ProjectCore::FMT::Detail
{
    template <typename ParserContext>
    class ParserNOTextPropertiesExecutor : public IParserTextPropertiesExecutor<ParserContext>
    {
    public:
        ~ParserNOTextPropertiesExecutor() override = default;

    public:
        using Base = IParserTextPropertiesExecutor<ParserContext>;
        using Base::SetContext;
        
    protected:
        using Base::m_Context;

    public:
        void AllPropertiesReset() override                                            {}

    public:
        void ResetColor() override                                                    {}
        void ExecuteColor(const TextProperties::TextColor::BasicColorFG&) override    {}
        void ExecuteColor(const TextProperties::TextColor::BasicColorBG&) override    {}
        void ExecuteColor(const TextProperties::TextColor::BasicColor&) override      {}
        void ExecuteColor(const TextProperties::TextColor::Color24bFG&) override      {}
        void ExecuteColor(const TextProperties::TextColor::Color24bBG&) override      {}
        void ExecuteColor(const TextProperties::TextColor::Color24b&) override        {}
        void ExecuteColor(const TextProperties::TextColor::ColorCubeFG&) override     {}
        void ExecuteColor(const TextProperties::TextColor::ColorCubeBG&) override     {}
        void ExecuteColor(const TextProperties::TextColor::ColorCube&) override       {}

    public:
        void ResetFront() override                                                    {}
        void ExecuteFront(const TextProperties::TextFront::FrontID&) override         {}

    public:
        void ResetStyle() override                                                                {}
        void ExecuteStyle(const TextProperties::TextStyle::Intensity&) override                   {}
        void ExecuteStyle(const TextProperties::TextStyle::Italic&) override                      {}
        void ExecuteStyle(const TextProperties::TextStyle::Underline&) override                   {}
        void ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::Color&) override       {}
        void ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::ColorCube&) override   {}
        void ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::Color24b&) override    {}
        void ExecuteStyle(const TextProperties::TextStyle::Blink&) override                       {}
        void ExecuteStyle(const TextProperties::TextStyle::Inverted&) override                    {}
        void ExecuteStyle(const TextProperties::TextStyle::Ideogram&) override                    {}
        void ExecuteStyle(const TextProperties::TextStyle::Script&) override                      {}
    };
}
