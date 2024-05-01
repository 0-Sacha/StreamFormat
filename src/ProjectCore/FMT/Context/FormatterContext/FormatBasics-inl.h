#pragma once

#include "BasicFormatterContext.h"
#include "ProjectCore/FMT/Detail/Forwarders.h"

namespace ProjectCore::FMT
{
    //---------------------------------------------//
    //----------------- Internals -----------------//
    //---------------------------------------------//

    template <typename FormatterContext>
    struct FormatterType<typename FormatterContext::FormatSpecifierType, FormatterContext>
    {
        static void Format(const typename FormatterContext::FormatSpecifierType& specifier, FormatterContext& context)
        {
            if(specifier.ValueIsText)
                context.SubContextArrayFMT("{ '{}', '{}' }", specifier.Name, specifier.ValueAsText);
            else
                context.SubContextArrayFMT("{ '{}', '{}' }", specifier.Name, specifier.ValueAsNumber);
        }
    };

    template <typename FormatterContext>
    struct FormatterType<typename FormatterContext::DataType, FormatterContext>
    {
        static void Format(const typename FormatterContext::DataType&, FormatterContext& context)
        {
            context.SubContextArrayFMT("{:C:red}", "Missing '{' or '}' because currently the format data is used as a parameter");
        }
    };


    //----------------------------------------------//
    //----------------- Forwarders -----------------//
    //----------------------------------------------//

    // Int Forwarders
    template <typename T, typename FormatterContext>
    struct FormatterType<Detail::ForwardAsInt<T>, FormatterContext>
    {
        static inline void Format(const T t, FormatterContext& context)
        {
            context.BufferOut().WriteIntFormatData(t, context.GetFormatData());
        }
    };

    // UInt Forwarders
    template <typename T, typename FormatterContext>
    struct FormatterType<Detail::ForwardAsUInt<T>, FormatterContext>
    {
        static inline void Format(const T t, FormatterContext& context)
        {
            context.BufferOut().WriteUIntFormatData(t, context.GetFormatData());
        }
    };


    // Float Forwarders
    template <typename T, typename FormatterContext>
    struct FormatterType<Detail::ForwardAsFloat<T>, FormatterContext> 
    {
        static void Format(const T t, FormatterContext& context)
        {
            context.BufferOut().WriteFloatFormatData(t, context.GetFormatData());
        }
    };

    // Char Forwarders
    template <typename T, typename FormatterContext>
    struct FormatterType<Detail::ForwardAsChar<T>, FormatterContext>
    {
        inline static void Format(const T t, FormatterContext& context)
        {
            context.BufferOut().PushBack(t);
        }
    };

    // Char Array Forwarders
    template <typename T, std::size_t SIZE, typename FormatterContext>
    struct FormatterType<Detail::ForwardAsCharArray<T, SIZE>, FormatterContext>
    {
        static void Format(const T(&t)[SIZE], FormatterContext& context)
        {
            const auto& data = context.GetFormatData();

            std::size_t begin = (std::size_t)context.GetFormatData().GetSpecifierAsNumber("begin", 0);
            std::size_t size = (std::size_t)context.GetFormatData().GetSpecifierAsNumber("size", static_cast<Detail::DataType>((t[SIZE - 1] == 0 ? SIZE - 1 : SIZE) - begin));

            if (data.HasSpecifier("indent"))
                return context.BufferOut().WriteIndentCharPtr(t + begin, static_cast<std::size_t>(size));

            if (data.TrueValue)     context.BufferOut().PushBack('\"');
            
            // TODO : this check is false becquse it need to check for a custom ShiftType/ShiftSize/ShiftPrint an no a HasSpec
            // Cause this check will use the costly one even when it is not needed
            if (data.HasSpec == false)
                context.BufferOut().FastWriteCharPtr(t + begin, static_cast<std::size_t>(size));
            else
                context.BufferOut().WriteCharPtr(t + begin, static_cast<std::size_t>(size), data.ShiftType, data.ShiftSize, data.ShiftPrint);

            if (data.TrueValue)     context.BufferOut().PushBack('\"');
        }
    };

    // Char Pointers Forwarders
    template <typename T, typename FormatterContext>
    struct FormatterType<Detail::ForwardAsCharPointer<T>, FormatterContext>
    {
        static void Format(const T* t, FormatterContext& context)
        {
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
                if (size != Detail::FORMAT_DATA_NOT_SPECIFIED)  context.BufferOut().FastWriteCharPtr(t + begin, size);
                else                                            context.BufferOut().FastWriteCharPtrNSize(t + begin);
            }
            else
            {
                if (size != Detail::FORMAT_DATA_NOT_SPECIFIED)  context.BufferOut().WriteCharPtr(t + begin, size, data.ShiftType, data.ShiftSize, data.ShiftPrint);
                else                                            context.BufferOut().WriteCharPtrNSize(t + begin, data.ShiftType, data.ShiftSize, data.ShiftPrint);
            }

            if (data.TrueValue) context.BufferOut().PushBack('\"');
        }
    };


    //-----------------------------------------------//
    //----------------- C/CXX Types -----------------//
    //-----------------------------------------------//

    // Bool
    template <typename FormatterContext>
    struct FormatterType<bool, FormatterContext>
    {
        static void Format(const bool t, FormatterContext& context)
        {
            if (!context.GetFormatData().TrueValue)
            {
                if (t == true)  context.BufferOut().FastWriteCharArray("True");
                else            context.BufferOut().FastWriteCharArray("False");
            }
            else
            {
                if (t == true)  context.BufferOut().PushBack('1');
                else            context.BufferOut().PushBack('0');
            }
        }
    };

    // Signed Types
    template <typename T, typename FormatterContext>
    requires Detail::AsSignedIntegerType<T>
    struct FormatterType<T, FormatterContext>
    {
        static inline void Format(const T t, FormatterContext& context)
        {
            FormatterType<Detail::ForwardAsInt<T>, FormatterContext>::Format(t, context);
        }
    };

    // Unsigned Types
    template <typename T, typename FormatterContext>
    requires Detail::AsUnsignedIntegerType<T>
    struct FormatterType<T, FormatterContext>
    {
        static inline void Format(const T t, FormatterContext& context)
        {
            FormatterType<Detail::ForwardAsUInt<T>, FormatterContext>::Format(t, context);
        }
    };

    // Float Types
    template <typename T, typename FormatterContext>
    requires Detail::AsFloatType<T>
    struct FormatterType<T, FormatterContext>
    {
        static inline void Format(const T t, FormatterContext& context)
        {
            FormatterType<Detail::ForwardAsFloat<T>, FormatterContext>::Format(t, context);
        }
    };

    // Char Types
    template <typename T, typename FormatterContext>
    requires Detail::AsCharType<T>
    struct FormatterType<T, FormatterContext>
    {
        inline static void Format(const T t, FormatterContext& context)
        {
            FormatterType<Detail::ForwardAsChar<T>, FormatterContext>::Format(t, context);
        }
    };
    // Char Arrays
    template <typename T, std::size_t SIZE, typename FormatterContext>
    requires Detail::AsCharType<T>
    struct FormatterType<T [SIZE], FormatterContext>
    {
        static void Format(const T (&t)[SIZE], FormatterContext& context)
        {
            FormatterType<Detail::ForwardAsCharArray<T, SIZE>, FormatterContext>::Format(t, context);
        }
    };
    // Char Pointers
    template <typename T, typename FormatterContext>
    requires Detail::AsCharType<T>
    struct FormatterType<T*, FormatterContext>
    {
        static void Format(const T* const t, FormatterContext& context)
        {
            FormatterType<Detail::ForwardAsCharPointer<T>, FormatterContext>::Format(t, context);
        }
    };

    
    //-------------------------------------------------------//
    //----------------- Pointers and Arrays -----------------//
    //-------------------------------------------------------//
    
    template <typename FormatterContext>
    struct FormatterType<void*, FormatterContext>
    {
        static void Format(const void* const t, FormatterContext& context) {
            if (t == nullptr)
                return context.BufferOut().FastWriteStringView(context.GetFormatData().GetSpecifierAsText("null", "nullptr"));

            if (context.GetFormatData().IntPrint == Detail::ValueIntPrint::Hex)
                return context.SubContextArrayFMT("{:X,=,U}", reinterpret_cast<std::uintptr_t>(t));
            else
                return FormatterType<Detail::ForwardAsInt<std::size_t>, FormatterContext>::Format(reinterpret_cast<std::uintptr_t>(t), context);
        }
    };

    template <typename T, typename FormatterContext>
    struct FormatterType<T*, FormatterContext>
    {
        static void Format(const T* const t, FormatterContext& context) {

            auto size = context.GetFormatData().GetSpecifierAsNumber("size", Detail::FORMAT_DATA_NOT_SPECIFIED);

            if(size == Detail::FORMAT_DATA_NOT_SPECIFIED)
            {
                if (context.GetFormatData().TrueValue)
                {
                    if (context.GetFormatData().IntPrint == Detail::ValueIntPrint::Hex)
                        return context.SubContextArrayFMT("{:X,=,U}", reinterpret_cast<std::uintptr_t>(t));
                    else
                        return FormatterType<Detail::ForwardAsInt<std::size_t>, FormatterContext>::Format(reinterpret_cast<std::uintptr_t>(t), context);
                }
                else
                {
                    bool all = context.GetFormatData().HasSpecifier("size");
                    if (all)
                    {
                        if (t == nullptr)
                            return context.BufferOut().FastWriteStringView(context.GetFormatData().GetSpecifierAsText("null", "nullptr"));
                        return context.SubContextArrayFMT("{} -> {:{}}", static_cast<const void* const>(t), *t, context.ForwardFormatData());
                    }
                    else
                        return context.WriteType(*t);
                }
                return;
            }

            if (t == nullptr)
                return context.BufferOut().FastWriteStringView(context.GetFormatData().GetSpecifierAsText("null", "nullptr"));

            context.BufferOut().FastWriteStringView(context.GetFormatData().GetSpecifierAsText("begin", STDEnumerableUtility::DefaultBegin));

            const auto& join = context.GetFormatData().GetSpecifierAsText("join", STDEnumerableUtility::DefaultJoin);

            auto beginValue = context.GetFormatData().GetSpecifierAsNumber("begin", 0);

            bool first = true;
            const T* begin    = t + beginValue;
            const T* end    = begin + size;

            while (begin < end) {
                if (first)  first = false;
                else        context.BufferOut().WriteIndentStringView(join);
                context.WriteType(*begin++);
            }

            context.BufferOut().FastWriteStringView(context.GetFormatData().GetSpecifierAsText("end", STDEnumerableUtility::DefaultEnd));
        }
    };

    template <typename T, std::size_t SIZE, typename FormatterContext>
    struct FormatterType<T [SIZE], FormatterContext>
    {
        static void Format(T const (&t)[SIZE], FormatterContext& context) {

            context.BufferOut().FastWriteStringView(context.GetFormatData().GetSpecifierAsText("begin", STDEnumerableUtility::DefaultBegin));

            const auto& join = context.GetFormatData().GetSpecifierAsText("join", STDEnumerableUtility::DefaultJoin);

            bool first = true;
            std::size_t beginValue = (std::size_t)context.GetFormatData().GetSpecifierAsNumber("begin", 0);
            const T* begin     = t + beginValue;
            // FIXME : all thoses static_cast<Detail::DataType> for size of string are dangerous
            const T* end      = begin + context.GetFormatData().GetSpecifierAsNumber("size", static_cast<Detail::DataType>(SIZE - beginValue));

            while(begin < end)
            {
                if (first)    first = false;
                else        context.BufferOut().WriteIndentStringView(join);
                context.WriteType(*begin++);
            }

            context.BufferOut().FastWriteStringView(context.GetFormatData().GetSpecifierAsText("end", STDEnumerableUtility::DefaultEnd));
        }
    };
}
