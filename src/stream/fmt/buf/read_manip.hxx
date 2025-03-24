#pragma once

#include "stream/fmt/buf/stream.hxx"
#include "stream/fmt/buf/manip.hxx"

#include <algorithm>

namespace stream::fmt::buf {
    template <typename TChar>
    class ReadManip {
    public:
        constexpr inline ReadManip(Stream<TChar>& buffer_) noexcept : buffer(buffer_) {}

    public:
        Stream<TChar>& buffer;

    public:
        template <typename T>
        constexpr void fast_read_integer(T& t) noexcept {
            bool sign = false;
            if constexpr (std::is_signed_v<T>) {
                sign = TestManip(buffer).is_equal_to_forward('-');
            }

            if (!TestAccess(buffer).is_a_digit()) {
                throw std::runtime_error("fmt error: Parse_NonValidDigit");
            }

            T value = static_cast<T>(0);
            while (TestAccess(buffer).is_a_digit()) {
                value = value * static_cast<T>(10) + static_cast<T>(buffer.get() - static_cast<TChar>('0'));
                Manip(buffer).forward();
            }

            t = sign ? -value : value;
        }

    public:
        template <typename T>
        constexpr inline void fast_read_float(T& t, std::int32_t float_precision = -1) noexcept {
            T intpart = static_cast<T>(0);

            TestAccess access(buffer);
            TestManip  manip(buffer);

            bool sign = manip.is_equal_to_forward('-');

            if (access.is_a_digit()) {
                fast_read_integer<T>(intpart);
            } else if (access.is_equal_to('.')) {
                buf::Manip(buffer).forward();
            } else {
                throw std::runtime_error("fmt error: Parse_NonValidDigit");
            }

            if (float_precision < 0) {
                while (access.is_a_digit() && buffer.is_end_of_string() == false) {
                    Manip(buffer).forward_force();
                }
            } else {
                while (access.is_a_digit() && float_precision > 0 && buffer.is_end_of_string() == false) {
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
        }

    public:
        template <typename CharPtr>
        void fast_read_char_ptr(const CharPtr* str, std::size_t size_to_copy, bool is_zero_ended = true) {
            if (Access(buffer).can_move_forward(size_to_copy) == false) {
                return ReadManip(buffer).fast_read_char_ptr(str, buffer.get_buffer_remaining_size(), is_zero_ended);
            }

            std::copy_n(str, size_to_copy, buffer.current_pos);
            buffer.current_pos += size_to_copy;

            if (is_zero_ended) {
                *str = 0;
            }
        }
        template <typename CharStr, std::size_t SIZE>
        void fast_read_char_array(const CharStr (&str)[SIZE], bool is_zero_ended = true) {
            return fast_read_char_ptr(str, SIZE);
        }
        template <typename CharStr>
        void fast_read_char_bound(const CharStr* begin, const CharStr* end, bool is_zero_ended = true) {
            return fast_read_char_ptr(begin, end - begin - (is_zero_ended ? 1 : 0), is_zero_ended);
        }
    };
}  // namespace stream::fmt::buf
