#pragma once

#include "stream.hxx"

namespace stream::fmt::buf {
    template <typename TChar>
    class Access {
    public:
        constexpr inline Access(const Stream<TChar>& buffer) noexcept : buffer(buffer) {}

    public:
        const Stream<TChar>& buffer;

    public:
        constexpr inline bool can_move_forward(const std::size_t count = 1) const noexcept {
            return buffer.current_pos + count <= buffer.buffer_end;
        }
        constexpr inline bool can_move_backward(const std::size_t count = 1) const noexcept {
            return buffer.current_pos - count >= buffer.buffer;
        }

        constexpr inline std::remove_cv_t<TChar> get_next(const std::size_t count = 1) const {
            if (Access(buffer).can_move_forward(count) == false) throw std::runtime_error("fmt error: Buffer_OutOfBoundAccess");
            return get_next_force(count);
        }
        constexpr inline std::remove_cv_t<TChar> get_prev(const std::size_t count = 1) const {
            if (Access(buffer).can_move_backward(count) == false) throw std::runtime_error("fmt error: Buffer_OutOfBoundAccess");
            return get_prev_force(count);
        }
        constexpr inline TChar get_next_force(const std::size_t count = 1) const noexcept {
            return *(buffer.current_pos + count);
        }
        constexpr inline TChar get_prev_force(const std::size_t count = 1) const noexcept {
            return *(buffer.current_pos - count);
        }
    };

    template <typename TChar>
    class Manip {
    public:
        constexpr inline Manip(Stream<TChar>& buffer) noexcept : buffer(buffer) {}

    public:
        Stream<TChar>& buffer;

    public:
        constexpr inline void reload(TChar* const buffer_, const std::size_t size_) noexcept {
            buffer.buffer      = buffer_;
            buffer.current_pos = buffer_;
            buffer.buffer_end  = buffer_ + size_;
        }
        constexpr inline void reload(std::basic_string_view<TChar> sv) noexcept {
            buffer.buffer      = sv.data();
            buffer.current_pos = sv.data();
            buffer.buffer_end  = sv.data() + sv.size();
        }

        constexpr inline void reload(Stream<TChar>& buffer_) noexcept {
            buffer.buffer      = buffer_.buffer;
            buffer.current_pos = buffer_.current_pos;
            buffer.buffer_end  = buffer_.buffer_end;
        }

        Access<TChar> access() {
            return Access(buffer);
        }

    public:
        constexpr inline void forward_force(const std::size_t count = 1) noexcept {
            buffer.current_pos += count;
        }
        constexpr inline void forward(const std::size_t count = 1) {
            if (!access().can_move_forward(count)) throw std::runtime_error("fmt error: Buffer_OutOfBoundAccess");
            buffer.current_pos += count;
        }

        constexpr inline void backward_force(const std::size_t count = 1) noexcept {
            buffer.current_pos -= count;
        }
        constexpr inline void backward(const std::size_t count = 1) {
            if (!access().can_move_backward(count)) throw std::runtime_error("fmt error: Buffer_OutOfBoundAccess");
            buffer.current_pos -= count;
        }

        constexpr inline std::remove_cv_t<TChar> get_and_forward() {
            if (Access(buffer).can_move_forward(1) == false) throw std::runtime_error("fmt error: Buffer_OutOfBoundAccess");
            return *buffer.current_pos++;
        }
        constexpr inline std::remove_cv_t<TChar> get_and_backward() {
            if (Access(buffer).can_move_backward(1) == false) throw std::runtime_error("fmt error: Buffer_OutOfBoundAccess");
            return *buffer.current_pos--;
        }
    };
}  // namespace stream::fmt::buf
