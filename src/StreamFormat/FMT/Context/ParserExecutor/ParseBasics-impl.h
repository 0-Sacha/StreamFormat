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
        static void Parse(bool& t, ParserExecutor& executor)
        {
            if (!executor.Data.PrefixSuffix)
            {
                if (Detail::BufferTestManip(executor.BufferIn).IsEqualToForward('t', 'T'))
                {
                    if (Detail::BufferTestManip(executor.BufferIn).IsSameForward("rue"))
                        t = true;
                }
                else if (Detail::BufferTestManip(executor.BufferIn).IsEqualToForward('f', 'F'))
                {
                    if (Detail::BufferTestManip(executor.BufferIn).IsSameForward("alse"))
                        t = false;
                }
            }
            else
            {
                if (Detail::BufferTestManip(executor.BufferIn).IsEqualToForward('1'))
                    { t = true; return; }
                else if (Detail::BufferTestManip(executor.BufferIn).IsEqualToForward('1'))
                    { t = false; return; }
            }

            throw Detail::FMTParseError();
        }
    };

    template <typename T, typename ParserExecutor>
    requires (std::is_integral_v<T> && !std::is_floating_point_v<T> && !Detail::IsCharType<T>::Value)
    struct ParserType<T, ParserExecutor>
    {
        static inline void Parse(T& t, ParserExecutor& executor) { Detail::FMTBufferReadManip(executor.BufferIn).ReadIntegerFormatData(t, executor.Data); }
    };

    template <typename T, typename ParserExecutor>
    requires std::is_floating_point_v<T>
    struct ParserType<T, ParserExecutor>
    {
        static inline void Parse(T& t, ParserExecutor& executor) { Detail::FMTBufferReadManip(executor.BufferIn).ReadFloatFormatData(t, executor.Data); }
    };

    //-------------------------------------------------------//
    //----------------- Pointers and Arrays -----------------//
    //-------------------------------------------------------//

    template <typename ParserExecutor>
    struct ParserType<void*, ParserExecutor>
    {
        static inline void Parse(void*&, ParserExecutor&)
        {
            // FIXME
            // TODO
        }
    };

    template <typename T, typename ParserExecutor>
    struct ParserType<T*, ParserExecutor>
    {
        static inline void Parse(T*&, ParserExecutor&)
        {
            // FIXME
            // TODO
        }
    };

    template <typename T, std::size_t SIZE, typename ParserExecutor>
    struct ParserType<T[SIZE], ParserExecutor>
    {
        static inline void Parse(T (&)[SIZE], ParserExecutor&)
        {
            // FIXME
            // TODO
        }
    };
}
