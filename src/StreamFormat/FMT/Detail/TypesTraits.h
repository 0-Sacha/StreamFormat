#pragma once

#include "StreamFormat/Core/Core.h"

#include <string>

namespace StreamFormat::FMT::Detail
{
    //--------------------------------------------//
    //----------------- BaseType -----------------//
    //--------------------------------------------//

    template <typename T>
    using GetBaseType = std::remove_cv_t<std::remove_reference_t<T>>;

    //------------------------------------------------------//
    //----------------- CXX Types Concepts -----------------//
    //------------------------------------------------------//

    template <typename T>
    struct IsCharType
    {
        using BaseType              = GetBaseType<T>;
        static constexpr bool Value = std::is_same_v<BaseType, char> || std::is_same_v<BaseType, wchar_t> || std::is_same_v<BaseType, char8_t> ||
                                      std::is_same_v<BaseType, char16_t> || std::is_same_v<BaseType, char32_t>;
    };
}
