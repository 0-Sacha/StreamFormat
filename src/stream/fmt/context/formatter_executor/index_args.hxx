#pragma once

#include "formatter_type.hxx"

namespace stream::fmt {
    template <typename T, typename FormatterExecutor>
    struct FCIndexArgs {
    public:
        FCIndexArgs(const std::uint8_t idx, const T& t) : m_Value(t), idx_(idx) {}

    public:
        inline bool IsRightIdx(std::uint8_t idx) const {
            return idx == idx_;
        }

    public:
        inline const T& get_value() const {
            return m_Value;
        }

    protected:
        const T&           m_Value;
        const std::uint8_t idx_;
    };

    template <typename T, typename FormatterExecutor>
    struct FormatterType<FCIndexArgs<T, FormatterExecutor>, FormatterExecutor> {
        template <typename Char>
        [[nodiscard]] static inline std::expected<void, FMTResult> format(const FCIndexArgs<T, FormatterExecutor>& t, FormatterExecutor& executor) {
            return executor.write_type(t.get_value());
        }
    };
}  // namespace stream::fmt
