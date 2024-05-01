#pragma once

#include "ProjectCore/FMT/Context/FormatterContext/BasicFormatterContext.h"

#include <string>
#include <string_view>
#include <memory>
#include <sstream>

namespace ProjectCore::FMT
{
    //------------------------------------------//
    //----------------- String -----------------//
    //------------------------------------------//

    template <typename FormatterContext, typename Char>
    struct FormatterType<std::basic_string<Char>, FormatterContext> {
        inline static void Format(const std::basic_string<Char>& t, FormatterContext& context) {
            context.BufferOut().FastWriteCharPtr(t.data(), t.size());
        }
    };

    template <typename FormatterContext, typename Char>
    struct FormatterType<std::basic_string_view<Char>, FormatterContext> {
        inline static void Format(const std::basic_string_view<Char>& t, FormatterContext& context) {
            context.BufferOut().FastWriteCharPtr(t.data(), t.size());
        }
    };


    template <typename FormatterContext, typename Char>
    struct FormatterType<std::basic_stringstream<Char>, FormatterContext> {
        inline static void Format(const std::basic_stringstream<Char>& t, FormatterContext& context) {
            context.BufferOut().FastWriteCharPtr(t.str(), t.size());
        }
    };

    //------------------------------------------//
    //----------------- Memory -----------------//
    //------------------------------------------//

    // UniquePtr
    template <typename T, typename FormatterContext>
    struct FormatterType<std::unique_ptr<T>, FormatterContext> {
        inline static void Format(const std::unique_ptr<T>& t, FormatterContext& context) {
            if (context.GetFormatData().TrueValue)  FormatterType<T*, FormatterContext>::Format(t.get(), context);
            else                                    FormatterType<T, FormatterContext>::Format(*t, context);
        }
    };

    // SharedPtr
    template <typename T, typename FormatterContext>
    struct FormatterType<std::shared_ptr<T>, FormatterContext> {
        inline static void Format(const std::shared_ptr<T>& t, FormatterContext& context) {
            if (context.GetFormatData().TrueValue)  FormatterType<T*, FormatterContext>::Format(t.get(), context);
            else                                    FormatterType<T, FormatterContext>::Format(*t, context);
        }
    };

    // WeakPtr
    template <typename T, typename FormatterContext>
    struct FormatterType<std::weak_ptr<T>, FormatterContext> {
        inline static void Format(const std::weak_ptr<T>& t, FormatterContext& context) {
            FormatterType<std::shared_ptr<T>, FormatterContext>::Format(t.lock(), context);
        }
    };
}
