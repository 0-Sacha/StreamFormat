#pragma once

#include "stream/fmt/buf/stream.h"
#include "stream/fmt/buf/utils/buffer_shift_manip.h"
#include "stream/fmt/buf/manip.h"
#include "stream/fmt/buf/test_manip.h"
#include "stream/fmt/buf/read_manip.h"

namespace stream::fmt::buf
{
    template <typename TChar>
    class FMTReadManip
    {
    public:
        FMTReadManip(Stream<TChar>& buffer) : buffer(buffer) {}
    public:
        Stream<TChar>& buffer;

    public:
        template <typename T>
        [[nodiscard]] std::expected<void, FMTResult> read_integer(T& i, detail::ShiftInfo shift = detail::ShiftInfo{})
        {
            ShiftReadManip shift_manip(buffer);
            buf::TestManip manip(buffer);

            SF_TRY(shift_manip.ignore_shift_begin_space(shift));

            bool sign = false;
            if constexpr (std::is_signed_v<T>)
            {
                sign = SF_TRY(manip.is_equal_to_forward('-'));
                if (sign) --shift.size;
            }

            TestAccess(buffer).is_a_digit();

            T res = (T)0;
            while (TestAccess(buffer).is_a_digit())
            {
                char c = SF_TRY(Manip(buffer).get_and_forward());
                res = res * 10 + (c - '0');
                --shift.size;
            }

            SF_TRY(shift_manip.ignore_shift_end(shift));

            i = sign ? -res : res;
            return {};
        }
    public:
        template <typename T>
        [[nodiscard]] std::expected<void, FMTResult> read_float(T& t, std::int32_t float_precision = -1, detail::ShiftInfo shift = detail::ShiftInfo{})
        {
            ShiftReadManip shift_manip(buffer);
            buf::TestAccess access(buffer);
            buf::TestManip manip(buffer);
            
            SF_TRY(shift_manip.ignore_shift_begin_space(shift));

            bool sign = SF_TRY(manip.is_equal_to_forward('-'));
            if (sign) --shift.size;

            T intpart = static_cast<T>(0);
            if (access.is_a_digit())
            {
                while (access.is_a_digit())
                {
                    char c = SF_TRY(Manip(buffer).get_and_forward());
                    intpart = intpart * 10 + (c - '0');
                    --shift.size;
                }
            }
            else if (access.is_equal_to('.'))
                { SF_TRY(buf::Manip(buffer).forward()); }
            else
                { return std::unexpected(FMTResult::Parse_NonValidDigit); }

            if (float_precision <= 0)
                while (access.is_a_digit() && access.is_end_of_string() == false)
                {
                    Manip(buffer).forward_force();
                    --shift.size;
                }
            else
            {
                while (Access(buffer).is_a_digit() && float_precision > 0 && Access(buffer).is_end_of_string() == false)
                {
                    Manip(buffer).forward_force();
                    float_precision--;
                    --shift.size;
                }
            }
            Manip(buffer).backward_force();

            T dec = (T)0;
            while (access.is_a_digit())
            {
                dec += static_cast<T>(buffer.get() - '0');
                Manip(buffer).backward_force();
                dec /= 10;
            }

            SF_TRY(shift_manip.ignore_shift_end(shift));

            t = sign ? - intpart - dec : intpart + dec;
            return {};
        }

    public:
        template <typename T>
        [[nodiscard]] std::expected<void, FMTResult> read_integer_h(T& i, std::uint8_t digitSize, std::uint8_t (&digit_lut)(TChar), TChar base_prefix = '\0', detail::ShiftInfo shift = detail::ShiftInfo{})
        {
            ShiftReadManip shift_manip(buffer);
            buf::TestAccess access(buffer);
            buf::TestManip manip(buffer);

            shift.size -= sizeof(T) * 8;
            if (base_prefix != '\0') shift.size -= 2;

            SF_TRY(shift_manip.ignore_shift_begin_space(shift));

            if (base_prefix != '\0')
            {
                SF_TRY(manip.skip_one_of('0'));
                SF_TRY(manip.skip_one_of(base_prefix));
            }

            T res = (T)0;
            while (digit_lut(buffer.get()) != std::numeric_limits<std::uint8_t>::max())
            {
                res = res << digitSize;
                res += digit_lut(buffer.get());
                Manip(buffer).forward_force();
            }

            SF_TRY(shift_manip.ignore_shift_end(shift));

            i = res;
            return {};
        }

    protected:
        static constexpr std::uint8_t digit_lut_bin(TChar in)
        {
            if (in == '0') return 0;
            if (in == '1') return 1;
            return std::numeric_limits<std::uint8_t>::max();
        }
        static constexpr std::uint8_t digit_lut_oct(TChar in)
        {
            if (in >= '0' && in <= '7')
                return in - '0';
            return std::numeric_limits<std::uint8_t>::max();
        }
        static constexpr std::uint8_t digit_lut_dec(TChar in)
        {
            if (in >= '0' && in <= '9')
                return in - '0';
            return std::numeric_limits<std::uint8_t>::max();
        }
        static constexpr std::uint8_t digit_lut_hexupper(TChar in)
        {
            if (in >= '0' && in <= '9')
                return in - '0';
            if (in >= 'A' && in <= 'F')
                return in - 'A';
            return std::numeric_limits<std::uint8_t>::max();
        }
        static constexpr std::uint8_t digit_lut_hexlower(TChar in)
        {
            if (in >= '0' && in <= '9')
                return in - '0';
            if (in >= 'a' && in <= 'f')
                return in - 'a';
            return std::numeric_limits<std::uint8_t>::max();
        }

    public:
        template <typename T, typename FormatDataCharType>
        [[nodiscard]] std::expected<void, FMTResult> read_integer_format_data(T& i, const detail::FormatData<FormatDataCharType>& formatdata)
        {
            if (formatdata.has_spec)
            {
                switch (formatdata.integer_print)
                {
                    case detail::IntegerPrintBase::Dec:
                        if (formatdata.shift.type == detail::ShiftInfo::ShiftType::Nothing)
                            return ReadManip(buffer).fast_read_integer(i);
                        else
                            return read_integer(i, formatdata.shift);
                    case detail::IntegerPrintBase::Bin:
                    case detail::IntegerPrintBase::BinUpper:
                        return read_integer_h(i, 1, digit_lut_bin, formatdata.prefix_suffix ? (char)formatdata.integer_print : '\0', formatdata.shift);
                    case detail::IntegerPrintBase::Oct:
                    case detail::IntegerPrintBase::OctUpper:
                        return read_integer_h(i, 3, digit_lut_oct, formatdata.prefix_suffix ? (char)formatdata.integer_print : '\0', formatdata.shift);
                    case detail::IntegerPrintBase::Hex:
                        return read_integer_h(i, 4, digit_lut_hexlower, formatdata.prefix_suffix ? (char)formatdata.integer_print : '\0', formatdata.shift);
                    case detail::IntegerPrintBase::HexUpper:
                        return read_integer_h(i, 4, digit_lut_hexupper, formatdata.prefix_suffix ? (char)formatdata.integer_print : '\0', formatdata.shift);
                }
            }
            return ReadManip(buffer).fast_read_integer(i);
        }
        template <typename T, typename FormatDataCharType>
        [[nodiscard]] std::expected<void, FMTResult> read_float_format_data(T& i, const detail::FormatData<FormatDataCharType>& formatdata)
        {
            if (formatdata.has_spec)
            {
                if (formatdata.ShiftType == detail::ShiftInfo::ShiftType::Nothing)
                    return ReadManip(buffer).fast_read_float(i, formatdata.float_precision);
                else
                    return read_float(i, formatdata.float_precision, formatdata.shift);
            }
            return ReadManip(buffer).fast_read_float(i, formatdata.float_precision);
        }

    public:
        template <typename CharStr>
        [[nodiscard]] std::expected<void, FMTResult> read_char_ptr(const CharStr* str, std::size_t sizeContainer, std::size_t sizeToWrite, detail::ShiftInfo shift = detail::ShiftInfo{})
        {
            // FIXME
            // TODO
            return std::unexpected(FMTResult::FunctionNotImpl);
        }

        template <typename CharStr, std::size_t SIZE>
        [[nodiscard]] inline std::expected<void, FMTResult> read_char_array(const CharStr (&str)[SIZE], detail::ShiftInfo shift = detail::ShiftInfo{})
        {
            return read_char_ptr(str, SIZE, 0, shift);
        }
        template <typename CharStr>
        [[nodiscard]] inline std::expected<void, FMTResult> read_char_bound(const CharStr* begin, const CharStr* end, detail::ShiftInfo shift = detail::ShiftInfo{})
        {
            return read_char_ptr(begin, end - begin, 0, shift);
        }
    };
}
