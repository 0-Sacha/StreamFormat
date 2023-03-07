#pragma once 

#include "IParserTextPropertiesExecutor.h"

namespace EngineCore::FMT::Detail
{
    template <typename ParserContext>
	class ParserNOTextPropertiesExecutor : public IParserTextPropertiesExecutor<ParserContext>
    {
    public:
        using Base = IParserTextPropertiesExecutor<ParserContext>;
        using Base::SetContext;
        
    protected:
        using Base::m_Context;

    public:
        void AllPropertiesReset() override                                              {}

    public:
        void ResetColor() override                                                      {}
        void ExecuteColor(const TextProperties::TextColor::BasicColorFG& t) override    {}
        void ExecuteColor(const TextProperties::TextColor::BasicColorBG& t) override    {}
        void ExecuteColor(const TextProperties::TextColor::BasicColor& t) override      {}
        void ExecuteColor(const TextProperties::TextColor::Color24bFG& t) override      {}
        void ExecuteColor(const TextProperties::TextColor::Color24bBG& t) override      {}
        void ExecuteColor(const TextProperties::TextColor::Color24b& t) override        {}
        void ExecuteColor(const TextProperties::TextColor::ColorCubeFG& t) override     {}
        void ExecuteColor(const TextProperties::TextColor::ColorCubeBG& t) override     {}
        void ExecuteColor(const TextProperties::TextColor::ColorCube& t) override       {}

    public:
        void ResetFront() override                                                      {}
        void ExecuteFront(const TextProperties::TextFront::FrontID& t) override         {}

    public:
        void ResetStyle() override                                                                  {}
        void ExecuteStyle(const TextProperties::TextStyle::Intensity& t) override                   {}
        void ExecuteStyle(const TextProperties::TextStyle::Italic& t) override                      {}
        void ExecuteStyle(const TextProperties::TextStyle::Underline& t) override                   {}
        void ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::Color& t) override       {}
        void ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::ColorCube& t) override   {}
        void ExecuteStyle(const TextProperties::TextStyle::UnderlineColor::Color24b& t) override    {}
        void ExecuteStyle(const TextProperties::TextStyle::Blink& t) override                       {}
        void ExecuteStyle(const TextProperties::TextStyle::Inverted& t) override                    {}
        void ExecuteStyle(const TextProperties::TextStyle::Ideogram& t) override                    {}
        void ExecuteStyle(const TextProperties::TextStyle::Script& t) override                      {}
    };
}
