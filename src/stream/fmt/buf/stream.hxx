#pragma once

#include "stream/fmt/detail/prelude.hxx"

namespace stream::fmt::buf {
    template <typename CharType>
    class Stream {
    public:
        using TChar = CharType;

    public:
        TChar* buffer;
        TChar* current_pos;
        TChar* buffer_end;  // Not included

    public:
        Stream() noexcept : buffer(nullptr), current_pos(nullptr), buffer_end(nullptr) {}
        Stream(TChar* const buffer_, const std::size_t size_) noexcept : buffer(buffer_), current_pos(buffer_), buffer_end(buffer_ + size_) {}

    public:
        constexpr inline TChar get() const {
            return *current_pos;
        }

    public:
        constexpr inline std::size_t get_buffer_total_size() const noexcept {
            return static_cast<std::size_t>(buffer_end - buffer);
        }
        constexpr inline std::size_t get_buffer_current_size() const noexcept {
            return static_cast<std::size_t>(current_pos - buffer);
        }
        constexpr inline std::size_t get_buffer_remaining_size() const noexcept {
            return static_cast<std::size_t>(buffer_end - current_pos);
        }

        constexpr inline bool is_out_of_bound() const noexcept {
            return current_pos < buffer || current_pos >= buffer_end;
        }
        constexpr inline bool is_empty() const noexcept {
            return current_pos >= buffer_end;
        }
        constexpr inline bool is_end_of_string() const noexcept {
            return is_empty() || get() == 0;
        }
    };

    template <typename CharType>
    class StreamView : public Stream<const CharType> {
    public:
        using typename Stream<const CharType>::TChar;

        using Stream<const CharType>::buffer;
        using Stream<const CharType>::current_pos;
        using Stream<const CharType>::buffer_end;

        using Stream<const CharType>::get;
        using Stream<const CharType>::get_buffer_total_size;
        using Stream<const CharType>::get_buffer_current_size;
        using Stream<const CharType>::get_buffer_remaining_size;
        using Stream<const CharType>::is_out_of_bound;
        using Stream<const CharType>::is_empty;
        using Stream<const CharType>::is_end_of_string;

    public:
        StreamView() noexcept : Stream<const CharType>() {}

        template <size_t SIZE>
        StreamView(const CharType (&data)[SIZE]) noexcept : Stream<const CharType>(data, SIZE) {
            while (buffer_end - 1 > buffer && *(buffer_end - 1) == 0)
                --buffer_end;
        }

        StreamView(std::basic_string_view<CharType> sv) noexcept : Stream<const CharType>(sv.data(), sv.size()) {}

        StreamView(const CharType* const buffer, const std::size_t size) noexcept : Stream<const CharType>(buffer, size) {}

    public:
        operator Stream<const CharType>() const {
            return Stream<const CharType>{.buffer = buffer, .current_pos = current_pos, .buffer_end = buffer_end};
        }
    };

    template <typename T>
    concept convertible_to_buffer_info = requires(T&& t) { Stream(std::forward<T>(t)); };

    template <typename T>
    concept convertible_to_buffer_info_view = requires(T&& t) { StreamView(std::forward<T>(t)); };
}  // namespace stream::fmt::buf
