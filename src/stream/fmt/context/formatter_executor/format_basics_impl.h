#pragma once

#include "basic_formatter_executor.h"

#include "stream/fmt/buffer/FMTBufferWriteManip.h"

namespace stream::fmt
{
    //---------------------------------------------//
    //----------------- Internals -----------------//
    //---------------------------------------------//

    template <typename FormatterExecutor>
    struct FormatterType<typename FormatterExecutor::detail::template FormatSpecifier<typename FormatterExecutor::TChar>, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const typename FormatterExecutor::detail::template FormatSpecifier<typename FormatterExecutor::TChar>& specifier, FormatterExecutor& executor)
        {
            if (specifier.ValueIsText)
                { SF_TRY(executor.Run("{ '{}', '{}' }", specifier.Name, specifier.AsText)); }
            else
                { SF_TRY(executor.Run("{ '{}', '{}' }", specifier.Name, specifier.AsNumber)); }
            return {};
        }
    };

    //----------------------------------------------//
    //----------------- Forwarders -----------------//
    //----------------------------------------------//

    namespace detail::Forwarders
    {
        template <typename T, typename FormatterExecutor>
        [[nodiscard]] std::expected<void, FMTResult> FormatObjectArray(const T* const buffer, std::size_t totalsize, FormatterExecutor& executor)
        {
            std::size_t beginIdx = (std::size_t)executor.Data.Specifiers.GetAsNumber("begin", 0);
            totalsize = executor.Data.Specifiers.GetAsNumber("totalsize", totalsize);
            totalsize = executor.Data.Specifiers.GetAsNumber("end", totalsize);
            
            std::size_t size = executor.Data.Specifiers.GetAsNumber("size", totalsize - beginIdx);

            if (size == std::numeric_limits<std::size_t>::max())
                { return std::unexpected(FMTResult::GivenArgs_UnableToDeduceSize); }

            SF_TRY(detail::BufferWriteManip(executor.buffer_out).FastWriteString(executor.Data.Specifiers.GetAsText("begin", STDEnumerableUtility::DefaultBegin)));

            std::basic_string_view<typename FormatterExecutor::TChar> join = executor.Data.Specifiers.GetAsText("join", STDEnumerableUtility::DefaultJoin);

            bool first = true;
            const T* itbegin = buffer + beginIdx;
            const T* itend = buffer + size + beginIdx;

            while (itbegin < itend)
            {
                if (first)
                    { first = false; }
                else
                    { SF_TRY(detail::FMTBufferWriteManip(executor.buffer_out).WriteIndentString(join)); }
                SF_TRY(executor.WriteType(*itbegin++));
            }

            return detail::BufferWriteManip(executor.buffer_out).FastWriteString(executor.Data.Specifiers.GetAsText("end", STDEnumerableUtility::DefaultEnd));
        }

        template <typename T, typename FormatterExecutor>
        [[nodiscard]] std::expected<void, FMTResult> FormatString(const T* buffer, std::size_t size, FormatterExecutor& executor)
        {
            std::size_t beginIdx = (std::size_t)executor.Data.Specifiers.GetAsNumber("begin", 0);
            size = executor.Data.Specifiers.GetAsNumber("size", size);
            if (size == std::numeric_limits<std::size_t>::max())
                { size = std::basic_string_view(buffer).size(); }

            if (executor.Data.Specifiers.Has("array"))
                return FormatObjectArray(buffer, size, executor);

            if (beginIdx > size) return {};
            const T* begin = buffer + beginIdx;

            // TODO: current indent ignore shift
            if (executor.Data.Specifiers.Has("indent"))
                return detail::FMTBufferWriteManip(executor.buffer_out).WriteIndentCharPtr(begin, size);

            if (executor.Data.PrefixSuffix)
                { SF_TRY(detail::BufferOutManip(executor.buffer_out).Pushback('\"')); }

            if (executor.Data.HasSpec == false)
                { SF_TRY(detail::BufferWriteManip(executor.buffer_out).FastWriteCharArray(begin, size)); }
            else
                { SF_TRY(detail::FMTBufferWriteManip(executor.buffer_out).WriteCharPtr(begin, size, executor.Data.Shift)); }

            if (executor.Data.PrefixSuffix)
                { SF_TRY(detail::BufferOutManip(executor.buffer_out).Pushback('\"')); }
            
            return {};
        }
    }

    //-----------------------------------------------//
    //----------------- C/CXX Types -----------------//
    //-----------------------------------------------//

    // Bool
    template <typename FormatterExecutor>
    struct FormatterType<bool, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const bool t, FormatterExecutor& executor)
        {
            if (executor.Data.PrefixSuffix)
            {
                if (t == true)
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("True");
                else
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("False");
            }
            else
            {
                if (t == true)
                    return detail::BufferOutManip(executor.buffer_out).Pushback('1');
                else
                    return detail::BufferOutManip(executor.buffer_out).Pushback('0');
            }

            return {};
        }
    };

    template <typename T, typename FormatterExecutor>
    requires (std::is_integral_v<T> && !std::is_floating_point_v<T> && !detail::IsCharType<T>::Value)
    struct FormatterType<T, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const T t, FormatterExecutor& executor)
            { return detail::FMTBufferWriteManip(executor.buffer_out).WriteIntegerFormatData(t, executor.Data); }
    };

    template <typename T, typename FormatterExecutor>
    requires std::is_floating_point_v<T>
    struct FormatterType<T, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const T t, FormatterExecutor& executor)
            { return detail::FMTBufferWriteManip(executor.buffer_out).WriteFloatFormatData(t, executor.Data); }
    };

    template <typename T, typename FormatterExecutor>
    requires detail::IsCharType<T>::Value
    struct FormatterType<T, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const T t, FormatterExecutor& executor)
            { return detail::BufferOutManip(executor.buffer_out).Pushback(t); }
    };

    //-------------------------------------------------------//
    //----------------- Pointers and Arrays -----------------//
    //-------------------------------------------------------//

    template <typename FormatterExecutor>
    struct FormatterType<void*, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const void* const t, FormatterExecutor& executor)
        {
            if (t == nullptr)
                return detail::BufferOutManip(executor.buffer_out).FastWriteString(executor.Data.GetAsText("null", "nullptr"));
            return detail::BufferWriteManip(executor.buffer_out).FastWriteInteger(std::size_t(t));
        }
    };

    template <typename T, typename FormatterExecutor>
    struct FormatterType<T*, FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const T* const t, FormatterExecutor& executor)
        {
            if (t == nullptr)
                { return detail::BufferWriteManip(executor.buffer_out).FastWriteString(executor.Data.Specifiers.GetAsText("null", "nullptr")); }

            if constexpr (detail::IsCharType<T>::Value)
                { return detail::Forwarders::FormatString(t, std::numeric_limits<std::size_t>::max(), executor); }
            else
                { detail::Forwarders::FormatObjectArray(t, std::numeric_limits<std::size_t>::max(), executor); }

            return {};
        }
    };

    template <typename T, std::size_t SIZE, typename FormatterExecutor>
    struct FormatterType<T[SIZE], FormatterExecutor>
    {
        [[nodiscard]] static inline std::expected<void, FMTResult> format(T const (&t)[SIZE], FormatterExecutor& executor)
        {
            if constexpr (detail::IsCharType<T>::Value)
            {
                std::size_t size = SIZE;
                while (t[size - 1] == '\0') --size;
                return detail::Forwarders::FormatString(t, size, executor);
            }
            else
            {
                return detail::Forwarders::FormatObjectArray(t, SIZE, executor);
            }
            
            return {};
        }
    };
}
