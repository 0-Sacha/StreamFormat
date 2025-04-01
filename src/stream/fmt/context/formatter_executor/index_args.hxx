#pragma once

#include "formatter_type.hxx"

namespace stream::fmt {
    template <typename T, typename FormatterExecutor>
    struct FCIndexArgs {
    public:
        FCIndexArgs(const std::uint8_t idx, const T& t) : value_(t), idx_(idx) {}

    public:
        inline bool IsRightIdx(std::uint8_t idx) const {
            return idx == idx_;
        }

    public:
        inline const T& get_value() const {
            return value_;
        }

    protected:
        const T&           value_;
        const std::uint8_t idx_;
    };

    template <typename T, typename FormatterExecutor>
    struct FormatterType<FCIndexArgs<T, FormatterExecutor>, FormatterExecutor> {
        template <typename Char>
        static inline void format(const FCIndexArgs<T, FormatterExecutor>& t, FormatterExecutor& executor) {
            return executor.write_type(t.get_value());
        }
    };
}  // namespace stream::fmt
