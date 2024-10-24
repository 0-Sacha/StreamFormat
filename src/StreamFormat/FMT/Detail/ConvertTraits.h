#pragma once

#include "Detail.h"

namespace StreamFormat::FMT::Detail
{
    template <typename T>
    struct FormatTypeForwardAs
    {
        using Type = T;
    };

    template <typename From, typename To>
    struct FMTContextConvert
    {
        static constexpr bool IsConvertible = false;
    };

    template <typename From, typename To>
    requires(std::is_convertible_v<From, To>&& std::is_convertible_v<const From&, To>) struct FMTContextConvert<From, To>
    {
        static constexpr bool IsConvertible = true;
        static constexpr To   Convert(const From& from) { return static_cast<To>(from); }
    };

    template <typename From>
    requires(std::is_convertible_v<From, typename std::int32_t>&&
                 std::is_convertible_v<const From&, typename std::int32_t>) struct FMTContextConvert<std::int32_t, From>
    {
        static constexpr bool                IsConvertible = true;
        static constexpr std::int32_t Convert(const From& from) { return std::int32_t(static_cast<typename std::int32_t>(from)); }
    };

    template <class From, class To>
    concept FMTCanContextConvert = requires(const From& from)
    {
        requires FMTContextConvert<From, To>::IsConvertible;
        {
            FMTContextConvert<From, To>::Convert(from)
            } -> std::same_as<To>;
    };

    template <typename From, typename To>
    struct FMTContextSame
    {
        static constexpr bool SameAs = false;
    };

    template <typename From, typename To>
    requires(std::is_same_v<Detail::GetBaseType<From>, Detail::GetBaseType<To>>) struct FMTContextSame<From, To>
    {
        static constexpr bool SameAs = true;
    };

    template <class From, class To>
    concept FMTIsContextSame = requires(To* to, const From& from)
    {
        requires FMTContextSame<From, To>::SameAs;
        *to = from;
    };
}
