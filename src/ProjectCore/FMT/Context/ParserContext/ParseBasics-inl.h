#pragma once

#include "BasicParserContext.h"
#include "ProjectCore/FMT/Detail/Forwarders.h"

namespace ProjectCore::FMT
{
    //---------------------------------------------//
    //----------------- Internals -----------------//
    //---------------------------------------------//

    template <typename ParserContext>
    struct ParserType<typename ParserContext::DataType, ParserContext>
    {
        static inline void Parse(typename ParserContext::DataType&, ParserContext&) { throw Detail::FMTShouldNotEndHere{}; }
    };

    //-------------------------------------------------------//
    //----------------- Pointers and Arrays -----------------//
    //-------------------------------------------------------//

    template <typename ParserContext>
    struct ParserType<void*, ParserContext>
    {
        static inline void Parse(void*&, ParserContext&)
        {
            // FIXME
            // TODO
        }
    };

    template <typename T, typename ParserContext>
    struct ParserType<T*, ParserContext>
    {
        static inline void Parse(T*&, ParserContext&)
        {
            // FIXME
            // TODO
        }
    };

    template <typename T, std::size_t SIZE, typename ParserContext>
    struct ParserType<T[SIZE], ParserContext>
    {
        static inline void Parse(T (&)[SIZE], ParserContext&)
        {
            // FIXME
            // TODO
        }
    };

    //----------------------------------------------//
    //----------------- Forwarders -----------------//
    //----------------------------------------------//

    // Int Forwarders
    template <typename T, typename ParserContext>
    struct ParserType<Detail::ForwardAsInt<T>, ParserContext>
    {
        static inline void Parse(T& t, ParserContext& context) { context.BufferIn().ReadIntFormatData(t, context.GetFormatData()); }
    };

    // UInt Forwarders
    template <typename T, typename ParserContext>
    struct ParserType<Detail::ForwardAsUInt<T>, ParserContext>
    {
        static inline void Parse(T& t, ParserContext& context) { context.BufferIn().ReadUIntFormatData(t, context.GetFormatData()); }
    };

    // Float Forwarders
    template <typename T, typename ParserContext>
    struct ParserType<Detail::ForwardAsFloat<T>, ParserContext>
    {
        static inline void Parse(T& t, ParserContext& context) { context.BufferIn().ReadFloatFormatData(t, context.GetFormatData()); }
    };

    // Char Forwarders
    template <typename T, typename ParserContext>
    struct ParserType<Detail::ForwardAsChar<T>, ParserContext>
    {
        static inline void Parse(T& t, ParserContext& context) { context.BufferIn().GetAndForward(t); }
    };

    // Char Array Forwarders
    template <typename T, std::size_t SIZE, typename ParserContext>
    struct ParserType<Detail::ForwardAsCharArray<T, SIZE>, ParserContext>
    {
        static inline void Parse(T (&t)[SIZE], ParserContext& context)
        {
            const auto& data = context.GetFormatData();

            std::size_t begin       = (std::size_t)context.GetFormatData().GetSpecifierAsNumber("begin", 0);
            bool        isZeroEnded = context.GetFormatData().HasSpecifier("no-zero-end") == false;
            std::size_t size =
                (std::size_t)context.GetFormatData().GetSpecifierAsNumber("size", static_cast<Detail::DataType>(SIZE - static_cast<std::size_t>(isZeroEnded ? 1 : 0) - begin));

            // if (data.HasSpecifier("indent"))
            //     return context.BufferIn().ReadIndentCharPtr(t + begin, size);

            if (data.TrueValue) context.BufferIn().Skip('\"');

            if (context.GetFormatData().HasSpecifier("glob"))
            {
                auto globberPattern = context.GetFormatData().GetSpecifierAsText("glob");
                context.BufferIn().FastReadCharPtrGlobber(globberPattern, t + begin, size, isZeroEnded);
            }
            else if (context.GetFormatData().HasSpecifier("regex"))
            {
                throw Detail::FMTImplError{};
            }
            else
            {
                if (data.HasSpec == false)
                    context.BufferIn().FastReadCharPtrThrow(t + begin, size, isZeroEnded);
                else
                    context.BufferIn().FastReadCharPtrThrow(t + begin, size, isZeroEnded);
                // context.BufferIn().ReadCharPtr(t + begin, size, 0, data.ShiftType, data.ShiftSize, data.ShiftPrint);
            }

            if (data.TrueValue) context.BufferIn().Skip('\"');
        }
    };

    // Char Pointers Forwarders
    template <typename T, typename ParserContext>
    struct ParserType<Detail::ForwardAsCharPointer<T>, ParserContext>
    {
        static inline void Parse(T* const, ParserContext&)
        {
            // FIXME
        }
    };

    //-----------------------------------------------//
    //----------------- C/CXX Types -----------------//
    //-----------------------------------------------//

    // Bool
    template <typename ParserContext>
    struct ParserType<bool, ParserContext>
    {
        static void Parse(bool& t, ParserContext& context)
        {
            const auto& data = context.GetFormatData();

            if (!data.TrueValue)
            {
                switch (context.BufferIn().Get())
                {
                    case 'T':
                    case 't':
                        if (context.BufferIn().IsSameForward("True")) t = true;

                    case 'F':
                    case 'f':
                        if (context.BufferIn().IsSameForward("False")) t = false;

                    default:
                        throw Detail::FMTParseError();
                }
                return;
            }
            else
            {
                if (context.BufferIn().IsEqualToForward('0'))
                {
                    t = false;
                    return;
                }
                else if (context.BufferIn().IsEqualToForward('1'))
                {
                    t = true;
                    return;
                }
            }

            throw Detail::FMTParseError();
        }
    };

    // Signed Types
    template <typename T, typename ParserContext>
    requires Detail::AsSignedIntegerType<T>
    struct ParserType<T, ParserContext>
    {
        static inline void Parse(T& t, ParserContext& context) { ParserType<Detail::ForwardAsInt<T>, ParserContext>::Parse(t, context); }
    };

    // Unsigned Types
    template <typename T, typename ParserContext>
    requires Detail::AsUnsignedIntegerType<T>
    struct ParserType<T, ParserContext>
    {
        static inline void Parse(T& t, ParserContext& context) { ParserType<Detail::ForwardAsUInt<T>, ParserContext>::Parse(t, context); }
    };

    // Float Types
    template <typename T, typename ParserContext>
    requires Detail::AsFloatType<T>
    struct ParserType<T, ParserContext>
    {
        static inline void Parse(T& t, ParserContext& context) { ParserType<Detail::ForwardAsFloat<T>, ParserContext>::Parse(t, context); }
    };

    // Char Types
    template <typename T, typename ParserContext>
    requires Detail::AsCharType<T>
    struct ParserType<T, ParserContext>
    {
        inline static void Parse(T& t, ParserContext& context) { ParserType<Detail::ForwardAsChar<T>, ParserContext>::Parse(t, context); }
    };
    // Char Arrays
    template <typename T, std::size_t SIZE, typename ParserContext>
    requires Detail::AsCharType<T>
    struct ParserType<T[SIZE], ParserContext>
    {
        static void Parse(T (&t)[SIZE], ParserContext& context) { ParserType<Detail::ForwardAsCharArray<T, SIZE>, ParserContext>::Parse(t, context); }
    };
    // Char Pointers
    template <typename T, typename ParserContext>
    requires Detail::AsCharType<T>
    struct ParserType<T*, ParserContext>
    {
        static void Parse(T* const t, ParserContext& context) { ParserType<Detail::ForwardAsCharPointer<T>, ParserContext>::Parse(t, context); }
    };
}
