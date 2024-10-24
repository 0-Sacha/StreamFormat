#pragma once

#include "FormatterType.h"

namespace StreamFormat::FMT
{
    template <typename T, typename FormatterExecutor>
    struct FCIndexArgs
    {
    public:
        FCIndexArgs(const std::uint8_t idx, const T& t)
            : m_Value(t)
            , m_Idx(idx)
        {}

    public:
        inline bool IsRightIdx(std::uint8_t idx) const { return idx == m_Idx; }

    public:
        inline const T& GetValue() const { return m_Value; }

    protected:
        const T&           m_Value;
        const std::uint8_t m_Idx;
    };

    template <typename T, typename FormatterExecutor>
    struct FormatterType<FCIndexArgs<T, FormatterExecutor>, FormatterExecutor>
    {
        template <typename Char>
        static inline void Format(const FCIndexArgs<T, FormatterExecutor>& t, FormatterExecutor& executor)
        {
            executor.WriteType(t.GetValue());
        }
    };
}
