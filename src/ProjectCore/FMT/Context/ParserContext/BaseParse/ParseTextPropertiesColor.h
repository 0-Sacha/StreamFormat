#pragma once

#include "ProjectCore/FMT/Context/ParserContext/BasicParserContext.h"

namespace ProjectCore::FMT
{
    template<typename ParserContext>
    struct ParserType<Detail::TextProperties::TextColor::ResetColor, ParserContext>
    {
        static void Format(const Detail::TextProperties::TextColor::ResetColor, ParserContext& context) {
            context.GetTextPropertiesParser().ColorModifReset();
        }
    };

    template<typename ParserContext>
    struct ParserType<Detail::TextProperties::TextColor::BasicColorFG, ParserContext>
    {
        static void Format(const Detail::TextProperties::TextColor::BasicColorFG& t, ParserContext& context) {
            context.GetTextPropertiesParser().ColorModif(t);
        }
    };

    template<typename ParserContext>
    struct ParserType<Detail::TextProperties::TextColor::BasicColorBG, ParserContext>
    {
        static void Format(const Detail::TextProperties::TextColor::BasicColorBG& t, ParserContext& context) {
            context.GetTextPropertiesParser().ColorModif(t);
        }
    };

    template<typename ParserContext>
    struct ParserType<Detail::TextProperties::TextColor::BasicColor, ParserContext>
    {
        static void Format(const Detail::TextProperties::TextColor::BasicColor& t, ParserContext& context) {
            context.GetTextPropertiesParser().ColorModif(t);
        }
    };

    template<typename ParserContext>
    struct ParserType<Detail::TextProperties::TextColor::Color24bFG, ParserContext>
    {
        static void Format(const Detail::TextProperties::TextColor::Color24bFG& t, ParserContext& context) {
            context.GetTextPropertiesParser().ColorModif(t);
        }
    };

    template<typename ParserContext>
    struct ParserType<Detail::TextProperties::TextColor::Color24bBG, ParserContext>
    {
        static void Format(const Detail::TextProperties::TextColor::Color24bBG& t, ParserContext& context) {
            context.GetTextPropertiesParser().ColorModif(t);
        }
    };

    template<typename ParserContext>
    struct ParserType<Detail::TextProperties::TextColor::Color24b, ParserContext>
    {
        static void Format(const Detail::TextProperties::TextColor::Color24b& t, ParserContext& context) {
            context.GetTextPropertiesParser().ColorModif(t);
        }
    };


    template<typename ParserContext>
    struct ParserType<Detail::TextProperties::TextColor::ColorCubeFG, ParserContext>
    {
        static void Format(const Detail::TextProperties::TextColor::ColorCubeFG& t, ParserContext& context) {
            context.GetTextPropertiesParser().ColorModif(t);
        }
    };

    template<typename ParserContext>
    struct ParserType<Detail::TextProperties::TextColor::ColorCubeBG, ParserContext>
    {
        static void Format(const Detail::TextProperties::TextColor::ColorCubeBG& t, ParserContext& context) {
            context.GetTextPropertiesParser().ColorModif(t);
        }
    };

    template<typename ParserContext>
    struct ParserType<Detail::TextProperties::TextColor::ColorCube, ParserContext>
    {
        static void Format(const Detail::TextProperties::TextColor::ColorCube& t, ParserContext& context) {
            context.GetTextPropertiesParser().ColorModif(t);
        }
    };
}
