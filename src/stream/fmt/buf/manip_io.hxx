#pragma once

#include "stream.hxx"
#include "streamio.hxx"
#include "manip.hxx"

#include "streamio_manager/basic_streamio_manager.hxx"

namespace stream::fmt::buf {
    template <typename TChar>
    class ManipIO {
    public:
        constexpr inline ManipIO(StreamIO<TChar>& buffer) noexcept : buffer(buffer) {}

    public:
        StreamIO<TChar>& buffer;

    public:
        void compute_generated_size() noexcept {
            buffer.Manager.compute_generated_size(Access(buffer).get_buffer_current_size());
        }

    public:
        [[nodiscard]] std::expected<void, FMTResult> add_size(const std::size_t count) noexcept {
            std::size_t currentSize = Access(buffer).get_buffer_current_size();
            SF_TRY(buffer.Manager.add_size(count))
            Manip(buffer).reload(buffer.Manager.get_buffer(), buffer.Manager.get_buffer_size());
            buffer.current_pos = buffer.Manager.get_buffer() + currentSize;
            return {};
        }

        [[nodiscard]] inline std::expected<void, FMTResult> reserve(const std::size_t count = 1) noexcept {
            if (buffer.current_pos + count <= buffer.buffer_end) return {};
            return add_size(static_cast<std::size_t>(count));
        }

        [[nodiscard]] inline std::expected<void, FMTResult> forward(const std::size_t count = 1) noexcept {
            SF_TRY(reserve(count));
            buffer.current_pos += count;
            return {};
        }

    public:
        inline void set(const TChar c) noexcept {
            *buffer.current_pos = c;
        }

        [[nodiscard]] inline std::expected<void, FMTResult> pushback(const TChar c) noexcept {
            SF_TRY(reserve(1));
            *buffer.current_pos++ = c;
            return {};
        }
        inline void pushback_force(const TChar c) noexcept {
            *buffer.current_pos++ = c;
        }

    public:
        [[nodiscard]] inline std::expected<void, FMTResult> pushback(const TChar c, auto count) noexcept {
            SF_TRY(reserve(count))
            while (count-- > 0)
                pushback_force(c);
            return {};
        }

    private:
        template <typename... Rest>
        inline void pushback_seq_impl(const TChar c, const Rest... rest) noexcept {
            force_pushback(c);
            if constexpr (sizeof...(rest) > 0) pushback_seq_impl(rest...);
        }

    public:
        template <typename... CharToPush>
        [[nodiscard]] inline std::expected<void, FMTResult> pushback_seq(const CharToPush... ele) noexcept {
            SF_TRY(reserve(sizeof...(ele)))
            pushback_seq_impl(ele...);
            return {};
        }
    };
}  // namespace stream::fmt::buf
