#pragma once

#include "formatter_type.hxx"

namespace stream::fmt {
    /////---------- string_view NamedArgs Do not allocate memory (Best) ----------/////
    template <typename T, typename CharName = char>
    struct StringViewNamedArgs {
    public:
        template <std::size_t SIZE>
        StringViewNamedArgs(const CharName (&name)[SIZE], const T& t) : name_(name), value(t) {}

        StringViewNamedArgs(std::basic_string_view<CharName> name, const T& t) : name_(name), value(t) {}

    public:
        T& get_value() {
            return value;
        }
        const T& get_value() const {
            return value;
        }
        std::basic_string_view<CharName> get_name() const {
            return name_;
        }

    protected:
        std::basic_string_view<CharName> name_;
        const T&                         value;
    };

    template <typename T, typename CharName, typename FormatterExecutor>
    struct FormatterType<StringViewNamedArgs<T, CharName>, FormatterExecutor> {
        static inline void format(const StringViewNamedArgs<T, CharName>& t, FormatterExecutor& executor) {
            return executor.write_type(t.get_value());
        }
    };

    /////---------- stringNamedArgs Allocate memory (Only if necessary) ----------/////
    template <typename T, typename CharName = char>
    struct StringNamedArgs {
    public:
        StringNamedArgs(std::string str, const T& t) : name_(std::move(str)), value(t) {}

    public:
        T& get_value() {
            return value;
        }
        const T& get_value() const {
            return value;
        }
        std::basic_string_view<CharName> get_name() const {
            return name_;
        }

    protected:
        std::basic_string<CharName> name_;
        const T&                    value;
    };

    template <typename T, typename CharName, typename FormatterExecutor>
    struct FormatterType<StringNamedArgs<T, CharName>, FormatterExecutor> {
        static inline void format(const StringNamedArgs<T, CharName>& t, FormatterExecutor& executor) {
            return executor.write_type(t.get_value());
        }
    };

    namespace detail {
        template <typename T>
        struct IsANamedArgs {
        public:
            [[maybe_unused]] inline constexpr static bool value = false;
        };

        template <typename T, typename CharName>
        struct IsANamedArgs<StringViewNamedArgs<T, CharName>> {
            [[maybe_unused]] inline constexpr static bool value = true;
        };

        template <typename T, typename CharName>
        struct IsANamedArgs<StringNamedArgs<T, CharName>> {
            [[maybe_unused]] inline constexpr static bool value = true;
        };

        template <typename T>
        inline constexpr bool IsANamedArgsValue = false;

        template <typename T, typename CharName>
        inline constexpr bool IsANamedArgsValue<StringViewNamedArgs<T, CharName>> = true;

        template <typename T, typename CharName>
        inline constexpr bool IsANamedArgsValue<StringNamedArgs<T, CharName>> = true;
    }  // namespace detail
}  // namespace stream::fmt

#define FORMAT(value) stream::fmt::StringViewNamedArgs(#value, value)
#define FORMAT_SV(name, value) stream::fmt::StringViewNamedArgs(name, value)
#define FORMAT_STR(name, value) stream::fmt::StringNamedArgs(name, value)
