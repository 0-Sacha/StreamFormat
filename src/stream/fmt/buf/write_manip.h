#pragma once

#include "stream.h"
#include "manip.h"
#include "test_manip.h"
#include "manip_io.h"

#include <type_traits>
#include <cmath>

namespace stream::fmt::buf
{
    class WriteUtils
    {
    public:
        template <typename T>
        static std::int32_t get_number_of_digit_dec(T value)
        {
            if constexpr (std::numeric_limits<T>::is_signed)
            {
                if (value < 0) value = -value;
            }
            std::int32_t nb = 0;
            while (true)
            {
                if (value < 10)
                    return nb + 1;
                else if (value < 100)
                    return nb + 2;
                else if (value < 1000)
                    return nb + 3;
                else if (value < 10000)
                    return nb + 4;
                else
                {
                    value /= static_cast<T>(10000);
                    nb += 4;
                }
            }
        }
    };

    template <typename TChar>
    class WriteManip
    {
    public:
        constexpr inline WriteManip(StreamIO<TChar>& buffer) noexcept : buffer(buffer) {}
    public:
        StreamIO<TChar>& buffer;
    
    public:
        static constexpr TChar BIN[2] = {'0', '1'};
        static constexpr TChar OCT[8] = {'0', '1', '2', '3', '4', '5', '6', '7'};
        static constexpr TChar UPPER_HEX[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'b', 'C', 'D', 'E', 'F'};
        static constexpr TChar LOWER_HEX[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    public:
        template <typename T>
        requires std::is_integral_v<T>
        [[nodiscard]] constexpr std::expected<void, FMTResult> fast_write_integer(T i)
        {
            ManipIO manip(buffer);

            if (i == 0) { SF_TRY(manip.pushback('0')); return {}; }

            if constexpr (std::is_signed_v<T>)
            {
                if (i < 0) { SF_TRY(manip.pushback('-')); i = -i; }
            }

            std::int32_t nb_digit = WriteUtils::get_number_of_digit_dec(i);
            SF_TRY(manip.forward(nb_digit));
            while (i > 0)
            {
                ManipIO(buffer).set(i % 10 + '0');
                Manip(buffer).backward_force();
                i /= 10;
            }
            SF_TRY(manip.forward(nb_digit));

            return {};
        }

    public:
        template <typename T>
        requires std::is_floating_point_v<T>
        [[nodiscard]] constexpr std::expected<void, FMTResult> fast_write_float(T i, std::int32_t float_precision = 2)
        {
            ManipIO manip(buffer);

            if (i == 0)
                { SF_TRY(manip.pushback('0')); return {}; }
            if (i < 0)
                { SF_TRY(manip.pushback('-')); i = -i; }

            T k = std::trunc(i);
            i = i - k;
            std::int32_t nb_digit = WriteUtils::get_number_of_digit_dec(k);
            SF_TRY(manip.forward(nb_digit));
            std::int32_t nb_digit_ = nb_digit;
            while (nb_digit_ > 0)
            {
                buffer.set(char(std::fmod(k, 10)) + '0');
                Manip(buffer).backward_force();
                k /= 10;
                nb_digit_--;
            }
            SF_TRY(manip.forward(nb_digit));
            SF_TRY(manip.pushback('.'));

            while (float_precision-- >= 0)
            {
                TChar intPart = static_cast<TChar>(std::trunc(i *= 10));
                SF_TRY(manip.pushback(intPart + '0'));
                i -= intPart;
            }

            return {};
        }

    public:
        template <typename CharInput>
        [[nodiscard]] constexpr std::expected<void, FMTResult> fast_write_char_array(const CharInput* str, std::size_t size)
        {
            auto reserve = ManipIO(buffer).reserve(size);
            if (reserve.has_value() == false) 
                return fast_write_char_array(str, Access(buffer).get_buffer_remaining_size());

            // TODO: Opti with bigger types
            while (size-- != 0 && *str != 0)
                ManipIO(buffer).pushback_force(*str++);

            return {};
        }
        template <typename CharInput>
        [[nodiscard]] inline constexpr std::expected<void, FMTResult> fast_write_string(std::basic_string_view<CharInput> sv)
        {
            return fast_write_char_array(sv.data(), sv.size());
        }
        [[nodiscard]] inline std::expected<void, FMTResult> fast_write_string(std::basic_string_view<TChar> sv)
        {
            return fast_write_char_array(sv.data(), sv.size());
        }
        template <typename CharInput, std::size_t SIZE>
        [[nodiscard]] inline std::expected<void, FMTResult> fast_write_string_literal(CharInput (&str)[SIZE])
        {
            std::size_t size = SIZE;
            while (str[size - 1] == 0)
                { --size; }
            return fast_write_char_array(str, size);
        }

    public:
        template <typename CharInput>
        [[nodiscard]] inline std::expected<void, FMTResult> basic_write_type(std::basic_string_view<CharInput> str) { return fast_write_string(str); }
        template <typename CharInput, std::size_t SIZE>
        [[nodiscard]] inline std::expected<void, FMTResult> basic_write_type(CharInput (&str)[SIZE]) { return fast_write_string_literal(str); }
        template <typename T> requires std::is_integral_v<T>
        [[nodiscard]] inline std::expected<void, FMTResult> basic_write_type(T t) { return fast_write_integer(t); }
        template <typename T> requires std::is_floating_point_v<T>
        [[nodiscard]] inline std::expected<void, FMTResult> basic_write_type(T t) { return fast_write_float(t); }

        template <typename Type, typename... Rest>
        [[nodiscard]] inline std::expected<void, FMTResult> basic_write_type(Type&& type, Rest&&... rest)
        {
            SF_TRY(basic_write_type(type));
            if constexpr (sizeof...(rest) > 0)
                SF_TRY(basic_write_type(std::forward<Rest>(rest)...));
            return {};
        }
    };
}
