#pragma once

#include "BasicParserExecutor.h"
#include "StreamFormat/FMT/Buffer/FMTBufferReadManip.h"

namespace StreamFormat::FMT
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
        [[nodiscard]] static std::expected<void, FMTResult> Parse(bool& t, ParserExecutor& executor)
        {
            if (!executor.Data.PrefixSuffix)
            {
                if (Detail::BufferTestAccess(executor.BufferIn).IsEqualTo('t', 'T'))
                {
                    SF_TRY(Detail::BufferManip(executor.BufferIn).Forward());
                    if (Detail::BufferTestAccess(executor.BufferIn).IsSame("rue"))
                    {
                        SF_TRY(Detail::BufferManip(executor.BufferIn).Forward());
                        t = true;
                    }
                }
                else if (Detail::BufferTestAccess(executor.BufferIn).IsEqualTo('f', 'F'))
                {
                    SF_TRY(Detail::BufferManip(executor.BufferIn).Forward());
                    if (Detail::BufferTestAccess(executor.BufferIn).IsSame("alse"))
                    {
                        SF_TRY(Detail::BufferManip(executor.BufferIn).Forward());
                        t = false;
                    }
                }
            }
            else
            {
                if (Detail::BufferTestAccess(executor.BufferIn).IsEqualTo('1'))
                {
                    SF_TRY(Detail::BufferManip(executor.BufferIn).Forward());
                    t = true;
                }
                else if (Detail::BufferTestAccess(executor.BufferIn).IsEqualTo('0'))
                {
                    SF_TRY(Detail::BufferManip(executor.BufferIn).Forward());
                    t = false;
                }
            }
            return {};
        }
    };

    template <typename T, typename ParserExecutor>
    requires (std::is_integral_v<T> && !std::is_floating_point_v<T> && !Detail::IsCharType<T>::Value)
    struct ParserType<T, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Parse(T& t, ParserExecutor& executor)
            { return Detail::FMTBufferReadManip(executor.BufferIn).ReadIntegerFormatData(t, executor.Data); }
    };

    template <typename T, typename ParserExecutor>
    requires std::is_floating_point_v<T>
    struct ParserType<T, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Parse(T& t, ParserExecutor& executor)
            { return Detail::FMTBufferReadManip(executor.BufferIn).ReadFloatFormatData(t, executor.Data); }
    };

    //-------------------------------------------------------//
    //----------------- Pointers and Arrays -----------------//
    //-------------------------------------------------------//

    template <typename ParserExecutor>
    struct ParserType<void*, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Parse(void*&, ParserExecutor&)
        {
            // FIXME
            // TODO
            return std::unexpected(FMTResult::FunctionNotImpl);
        }
    };

    template <typename T, typename ParserExecutor>
    struct ParserType<T*, ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Parse(T*&, ParserExecutor&)
        {
            // FIXME
            // TODO
            return std::unexpected(FMTResult::FunctionNotImpl);
        }
    };

    template <typename T, std::size_t SIZE, typename ParserExecutor>
    struct ParserType<T[SIZE], ParserExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> Parse(T (&)[SIZE], ParserExecutor&)
        {
            // FIXME
            // TODO
            return std::unexpected(FMTResult::FunctionNotImpl);
        }
    };
}
