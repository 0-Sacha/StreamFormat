#pragma once

#include "prelude.h"

namespace stream::fmt::detail
{
    template <typename T>
    struct FormatTypeForwardAs
    {
        using type = T;
    };

    template <typename From, typename To>
    struct FMTContextConvert
    {
        static constexpr bool is_convertible = false;
    };

    template <typename From, typename To>
    requires(std::is_convertible_v<From, To>&& std::is_convertible_v<const From&, To>) struct FMTContextConvert<From, To>
    {
        static constexpr bool is_convertible = true;
        static constexpr To   convert(const From& from) { return static_cast<To>(from); }
    };

    template <typename From>
    requires(std::is_convertible_v<From, typename std::int32_t>&&
                 std::is_convertible_v<const From&, typename std::int32_t>) struct FMTContextConvert<std::int32_t, From>
    {
        static constexpr bool                is_convertible = true;
        static constexpr std::int32_t convert(const From& from) { return std::int32_t(static_cast<typename std::int32_t>(from)); }
    };

    template <class From, class To>
    concept FMTCanContextConvert = requires(const From& from)
    {
        requires FMTContextConvert<From, To>::is_convertible;
        {
            FMTContextConvert<From, To>::convert(from)
            } -> std::same_as<To>;
    };

    template <typename From, typename To>
    struct FMTContextSame
    {
        static constexpr bool same_as = false;
    };

    template <typename From, typename To>
    requires(std::is_same_v<detail::get_base_type<From>, detail::get_base_type<To>>) struct FMTContextSame<From, To>
    {
        static constexpr bool same_as = true;
    };

    template <class From, class To>
    concept fmt_is_context_same = requires(To* to, const From& from)
    {
        requires FMTContextSame<From, To>::same_as;
        *to = from;
    };
}
