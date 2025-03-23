#pragma once

#include "stream/fmt/buf/stream.h"
#include "stream/fmt/buf/manip.h"

namespace stream::fmt::buf
{
    template <typename TChar>
    class TestAccess
    {
    public:
        constexpr inline TestAccess(const Stream<TChar>& buffer) noexcept : buffer(buffer) {}
    public:
        const Stream<TChar>& buffer;
    
    public:
        constexpr inline bool is_equal_to(const TChar c) const noexcept { return buffer.get() == c; }
        constexpr inline bool is_not_equal_to(const TChar c) const noexcept { return buffer.get() != c; }
        template <typename... CharToTest>
        constexpr inline bool is_equal_to(const TChar c, const CharToTest... ele) const noexcept
        {
            return is_equal_to(c) || is_equal_to(ele...);
        }
        template <typename... CharToTest>
        constexpr inline bool is_not_equal_to(const TChar c, const CharToTest... ele) const noexcept
        {
            return is_not_equal_to(c) && is_not_equal_to(ele...);
        }

    public:
        constexpr inline bool IsLowerCase() const noexcept { return buffer.get() >= 'a' && buffer.get() <= 'z'; }
        constexpr inline bool IsUpperCase() const noexcept { return buffer.get() >= 'A' && buffer.get() <= 'Z'; }
        constexpr inline bool is_a_digit() const noexcept { return buffer.get() >= '0' && buffer.get() <= '9'; }

    public:
        template <typename CharToTest>
        constexpr bool is_same(const CharToTest* str, std::size_t size) const noexcept
        {
            if (size > Access(buffer).get_buffer_remaining_size())
                { return false; }

            const TChar* bufferStr = buffer.current_pos;
            bool is_same = true;
            while (is_same && size != 0 && *str != 0)
            {
                is_same = *bufferStr++ == *str++;
                --size;
            }
            if (size != 0)
                { return false; }
            return is_same;
        }
        template <typename CharToTest>
        constexpr inline bool is_same(std::basic_string_view<CharToTest> sv) const noexcept
        {
            return is_same(sv.data(), sv.size());
        }
    };

    template <typename TChar>
    class TestManip
    {
    public:
        constexpr inline TestManip(Stream<TChar>& buffer) noexcept : buffer(buffer) {}
    public:
        Stream<TChar>& buffer;

        using TConstChar = std::remove_const_t<TChar>;

    public:
        TestAccess<TChar> access() const noexcept { return TestAccess<TChar>(buffer); }

    public:
        template <typename... CharToTest>
        [[nodiscard]] constexpr inline std::expected<bool, FMTResult> is_equal_to_forward(const CharToTest... ele) noexcept
        {
            if (access().is_equal_to(ele...))
            {
                SF_TRY(Manip(buffer).forward());
                return true;
            }
            return false;
        }
        template <typename... CharToTest>
        [[nodiscard]] constexpr inline std::expected<bool, FMTResult> is_not_equal_forward(const CharToTest... ele) noexcept
        {
            if (access().is_not_equal_to(ele...))
            {
                SF_TRY(Manip(buffer).forward());
                return true;
            }
            return false;
        }

    public:
        template <typename CharToTest>
        [[nodiscard]] constexpr std::expected<bool, FMTResult> is_same_forward(const CharToTest* str, std::size_t size) noexcept
        {
            if (access().is_same(str, size))
            {
                SF_TRY(Manip(buffer).forward(size));
                return true;
            }
            return false;
        }
        template <typename CharToTest>
        [[nodiscard]] constexpr inline std::expected<bool, FMTResult> is_same_forward(std::basic_string_view<CharToTest> sv) noexcept
        {
            if (access().is_same(sv))
            {
                SF_TRY(Manip(buffer).forward(sv.size()));
                return true;
            }
            return false;
        }

    public:
        template <typename... CharToTest>
        [[nodiscard]] inline std::expected<void, FMTResult> skip_one_of(const CharToTest... ele) noexcept
        {
            if (access().is_equal_to(ele...))
            {
                SF_TRY(Manip(buffer).forward());
                return {};
            }
            return std::unexpected(FMTResult::Parse_TokenNotExpected);
        }

        template <typename... CharToTest>
        inline void ignore_one_of(const CharToTest... ele) noexcept
        {
            if (access().is_equal_to(ele...) && Access(buffer).can_move_forward())
                { Manip(buffer).forward_force(); }
        }

        template <typename... CharToTest>
        inline void ignore_every(const CharToTest... ele) noexcept
        {
            while (access().is_equal_to(ele...) && Access(buffer).can_move_forward())
                { Manip(buffer).forward_force(); }
        }
        
    public:
        [[nodiscard]] inline void IgnoreOneSpace() noexcept { return ignore_one_of(' ', '\t'); }
        [[nodiscard]] inline void IgnoreOneBlank() noexcept { return ignore_one_of(' ', '\t', '\n', '\r', '\v'); }

        inline void ignore_every_spaces() noexcept { ignore_every(' ', '\t'); }
        inline void IgnoreEveryBlanks() noexcept { ignore_every(' ', '\t', '\n', '\r', '\v'); }

    public:
        template <typename... CharToTest>
        inline void GoTo(const CharToTest... ele) noexcept
        {
            while (access().is_not_equal_to(ele...) && Access(buffer).can_move_forward())
                Manip(buffer).forward_force();
        }
        template <typename... CharToTest>
        [[nodiscard]] inline std::expected<void, FMTResult> go_to_forward(const CharToTest... ele) noexcept
        {
            GoTo(ele...);
            return Manip(buffer).forward();
        }

    public:
        template <typename Func>
        [[nodiscard]] std::expected<std::basic_string_view<TConstChar>, FMTResult> ViewExec(Func&& func)
        {
            TChar* begin = buffer.current_pos;
            SF_TRY(func());
            TChar* end = buffer.current_pos;
            return std::basic_string_view<TConstChar>(begin, end - begin);
        }

        template <typename... CharToTest>
        [[nodiscard]] inline std::expected<std::basic_string_view<TConstChar>, FMTResult> view_until(CharToTest&&... c)
        {
            return ViewExec([&] -> std::expected<void, FMTResult> { TestManip(buffer).GoTo(std::forward<CharToTest>(c)...); return {}; });
        }
    };
}
