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
        void write_integer(T i, detail::ShiftInfo shift = detail::ShiftInfo{}) {
            char old_after = shift.print.after;
            if (shift.print.after >= '0' && shift.print.after <= '9') shift.print.after = ' ';

            std::int32_t nb_digit = WriteUtils::get_number_of_digit_dec(i);

            shift.size -= nb_digit;
            if (i < 0) --shift.size;

            if (shift.size <= 0) {
                return WriteManip(buffer).fast_write_integer(i);
            }

            if (!shift.print.before_is_a_digit()) {
                ShiftWriteManip(buffer).write_shift_begin(shift);
            }
            if (i < 0) {
                ManipIO(buffer).pushback('-');
                i = -i;
            }
            if (shift.print.before_is_a_digit()) {
                ShiftWriteManip(buffer).write_shift_right_all(shift);
            }

            if (i == 0) {
                ManipIO(buffer).pushback('0');
            } else {
                ManipIO(buffer).forward(nb_digit);
                std::int32_t nb_digit_ = nb_digit;
                while (nb_digit_ > 0) {
                    Manip(buffer).backward_force();
                    buffer.set(i % 10 + '0');
                    i /= 10;
                    nb_digit_--;
                }
                ManipIO(buffer).forward(nb_digit);
            }

            ShiftWriteManip(buffer).write_shift_end(shift);

            shift.print.after = old_after;
        }

    public:
        template <typename T>
        void write_float(T i, std::int32_t float_precision = 2, detail::ShiftInfo shift = detail::ShiftInfo{}) {
            char old_before = shift.print.before;
            if (shift.print.before >= '0' && shift.print.before <= '9') shift.print.before = ' ';

            std::int32_t nb_digit = WriteUtils::get_number_of_digit_dec(std::trunc(i));

            shift.size -= nb_digit + float_precision + 1;
            if (i < 0) --shift.size;

            if (shift.size <= 0) {
                return WriteManip(buffer).fast_write_float(i, float_precision);
            }

            if (!shift.print.before_is_a_digit()) {
                ShiftWriteManip(buffer).write_shift_begin(shift);
            }
            if (i < 0) {
                ManipIO(buffer).pushback('-');
                i = -i;
            }
            if (shift.print.before_is_a_digit()) {
                ShiftWriteManip(buffer).write_shift_right_all(shift);
            }

            T k = std::trunc(i);
            if (k == 0) {
                ManipIO(buffer).pushback('0');
            } else {
                ManipIO(buffer).forward(nb_digit);
                std::int32_t nb_digit_ = nb_digit;
                while (nb_digit_ > 0) {
                    Manip(buffer).backward_force();
                    buffer.set(char(std::fmod(i, 10)) + '0');
                    k /= 10;
                    nb_digit_--;
                }
                ManipIO(buffer).forward(nb_digit);
            }

            ManipIO(buffer).pushback('.');
            i -= k;
            while (float_precision-- != 0) {
                T decimal = std::trunc(i *= 10);
                ManipIO(buffer).pushback((char)decimal + '0');
                i -= decimal;
            }

            ShiftWriteManip(buffer).write_shift_end(shift);

            shift.print.before = old_before;
        }

    public:
        template <typename T>
        void write_integer_h(T i, std::uint8_t digitsize, const TChar* const lut, TChar base_prefix = '\0', detail::ShiftInfo shift = detail::ShiftInfo{}) {
            ManipIO manip(buffer);

            std::int32_t digit_count = sizeof(T) * (8 / digitsize);
            std::uint8_t mask        = (1 << digitsize) - 1;

            if (i != 0) {
                // Remove leading 0
                std::int32_t last_pos_with_data = digit_count;
                std::int32_t k                  = digit_count;
                T            cpy_i              = i;
                while (--k != 0) {
                    if ((cpy_i & mask) != 0) {
                        last_pos_with_data = k;
                    }
                    cpy_i = cpy_i >> digitsize;
                }
                digit_count -= last_pos_with_data;
            }

            if (base_prefix != '\0') {
                ManipIO(buffer).pushback('0');
                ManipIO(buffer).pushback(base_prefix);
            }

            if (i == 0) {
                ManipIO(buffer).pushback('0');
                return;
            }

            manip.forward(digit_count);
            std::int32_t k = digit_count + 1;
            while (--k != 0) {
                Manip(buffer).backward_force();
                buffer.set(lut[i & mask]);
                i = i >> digitsize;
            }
            manip.forward(digit_count);
        }

    public:
        template <typename T>
        void write_integer_format_data(T i, const detail::FormatData<TChar>& formatdata) {
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
        void write_float_formatdata(T i, const detail::FormatData<TChar>& formatdata) {
            if (formatdata.has_spec) {
                if (formatdata.shift.type != detail::ShiftInfo::ShiftType::Nothing) return write_float(i, formatdata.float_precision, formatdata.shift);
            }

            return WriteManip(buffer).fast_write_float(i, formatdata.float_precision);
        }

    public:
        template <typename CharStr>
        void write_indent_char_ptr(const CharStr* str, std::size_t size) {
            while (size > 0) {
                const CharStr* const begin = str;
                while (size > 0 && *str != '\n') {
                    ++str, --size;
                }
                const CharStr* const end = str;

                WriteManip(buffer).fast_write_sv(std::basic_string_view(begin, end));

                if (size > 0 && *str == '\n') {
                    FMTManipIO(buffer).new_line_indent();
                    ++str;
                    --size;
                }
            }
        }
        void write_indent_sv(std::basic_string_view<TChar> sv) {
            return write_indent_char_ptr(sv.data(), sv.size());
        }

        void write_sv(std::basic_string_view<TChar> sv, detail::ShiftInfo& shift) {
            if (shift.size <= 0) {
                return WriteManip(buffer).fast_write_sv(sv);
            }

            if (ManipIO(buffer).reserve(std::max(static_cast<std::size_t>(shift.size), sv.size())) == false) {
                throw std::bad_alloc();
            }

            if (static_cast<std::size_t>(shift.size) > sv.size()) {
                shift.size -= static_cast<std::int32_t>(sv.size());

                ShiftWriteManip(buffer).write_shift_begin(shift);

                WriteManip(buffer).fast_write_sv(sv);

                ShiftWriteManip(buffer).write_shift_end(shift);
            } else {
                WriteManip(buffer).fast_write_sv(sv);
            }
        }
    };
}  // namespace stream::fmt::buf
