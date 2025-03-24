#pragma once

#include "stream/fmt/buf/stream.hxx"
#include "stream/fmt/buf/manip_io.hxx"
#include "stream/fmt/buf/test_manip.hxx"
#include "stream/fmt/buf/write_manip.hxx"
#include "stream/fmt/buf/read_manip.hxx"

#include "stream/fmt/buf/streamio_manager/dynamic_streamio_manager.hxx"
#include "stream/fmt/buf/streamio_manager/given_streamio_manager.hxx"
#include "stream/fmt/buf/streamio_manager/static_streamio_manager.hxx"

namespace stream::fmt::buf {
    template <typename TChar>
    class UtilsManip {
    public:
        constexpr inline UtilsManip(Stream<TChar>& buffer_) noexcept : buffer(buffer_) {}

    public:
        Stream<TChar>& buffer;

        using TConstChar = std::remove_const_t<TChar>;

    public:
        template <std::size_t SIZE>
        std::optional<std::size_t> get_word_from_list(const std::basic_string_view<TConstChar> (&data)[SIZE]) {
            for (std::size_t idx = 0; idx < SIZE; ++idx) {
                bool found = TestManip(buffer).is_same_forward(data[idx]);
                if (found) return idx;
            }
            return std::nullopt;
        }

        // TODO: use static map ?
        template <typename T>
        using DictPairs = std::pair<std::basic_string_view<TConstChar>, T>;

        template <typename T, std::size_t SIZE>
        T get_word_from_dict_pairs(const DictPairs<T> (&data)[SIZE]) {
            for (std::size_t idx = 0; idx < SIZE; ++idx) {
                bool found = TestManip(buffer).is_same_forward(data[idx].first);
                if (found) return data[idx].second;
            }
            throw std::runtime_error("fmt error: Specifiers_Invalid");
        }
    };

    namespace utils {
        template <typename CharIn, typename CharOut>
        static void parse_escaped_quoted_string(buf::Stream<CharIn>& buffer, buf::StreamIO<CharOut>& stringOut) {
            buf::TestManip(buffer).skip_one_of('"');
            while (buffer.is_end_of_string() == false) {
                auto view = buf::TestManip(buffer).view_until('"', '\\');
                buf::WriteManip(stringOut).fast_write_string(view);

                if (buf::TestAccess(buffer).is_equal_to('"')) {
                    break;
                }

                buf::TestManip(buffer).skip_one_of('\\');
                switch (buffer.get()) {
                    // TODO : Do all others escape char
                    case '"':
                        buf::ManipIO(stringOut).pushback('"');
                        break;
                    case 't':
                        buf::ManipIO(stringOut).pushback('\t');
                        break;
                    case 'r':
                        buf::ManipIO(stringOut).pushback('\r');
                        break;
                    case 'n':
                        buf::ManipIO(stringOut).pushback('\n');
                        break;
                    default:
                        break;
                }
            }
            buf::TestManip(buffer).skip_one_of('"');
        }

        template <typename CharIn, typename CharOut>
        static void format_escaped_quoted_string(buf::StreamIO<CharOut>& buffer, buf::Stream<CharIn>& string_in) {
            buf::ManipIO(buffer).pushback('"');
            while (string_in.is_end_of_string() == false) {
                auto view = buf::TestManip(string_in).view_until('\\');
                buf::WriteManip(buffer).fast_write_string(view);

                if (string_in.is_end_of_string()) break;

                // TODO
                buf::TestManip(string_in).skip_one_of('\\');
                switch (string_in.get()) {
                    // TODO : Do all others escape char
                    case '"':
                        buf::ManipIO(buffer).pushback('"');
                        break;
                    case 't':
                        buf::ManipIO(buffer).pushback('\t');
                        break;
                    case 'r':
                        buf::ManipIO(buffer).pushback('\r');
                        break;
                    case 'n':
                        buf::ManipIO(buffer).pushback('\n');
                        break;
                    default:
                        break;
                }
            }
            buf::ManipIO(buffer).pushback('"');
        }
    };  // namespace utils
}  // namespace stream::fmt::buf
