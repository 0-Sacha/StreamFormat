#pragma once

#include "BasicParserExecutor.h"
#include "stream/fmt/buffer/FMTBufferReadManip.h"

namespace stream::fmt
{
    //----------------------------------------------//
    //----------------- Forwarders -----------------//
    //----------------------------------------------//

    //-----------------------------------------------//
    //----------------- C/CXX Types -----------------//
    //-----------------------------------------------//

    template <typename ParserExecutor>
    struct ParserType<bool, ParserExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> parse(bool& t, ParserExecutor& executor)
        {
            if (!executor.Data.PrefixSuffix)
            {
                if (detail::BufferTestAccess(executor.BufferIn).IsEqualTo('t', 'T'))
                {
                    SF_TRY(detail::BufferManip(executor.BufferIn).Forward());
                    if (detail::BufferTestAccess(executor.BufferIn).IsSame("rue"))
                    {
                        SF_TRY(detail::BufferManip(executor.BufferIn).Forward());
                        t = true;
                    }
                }
                else if (detail::BufferTestAccess(executor.BufferIn).IsEqualTo('f', 'F'))
                {
                    SF_TRY(detail::BufferManip(executor.BufferIn).Forward());
                    if (detail::BufferTestAccess(executor.BufferIn).IsSame("alse"))
                    {
                        SF_TRY(detail::BufferManip(executor.BufferIn).Forward());
                        t = false;
                    }
                }
            }
            else
            {
                if (detail::BufferTestAccess(executor.BufferIn).IsEqualTo('1'))
                {
                    SF_TRY(detail::BufferManip(executor.BufferIn).Forward());
                    t = true;
                }
                else if (detail::BufferTestAccess(executor.BufferIn).IsEqualTo('0'))
                {
                    SF_TRY(detail::BufferManip(executor.BufferIn).Forward());
                    t = false;
                }
            }
            return {};
        }
    };

    template <typename T, typename ParserExecutor>
    requires (std::is_integral_v<T> && !std::is_floating_point_v<T> && !detail::IsCharType<T>::Value)
    struct ParserType<T, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(T& t, ParserExecutor& executor)
            { return detail::FMTBufferReadManip(executor.BufferIn).ReadIntegerFormatData(t, executor.Data); }
    };

    template <typename T, typename ParserExecutor>
    requires std::is_floating_point_v<T>
    struct ParserType<T, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(T& t, ParserExecutor& executor)
            { return detail::FMTBufferReadManip(executor.BufferIn).ReadFloatFormatData(t, executor.Data); }
    };

    //-------------------------------------------------------//
    //----------------- Pointers and Arrays -----------------//
    //-------------------------------------------------------//

    template <typename ParserExecutor>
    struct ParserType<void*, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(void*&, ParserExecutor&)
        {
            // FIXME
            // TODO
            return std::unexpected(FMTResult::FunctionNotImpl);
        }
    };

    template <typename T, typename ParserExecutor>
    struct ParserType<T*, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(T*&, ParserExecutor&)
        {
            // FIXME
            // TODO
            return std::unexpected(FMTResult::FunctionNotImpl);
        }
    };

    template <typename T, std::size_t SIZE, typename ParserExecutor>
    struct ParserType<T[SIZE], ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> parse(T (&)[SIZE], ParserExecutor&)
        {
            // FIXME
            // TODO
            return std::unexpected(FMTResult::FunctionNotImpl);
        }
    };
}
