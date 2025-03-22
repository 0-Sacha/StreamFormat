#pragma once

#include "stream/core/prelude.h"

// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

namespace stream::fmt::detail
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
