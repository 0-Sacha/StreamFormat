#pragma once

#include "StreamFormat/FMT/Buffer/BufferInfo.h"
#include "StreamFormat/FMT/Buffer/BufferManip.h"

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    class BufferTestAccess
    {
    public:
        constexpr inline BufferTestAccess(const BufferInfo<TChar>& buffer) noexcept : Buffer(buffer) {}
    public:
        const BufferInfo<TChar>& Buffer;
    
    public:
        constexpr inline bool IsEqualTo(const TChar c) const noexcept { return Buffer.Get() == c; }
        constexpr inline bool IsNotEqualTo(const TChar c) const noexcept { return Buffer.Get() != c; }
        template <typename... CharToTest>
        constexpr inline bool IsEqualTo(const TChar c, const CharToTest... ele) const noexcept
        {
            return IsEqualTo(c) || IsEqualTo(ele...);
        }
        template <typename... CharToTest>
        constexpr inline bool IsNotEqualTo(const TChar c, const CharToTest... ele) const noexcept
        {
            return IsNotEqualTo(c) && IsNotEqualTo(ele...);
        }
        
        constexpr inline bool NextIsEqualTo(const TChar c) const noexcept { return BufferAccess(Buffer).GetNextForce() + 1 == c; }
        constexpr inline bool NextIsNotEqualTo(const TChar c) const noexcept { return BufferAccess(Buffer).GetNextForce() + 1 != c; }
        constexpr inline bool PrevIsEqualTo(const TChar c) const noexcept { return BufferAccess(Buffer).GetPrevForce() - 1 == c; }
        constexpr inline bool PrevIsNotEqualTo(const TChar c) const noexcept { return BufferAccess(Buffer).GetPrevForce() - 1 != c; }

    public:
        constexpr inline bool IsLowerCase() const noexcept { return Buffer.Get() >= 'a' && Buffer.Get() <= 'z'; }
        constexpr inline bool IsUpperCase() const noexcept { return Buffer.Get() >= 'A' && Buffer.Get() <= 'Z'; }
        constexpr inline bool IsADigit() const noexcept { return Buffer.Get() >= '0' && Buffer.Get() <= '9'; }

    public:
        template <typename CharToTest>
        constexpr bool IsSame(const CharToTest* str, std::size_t size) const noexcept
        {
            if (size > BufferAccess(Buffer).GetBufferRemainingSize())
                { return false; }

            const TChar* bufferStr = Buffer.CurrentPos;
            bool isSame = true;
            while (isSame && size != 0 && *str != 0)
            {
                isSame = *bufferStr++ == *str++;
                --size;
            }
            if (size != 0)
                { return false; }
            return isSame;
        }
        template <typename CharToTest>
        constexpr inline bool IsSame(std::basic_string_view<CharToTest> sv) const noexcept
        {
            return IsSame(sv.data(), sv.size());
        }
    };

    template <typename TChar>
    class BufferTestManip
    {
    public:
        constexpr inline BufferTestManip(BufferInfo<TChar>& buffer) noexcept : Buffer(buffer) {}
    public:
        BufferInfo<TChar>& Buffer;

        using TConstChar = std::remove_const_t<TChar>;

    public:
        BufferTestAccess<TChar> Access() const noexcept { return BufferTestAccess<TChar>(Buffer); }

    public:
        template <typename... CharToTest>
        [[nodiscard]] constexpr inline std::expected<bool, FMTResult> IsEqualToForward(const CharToTest... ele) noexcept
        {
            if (Access().IsEqualTo(ele...))
            {
                SF_TRY(BufferManip(Buffer).Forward());
                return true;
            }
            return false;
        }
        template <typename... CharToTest>
        [[nodiscard]] constexpr inline std::expected<bool, FMTResult> IsNotEqualForward(const CharToTest... ele) noexcept
        {
            if (Access().IsNotEqualTo(ele...))
            {
                SF_TRY(BufferManip(Buffer).Forward());
                return true;
            }
            return false;
        }

    public:
        template <typename CharToTest>
        [[nodiscard]] constexpr std::expected<bool, FMTResult> IsSameForward(const CharToTest* str, std::size_t size) noexcept
        {
            if (Access().IsSame(str, size))
            {
                SF_TRY(BufferManip(Buffer).Forward(size));
                return true;
            }
            return false;
        }
        template <typename CharToTest>
        [[nodiscard]] constexpr inline std::expected<bool, FMTResult> IsSameForward(std::basic_string_view<CharToTest> sv) noexcept
        {
            if (Access().IsSame(sv))
            {
                SF_TRY(BufferManip(Buffer).Forward(sv.size()));
                return true;
            }
            return false;
        }

    public:
        template <typename... CharToTest>
        [[nodiscard]] inline std::expected<void, FMTResult> SkipOneOf(const CharToTest... ele) noexcept
        {
            if (Access().IsEqualTo(ele...))
            {
                SF_TRY(BufferManip(Buffer).Forward());
                return;
            }
            return std::unexpected(FMTResult::Parse_TokenNotExpected);
        }

        template <typename... CharToTest>
        inline void IgnoreOneOf(const CharToTest... ele) noexcept
        {
            if (Access().IsEqualTo(ele...) && BufferAccess(Buffer).CanMoveForward())
                { BufferManip(Buffer).ForceForward(); }
        }

        template <typename... CharToTest>
        inline void IgnoreEvery(const CharToTest... ele) noexcept
        {
            while (Access().IsEqualTo(ele...) && BufferAccess(Buffer).CanMoveForward())
                { BufferManip(Buffer).ForceForward(); }
        }
        
    public:
        [[nodiscard]] inline void IgnoreOneSpace() noexcept { return IgnoreOneOf(' ', '\t'); }
        [[nodiscard]] inline void IgnoreOneBlank() noexcept { return IgnoreOneOf(' ', '\t', '\n', '\r', '\v'); }

        inline void IgnoreEverySpaces() noexcept { IgnoreEvery(' ', '\t'); }
        inline void IgnoreEveryBlanks() noexcept { IgnoreEvery(' ', '\t', '\n', '\r', '\v'); }

    public:
        template <typename... CharToTest>
        inline void GoTo(const CharToTest... ele) noexcept
        {
            while (Access().IsNotEqualTo(ele...) && BufferAccess(Buffer).CanMoveForward())
                BufferManip(Buffer).ForceForward();
        }
        template <typename... CharToTest>
        [[nodiscard]] inline std::expected<void, FMTResult> GoToForward(const CharToTest... ele) noexcept
        {
            GoTo(ele...);
            return BufferManip(Buffer).Forward();
        }

    public:
        template <typename Func>
        [[nodiscard]] std::expected<std::basic_string_view<TConstChar>, FMTResult> ViewExec(Func&& func)
        {
            TChar* begin = Buffer.CurrentPos;
            SF_TRY(func());
            TChar* end = Buffer.CurrentPos;
            return std::basic_string_view<TConstChar>(begin, end - begin);
        }

        template <typename... CharToTest>
        [[nodiscard]] inline std::expected<std::basic_string_view<TConstChar>, FMTResult> ViewUntil(CharToTest&&... c)
        {
            return ViewExec([&] -> std::expected<void, FMTResult> { BufferTestManip(Buffer).GoTo(std::forward<CharToTest>(c)...); return {}; });
        }
    };
}
