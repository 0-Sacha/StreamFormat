#pragma once

#include "EngineCore/Core/Core.h"
#include "EngineCore/Detail/Detail.h"

// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

namespace EngineCore::FMT::Detail
{
    struct TextProperties
    {
        struct Reset {};

        struct TextColor;
        struct TextStyle;
        struct TextFront;

        struct Properties;
    };

}
