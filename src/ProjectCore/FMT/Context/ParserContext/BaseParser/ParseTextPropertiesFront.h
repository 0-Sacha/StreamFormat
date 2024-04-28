#pragma once

#include "ProjectCore/FMT/Context/ParserContext/BasicParserContext.h"

namespace ProjectCore::FMT
{
    template<typename ParserContext>
    struct ParserType<Detail::TextProperties::TextFront::ResetFront, ParserContext>
    {
        static void Format(const Detail::TextProperties::TextFront::ResetFront, ParserContext& context) {
            context.GetTextProperties().ApplyFrontReset();
        }
    };

    template<typename ParserContext>
    struct ParserType<Detail::TextProperties::TextFront::FrontID, ParserContext>
    {
        static void Format(const Detail::TextProperties::TextFront::FrontID t, ParserContext& context) {
            context.GetTextProperties().ApplyFront(t);
        }
    };
}
