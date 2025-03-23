#pragma once

#include "stream/core/prelude.h"

#include <string>

namespace stream::fmt::detail
{
    template <typename T>
    using get_base_type = std::remove_cv_t<std::remove_reference_t<T>>;

    template <typename T>
    struct IsCharType
    {
        using BaseType              = get_base_type<T>;
        static constexpr bool value = std::is_same_v<BaseType, char> || std::is_same_v<BaseType, wchar_t> || std::is_same_v<BaseType, char8_t> ||
                                      std::is_same_v<BaseType, char16_t> || std::is_same_v<BaseType, char32_t>;
    };
}
