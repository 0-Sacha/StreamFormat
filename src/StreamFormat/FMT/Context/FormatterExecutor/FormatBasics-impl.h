#pragma once

#include "BasicFormatterExecutor.h"

#include "StreamFormat/FMT/Buffer/FMTBufferWriteManip.h"

namespace StreamFormat::FMT
{
    //---------------------------------------------//
    //----------------- Internals -----------------//
    //---------------------------------------------//

    template <typename FormatterExecutor>
    struct FormatterType<typename FormatterExecutor::Detail::template FormatSpecifier<FormatterExecutor::TChar>, FormatterExecutor>
    {
        static void Format(const typename FormatterExecutor::Detail::template FormatSpecifier<FormatterExecutor::TChar>& specifier, FormatterExecutor& executor)
        {
            if (specifier.ValueIsText)
                executor.Run("{ '{}', '{}' }", specifier.Name, specifier.AsText);
            else
                executor.Run("{ '{}', '{}' }", specifier.Name, specifier.AsNumber);
        }
    };

    //----------------------------------------------//
    //----------------- Forwarders -----------------//
    //----------------------------------------------//

    namespace Detail::Forwarders
    {
        template <typename T, typename FormatterExecutor>
        void FormatObjectArray(const T* const buffer, std::size_t totalsize, FormatterExecutor& executor)
        {
            std::size_t beginIdx = (std::size_t)executor.Data.Specifiers.GetAsNumber("begin", 0);
            totalsize = executor.Data.Specifiers.GetAsNumber("totalsize", totalsize);
            totalsize = executor.Data.Specifiers.GetAsNumber("end", totalsize);
            
            std::size_t size = executor.Data.Specifiers.GetAsNumber("size", totalsize - beginIdx);

            if (size == std::numeric_limits<std::size_t>::max())
            {
                Detail::BufferWriteManip(executor.BufferOut).FastWriteString("<unable to deduce size>");
                return;
            }

            Detail::BufferWriteManip(executor.BufferOut).FastWriteString(executor.Data.Specifiers.GetAsText("begin", STDEnumerableUtility::DefaultBegin));

            std::basic_string_view<typename FormatterExecutor::TChar> join = executor.Data.Specifiers.GetAsText("join", STDEnumerableUtility::DefaultJoin);

            bool first = true;
            const T* itbegin = buffer + beginIdx;
            const T* itend = buffer + size + beginIdx;

            while (itbegin < itend)
            {
                if (first)
                    first = false;
                else
                    Detail::FMTBufferWriteManip(executor.BufferOut).WriteIndentString(join);
                executor.WriteType(*itbegin++);
            }

            Detail::BufferWriteManip(executor.BufferOut).FastWriteString(executor.Data.Specifiers.GetAsText("end", STDEnumerableUtility::DefaultEnd));
        }

        template <typename T, typename FormatterExecutor>
        void FormatString(const T* buffer, std::size_t size, FormatterExecutor& executor)
        {
            std::size_t beginIdx = (std::size_t)executor.Data.Specifiers.GetAsNumber("begin", 0);
            size  = executor.Data.Specifiers.GetAsNumber("size", size);
            if (size == std::numeric_limits<std::size_t>::max()) size = std::basic_string_view(buffer).size();

            if (executor.Data.Specifiers.Has("array")) return FormatObjectArray(buffer, size, executor);

            if (beginIdx > size) return;
            const T* begin = buffer + beginIdx;

            // TODO: current indent ignore shift
            if (executor.Data.Specifiers.Has("indent"))
                return Detail::FMTBufferWriteManip(executor.BufferOut).WriteIndentCharPtr(begin, size);

            if (executor.Data.PrefixSuffix) Detail::BufferOutManip(executor.BufferOut).Pushback('\"');

            if (executor.Data.HasSpec == false)
                Detail::BufferWriteManip(executor.BufferOut).FastWriteCharArray(begin, size);
            else
                Detail::FMTBufferWriteManip(executor.BufferOut).WriteCharPtr(begin, size, executor.Data.Shift);

            if (executor.Data.PrefixSuffix) Detail::BufferOutManip(executor.BufferOut).Pushback('\"');
        }
    }

    //-----------------------------------------------//
    //----------------- C/CXX Types -----------------//
    //-----------------------------------------------//

    // Bool
    template <typename FormatterExecutor>
    struct FormatterType<bool, FormatterExecutor>
    {
        static void Format(const bool t, FormatterExecutor& executor)
        {
            if (executor.Data.PrefixSuffix)
            {
                if (t == true)
                    Detail::BufferWriteManip(executor.BufferOut).FastWriteStringLitteral("True");
                else
                    Detail::BufferWriteManip(executor.BufferOut).FastWriteStringLitteral("False");
            }
            else
            {
                if (t == true)
                    Detail::BufferManip(executor.BufferOut).Pushback('1');
                else
                    Detail::BufferManip(executor.BufferOut).Pushback('0');
            }
        }
    };

    template <typename T, typename FormatterExecutor>
    requires (std::is_integral_v<T> && !std::is_floating_point_v<T> && !Detail::IsCharType<T>::Value)
    struct FormatterType<T, FormatterExecutor>
    {
        static inline void Format(const T t, FormatterExecutor& executor) { Detail::FMTBufferWriteManip(executor.BufferOut).WriteIntegerFormatData(t, executor.Data); }
    };

    template <typename T, typename FormatterExecutor>
    requires std::is_floating_point_v<T>
    struct FormatterType<T, FormatterExecutor>
    {
        static inline void Format(const T t, FormatterExecutor& executor) { Detail::FMTBufferWriteManip(executor.BufferOut).WriteFloatFormatData(t, executor.Data); }
    };

    template <typename T, typename FormatterExecutor>
    requires Detail::IsCharType<T>::Value
    struct FormatterType<T, FormatterExecutor>
    {
        static inline void Format(const T t, FormatterExecutor& executor) { Detail::BufferOutManip(executor.BufferOut).Pushback(t); }
    };

    //-------------------------------------------------------//
    //----------------- Pointers and Arrays -----------------//
    //-------------------------------------------------------//

    template <typename FormatterExecutor>
    struct FormatterType<void*, FormatterExecutor>
    {
        static void Format(const void* const t, FormatterExecutor& executor)
        {
            if (t == nullptr)
                return Detail::BufferOutManip(executor.BufferOut).FastWriteString(executor.Data.GetAsText("null", "nullptr"));
            Detail::BufferWriteManip(executor.BufferOut).FastWriteInteger(std::size_t(t));
        }
    };

    template <typename T, typename FormatterExecutor>
    struct FormatterType<T*, FormatterExecutor>
    {
        static void Format(const T* const t, FormatterExecutor& executor)
        {
            if (t == nullptr)
                return Detail::BufferWriteManip(executor.BufferOut).FastWriteString(executor.Data.Specifiers.GetAsText("null", "nullptr"));

            if constexpr (Detail::IsCharType<T>::Value)
            {
                Detail::Forwarders::FormatString(t, std::numeric_limits<std::size_t>::max(), executor);
            }
            else
            {
                Detail::Forwarders::FormatObjectArray(t, std::numeric_limits<std::size_t>::max(), executor);
            }
        }
    };

    template <typename T, std::size_t SIZE, typename FormatterExecutor>
    struct FormatterType<T[SIZE], FormatterExecutor>
    {
        static void Format(T const (&t)[SIZE], FormatterExecutor& executor)
        {
            if constexpr (Detail::IsCharType<T>::Value)
            {
                std::size_t size = SIZE;
                while (t[size - 1] == '\0') --size;
                Detail::Forwarders::FormatString(t, size, executor);
            }
            else
            {
                Detail::Forwarders::FormatObjectArray(t, SIZE, executor);
            }
        }
    };
}
