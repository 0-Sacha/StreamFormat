#pragma once

#include "stream/fmt/buf/stream.hxx"
#include "stream/fmt/buf/manip.hxx"

namespace stream::fmt::buf {
    template <typename TChar>
    class ReadManip {
    public:
        constexpr inline ReadManip(Stream<TChar>& buffer_) noexcept : buffer(buffer_) {}

    public:
        Stream<TChar>& buffer;

    public:
        template <typename T>
        [[nodiscard]] constexpr std::expected<void, FMTResult> fast_read_integer(T& t) noexcept {
            bool sign = false;
            if constexpr (std::is_signed_v<T>) {
                sign = SF_TRY(TestManip(buffer).is_equal_to_forward('-'));
            }

            if (!TestAccess(buffer).is_a_digit()) {
                return std::unexpected(FMTResult::Parse_NonValidDigit);
            }

            T value = static_cast<T>(0);
            while (TestAccess(buffer).is_a_digit()) {
                char c = SF_TRY(Manip(buffer).get_and_forward());
                value  = value * static_cast<T>(10) + static_cast<T>(c - static_cast<TChar>('0'));
            }

            t = sign ? -value : value;
            return {};
        }

    public:
        template <typename T>
        [[nodiscard]] constexpr inline std::expected<void, FMTResult> fast_read_float(T& t, std::int32_t float_precision = -1) noexcept {
            T intpart = static_cast<T>(0);

            TestAccess access(buffer);
            TestManip  manip(buffer);

            bool sign = SF_TRY(manip.is_equal_to_forward('-'));

            if (access.is_a_digit()) {
                SF_TRY(fast_read_integer<T>(intpart));
            } else if (access.is_equal_to('.')) {
                SF_TRY(buf::Manip(buffer).forward());
            } else {
                return std::unexpected(FMTResult::Parse_NonValidDigit);
            }

            if (float_precision < 0) {
                while (access.is_a_digit() && Access(buffer).is_end_of_string() == false) {
                    Manip(buffer).forward_force();
                }
            } else {
                while (access.is_a_digit() && float_precision > 0 && Access(buffer).is_end_of_string() == false) {
                    Manip(buffer).forward_force();
                    float_precision--;
                }
            }
            Manip(buffer).backward_force();

            T dec = static_cast<T>(0);
            while (access.is_a_digit()) {
                dec += static_cast<T>(buffer.get() - '0');
                Manip(buffer).backward_force();
                dec /= 10;
            }

            t = sign ? -intpart - dec : intpart + dec;
            return {};
        }

    public:
        template <typename CharPtr>
        [[nodiscard]] std::expected<void, FMTResult> FastReadCharPtr(const CharPtr* str, std::size_t sizeToCopy, bool isZeroEnded = true) {
            if (Access(buffer).can_move_forward(sizeToCopy) == false) {
                return ReadManip(buffer).FastReadCharPtr(str, Access(buffer).get_buffer_remaining_size(), isZeroEnded);
            }

            // TODO : Opti with bigger types
            while (sizeToCopy-- != 0) {
                *str++ = SF_TRY(Manip(buffer).get_and_forward());
            }
            if (isZeroEnded) {
                *str = 0;
            }

            return {};
        }
        template <typename CharStr, std::size_t SIZE>
        [[nodiscard]] inline std::expected<void, FMTResult> FastReadCharArray(const CharStr (&str)[SIZE], bool isZeroEnded = true) {
            return FastReadCharPtr(str, SIZE);
        }
        template <typename CharStr>
        [[nodiscard]] inline std::expected<void, FMTResult> FastReadCharBound(const CharStr* begin, const CharStr* end, bool isZeroEnded = true) {
            return FastReadCharPtr(begin, end - begin - (isZeroEnded ? 1 : 0), isZeroEnded);
        }
    };
}  // namespace stream::fmt::buf
