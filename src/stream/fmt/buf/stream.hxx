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
        constexpr inline TChar get() const {
            return *current_pos;
        }

    public:
        Stream() noexcept : buffer(nullptr), current_pos(nullptr), buffer_end(nullptr) {}

        Stream(TChar* const buffer_, const std::size_t size_) noexcept : buffer(buffer_), current_pos(buffer_), buffer_end(buffer_ + size_) {}
    };

    template <typename CharType>
    class StreamView : public Stream<const CharType> {
    public:
        using typename Stream<const CharType>::TChar;

        using Stream<const CharType>::buffer;
        using Stream<const CharType>::current_pos;
        using Stream<const CharType>::buffer_end;

        using Stream<const CharType>::get;

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
