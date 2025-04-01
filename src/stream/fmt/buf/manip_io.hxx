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
            buffer.manager.compute_generated_size(buffer.get_buffer_current_size());
        }

    public:
        bool add_size(const std::size_t count) noexcept {
            std::size_t currentSize = buffer.get_buffer_current_size();
            if (buffer.manager.add_size(count) == false) return false;
            Manip(buffer).reload(buffer.manager.get_buffer(), buffer.manager.get_buffer_size());
            buffer.current_pos = buffer.manager.get_buffer() + currentSize;
            return true;
        }

        inline bool reserve(const std::size_t count = 1) noexcept {
            if (buffer.current_pos + count <= buffer.buffer_end) return true;
            return add_size(count);
        }

        void forward(const std::size_t count = 1) {
            if (reserve(count) == false) throw std::bad_alloc();
            buffer.current_pos += count;
        }

    public:
        inline void set(const TChar c) noexcept {
            *buffer.current_pos = c;
        }

        void pushback(const TChar c) {
            if (reserve(1) == false) throw std::bad_alloc();
            *buffer.current_pos++ = c;
        }
        inline void pushback_force(const TChar c) noexcept {
            *buffer.current_pos++ = c;
        }

    public:
        void pushback(const TChar c, auto count) {
            if (reserve(count) == false) throw std::bad_alloc();
            while (count-- > 0)
                pushback_force(c);
        }

    private:
        template <typename... Rest>
        inline void pushback_seq_impl(const TChar c, const Rest... rest) noexcept {
            force_pushback(c);
            if constexpr (sizeof...(rest) > 0) pushback_seq_impl(rest...);
        }

    public:
        template <typename... CharToPush>
        void pushback_seq(const CharToPush... ele) {
            if (reserve(sizeof...(ele)) == false) throw std::bad_alloc();
            pushback_seq_impl(ele...);
        }
    };
}  // namespace stream::fmt::buf
