#pragma once

#include "../FormatterType.h"

namespace ProjectCore::FMT
{
    template<typename T, typename FormatterContext>
    struct FCIndexArgs {

        FCIndexArgs(const std::uint8_t idx, const T& t)
            : m_Value(t), m_Idx(idx) {}

    public:
        inline bool IsRightIdx(std::uint8_t idx) const { return idx == m_Idx; }

    public:
        inline const T& GetValue() const { return m_Value; }

    protected:
        const T& m_Value;
        const std::uint8_t m_Idx;
    };

    template<typename T, typename FormatterContext>
    struct FormatterType<FCIndexArgs<T, FormatterContext>, FormatterContext>
    {
        template<typename Char>
        inline static void Format(const FCIndexArgs<T, FormatterContext>& t, FormatterContext& context) {
            context.RunType(t.GetValue());
        }
    };
}
