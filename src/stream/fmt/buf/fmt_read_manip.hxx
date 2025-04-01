#pragma once

#include "stream/fmt/buf/stream.hxx"
#include "stream/fmt/buf/utils/buffer_shift_manip.hxx"
#include "stream/fmt/buf/manip.hxx"
#include "stream/fmt/buf/test_manip.hxx"
#include "stream/fmt/buf/read_manip.hxx"

namespace stream::fmt::buf {
    template <typename TChar>
    class FMTReadManip {
    public:
        FMTReadManip(Stream<TChar>& buffer) : buffer(buffer) {}

    public:
        Stream<TChar>& buffer;

    public:
        template <typename T>
        void read_integer(T& i, detail::ShiftInfo shift = detail::ShiftInfo{}) {
            ShiftReadManip shift_manip(buffer);
            buf::TestManip manip(buffer);

            shift_manip.ignore_shift_begin_space(shift);

            bool sign = false;
            if constexpr (std::is_signed_v<T>) {
                sign = manip.is_equal_to_forward('-');
                if (manip.is_equal_to_forward('-')) --shift.size;
            }

            TestAccess(buffer).is_a_digit();

            T res = (T)0;
            while (TestAccess(buffer).is_a_digit()) {
                res = res * 10 + (Manip(buffer).get_and_forward() - '0');
                --shift.size;
            }

            shift_manip.ignore_shift_end(shift);

            i = sign ? -res : res;
        }

    public:
        template <typename T>
        void read_float(T& t, std::int32_t float_precision = -1, detail::ShiftInfo shift = detail::ShiftInfo{}) {
            ShiftReadManip  shift_manip(buffer);
            buf::TestAccess access(buffer);
            buf::TestManip  manip(buffer);

            shift_manip.ignore_shift_begin_space(shift);

            bool sign = manip.is_equal_to_forward('-');
            if (sign) --shift.size;

            T intpart = static_cast<T>(0);
            if (access.is_a_digit()) {
                while (access.is_a_digit()) {
                    intpart = intpart * 10 + (buffer.get() - '0');
                    Manip(buffer).forward();
                    --shift.size;
                }
            } else if (access.is_equal_to('.')) {
                buf::Manip(buffer).forward();
            } else {
                throw std::runtime_error("fmt error: Parse_NonValidDigit");
            }

            if (float_precision <= 0)
                while (access.is_a_digit() && buffer.is_end_of_string() == false) {
                    Manip(buffer).forward_force();
                    --shift.size;
                }
            else {
                while (Access(buffer).is_a_digit() && float_precision > 0 && buffer.is_end_of_string() == false) {
                    Manip(buffer).forward_force();
                    float_precision--;
                    --shift.size;
                }
            }
            Manip(buffer).backward_force();

            T dec = (T)0;
            while (access.is_a_digit()) {
                dec += static_cast<T>(buffer.get() - '0');
                Manip(buffer).backward_force();
                dec /= 10;
            }

            shift_manip.ignore_shift_end(shift);

            t = sign ? -intpart - dec : intpart + dec;
        }

    public:
        template <typename T>
        void read_integer_h(T& i, std::uint8_t digitsize, std::optional<std::uint8_t> (&digit_lut)(TChar), TChar base_prefix = '\0',
                            detail::ShiftInfo shift = detail::ShiftInfo{}) {
            ShiftReadManip  shift_manip(buffer);
            buf::TestAccess access(buffer);
            buf::TestManip  manip(buffer);

            shift.size -= sizeof(T) * 8;
            if (base_prefix != '\0') shift.size -= 2;

            shift_manip.ignore_shift_begin_space(shift);

            if (base_prefix != '\0') {
                manip.skip_one_of('0');
                manip.skip_one_of(base_prefix);
            }

            T                           res         = (T)0;
            std::optional<std::uint8_t> get_current = digit_lut(buffer.get());
            while (get_current.has_value()) {
                res = res << digitsize;
                res += get_current.value();
                get_current = digit_lut(buffer.get());
                Manip(buffer).forward_force();
            }

            shift_manip.ignore_shift_end(shift);

            i = res;
        }

    protected:
        static constexpr std::optional<std::uint8_t> digit_lut_bin(TChar in) {
            if (in == '0') return 0;
            if (in == '1') return 1;
            return std::nullopt;
        }
        static constexpr std::optional<std::uint8_t> digit_lut_oct(TChar in) {
            if (in >= '0' && in <= '7') return in - '0';
            return std::nullopt;
        }
        static constexpr std::optional<std::uint8_t> digit_lut_dec(TChar in) {
            if (in >= '0' && in <= '9') return in - '0';
            return std::nullopt;
        }
        static constexpr std::optional<std::uint8_t> digit_lut_hexupper(TChar in) {
            if (in >= '0' && in <= '9') return in - '0';
            if (in >= 'A' && in <= 'F') return in - 'A';
            return std::nullopt;
        }
        static constexpr std::optional<std::uint8_t> digit_lut_hexlower(TChar in) {
            if (in >= '0' && in <= '9') return in - '0';
            if (in >= 'a' && in <= 'f') return in - 'a';
            return std::nullopt;
        }

    public:
        template <typename T, typename FormatDataCharType>
        void read_integer_format_data(T& i, const detail::FormatData<FormatDataCharType>& formatdata) {
            if (formatdata.has_spec) {
                switch (formatdata.integer_print) {
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
        void read_float_format_data(T& i, const detail::FormatData<FormatDataCharType>& formatdata) {
            if (formatdata.has_spec) {
                if (formatdata.ShiftType == detail::ShiftInfo::ShiftType::Nothing)
                    return ReadManip(buffer).fast_read_float(i, formatdata.float_precision);
                else
                    return read_float(i, formatdata.float_precision, formatdata.shift);
            }
            return ReadManip(buffer).fast_read_float(i, formatdata.float_precision);
        }

    public:
        template <typename CharStr>
        void read_char_ptr(const CharStr* str, std::size_t sizeContainer, std::size_t sizeToWrite, detail::ShiftInfo shift = detail::ShiftInfo{}) {
            // FIXME
            // TODO
            throw std::runtime_error("fmt error: FunctionNotImpl");
        }

        template <typename CharStr, std::size_t SIZE>
        void read_char_array(const CharStr (&str)[SIZE], detail::ShiftInfo shift = detail::ShiftInfo{}) {
            return read_char_ptr(str, SIZE, 0, shift);
        }
        template <typename CharStr>
        void read_char_bound(const CharStr* begin, const CharStr* end, detail::ShiftInfo shift = detail::ShiftInfo{}) {
            return read_char_ptr(begin, end - begin, 0, shift);
        }
    };
}  // namespace stream::fmt::buf
