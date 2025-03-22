#pragma once

#include "text_properties_color.h"
#include "text_properties_front.h"
#include "text_properties_style.h"

namespace stream::fmt::detail
{
    struct TextProperties::Properties
    {
        TextProperties::TextColor::Color color;
        TextProperties::TextStyle::Style style;
        TextProperties::TextFront::Front front;
    };

    inline bool operator==(const TextProperties::Properties& lhs, const TextProperties::Properties& rhs)
    {
        return lhs.color == rhs.color && lhs.style == rhs.style && lhs.front == rhs.front;
    }
}
