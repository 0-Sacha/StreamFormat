#pragma once

<<<<<<< HEAD:src/EngineCore/FMT/Context/FormatContext/Utils/FormatContextTemplate.h
#include "FMT/Core/Detail/Detail.h"
=======
#include "FMT/Detail/Detail.h"
>>>>>>> 040fab10b4777918832b29a04b07add2d411d3ab:src/EngineCore/Instrumentation/Formatter/Context/FormatContext/Utils/FormatContextTemplate.h

namespace EngineCore::FMT::Context {

    template <typename T>
    struct FormatTypeForwardAs
    {
        using Type = T;
    };


    template <typename From, typename To>
    struct FormatContextArgsTupleConvertFunc
    {
        static constexpr bool IsConvertible = false;
    };

    template <typename From, typename To>
    requires (std::is_convertible_v<From, To>)
    struct FormatContextArgsTupleConvertFunc<From, To>
    {
        static constexpr bool IsConvertible = false;
        static constexpr To Convert(const From& from) { return from; }
    };

    template <typename From, typename To>
    struct FormatContextArgsTupleSameAs
    {
        static constexpr bool SameAs = false;
    };

    template <typename From, typename To>
    requires (std::is_same_v<Detail::GetBaseType<From>, Detail::GetBaseType<To>>)
    struct FormatContextArgsTupleSameAs<From, To>
    {
        static constexpr bool SameAs = true;
    };




    // Base Specializer

    template <typename From>
    requires (std::is_convertible_v<From, Detail::FormatIndex::BaseType>)
    struct FormatContextArgsTupleConvertFunc<Detail::FormatIndex, From>
    {
        static constexpr bool IsConvertible = true;
        static constexpr Detail::FormatIndex Convert(const From& from) { return Detail::FormatIndex(from); }
    };
}
