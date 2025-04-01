#pragma once

#include "basic_parser_executor.hxx"
#include "stream/fmt/buf/fmt_read_manip.hxx"

namespace stream::fmt {
    //----------------------------------------------//
    //----------------- forwarders -----------------//
    //----------------------------------------------//

    //-----------------------------------------------//
    //----------------- C/CXX Types -----------------//
    //-----------------------------------------------//

    template <typename ParserExecutor>
    struct ParserType<bool, ParserExecutor> {
        static void parse(bool& t, ParserExecutor& executor) {
            if (!executor.data.prefix_suffix) {
                if (buf::TestAccess(executor.istream).is_equal_to('t', 'T')) {
                    buf::Manip(executor.istream).forward();
                    if (buf::TestAccess(executor.istream).is_same("rue")) {
                        buf::Manip(executor.istream).forward(3);
                        t = true;
                    }
                } else if (buf::TestAccess(executor.istream).is_equal_to('f', 'F')) {
                    buf::Manip(executor.istream).forward();
                    if (buf::TestAccess(executor.istream).is_same("alse")) {
                        buf::Manip(executor.istream).forward(4);
                        t = false;
                    }
                }
            } else {
                if (buf::TestAccess(executor.istream).is_equal_to('1')) {
                    buf::Manip(executor.istream).forward();
                    t = true;
                } else if (buf::TestAccess(executor.istream).is_equal_to('0')) {
                    buf::Manip(executor.istream).forward();
                    t = false;
                }
            }
        }
    };

    template <typename T, typename ParserExecutor>
        requires(std::is_integral_v<T> && !std::is_floating_point_v<T> && !detail::IsCharType<T>::value)
    struct ParserType<T, ParserExecutor> {
        static inline void parse(T& t, ParserExecutor& executor) {
            return buf::FMTReadManip(executor.istream).read_integer_format_data(t, executor.data);
        }
    };

    template <typename T, typename ParserExecutor>
        requires std::is_floating_point_v<T>
    struct ParserType<T, ParserExecutor> {
        static inline void parse(T& t, ParserExecutor& executor) {
            return buf::FMTReadManip(executor.istream).read_float_format_data(t, executor.data);
        }
    };

    //-------------------------------------------------------//
    //----------------- Pointers and Arrays -----------------//
    //-------------------------------------------------------//

    template <typename ParserExecutor>
    struct ParserType<void*, ParserExecutor> {
        static inline void parse(void*&, ParserExecutor&) {
            // FIXME
            // TODO
            throw std::runtime_error("fmt error: FunctionNotImpl");
        }
    };

    template <typename T, typename ParserExecutor>
    struct ParserType<T*, ParserExecutor> {
        static inline void parse(T*&, ParserExecutor&) {
            // FIXME
            // TODO
            throw std::runtime_error("fmt error: FunctionNotImpl");
        }
    };

    template <typename T, std::size_t SIZE, typename ParserExecutor>
    struct ParserType<T[SIZE], ParserExecutor> {
        static inline void parse(T (&)[SIZE], ParserExecutor&) {
            // FIXME
            // TODO
            throw std::runtime_error("fmt error: FunctionNotImpl");
        }
    };
}  // namespace stream::fmt
