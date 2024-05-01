#pragma once

#include "ProjectCore/Core/Core.h"

#include <string>

namespace ProjectCore::FMT::Detail
{
    //--------------------------------------------//
    //----------------- BaseType -----------------//
    //--------------------------------------------//

    template <typename T>
    struct RemoveConstPt
    {
        using type = T;
    };

    template <typename T>
    struct RemoveConstPt<T*>
    {
        using type = T*;
    };

    template <typename T>
    struct RemoveConstPt<const T*>
    {
        using type = T*;
    };

    template <typename T>
    using GetBaseType = typename RemoveConstPt<std::remove_cv_t<std::remove_reference_t<T>>>::type;


    //------------------------------------------------------//
    //----------------- CXX Types Concepts -----------------//
    //------------------------------------------------------//

    template <typename T>
    struct IsCharType
    {
        using BaseType = GetBaseType<T>;
        static constexpr bool Value = std::is_same_v<BaseType, char>
                                   || std::is_same_v<BaseType, wchar_t>
                                   || std::is_same_v<BaseType, char8_t>
                                   || std::is_same_v<BaseType, char16_t>
                                   || std::is_same_v<BaseType, char32_t>;
    };

    template <typename T>
    concept AsCharType = IsCharType<T>::Value;

    template <typename T>
    concept AsFloatType = std::is_floating_point_v<T>;

    template <typename T>
    concept AsSignedIntegerType = std::is_signed_v<T> && !std::is_floating_point_v<T> && !IsCharType<T>::Value;

    template <typename T>
    concept AsUnsignedIntegerType = std::is_unsigned_v<T> && !std::is_floating_point_v<T> && !IsCharType<T>::Value;

    
    //----------------------------------------------------------//
    //----------------- Buffers Types Concepts -----------------//
    //----------------------------------------------------------//

    template <typename T>
    struct FMTCharTypeFromBuffer
    {
        using Type = void;
    };
    
    template <typename T>
    struct FMTCharTypeFromBuffer<std::basic_string<T>> {
        using Type = GetBaseType<T>;
    };

    template <typename T>
    struct FMTCharTypeFromBuffer<std::basic_string_view<T>> {
        using Type = GetBaseType<T>;
    };

    template <typename T, std::size_t SIZE>
    requires IsCharType<T>::Value
    struct FMTCharTypeFromBuffer<T[SIZE]>
    {
        using Type = GetBaseType<T>;
    };

    template <typename T>
    requires IsCharType<T>::Value
    struct FMTCharTypeFromBuffer<T*>
    {
        using Type = GetBaseType<T>;
    };
}
