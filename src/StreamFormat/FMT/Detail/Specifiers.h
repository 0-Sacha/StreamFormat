#pragma once

#include "StreamFormat/Core/Core.h"

#include <array>
#include <string_view>
#include <limits>

namespace StreamFormat::FMT::Detail
{
    enum class IntegerPrintBase : char
    {
        Dec = 'd',
        Bin = 'b',
        BinUpper = 'B',
        Hex = 'x',
        HexUpper = 'X',
        Oct = 'o',
        OctUpper = 'O',
    };

    struct ShiftInfo
    {
    public:
        enum class ShiftType : std::int8_t
        {
            Nothing,
            Right,
            Left,
            CenterRight,
            CenterLeft,
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

    public:
        ShiftType       Type  = ShiftType::Default;     // <  - >  - ^
        ShiftPrint      Print = ShiftPrint{};           // 0 - ' ' - * .....
        std::int32_t    Size  = -1;                     // <? - >? - ^?
    };
}

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    struct FormatSpecifier
    {
        FormatSpecifier()
            : Name(nullptr, 0)
            , AsText(nullptr, 0)
            , AsNumber(0)
            , HasText(false)
            , HasNumber(false)
        {}

        FormatSpecifier(std::basic_string_view<TChar> name)
            : Name(name)
            , AsText(nullptr, 0)
            , AsNumber(0)
            , HasText(false)
            , HasNumber(false)
        {}

        FormatSpecifier(std::basic_string_view<TChar> name, std::basic_string_view<TChar> value)
            : Name(name)
            , AsText(value)
            , AsNumber(0)
            , HasText(true)
            , HasNumber(false)
        {}

        FormatSpecifier(std::basic_string_view<TChar> name, const std::int32_t value)
            : Name(name)
            , AsText(nullptr, 0)
            , AsNumber(value)
            , HasText(false)
            , HasNumber(true)
        {}

        FormatSpecifier(std::basic_string_view<TChar> name, const std::int32_t valueAsNumber, std::basic_string_view<TChar> valueAsText)
            : Name(name)
            , AsText(valueAsText)
            , AsNumber(valueAsNumber)
            , HasText(true)
            , HasNumber(true)
        {}

        std::basic_string_view<TChar>  Name = "";
        std::basic_string_view<TChar>  AsText = "";
        std::int32_t                        AsNumber = 0;
        bool                                HasText = false;
        bool                                HasNumber = false;
    };

    template <typename TChar, std::size_t SIZE>
    struct FormatSpecifierList
    {
    public:
        std::uint8_t                                    SpecifierCount = 0;
        std::array<FormatSpecifier<TChar>, SIZE>   Specifier{};

        struct Constraint
        {
            bool HasText = false;
            bool HasNumber = false;
        };

    public:
        static inline constexpr std::uint8_t NotFound() { return (std::numeric_limits<std::uint8_t>::max)(); }

        FormatSpecifier<TChar>* Get(std::basic_string_view<TChar> name, const Constraint& constraint = Constraint{})
        {
            STREAMFORMAT_ASSERT(SpecifierCount <= SIZE);
            for (std::uint8_t i = 0; i < SpecifierCount; ++i)
                if (Specifier[i].Name == name)
                {
                    bool textContraintsatisfied = !constraint.HasText || Specifier[i].HasText;
                    bool numberContraintsatisfied = !constraint.HasNumber || Specifier[i].HasNumber;
                    if (textContraintsatisfied && numberContraintsatisfied)
                        return &Specifier[i];
                }
            return nullptr;
        }

        const FormatSpecifier<TChar>* Get(std::basic_string_view<TChar> name, const Constraint& constraint = Constraint{}) const
        {
            STREAMFORMAT_ASSERT(SpecifierCount <= SIZE);
            for (std::uint8_t i = 0; i < SpecifierCount; ++i)
                if (Specifier[i].Name == name)
                {
                    bool textContraintsatisfied = !constraint.HasText || Specifier[i].HasText;
                    bool numberContraintsatisfied = !constraint.HasNumber || Specifier[i].HasNumber;
                    if (textContraintsatisfied && numberContraintsatisfied)
                        return &Specifier[i];
                }
            return nullptr;
        }

        bool Has(std::basic_string_view<TChar> name) const { return Get(name) != nullptr; }

        std::int32_t GetAsNumber(std::basic_string_view<TChar> name, std::int32_t defaultValue) const
        {
            const FormatSpecifier<TChar>* get = Get(name, Constraint{.HasNumber = true});
            if (get == nullptr || !get->HasNumber)
                return defaultValue;
            return get->AsNumber;
        }

        std::basic_string_view<TChar> GetAsText(std::basic_string_view<TChar> name, std::basic_string_view<TChar> defaultValue) const
        {
            const FormatSpecifier<TChar>* get = Get(name, Constraint{.HasText = true});
            if (get == nullptr || !get->HasText)
                return defaultValue;
            return get->AsText;
        }

    public:
        void Pushback(const FormatSpecifier<TChar>& specifier)
        {
            if (SpecifierCount < SIZE)
                Specifier[SpecifierCount++] = specifier;
        }

        void Concat(const FormatSpecifier<TChar>& specifier)
        {
            FormatSpecifier<TChar>* local = Get(specifier.Name);
            if (local == nullptr)
                return Pushback(specifier);

            if (specifier.HasText)
                { local->HasText = true; local->AsText  = specifier.AsText; }
            if (specifier.HasNumber)
                { local->HasNumber = true; local->AsNumber  = specifier.AsNumber; }
        }
    };

    template <typename TChar>
    struct FormatData
    {
    public:
        bool HasSpec = false;
        bool KeepNewStyle = false; // W

        bool PrefixSuffix = false; // #
        IntegerPrintBase IntegerPrint = IntegerPrintBase::Dec; // B  - X  - O  - D
        std::int32_t FloatPrecision = -1; // .
        ShiftInfo Shift;

        FormatSpecifierList<TChar, 10> Specifiers;

        std::basic_string_view<TChar> NextOverride = std::basic_string_view<TChar>(nullptr, 0);

    public:
        void Apply(const FormatData& given) { *this = given; }

        void Apply(const IntegerPrintBase& given) { IntegerPrint = given; }
        void Apply(const ShiftInfo& given) { Shift = given; }
        void Apply(const FormatSpecifier<TChar>& given) { Specifiers.Concat(given); }

        template <typename T>
        bool TestApply(const T* given)
            requires requires(const T& value, FormatData& data)
            {
                data.Apply(value);
            }
        {
            if (given == nullptr) return false;
            Apply(*given);
            return true;
        }
    };

    template <typename T, typename TChar>
    concept FormatDataCanApply = requires(const T& value, FormatData<TChar>& data)
    {
        data.Apply(value);
    };
}
