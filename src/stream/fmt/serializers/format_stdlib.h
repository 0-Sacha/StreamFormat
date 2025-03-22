#pragma once

#include "stream/fmt/context/formatter_executor/basic_formatter_executor.h"

#include <memory>
#include <sstream>
#include <string>
#include <string_view>

namespace stream::fmt
{
    //------------------------------------------//
    //----------------- String -----------------//
    //------------------------------------------//

    template <typename FormatterExecutor, typename Char>
    struct FormatterType<std::basic_string<Char>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::basic_string<Char>& t, FormatterExecutor& executor)
            { return detail::BufferWriteManip(executor.buffer_out).FastWriteString(t); }
    };

    template <typename FormatterExecutor, typename Char>
    struct FormatterType<std::basic_string_view<Char>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(std::basic_string_view<Char> t, FormatterExecutor& executor)
            { return detail::BufferWriteManip(executor.buffer_out).FastWriteString(t); }
    };

    template <typename FormatterExecutor, typename Char>
    struct FormatterType<std::basic_stringstream<Char>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::basic_stringstream<Char>& t, FormatterExecutor& executor)
            { return detail::BufferWriteManip(executor.buffer_out).FastWriteCharArray(t.str(), t.size()); }
    };

    //------------------------------------------//
    //----------------- Memory -----------------//
    //------------------------------------------//

    // UniquePtr
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::unique_ptr<T>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::unique_ptr<T>& t, FormatterExecutor& executor)
        {
            if (executor.Data.TrueValue)
                return FormatterType<T*, FormatterExecutor>::format(t.get(), executor);
            else
                return FormatterType<T, FormatterExecutor>::format(*t, executor);

            return {};
        }
    };

    // SharedPtr
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::shared_ptr<T>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::shared_ptr<T>& t, FormatterExecutor& executor)
        {
            if (executor.Data.TrueValue)
                return FormatterType<T*, FormatterExecutor>::format(t.get(), executor);
            else
                return FormatterType<T, FormatterExecutor>::format(*t, executor);

            return {};
        }
    };

    // WeakPtr
    template <typename T, typename FormatterExecutor>
    struct FormatterType<std::weak_ptr<T>, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const std::weak_ptr<T>& t, FormatterExecutor& executor)
            { return FormatterType<std::shared_ptr<T>, FormatterExecutor>::format(t.lock(), executor); }
    };
}
