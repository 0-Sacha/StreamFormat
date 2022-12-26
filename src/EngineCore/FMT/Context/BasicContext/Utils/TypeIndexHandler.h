#pragma once

#include "FMT/Detail/Detail.h"
#include "FormatterContextTemplate.h"

namespace EngineCore::FMT::Detail {

    template <typename ...T>
    class TypeIndexHandler { };

    template <>
    class TypeIndexHandler<>
    {
        public:
            template <typename CastTo>
            CastTo* Cast(void* type, int uid)
                    { return nullptr; }

            template <typename ConvertTo>
            ConvertTo Convert(void* from, void* to, int uid)
                    { return ConvertTo{}; }
    };

    template <typename T, typename... REST>
    class TypeIndexHandler<T, REST...> : public TypeIndexHandler<REST...>
    {
        public:
            template <typename CastTo>
            CastTo* Cast(void* type, int uid)
            {
                if constexpr (uid != RuntimeTypeUID<T>::value) 
                    TypeIndexHandler<REST...>::Cast<CastTo>(type, uid);

                if constexpr (Context::FormatterContextArgsTupleSameAs<T, CastTo>::SameAs)
                    return reinterpret_cast<T*>(type);
                return nullptr;
            }

            template <typename ConvertTo>
            ConvertTo Convert(void* from, int uid)
            {
                if constexpr (uid != RuntimeTypeUID<T>::value) 
                    return TypeIndexHandler<REST...>::Convert<ConvertTo>(from, to, uid);

                if constexpr (Context::FormatterContextArgsTupleConvertFunc<T, ConvertTo>::IsConvertible)
                {
                    T& value = *reinterpret_cast<T*>(from);
                    return Context::FormatterContextArgsTupleConvertFunc<T, ConvertTo>::Convert(value);
                }
            }
    };

    static inline TypeIndexHandler<char, wchar_t, char16_t, char32_t,
                                   std::int8_t, std::int16_t, std::int32_t, std::int64_t,
                                   std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t,
                                   
                                   ValueIntPrint,
                                   PrintStyle,
                                   DigitSize,
                                   ShiftSize,
                                   FloatPrecision,
                                   ShiftPrint,
                                   ShiftType,
                                   
                                   FormatData<char>,
                                   FormatData<wchar_t>,
                                   FormatData<char16_t>,
                                   FormatData<char32_t>,
                                   FormatSpecifier<char>,
                                   FormatSpecifier<wchar_t>,
                                   FormatSpecifier<char16_t>,
                                   FormatSpecifier<char32_t>> Handler;
}
