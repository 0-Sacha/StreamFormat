#pragma once

#include "TextPropertiesColor.h"
#include "TextPropertiesStyle.h"
#include "TextPropertiesFront.h"

namespace ProjectCore::FMT::Detail
{
    struct TextProperties::Properties
    {
        TextProperties::TextColor::Color Color;
        TextProperties::TextStyle::Style Style;
        TextProperties::TextFront::Front Front;
    };

    inline bool operator==(const TextProperties::Properties& lhs, const TextProperties::Properties& rhs)
    {
        return lhs.Color == rhs.Color && lhs.Style == rhs.Style && lhs.Front == rhs.Front;
    }
}
