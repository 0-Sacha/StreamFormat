#pragma once

#include "stream/fmt/buf/stream.hxx"
#include "stream/fmt/buf/manip.hxx"

namespace stream::fmt::buf {
    template <typename TChar>
    class TestAccess {
    public:
        constexpr inline TestAccess(const Stream<TChar>& buffer) noexcept : buffer(buffer) {}

    public:
        const Stream<TChar>& buffer;

    public:
        constexpr inline bool is_equal_to(const TChar c) const noexcept {
            return buffer.get() == c;
        }
        constexpr inline bool is_not_equal_to(const TChar c) const noexcept {
            return buffer.get() != c;
        }
        template <typename... CharToTest>
        constexpr inline bool is_equal_to(const TChar c, const CharToTest... ele) const noexcept {
            return is_equal_to(c) || is_equal_to(ele...);
        }
        template <typename... CharToTest>
        constexpr inline bool is_not_equal_to(const TChar c, const CharToTest... ele) const noexcept {
            return is_not_equal_to(c) && is_not_equal_to(ele...);
        }

    public:
        constexpr inline bool is_lower_case() const noexcept {
            return buffer.get() >= 'a' && buffer.get() <= 'z';
        }
        constexpr inline bool is_upper_case() const noexcept {
            return buffer.get() >= 'A' && buffer.get() <= 'Z';
        }
        constexpr inline bool is_a_digit() const noexcept {
            return buffer.get() >= '0' && buffer.get() <= '9';
        }

    public:
        template <typename CharToTest>
        constexpr bool is_same(const CharToTest* str, std::size_t size, bool exact = false) const noexcept {
            if (exact == true && size != buffer.get_buffer_remaining_size()) {
                return false;
            }
            if (size > buffer.get_buffer_remaining_size()) {
                return false;
            }

            const TChar* bufferStr = buffer.current_pos;
            bool         is_same   = true;
            while (is_same && size != 0 && *str != 0) {
                is_same = *bufferStr++ == *str++;
                --size;
            }
            if (size != 0) {
                return false;
            }
            return is_same;
        }
        template <typename CharToTest>
        constexpr inline bool is_same(std::basic_string_view<CharToTest> sv, bool exact = false) const noexcept {
            return is_same(sv.data(), sv.size(), false);
        }
    };

    template <typename TChar>
    class TestManip {
    public:
        constexpr inline TestManip(Stream<TChar>& buffer) noexcept : buffer(buffer) {}

    public:
        Stream<TChar>& buffer;

        using TConstChar = std::remove_const_t<TChar>;

    public:
        TestAccess<TChar> access() const noexcept {
            return TestAccess<TChar>(buffer);
        }

    public:
        template <typename... CharToTest>
        constexpr inline bool is_equal_to_forward(const CharToTest... ele) {
            if (access().is_equal_to(ele...)) {
                Manip(buffer).forward();
                return true;
            }
            return false;
        }
        template <typename... CharToTest>
        constexpr inline bool is_not_equal_forward(const CharToTest... ele) {
            if (access().is_not_equal_to(ele...)) {
                Manip(buffer).forward();
                return true;
            }
            return false;
        }

    public:
        template <typename CharToTest>
        constexpr bool is_same_forward(const CharToTest* str, std::size_t size) {
            if (access().is_same(str, size)) {
                Manip(buffer).forward(size);
                return true;
            }
            return false;
        }
        template <typename CharToTest>
        constexpr inline bool is_same_forward(std::basic_string_view<CharToTest> sv) {
            if (access().is_same(sv)) {
                Manip(buffer).forward(sv.size());
                return true;
            }
            return false;
        }

    public:
        template <typename... CharToTest>
        void skip_one_of(const CharToTest... ele) {
            if (access().is_equal_to(ele...)) {
                Manip(buffer).forward();
            }
            throw std::runtime_error("fmt error: Parse_TokenNotExpected");
        }

        template <typename... CharToTest>
        inline void ignore_one_of(const CharToTest... ele) {
            if (access().is_equal_to(ele...) && Access(buffer).can_move_forward()) {
                Manip(buffer).forward_force();
            }
        }

        template <typename... CharToTest>
        inline void ignore_every(const CharToTest... ele) {
            while (access().is_equal_to(ele...) && Access(buffer).can_move_forward()) {
                Manip(buffer).forward_force();
            }
        }

    public:
        void IgnoreOneSpace() {
            return ignore_one_of(' ', '\t');
        }
        void IgnoreOneBlank() {
            return ignore_one_of(' ', '\t', '\n', '\r', '\v');
        }

        inline void ignore_every_spaces() {
            ignore_every(' ', '\t');
        }
        inline void IgnoreEveryBlanks() {
            ignore_every(' ', '\t', '\n', '\r', '\v');
        }

    public:
        template <typename... CharToTest>
        inline void GoTo(const CharToTest... ele) noexcept {
            while (access().is_not_equal_to(ele...) && Access(buffer).can_move_forward())
                Manip(buffer).forward_force();
        }
        template <typename... CharToTest>
        void go_to_forward(const CharToTest... ele) {
            GoTo(ele...);
            return Manip(buffer).forward();
        }

    public:
        template <typename Func>
        std::basic_string_view<TConstChar> view_exec(Func&& func) {
            TChar* begin = buffer.current_pos;
            func();
            TChar* end = buffer.current_pos;
            return std::basic_string_view<TConstChar>(begin, end - begin);
        }

        template <typename... CharToTest>
        inline std::basic_string_view<TConstChar> view_until(CharToTest&&... c) {
            return view_exec([&] { TestManip(buffer).GoTo(std::forward<CharToTest>(c)...); });
        }
    };
}  // namespace stream::fmt::buf
