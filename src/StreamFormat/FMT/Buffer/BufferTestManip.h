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
        constexpr inline BufferManipResult IsEqualTo(const TChar c) const noexcept { return Buffer.Get() == c; }
        constexpr inline BufferManipResult IsNotEqualTo(const TChar c) const noexcept { return Buffer.Get() != c; }
        template <typename... CharToTest>
        constexpr inline BufferManipResult IsEqualTo(const TChar c, const CharToTest... ele) const noexcept
        {
            return IsEqualTo(c) || IsEqualTo(ele...);
        }
        template <typename... CharToTest>
        constexpr inline BufferManipResult IsNotEqualTo(const TChar c, const CharToTest... ele) const noexcept
        {
            return IsNotEqualTo(c) && IsNotEqualTo(ele...);
        }
        
        constexpr inline BufferManipResult NextIsEqualTo(const TChar c) const noexcept { return BufferAccess(Buffer).GetNextForce() + 1 == c; }
        constexpr inline BufferManipResult NextIsNotEqualTo(const TChar c) const noexcept { return BufferAccess(Buffer).GetNextForce() + 1 != c; }
        constexpr inline BufferManipResult PrevIsEqualTo(const TChar c) const noexcept { return BufferAccess(Buffer).GetPrevForce() - 1 == c; }
        constexpr inline BufferManipResult PrevIsNotEqualTo(const TChar c) const noexcept { return BufferAccess(Buffer).GetPrevForce() - 1 != c; }

    public:
        constexpr inline BufferManipResult IsLowerCase() const noexcept { return Buffer.Get() >= 'a' && Buffer.Get() <= 'z'; }
        constexpr inline BufferManipResult IsUpperCase() const noexcept { return Buffer.Get() >= 'A' && Buffer.Get() <= 'Z'; }
        constexpr inline BufferManipResult IsADigit() const noexcept { return Buffer.Get() >= '0' && Buffer.Get() <= '9'; }

    public:
        template <typename CharToTest>
        constexpr BufferManipResult IsSame(const CharToTest* str, std::size_t size) const noexcept
        {
            if (size > BufferAccess(Buffer).GetBufferRemainingSize()) return false;

            const TChar* bufferStr = Buffer.CurrentPos;
            bool isSame = true;
            while (isSame && size != 0 && *str != 0)
            {
                isSame = *bufferStr++ == *str++;
                --size;
            }
            if (size != 0 && *str != 0) isSame = false;
            return isSame;
        }
        template <typename CharToTest>
        constexpr inline BufferManipResult IsSame(std::basic_string_view<CharToTest> sv) const noexcept
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
        constexpr inline BufferManipResult IsEqualToForward(const CharToTest... ele) noexcept
        {
            if (Access().IsEqualTo(ele...))
                return BufferManip(Buffer).Forward();
            return false;
        }
        template <typename... CharToTest>
        constexpr inline BufferManipResult IsNotEqualForward(const CharToTest... ele) noexcept
        {
            if (Access().IsNotEqualTo(ele...))
                return BufferManip(Buffer).Forward();
            return false;
        }

    public:
        template <typename CharToTest>
        constexpr BufferManipResult IsSameForward(const CharToTest* str, std::size_t size) noexcept
        {
            if (Access().IsSame(str, size))
                return BufferManip(Buffer).Forward(size);
            return false;
        }
        template <typename CharToTest>
        constexpr inline BufferManipResult IsSameForward(std::basic_string_view<CharToTest> sv) noexcept
        {
            if (Access().IsSame(sv))
                return BufferManip(Buffer).Forward(sv.size());
            return false;
        }

    public:
        template <typename... CharToTest>
        inline void Skip(const CharToTest... ele) noexcept { IsEqualToForward(ele...); }
        template <typename... CharToTest>
        inline void SkipAll(const CharToTest... ele) noexcept
        {
            while (Access().IsEqualTo(ele...) && BufferAccess(Buffer).CanMoveForward())
                BufferManip(Buffer).ForceForward();
        }
        
    public:
        inline void SkipSpace() noexcept { Skip(' ', '\t'); }
        inline void SkipBlank() noexcept { Skip(' ', '\t', '\n', '\r', '\v'); }

        inline void SkipAllSpaces() noexcept { SkipAll(' ', '\t'); }
        inline void SkipAllBlanks() noexcept { SkipAll(' ', '\t', '\n', '\r', '\v'); }

    public:
        template <typename... CharToTest>
        inline void GoTo(const CharToTest... ele) noexcept
        {
            while (Access().IsNotEqualTo(ele...) && BufferAccess(Buffer).CanMoveForward())
                BufferManip(Buffer).ForceForward();
        }
        template <typename... CharToTest>
        inline void GoToForward(const CharToTest... ele) noexcept
        {
            GoTo(ele...);
            BufferManip(Buffer).Forward();
        }

    public:
        template <typename Func>
        std::basic_string_view<TConstChar> ViewExec(Func&& func)
        {
            TChar* begin = Buffer.CurrentPos;
            func();
            TChar* end = Buffer.CurrentPos;
            return std::basic_string_view<TConstChar>(begin, end - begin);
        }

        template <typename... CharToTest>
        inline std::basic_string_view<TConstChar> ViewUntil(CharToTest&&... c)
        {
            return ViewExec([&]{BufferTestManip(Buffer).GoTo(std::forward<CharToTest>(c)...);});
        }
    };
}
