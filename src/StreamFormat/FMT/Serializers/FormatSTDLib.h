#pragma once

#include "StreamFormat/FMT/Context/FormatterExecutor/BasicFormatterExecutor.h"

#include <memory>
#include <sstream>
#include <string>
#include <string_view>

namespace StreamFormat::FMT
{
    //------------------------------------------//
    //----------------- String -----------------//
    //------------------------------------------//

    template <typename FormatterExecutor, typename Char>
    struct FormatterType<std::basic_string<Char>, FormatterExecutor>
    {
        static inline void Format(const std::basic_string<Char>& t, FormatterExecutor& executor) { Detail::BufferWriteManip(executor.BufferOut).FastWriteString(t); }
    };

    template <typename FormatterExecutor, typename Char>
    struct FormatterType<std::basic_string_view<Char>, FormatterExecutor>
    {
        static inline void Format(std::basic_string_view<Char> t, FormatterExecutor& executor) { Detail::BufferWriteManip(executor.BufferOut).FastWriteString(t); }
    };

    template <typename FormatterExecutor, typename Char>
    struct FormatterType<std::basic_stringstream<Char>, FormatterExecutor>
    {
        static inline void Format(const std::basic_stringstream<Char>& t, FormatterExecutor& executor) { Detail::BufferWriteManip(executor.BufferOut).FastWriteCharArray(t.str(), t.size()); }
    };

    //------------------------------------------//
    //----------------- Memory -----------------//
    //------------------------------------------//

    // UniquePtr
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::unique_ptr<T>, FormatterExecutor>
    {
        static inline void Format(const std::unique_ptr<T>& t, FormatterExecutor& executor)
        {
            if (executor.Data.TrueValue)
                FormatterType<T*, FormatterExecutor>::Format(t.get(), executor);
            else
                FormatterType<T, FormatterExecutor>::Format(*t, executor);
        }
    };

    // SharedPtr
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::shared_ptr<T>, FormatterExecutor>
    {
        static inline void Format(const std::shared_ptr<T>& t, FormatterExecutor& executor)
        {
            if (executor.Data.TrueValue)
                FormatterType<T*, FormatterExecutor>::Format(t.get(), executor);
            else
                FormatterType<T, FormatterExecutor>::Format(*t, executor);
        }
    };

    // WeakPtr
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::weak_ptr<T>, FormatterExecutor>
    {
        static inline void Format(const std::weak_ptr<T>& t, FormatterExecutor& executor) { FormatterType<std::shared_ptr<T>, FormatterExecutor>::Format(t.lock(), executor); }
    };
}
