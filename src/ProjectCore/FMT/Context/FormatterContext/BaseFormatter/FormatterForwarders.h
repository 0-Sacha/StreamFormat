#pragma once

#include "ProjectCore/FMT/Context/FormatterContext/BasicFormatterContext.h"
#include "ProjectCore/FMT/Detail/Forwarders.h"

namespace ProjectCore::FMT
{
    // Int Forwarders
    template<typename T, typename FormatterContext>
    struct FormatterType<Detail::ForwardAsInt<T>, FormatterContext> {
        static inline void Format(const T t, FormatterContext& context) {
            context.BufferOut().WriteIntFormatData(t, context.GetFormatData());
        }
    };

    // UInt Forwarders
    template<typename T, typename FormatterContext>
    struct FormatterType<Detail::ForwardAsUInt<T>, FormatterContext> {
        static inline void Format(const T t, FormatterContext& context) {
            context.BufferOut().WriteUIntFormatData(t, context.GetFormatData());
        }
    };

    // Float Forwarders
    template<typename T, typename FormatterContext>
    struct FormatterType<Detail::ForwardAsFloat<T>, FormatterContext> {
        static void Format(const T t, FormatterContext& context) {
            context.BufferOut().WriteFloatFormatData(t, context.GetFormatData());
        }
    };

    // Char Forwarders
    template<typename T, typename FormatterContext>
    struct FormatterType<Detail::ForwardAsChar<T>, FormatterContext> {
        inline static void Format(const T t, FormatterContext& context) {
            context.BufferOut().PushBack(t);
        }
    };

    // Char Array Forwarders
    template<typename T, std::size_t SIZE, typename FormatterContext>
    struct FormatterType<Detail::ForwardAsCharArray<T, SIZE>, FormatterContext> {
        static void Format(const T(&t)[SIZE], FormatterContext& context) {
            const auto& data = context.GetFormatData();

            std::size_t begin = (std::size_t)context.GetFormatData().GetSpecifierAsNumber("begin", 0);
            std::size_t size = (std::size_t)context.GetFormatData().GetSpecifierAsNumber("size", static_cast<Detail::DataType>((t[SIZE - 1] == 0 ? SIZE - 1 : SIZE) - begin));

            if (data.HasSpecifier("indent"))
                return context.BufferOut().WriteIndentCharPtr(t + begin, static_cast<std::size_t>(size));

            if (data.TrueValue)    context.BufferOut().PushBack('\"');
            
            // TODO : this check is false becquse it need to check for a custom ShiftType/ShiftSize/ShiftPrint an no a HasSpec
            // Cause this check will use the costly one even when it is not needed
            if (data.HasSpec == false)
                context.BufferOut().FastWriteCharPtr(t + begin, static_cast<std::size_t>(size));
            else
                context.BufferOut().WriteCharPtr(t + begin, static_cast<std::size_t>(size), data.ShiftType, data.ShiftSize, data.ShiftPrint);

            if (data.TrueValue)    context.BufferOut().PushBack('\"');
        }
    };

    // Char Pointers Forwarders
    template<typename T, typename FormatterContext>
    struct FormatterType<Detail::ForwardAsCharPointer<T>, FormatterContext> {
        static void Format(const T* t, FormatterContext& context) {
            const auto& data = context.GetFormatData();

            if (t == nullptr)
                return context.BufferOut().FastWriteStringView(data.GetSpecifierAsText("null", "[nullptr string]"));

            std::size_t begin = (std::size_t)data.GetSpecifierAsNumber("begin", 0);
            std::size_t size = (std::size_t)data.GetSpecifierAsNumber("size", Detail::FORMAT_DATA_NOT_SPECIFIED);

            if (data.HasSpecifier("indent"))
            {
                if (size == Detail::FORMAT_DATA_NOT_SPECIFIED)
                    return context.BufferOut().WriteIndentCharPtrNSize(t + begin);
                return context.BufferOut().WriteIndentCharPtr(t + begin, size);
            }

            if (data.TrueValue) context.BufferOut().PushBack('\"');

            // TODO : this check is false becquse it need to check for a custom ShiftType/ShiftSize/ShiftPrint an no a HasSpec
            // Cause this check will use the costly one even when it is not needed
            if (data.HasSpec == false)
            {
                if (size != Detail::FORMAT_DATA_NOT_SPECIFIED)    context.BufferOut().FastWriteCharPtr(t + begin, size);
                else                                            context.BufferOut().FastWriteCharPtrNSize(t + begin);
            }
            else
            {
                if (size != Detail::FORMAT_DATA_NOT_SPECIFIED)    context.BufferOut().WriteCharPtr(t + begin, size, data.ShiftType, data.ShiftSize, data.ShiftPrint);
                else                                            context.BufferOut().WriteCharPtrNSize(t + begin, data.ShiftType, data.ShiftSize, data.ShiftPrint);
            }

            if (data.TrueValue) context.BufferOut().PushBack('\"');
        }
    };
}
