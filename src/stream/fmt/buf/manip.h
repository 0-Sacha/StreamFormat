#pragma once

#include "stream.h"

namespace stream::fmt::buf
{
    template <typename TChar>
    class Access
    {
    public:
        constexpr inline Access(const Stream<TChar>& buffer) noexcept : buffer(buffer) {}
    public:
        const Stream<TChar>& buffer;
        
    public:
        constexpr inline std::size_t get_buffer_total_size() const noexcept { return static_cast<std::size_t>(buffer.buffer_end - buffer.buffer); }
        constexpr inline std::size_t get_buffer_current_size() const noexcept { return static_cast<std::size_t>(buffer.current_pos - buffer.buffer); }
        constexpr inline std::size_t get_buffer_remaining_size() const noexcept { return static_cast<std::size_t>(buffer.buffer_end - buffer.current_pos); }

    public:
        constexpr inline bool can_move_forward(const std::size_t count = 1) const noexcept { return buffer.current_pos + count <= buffer.buffer_end; }
        constexpr inline bool can_move_backward(const std::size_t count = 1) const noexcept { return buffer.current_pos - count >= buffer.buffer; }

        constexpr inline bool is_out_of_bound() const noexcept { return buffer.current_pos < buffer.buffer || buffer.current_pos >= buffer.buffer_end; }
        constexpr inline bool is_empty() const noexcept { return buffer.current_pos >= buffer.buffer_end; }
        constexpr inline bool is_end_of_string() const noexcept { return is_empty() || buffer.get() == 0; }

        [[nodiscard]] constexpr inline std::expected<std::remove_cv_t<TChar>, FMTResult> get_next(const std::size_t count = 1) const
        {
            if (Access(buffer).can_move_forward(count) == false)
                return std::unexpected(FMTResult::Buffer_OutOfBoundAccess);
            return Manip(buffer).get_next_force(count);
        }
        [[nodiscard]] constexpr inline std::expected<std::remove_cv_t<TChar>, FMTResult> get_prev(const std::size_t count = 1) const
        {
            if (Access(buffer).can_move_backward(count) == false)
                return std::unexpected(FMTResult::Buffer_OutOfBoundAccess);
            return Manip(buffer).get_prev_force(count);
        }
        constexpr inline TChar get_next_force(const std::size_t count = 1) const noexcept { return *(buffer.current_pos + count); }
        constexpr inline TChar get_prev_force(const std::size_t count = 1) const noexcept { return *(buffer.current_pos - count); }
    };

    template <typename TChar>
    class Manip
    {
    public:
        constexpr inline Manip(Stream<TChar>& buffer) noexcept : buffer(buffer) {}
    public:
        Stream<TChar>& buffer;
        
    public:
        constexpr inline void reload(TChar* const buffer_, const std::size_t size_) noexcept
        {
            buffer.buffer      = buffer_;
            buffer.current_pos = buffer_;
            buffer.buffer_end  = buffer_ + size_;
        }

        constexpr inline void reload(Stream<TChar>& buffer_) noexcept
        {
            buffer.buffer      = buffer_.buffer;
            buffer.current_pos = buffer_.current_pos;
            buffer.buffer_end  = buffer_.buffer_end;
        }

        Access<TChar> access() { return Access(buffer); }

    public:
        constexpr inline void forward_force(const std::size_t count = 1) noexcept { buffer.current_pos += count; }
        [[nodiscard]] constexpr inline std::expected<void, FMTResult> forward(const std::size_t count = 1) noexcept
        {
            if (!access().can_move_forward(count))
                return std::unexpected(FMTResult::Buffer_OutOfBoundAccess);
            buffer.current_pos += count;
            return {};
        }

        constexpr inline void backward_force(const std::size_t count = 1) noexcept { buffer.current_pos -= count; }
        [[nodiscard]] constexpr inline std::expected<void, FMTResult> backward(const std::size_t count = 1) noexcept
        {
            if (!access().can_move_backward(count))
                return std::unexpected(FMTResult::Buffer_OutOfBoundAccess);
            buffer.current_pos -= count;
            return {};
        }

        [[nodiscard]] constexpr inline std::expected<std::remove_cv_t<TChar>, FMTResult> get_and_forward()
        {
            if (Access(buffer).can_move_forward(1) == false)
                return std::unexpected(FMTResult::Buffer_OutOfBoundAccess);
            return *buffer.current_pos++;
        }
        [[nodiscard]] constexpr inline std::expected<std::remove_cv_t<TChar>, FMTResult> get_and_backward()
        {
            if (Access(buffer).can_move_backward(1) == false)
                return std::unexpected(FMTResult::Buffer_OutOfBoundAccess);
            return *buffer.current_pos--;
        }
    };
}
