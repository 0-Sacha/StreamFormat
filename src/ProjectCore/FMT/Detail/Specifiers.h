#pragma once

#include "ProjectCore/Core/Core.h"

#include "ContextTypes.h"

#include <array>
#include <string_view>

namespace ProjectCore::FMT::Detail
{
    enum class ValueIntPrint : DataType
    {
        Dec,
        Bin,
        Hex,
        Oct,
        Default = Dec
    };

    enum class ShiftType : DataType
    {
        Nothing,
        Right,
        Left,
        CenterRight,
        CenterLeft,
        Default = Nothing
    };

    enum class PrintStyle : DataType
    {
        Nothing,
        UpperCase,
        LowerCase,
        Default = Nothing
    };

    struct ShiftPrint
    {
    public:
        constexpr ShiftPrint()
            : Before(' ')
            , After(' ')
        {}

        constexpr ShiftPrint(char c)
            : Before(c)
            , After(c)
        {}

        constexpr ShiftPrint(char before, char after)
            : Before(before)
            , After(after)
        {}

    public:
        char Before;
        char After;

    public:
        constexpr bool BeforeIsADigit() const { return Before >= '0' && Before <= '9'; }

        constexpr void ValidateForNumber()
        {
            if (After >= '0' && After <= '9') After = ' ';
        }
    };

    static constexpr ShiftPrint ShiftPrint_Space   = ShiftPrint(' ');
    static constexpr ShiftPrint ShiftPrint_Zeros   = ShiftPrint('0', ' ');
    static constexpr ShiftPrint ShiftPrint_Chevron = ShiftPrint('>', '<');

    // No need of virtual destructor since DigitSize is purely a renaming of BasicCustomDataType<DataType, -1, -2>
    struct DigitSize : public BasicCustomDataType<DataType, -1, -2>
    {
    public:
        static constexpr DataType MAX_DIGIT_SIZE = std::numeric_limits<DataType>::max();

    public:
        inline constexpr DigitSize(const DataType value = DEFAULT)
            : BasicCustomDataType<DataType, -1, -2>(value)
        {}

    public:
        using Base = BasicCustomDataType<DataType, -1, -2>;
        using Base::operator+;
        using Base::operator-;
        using Base::operator++;
        using Base::operator--;

        using Base::operator=;
        using Base::operator+=;
        using Base::operator-=;
        using Base::operator*=;
        using Base::operator/=;
    };

    // No need of virtual destructor since ShiftSize is purely a renaming of BasicCustomDataType<DataType, 0, -1>
    struct ShiftSize : public BasicCustomDataType<DataType, 0, -1>
    {
    public:
        inline constexpr ShiftSize(const DataType value = DEFAULT)
            : BasicCustomDataType<DataType, 0, -1>(value)
        {}

    public:
        using Base = BasicCustomDataType<DataType, 0, -1>;
        using Base::operator+;
        using Base::operator-;
        using Base::operator++;
        using Base::operator--;

        using Base::operator=;
        using Base::operator+=;
        using Base::operator-=;
        using Base::operator*=;
        using Base::operator/=;
    };

    // No need of virtual destructor since FloatPrecision is purely a renaming of BasicCustomDataType<DataType, -1, -2>
    struct FloatPrecision : public BasicCustomDataType<DataType, -1, -2>
    {
    public:
        static constexpr DataType BASIC_DECIMAL_SIZE = 4;

    public:
        inline constexpr FloatPrecision(const DataType value = DEFAULT)
            : BasicCustomDataType<DataType, -1, -2>(value)
        {}

        inline constexpr void SetToBasicSizeIfDefault()
        {
            if (IsDefault()) Value = BASIC_DECIMAL_SIZE;
        }

    public:
        using Base = BasicCustomDataType<DataType, -1, -2>;
        using Base::operator+;
        using Base::operator-;
        using Base::operator++;
        using Base::operator--;

        using Base::operator=;
        using Base::operator+=;
        using Base::operator-=;
        using Base::operator*=;
        using Base::operator/=;
    };

}

namespace ProjectCore::FMT::Detail
{
    template <typename CharFormat>
    struct FormatSpecifier
    {
        FormatSpecifier()
            : Name(nullptr, 0)
            , ValueAsText(nullptr, 0)
            , ValueAsNumber(0)
            , ValueHasText(false)
            , ValueHasNumber(false)
        {}

        FormatSpecifier(const std::basic_string_view<CharFormat>& name)
            : Name(name)
            , ValueAsText(nullptr, 0)
            , ValueAsNumber(0)
            , ValueHasText(false)
            , ValueHasNumber(false)
        {}

        FormatSpecifier(const std::basic_string_view<CharFormat>& name, const std::basic_string_view<CharFormat>& value)
            : Name(name)
            , ValueAsText(value)
            , ValueAsNumber(0)
            , ValueHasText(true)
            , ValueHasNumber(false)
        {}

        FormatSpecifier(const std::basic_string_view<CharFormat>& name, const Detail::DataType value)
            : Name(name)
            , ValueAsText(nullptr, 0)
            , ValueAsNumber(value)
            , ValueHasText(false)
            , ValueHasNumber(true)
        {}

        FormatSpecifier(const std::basic_string_view<CharFormat>& name, const Detail::DataType valueAsNumber, const std::basic_string_view<CharFormat>& valueAsText)
            : Name(name)
            , ValueAsText(valueAsText)
            , ValueAsNumber(valueAsNumber)
            , ValueHasText(true)
            , ValueHasNumber(true)
        {}

        FormatSpecifier(const std::basic_string_view<CharFormat>& name, const std::basic_string_view<CharFormat>& valueAsText, const Detail::DataType valueAsNumber)
            : Name(name)
            , ValueAsText(valueAsText)
            , ValueAsNumber(valueAsNumber)
            , ValueHasText(true)
            , ValueHasNumber(true)
        {}

        static inline constexpr Detail::DataType                   SpecifierAsNumberNotSpecified = Detail::FORMAT_DATA_NOT_SPECIFIED;
        static inline constexpr std::basic_string_view<CharFormat> SpecifierAsTextNotSpecified   = std::basic_string_view<CharFormat>("");

        std::basic_string_view<CharFormat> Name;
        std::basic_string_view<CharFormat> ValueAsText;
        Detail::DataType                   ValueAsNumber;
        bool                               ValueHasText;
        bool                               ValueHasNumber;
    };

    template <typename CharFormat>
    struct FormatData
    {
    public:
        using FormatSpecifierType = FormatSpecifier<CharFormat>;

    public:
        bool IsInit  = false;
        bool HasSpec = false;

        bool KeepNewStyle = false;  // W

        bool TrueValue = false;  // =
        bool Safe      = false;  // Safe

        Detail::ValueIntPrint  IntPrint       = Detail::ValueIntPrint::Default;  // B  - X  - O  - D
        Detail::DigitSize      DigitSize      = Detail::DigitSize{};             // B? - X? - O? - D?
        Detail::FloatPrecision FloatPrecision = Detail::FloatPrecision{};        // .

        Detail::PrintStyle PrintStyle = Detail::PrintStyle::Default;  // U  - L

        Detail::ShiftPrint ShiftPrint = Detail::ShiftPrint{};        // 0 - ' ' - * .....
        Detail::ShiftSize  ShiftSize  = Detail::ShiftSize{};         // <? - >? - ^?
        Detail::ShiftType  ShiftType  = Detail::ShiftType::Default;  // <  - >  - ^

        std::basic_string_view<CharFormat> NextOverride = std::basic_string_view<CharFormat>(nullptr, 0);

        std::uint8_t                                SpecifierCount = 0;
        std::array<FormatSpecifier<CharFormat>, 10> Specifier{};

    public:
        static inline constexpr std::uint8_t NotFound() { return (std::numeric_limits<std::uint8_t>::max)(); }

        FormatSpecifierType* GetSpecifier(const std::basic_string_view<CharFormat>& name)
        {
            for (std::uint8_t i = 0; i < SpecifierCount; ++i)
                if (Specifier[i].Name == name) return &Specifier[i];
            return nullptr;
        }

        FormatSpecifierType* GetSpecifierOnlyText(const std::basic_string_view<CharFormat>& name)
        {
            for (std::uint8_t i = 0; i < SpecifierCount; ++i)
                if (Specifier[i].ValueHasText && Specifier[i].Name == name) return &Specifier[i];
            return nullptr;
        }

        FormatSpecifierType* GetSpecifierOnlyNumber(const std::basic_string_view<CharFormat>& name)
        {
            for (std::uint8_t i = 0; i < SpecifierCount; ++i)
                if (Specifier[i].ValueHasNumber && Specifier[i].Name == name) return &Specifier[i];
            return nullptr;
        }

        const FormatSpecifierType* GetSpecifier(const std::basic_string_view<CharFormat>& name) const
        {
            for (std::uint8_t i = 0; i < SpecifierCount; ++i)
                if (Specifier[i].Name == name) return &Specifier[i];
            return nullptr;
        }

        bool HasSpecifier(const std::basic_string_view<CharFormat>& name) const { return GetSpecifier(name) != nullptr; }

        const FormatSpecifierType* GetSpecifierOnlyText(const std::basic_string_view<CharFormat>& name) const
        {
            for (std::uint8_t i = 0; i < SpecifierCount; ++i)
                if (Specifier[i].ValueHasText && Specifier[i].Name == name) return &Specifier[i];
            return nullptr;
        }

        const FormatSpecifierType* GetSpecifierOnlyNumber(const std::basic_string_view<CharFormat>& name) const
        {
            for (std::uint8_t i = 0; i < SpecifierCount; ++i)
                if (Specifier[i].ValueHasNumber && Specifier[i].Name == name) return &Specifier[i];
            return nullptr;
        }

        std::basic_string_view<CharFormat> GetSpecifierAsText(const std::basic_string_view<CharFormat>& name,
                                                              const std::basic_string_view<CharFormat>& defaultValue = FormatSpecifierType::SpecifierAsTextNotSpecified) const
        {
            const FormatSpecifierType* formatSpecifier = GetSpecifierOnlyText(name);
            if (formatSpecifier == nullptr) return defaultValue;
            return formatSpecifier->ValueAsText;
        }

        Detail::DataType GetSpecifierAsNumber(const std::basic_string_view<CharFormat>& name,
                                              const Detail::DataType                    defaultValue = FormatSpecifierType::SpecifierAsNumberNotSpecified) const
        {
            const FormatSpecifierType* formatSpecifier = GetSpecifierOnlyNumber(name);
            if (formatSpecifier == nullptr) return defaultValue;
            return formatSpecifier->ValueAsNumber;
        }

        void AddSpecifierForce(const FormatSpecifierType& specifier)
        {
            if (SpecifierCount < Specifier.size()) Specifier[SpecifierCount++] = specifier;
        }

        void AddSpecifier(const FormatSpecifierType& specifier, bool dontOverride = false)
        {
            FormatSpecifierType* formatSpecifier = GetSpecifier(specifier.Name);
            if (formatSpecifier == nullptr)
                AddSpecifierForce(specifier);
            else if (dontOverride == false)
            {
                if (specifier.ValueHasText)
                {
                    formatSpecifier->ValueHasText = true;
                    formatSpecifier->ValueAsText  = specifier.ValueAsText;
                }
                if (specifier.ValueHasNumber)
                {
                    formatSpecifier->ValueHasNumber = true;
                    formatSpecifier->ValueAsNumber  = specifier.ValueAsNumber;
                }
            }
        }

        void AddSpecifier(const std::basic_string_view<CharFormat>& name, const std::basic_string_view<CharFormat>& value, bool dontOverride = false)
        {
            FormatSpecifierType* formatSpecifier = GetSpecifier(name);
            if (formatSpecifier == nullptr)
                AddSpecifierForce(FormatSpecifierType(name, value));
            else if (dontOverride == false)
            {
                formatSpecifier->ValueHasText = true;
                formatSpecifier->ValueAsText  = value;
            }
        }

        void AddSpecifier(const std::basic_string_view<CharFormat>& name, const Detail::DataType value, bool dontOverride = false)
        {
            FormatSpecifierType* formatSpecifier = GetSpecifier(name);
            if (formatSpecifier == nullptr)
                AddSpecifierForce(FormatSpecifierType(name, value));
            else if (dontOverride == false)
            {
                formatSpecifier->ValueHasNumber = true;
                formatSpecifier->ValueAsNumber  = value;
            }
        }

        void AddSpecifier(const std::basic_string_view<CharFormat>& name)
        {
            FormatSpecifierType* formatSpecifier = GetSpecifier(name);
            if (formatSpecifier == nullptr) AddSpecifierForce(FormatSpecifierType(name));
        }

    public:
        void Apply(const FormatData& given) { *this = given; }

        void Apply(const Detail::ValueIntPrint& given) { IntPrint = given; }
        void Apply(const Detail::PrintStyle& given) { PrintStyle = given; }
        void Apply(const Detail::DigitSize& given) { DigitSize = given; }
        void Apply(const Detail::ShiftSize& given) { ShiftSize = given; }
        void Apply(const Detail::FloatPrecision& given) { FloatPrecision = given; }
        void Apply(const Detail::ShiftPrint& given) { ShiftPrint = given; }
        void Apply(const Detail::ShiftType& given) { ShiftType = given; }
        void Apply(const FormatSpecifier<CharFormat>& given) { AddSpecifier(given); }

        template <typename T>
        bool TestApply(const T* given) requires requires(const T& value, FormatData& data)
        {
            data.Apply(value);
        }
        {
            if (given == nullptr) return false;
            Apply(*given);
            return true;
        }
    };

    template <typename T, typename CharFormat>
    concept FormatDataCanApply = requires(const T& value, FormatData<CharFormat>& data)
    {
        data.Apply(value);
    };
}
