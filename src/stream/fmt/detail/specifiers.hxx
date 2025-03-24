#pragma once

#include "stream/core/prelude.hxx"
#include "stream/core/prelude.hxx"

#include <array>
#include <string_view>
#include <limits>

namespace stream::fmt::detail {
    enum class IntegerPrintBase : char {
        Dec      = 'd',
        Bin      = 'b',
        BinUpper = 'B',
        Hex      = 'x',
        HexUpper = 'X',
        Oct      = 'o',
        OctUpper = 'O',
    };

    struct ShiftInfo {
    public:
        enum class ShiftType : std::int8_t {
            Nothing,
            Right,
            Left,
            CenterRight,
            CenterLeft,
            Default = Nothing
        };

        struct ShiftPrint {
        public:
            constexpr ShiftPrint() : before(' '), after(' ') {}

            constexpr ShiftPrint(char c) : before(c), after(c) {}

            constexpr ShiftPrint(char before, char after) : before(before), after(after) {}

        public:
            char before;
            char after;

        public:
            constexpr bool before_is_a_digit() const {
                return before >= '0' && before <= '9';
            }
        };

    public:
        ShiftType    type  = ShiftType::Default;  // <  - >  - ^
        ShiftPrint   print = ShiftPrint{};        // 0 - ' ' - * .....
        std::int32_t size  = -1;                  // <? - >? - ^?
    };
}  // namespace stream::fmt::detail

namespace stream::fmt::detail {
    template <typename TChar>
    struct FormatSpecifier {
        FormatSpecifier() : name(nullptr, 0), as_text(nullptr, 0), as_number(0), has_text(false), has_number(false) {}

        FormatSpecifier(std::basic_string_view<TChar> name) : name(name), as_text(nullptr, 0), as_number(0), has_text(false), has_number(false) {}

        FormatSpecifier(std::basic_string_view<TChar> name, std::basic_string_view<TChar> value) : name(name), as_text(value), as_number(0), has_text(true), has_number(false) {}

        FormatSpecifier(std::basic_string_view<TChar> name, const std::int32_t value) : name(name), as_text(nullptr, 0), as_number(value), has_text(false), has_number(true) {}

        FormatSpecifier(std::basic_string_view<TChar> name, const std::int32_t value_as_number, std::basic_string_view<TChar> value_as_text)
            : name(name), as_text(value_as_text), as_number(value_as_number), has_text(true), has_number(true) {}

        std::basic_string_view<TChar> name       = "";
        std::basic_string_view<TChar> as_text    = "";
        std::int32_t                  as_number  = 0;
        bool                          has_text   = false;
        bool                          has_number = false;
    };

    template <typename TChar, std::size_t SIZE>
    struct FormatSpecifierList {
    public:
        std::uint8_t                             specifier_count = 0;
        std::array<FormatSpecifier<TChar>, SIZE> specifiers{};

        struct Constraint {
            bool has_text   = false;
            bool has_number = false;
        };

    public:
        FormatSpecifier<TChar>* get(std::basic_string_view<TChar> name, const Constraint& constraint = Constraint{}) {
            STREAMFORMAT_ASSERT(specifier_count <= SIZE);
            for (std::uint8_t i = 0; i < specifier_count; ++i)
                if (specifiers[i].name == name) {
                    bool text_contraint_satisfied   = !constraint.has_text || specifiers[i].has_text;
                    bool number_contraint_satisfied = !constraint.has_number || specifiers[i].has_number;
                    if (text_contraint_satisfied && number_contraint_satisfied) return &specifiers[i];
                }
            return nullptr;
        }

        const FormatSpecifier<TChar>* get(std::basic_string_view<TChar> name, const Constraint& constraint = Constraint{}) const {
            STREAMFORMAT_ASSERT(specifier_count <= SIZE);
            for (std::uint8_t i = 0; i < specifier_count; ++i)
                if (specifiers[i].name == name) {
                    bool text_contraint_satisfied   = !constraint.has_text || specifiers[i].has_text;
                    bool number_contraint_satisfied = !constraint.has_number || specifiers[i].has_number;
                    if (text_contraint_satisfied && number_contraint_satisfied) return &specifiers[i];
                }
            return nullptr;
        }

        bool has(std::basic_string_view<TChar> name) const {
            return get(name) != nullptr;
        }

        std::int32_t get_as_number(std::basic_string_view<TChar> name, std::int32_t default_value) const {
            const FormatSpecifier<TChar>* getptr = get(name, Constraint{.has_number = true});
            if (getptr == nullptr || !getptr->has_number) return default_value;
            return getptr->as_number;
        }

        std::basic_string_view<TChar> get_as_text(std::basic_string_view<TChar> name, std::basic_string_view<TChar> default_value) const {
            const FormatSpecifier<TChar>* getptr = get(name, Constraint{.has_text = true});
            if (getptr == nullptr || !getptr->has_text) return default_value;
            return getptr->as_text;
        }

    public:
        void pushback(const FormatSpecifier<TChar>& specifier) {
            if (specifier_count >= SIZE) throw std::runtime_error("fmt error: Specifiers_Full");
            specifiers[specifier_count++] = specifier;
        }

        void concat(const FormatSpecifier<TChar>& specifier) {
            FormatSpecifier<TChar>* local = get(specifier.name);
            if (local == nullptr) return pushback(specifier);

            if (specifier.has_text) {
                local->has_text = true;
                local->as_text  = specifier.as_text;
            }
            if (specifier.has_number) {
                local->has_number = true;
                local->as_number  = specifier.as_number;
            }
        }
    };

    template <typename TChar>
    struct FormatData {
    public:
        bool has_spec       = false;
        bool keep_new_style = false;  // W

        bool             prefix_suffix   = false;                  // #
        IntegerPrintBase integer_print   = IntegerPrintBase::Dec;  // b  - X  - O  - D
        std::int32_t     float_precision = -1;                     // .
        ShiftInfo        shift;

        FormatSpecifierList<TChar, 10> specifiers;

        std::basic_string_view<TChar> next_override = std::basic_string_view<TChar>(nullptr, 0);

    public:
        void apply(const FormatData& given) {
            *this = given;
        }

        void apply(const IntegerPrintBase& given) {
            integer_print = given;
        }
        void apply(const ShiftInfo& given) {
            shift = given;
        }
        void apply(const FormatSpecifier<TChar>& given) {
            specifiers.concat(given);
        }

        template <typename T>
        bool testapply(const T* given)
            requires requires(const T& value, FormatData& data) { data.apply(value); }
        {
            if (given == nullptr) return false;
            apply(*given);
            return true;
        }
    };

    template <typename T, typename TChar>
    concept format_data_can_apply = requires(const T& value, FormatData<TChar>& data) { data.apply(value); };
}  // namespace stream::fmt::detail
