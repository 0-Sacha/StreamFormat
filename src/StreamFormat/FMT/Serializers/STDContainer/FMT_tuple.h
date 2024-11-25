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
    [[nodiscard]] static inline std::expected<void, FMTResult> TupleFormatRec(FormatterExecutor& executor)
    {
        return {};
    }

    template <typename T, typename FormatterExecutor>
    [[nodiscard]] static inline std::expected<void, FMTResult> TupleFormatRec(FormatterExecutor& executor, const T& t)
    {
        return executor.WriteType(t);
    }

    template <typename T, typename FormatterExecutor, typename... Args>
    [[nodiscard]] static inline std::expected<void, FMTResult> TupleFormatRec(FormatterExecutor& executor, const T& t, Args&&... args)
    {
        SF_TRY(executor.WriteType(t));
        SF_TRY(executor.BufferOut.Pushback(','));
        SF_TRY(executor.BufferOut.Pushback(' '));
        return TupleFormatRec(context, args...);
    }
}

namespace StreamFormat::FMT
{
    template <typename... T, typename FormatterExecutor>
    struct FormatterType<std::tuple<T...>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Format(const std::tuple<T...>& t, FormatterExecutor& executor)
        {
            SF_TRY(executor.BufferOut.Pushback('<'));
            std::expected<void, FMTResult> err = {};
            std::apply([&context, &err](auto&&... args)
                {
                    auto&& res = TupleDetail::TupleFormatRec(context, args...);
                    if (not res)
                        { err = res.error(); }
                }, t);
            SF_TRY(executor.BufferOut.Pushback('>'));
        }
    };

    template <typename T1, typename T2, typename FormatterExecutor>
    struct FormatterType<std::pair<T1, T2>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Format(const std::pair<T1, T2>& t, FormatterExecutor& executor)
        {
            SF_TRY(executor.BufferOut.Pushback('<'));
            SF_TRY(executor.WriteType(t.first));
            SF_TRY(executor.BufferOut.Pushback(':'));
            SF_TRY(executor.WriteType(t.second));
            SF_TRY(executor.BufferOut.Pushback('>'));

            return {};
        }
    };
}
