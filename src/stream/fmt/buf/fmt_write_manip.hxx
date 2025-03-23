#pragma once

#include "stream.hxx"
#include "fmt_manip_io.hxx"
#include "utils/buffer_shift_manip.hxx"
#include "manip_io.hxx"
#include "write_manip.hxx"

#include <type_traits>

namespace stream::fmt::buf {
    template <typename TChar>
    class FMTWriteManip {
    public:
        FMTWriteManip(FMTStreamIO<TChar>& buffer) : buffer(buffer) {}

    public:
        FMTStreamIO<TChar>& buffer;

    public:
        template <typename T>
        [[nodiscard]] std::expected<void, FMTResult> write_integer(T i, detail::ShiftInfo shift = detail::ShiftInfo{}) {
            char old_after = shift.print.after;
            if (shift.print.after >= '0' && shift.print.after <= '9') shift.print.after = ' ';

            std::int32_t nb_digit = WriteUtils::get_number_of_digit_dec(i);

            shift.size -= nb_digit;
            if (i < 0) --shift.size;

            if (shift.size <= 0) {
                return WriteManip(buffer).fast_write_integer(i);
            }

            if (!shift.print.before_is_a_digit()) {
                SF_VERIFY(ShiftWriteManip(buffer).write_shift_begin(shift));
            }
            if (i < 0) {
                SF_VERIFY(ManipIO(buffer).pushback('-'));
                i = -i;
            }
            if (shift.print.before_is_a_digit()) {
                SF_VERIFY(ShiftWriteManip(buffer).write_shift_right_all(shift));
            }

            if (i == 0) {
                SF_VERIFY(ManipIO(buffer).pushback('0'));
            } else {
                SF_VERIFY(ManipIO(buffer).forward(nb_digit));
                std::int32_t nb_digit_ = nb_digit;
                while (nb_digit_ > 0) {
                    Manip(buffer).backward_force();
                    buffer.set(i % 10 + '0');
                    i /= 10;
                    nb_digit_--;
                }
                SF_VERIFY(ManipIO(buffer).forward(nb_digit));
            }

            SF_VERIFY(ShiftWriteManip(buffer).write_shift_end(shift));

            shift.print.after = old_after;
            return {};
        }

    public:
        template <typename T>
        [[nodiscard]] std::expected<void, FMTResult> write_float(T i, std::int32_t float_precision = 2, detail::ShiftInfo shift = detail::ShiftInfo{}) {
            char old_before = shift.print.before;
            if (shift.print.before >= '0' && shift.print.before <= '9') shift.print.before = ' ';

            std::int32_t nb_digit = WriteUtils::get_number_of_digit_dec(std::trunc(i));

            shift.size -= nb_digit + float_precision + 1;
            if (i < 0) --shift.size;

            if (shift.size <= 0) {
                return WriteManip(buffer).fast_write_float(i, float_precision);
            }

            if (!shift.print.before_is_a_digit()) {
                SF_VERIFY(ShiftWriteManip(buffer).write_shift_begin(shift));
            }
            if (i < 0) {
                SF_VERIFY(ManipIO(buffer).pushback('-'));
                i = -i;
            }
            if (shift.print.before_is_a_digit()) {
                SF_VERIFY(ShiftWriteManip(buffer).write_shift_right_all(shift));
            }

            T k = std::trunc(i);
            if (k == 0) {
                SF_VERIFY(ManipIO(buffer).pushback('0'));
            } else {
                SF_VERIFY(ManipIO(buffer).forward(nb_digit));
                std::int32_t nb_digit_ = nb_digit;
                while (nb_digit_ > 0) {
                    Manip(buffer).backward_force();
                    buffer.set(char(std::fmod(i, 10)) + '0');
                    k /= 10;
                    nb_digit_--;
                }
                SF_VERIFY(ManipIO(buffer).forward(nb_digit));
            }

            SF_VERIFY(ManipIO(buffer).pushback('.'));
            i -= k;
            while (float_precision-- != 0) {
                T decimal = std::trunc(i *= 10);
                SF_VERIFY(ManipIO(buffer).pushback((char)decimal + '0'));
                i -= decimal;
            }

            SF_VERIFY(ShiftWriteManip(buffer).write_shift_end(shift));

            shift.print.before = old_before;
            return {};
        }

    public:
        template <typename T>
        [[nodiscard]] std::expected<void, FMTResult> write_integer_h(T i, std::uint8_t digitSize, const TChar* const lut, TChar base_prefix = '\0',
                                                                     detail::ShiftInfo shift = detail::ShiftInfo{}) {
            ManipIO manip(buffer);

            std::int32_t digit_count = sizeof(T) * 8;
            {
                // Remove leading 0
                std::int32_t last_pos_with_data = 0;
                std::int32_t k                  = digit_count + 1;
                T            cpyI               = i;
                while (--k != 0) {
                    if ((cpyI & (0b1 << digitSize)) != 0) last_pos_with_data = k;
                    cpyI = cpyI >> digitSize;
                }
                digit_count -= last_pos_with_data;
            }

            if (base_prefix != '\0') {
                SF_VERIFY(ManipIO(buffer).pushback('0'));
                SF_VERIFY(ManipIO(buffer).pushback(base_prefix));
            }

            SF_VERIFY(manip.forward(digit_count));
            std::int32_t k = digit_count + 1;
            while (--k != 0) {
                Manip(buffer).backward_force();
                buffer.set(lut[i & (0b1 << digitSize)]);
                i = i >> digitSize;
            }
            SF_VERIFY(manip.forward(digit_count));
            return {};
        }

    public:
        template <typename T>
        [[nodiscard]] std::expected<void, FMTResult> write_integer_format_data(T i, const detail::FormatData<TChar>& formatdata) {
            if (formatdata.has_spec) {
                switch (formatdata.integer_print) {
                    case detail::IntegerPrintBase::Dec:
                        if (formatdata.shift.type == detail::ShiftInfo::ShiftType::Nothing)
                            return WriteManip(buffer).fast_write_integer(i);
                        else
                            return write_integer(i, formatdata.shift);
                    case detail::IntegerPrintBase::Bin:
                    case detail::IntegerPrintBase::BinUpper:
                        return write_integer_h(i, 1, WriteManip<TChar>::BIN, formatdata.prefix_suffix ? (char)formatdata.integer_print : '\0', formatdata.shift);
                    case detail::IntegerPrintBase::Oct:
                    case detail::IntegerPrintBase::OctUpper:
                        return write_integer_h(i, 3, WriteManip<TChar>::OCT, formatdata.prefix_suffix ? (char)formatdata.integer_print : '\0', formatdata.shift);
                    case detail::IntegerPrintBase::Hex:
                        return write_integer_h(i, 4, WriteManip<TChar>::LOWER_HEX, formatdata.prefix_suffix ? (char)formatdata.integer_print : '\0', formatdata.shift);
                    case detail::IntegerPrintBase::HexUpper:
                        return write_integer_h(i, 4, WriteManip<TChar>::UPPER_HEX, formatdata.prefix_suffix ? (char)formatdata.integer_print : '\0', formatdata.shift);
                }
            }
            return WriteManip(buffer).fast_write_integer(i);
        }
        template <typename T>
        [[nodiscard]] std::expected<void, FMTResult> write_float_formatdata(T i, const detail::FormatData<TChar>& formatdata) {
            if (formatdata.has_spec) {
                if (formatdata.shift.type != detail::ShiftInfo::ShiftType::Nothing) return write_float(i, formatdata.float_precision, formatdata.shift);
            }

            return WriteManip(buffer).fast_write_float(i, formatdata.float_precision);
        }

    public:
        template <typename CharStr>
        [[nodiscard]] inline std::expected<void, FMTResult> write_indent_char_ptr(const CharStr* str, std::size_t size) {
            while (size > 0) {
                const CharStr* const begin = str;
                while (size > 0 && *str != '\n') {
                    ++str, --size;
                }
                const CharStr* const end = str;

                SF_VERIFY(WriteManip(buffer).fast_write_char_array(begin, end - begin));

                if (size > 0 && *str == '\n') {
                    SF_VERIFY(FMTManipIO(buffer).new_line_indent());
                    ++str;
                    --size;
                }
            }
            return {};
        }
        template <typename CharStr>
        [[nodiscard]] inline std::expected<void, FMTResult> write_indent_char_bound(const CharStr* begin, const CharStr* end) {
            return write_indent_char_ptr(begin, end - begin);
        }
        template <typename CharStr>
        [[nodiscard]] inline std::expected<void, FMTResult> write_indent_string(std::basic_string_view<CharStr> str) {
            return write_indent_char_ptr(str.data(), str.size());
        }

        template <typename CharStr>
        [[nodiscard]] inline std::expected<void, FMTResult> write_char_ptr(const CharStr* str, std::size_t size, detail::ShiftInfo& shift) {
            if (shift.size <= 0) return WriteManip(buffer).fast_write_char_array(str, size);

            SF_VERIFY(ManipIO(buffer).reserve(std::max(static_cast<std::size_t>(shift.size), size)));

            if (static_cast<std::size_t>(shift.size) > size) {
                shift.size -= static_cast<std::int32_t>(size);

                SF_VERIFY(ShiftWriteManip(buffer).write_shift_begin(shift));

                SF_VERIFY(WriteManip(buffer).fast_write_char_array(str, size));

                SF_VERIFY(ShiftWriteManip(buffer).write_shift_end(shift));
            } else {
                SF_VERIFY(WriteManip(buffer).fast_write_char_array(str, size));
            }
            return {};
        }
        template <typename CharStr>
        [[nodiscard]] inline std::expected<void, FMTResult> write_char_bound(const CharStr* begin, const CharStr* end, detail::ShiftInfo& shift) {
            return write_char_ptr(begin, end - begin, shift);
        }
        template <typename CharStr>
        [[nodiscard]] inline std::expected<void, FMTResult> write_string(std::basic_string_view<CharStr> str, detail::ShiftInfo& shift) {
            return write_char_ptr(str.data(), str.size(), shift);
        }
    };
}  // namespace stream::fmt::buf
