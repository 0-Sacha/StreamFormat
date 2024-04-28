#pragma once

#include "ProjectCore/Core/Core.h"

// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

namespace ProjectCore::FMT::Detail
{
    struct TextProperties
    {
        struct ResetProperties {};

        struct TextColor;
        struct TextStyle;
        struct TextFront;

        struct Properties;
    };
}
