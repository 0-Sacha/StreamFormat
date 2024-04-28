#pragma once

#include "ProjectCore/Core/Core.h"

#include <string>

namespace ProjectCore::FMT::Detail
{
    template<typename T>
    struct RemoveConstPt
    {
        using type = T;
    };

    template<typename T>
    struct RemoveConstPt<T*>
    {
        using type = T*;
    };

    template<typename T>
    struct RemoveConstPt<const T*>
    {
        using type = T*;
    };

    template<typename T>
    using GetBaseType = typename RemoveConstPt<std::remove_cv_t<std::remove_reference_t<T>>>::type;



    template<typename T>
    struct IsCharType
    {
        using BaseType = GetBaseType<T>;
        static constexpr bool Value = std::is_same_v<BaseType, char>
                                   || std::is_same_v<BaseType, wchar_t>
                                   || std::is_same_v<BaseType, char8_t>
                                   || std::is_same_v<BaseType, char16_t>
                                   || std::is_same_v<BaseType, char32_t>;
    };

    template<typename T>
    struct FMTCharTypeFromBuffer
    {
        using Type = void;
    };
    
    template<typename T>
    struct FMTCharTypeFromBuffer<std::basic_string<T>> {
        using Type = GetBaseType<T>;
    };

    template<typename T>
    struct FMTCharTypeFromBuffer<std::basic_string_view<T>> {
        using Type = GetBaseType<T>;
    };

    template<typename T, std::size_t SIZE>
    requires IsCharType<T>::Value
    struct FMTCharTypeFromBuffer<T[SIZE]>
    {
        using Type = GetBaseType<T>;
    };

    template<typename T>
    requires IsCharType<T>::Value
    struct FMTCharTypeFromBuffer<T*>
    {
        using Type = GetBaseType<T>;
    };


    template<typename T>
    struct NumberDetail
    {
        bool IsFloatingNumber    = std::is_floating_point_v<T>;
        bool IsSigned            = std::is_signed_v<T>;
    };
}
