#pragma once

#include <tuple>
#include <utility>
#include "StreamFormat/FMT/Context/FormatterExecutor/FormatterType.h"

namespace StreamFormat::FMT::TupleDetail
{
    template <std::uint32_t N, typename... Args>
    using NthTypeOf = typename std::tuple_element<N, std::tuple<Args...>>::type;

    template <std::uint32_t N, typename... Args>
    constexpr NthTypeOf<N, Args...>& Get(Args&&... args)
    {
        std::tuple<Args...> tuple(args...);
        return std::get<N>(tuple);
    }

    template <typename FormatterExecutor>
    static void TupleFormatRec(FormatterExecutor& executor)
    {}

    template <typename T, typename FormatterExecutor>
    static void TupleFormatRec(FormatterExecutor& executor, const T& t)
    {
        executor.WriteType(t);
    }

    template <typename T, typename FormatterExecutor, typename... Args>
    static void TupleFormatRec(FormatterExecutor& executor, const T& t, Args&&... args)
    {
        executor.WriteType(t);
        executor.BufferOut.Pushback(',');
        executor.BufferOut.Pushback(' ');
        TupleFormatRec(context, args...);
    }
}

namespace StreamFormat::FMT
{
    template <typename... T, typename FormatterExecutor>
    struct FormatterType<std::tuple<T...>, FormatterExecutor>
    {
        static void Format(const std::tuple<T...>& t, FormatterExecutor& executor)
        {
            executor.BufferOut.Pushback('<');
            std::apply([&context](auto&&... args) { TupleDetail::TupleFormatRec(context, args...); }, t);
            executor.BufferOut.Pushback('>');
        }
    };

    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::pair<T1, T2>, FormatterExecutor>
    {
        static void Format(const std::pair<T1, T2>& t, FormatterExecutor& executor)
        {
            executor.BufferOut.Pushback('<');
            executor.WriteType(t.first);
            executor.BufferOut.Pushback(':');
            executor.WriteType(t.second);
            executor.BufferOut.Pushback('>');
        }
    };
}
