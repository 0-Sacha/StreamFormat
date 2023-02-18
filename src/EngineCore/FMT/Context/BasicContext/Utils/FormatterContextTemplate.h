#pragma once

#include "EngineCore/FMT/Detail/Detail.h"

namespace EngineCore::FMT::Detail {

    template <typename T>
    struct FormatTypeForwardAs
    {
        using Type = T;
    };

    template <typename From, typename To>
    struct FormatterContextArgsTupleConvertFunc
    {
        static constexpr bool IsConvertible = false;
    };

    template <typename From, typename To>
    requires (std::is_convertible_v<From, To>)
    struct FormatterContextArgsTupleConvertFunc<From, To>
    {
        static constexpr bool IsConvertible = false;
        static constexpr To Convert(const From& from) { return from; }
    };

    template <typename From, typename To>
    struct FormatterContextArgsTupleSameAs
    {
        static constexpr bool SameAs = false;
    };

    template <typename From, typename To>
    requires (std::is_same_v<Detail::GetBaseType<From>, Detail::GetBaseType<To>>)
    struct FormatterContextArgsTupleSameAs<From, To>
    {
        static constexpr bool SameAs = true;
    };

    // Base Specializer
    template <typename From>
    requires (std::is_convertible_v<From, Detail::FormatIndex::BaseType>)
    struct FormatterContextArgsTupleConvertFunc<Detail::FormatIndex, From>
    {
        static constexpr bool IsConvertible = true;
        static constexpr Detail::FormatIndex Convert(const From& from) { return Detail::FormatIndex(static_cast<Detail::FormatIndex::BaseType>(from)); }
    };

}
