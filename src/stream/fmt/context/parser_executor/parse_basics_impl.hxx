#pragma once

#include "basic_parser_executor.hxx"
#include "stream/fmt/buf/fmt_read_manip.hxx"

namespace stream::fmt {
    //----------------------------------------------//
    //----------------- Forwarders -----------------//
    //----------------------------------------------//

    //-----------------------------------------------//
    //----------------- C/CXX Types -----------------//
    //-----------------------------------------------//

    template <typename ParserExecutor>
    struct ParserType<bool, ParserExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> parse(bool& t, ParserExecutor& executor) {
            if (!executor.data.prefix_suffix) {
                if (buf::TestAccess(executor.istream).is_equal_to('t', 'T')) {
                    SF_TRY(buf::Manip(executor.istream).forward());
                    if (buf::TestAccess(executor.istream).is_same("rue")) {
                        SF_TRY(buf::Manip(executor.istream).forward());
                        t = true;
                    }
                } else if (buf::TestAccess(executor.istream).is_equal_to('f', 'F')) {
                    SF_TRY(buf::Manip(executor.istream).forward());
                    if (buf::TestAccess(executor.istream).is_same("alse")) {
                        SF_TRY(buf::Manip(executor.istream).forward());
                        t = false;
                    }
                }
            } else {
                if (buf::TestAccess(executor.istream).is_equal_to('1')) {
                    SF_TRY(buf::Manip(executor.istream).forward());
                    t = true;
                } else if (buf::TestAccess(executor.istream).is_equal_to('0')) {
                    SF_TRY(buf::Manip(executor.istream).forward());
                    t = false;
                }
            }
            return {};
        }
    };

    template <typename T, typename ParserExecutor>
        requires(std::is_integral_v<T> && !std::is_floating_point_v<T> && !detail::IsCharType<T>::value)
    struct ParserType<T, ParserExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(T& t, ParserExecutor& executor) {
            return buf::FMTReadManip(executor.istream).read_integer_format_data(t, executor.data);
        }
    };

    template <typename T, typename ParserExecutor>
        requires std::is_floating_point_v<T>
    struct ParserType<T, ParserExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(T& t, ParserExecutor& executor) {
            return buf::FMTReadManip(executor.istream).read_float_format_data(t, executor.data);
        }
    };

    //-------------------------------------------------------//
    //----------------- Pointers and Arrays -----------------//
    //-------------------------------------------------------//

    template <typename ParserExecutor>
    struct ParserType<void*, ParserExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(void*&, ParserExecutor&) {
            // FIXME
            // TODO
            return std::unexpected(FMTResult::FunctionNotImpl);
        }
    };

    template <typename T, typename ParserExecutor>
    struct ParserType<T*, ParserExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(T*&, ParserExecutor&) {
            // FIXME
            // TODO
            return std::unexpected(FMTResult::FunctionNotImpl);
        }
    };

    template <typename T, std::size_t SIZE, typename ParserExecutor>
    struct ParserType<T[SIZE], ParserExecutor> {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(T (&)[SIZE], ParserExecutor&) {
            // FIXME
            // TODO
            return std::unexpected(FMTResult::FunctionNotImpl);
        }
    };
}  // namespace stream::fmt
