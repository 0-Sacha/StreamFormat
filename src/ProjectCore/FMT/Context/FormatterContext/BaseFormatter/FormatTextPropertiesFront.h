#pragma once

#include "ProjectCore/FMT/Context/FormatterContext/BasicFormatterContext.h"

namespace ProjectCore::FMT
{
    template<typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextFront::ResetFront, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextFront::ResetFront, FormatterContext& context)
        {
            context.GetTextProperties().ApplyFrontReset();
        }
    };

    template<typename FormatterContext>
    struct FormatterType<Detail::TextProperties::TextFront::FrontID, FormatterContext>
    {
        static void Format(const Detail::TextProperties::TextFront::FrontID t, FormatterContext& context)
        {
            context.GetTextProperties().AskApplyFront(t);
        }
    };
}
