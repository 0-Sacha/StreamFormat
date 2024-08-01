#pragma once

#include "StreamFormat/Core/Core.h"

// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

namespace StreamFormat::FMT::Detail
{
    struct TextProperties
    {
        struct ResetProperties
        {
        };

        struct TextColor;
        struct TextStyle;
        struct TextFront;

        struct Properties;
    };
}
