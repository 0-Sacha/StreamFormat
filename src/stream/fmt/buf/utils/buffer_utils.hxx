#pragma once

#include "stream/fmt/buf/stream.h"
#include "stream/fmt/buf/manip_io.h"
#include "stream/fmt/buf/test_manip.h"
#include "stream/fmt/buf/write_manip.h"
#include "stream/fmt/buf/read_manip.h"

#include "stream/fmt/buf/streamio_manager/dynamic_streamio_manager.h"
#include "stream/fmt/buf/streamio_manager/given_streamio_manager.h"
#include "stream/fmt/buf/streamio_manager/static_streamio_manager.h"

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
        [[nodiscard]] std::expected<std::size_t, FMTResult> get_word_from_list(const std::basic_string_view<TConstChar> (&data)[SIZE]) {
            for (std::size_t idx = 0; idx < SIZE; ++idx) {
                bool found = SF_TRY(TestManip(buffer).is_same_forward(data[idx]));
                if (found) return idx;
            }
            return std::unexpected(FMTResult::Specifiers_Invalid);
        }

        // TODO: use static map ?
        template <typename T>
        using DictPairs = std::pair<std::basic_string_view<TConstChar>, T>;

        template <typename T, std::size_t SIZE>
        [[nodiscard]] std::expected<T, FMTResult> get_word_from_dict_pairs(const DictPairs<T> (&data)[SIZE]) {
            for (std::size_t idx = 0; idx < SIZE; ++idx) {
                bool found = SF_TRY(TestManip(buffer).is_same_forward(data[idx].first));
                if (found) return data[idx].second;
            }
            return std::unexpected(FMTResult::Specifiers_Invalid);
        }
    };

    namespace utils {
        template <typename CharIn, typename CharOut>
        [[nodiscard]] static std::expected<void, FMTResult> parse_escaped_quoted_string(buf::Stream<CharIn>& buffer, buf::StreamIO<CharOut>& stringOut) {
            SF_TRY(buf::TestManip(buffer).skip_one_of('"'));
            while (buf::Access(buffer).is_end_of_string() == false) {
                auto view = SF_TRY(buf::TestManip(buffer).view_until('"', '\\'));
                SF_TRY(buf::WriteManip(stringOut).fast_write_string(view));

                if (buf::TestAccess(buffer).is_equal_to('"')) {
                    break;
                }

                SF_TRY(buf::TestManip(buffer).skip_one_of('\\'));
                switch (buffer.get()) {
                    // TODO : Do all others escape char
                    case '"':
                        SF_TRY(buf::ManipIO(stringOut).pushback('"'));
                        break;
                    case 't':
                        SF_TRY(buf::ManipIO(stringOut).pushback('\t'));
                        break;
                    case 'r':
                        SF_TRY(buf::ManipIO(stringOut).pushback('\r'));
                        break;
                    case 'n':
                        SF_TRY(buf::ManipIO(stringOut).pushback('\n'));
                        break;
                    default:
                        break;
                }
            }
            SF_TRY(buf::TestManip(buffer).skip_one_of('"'));

            return {};
        }

        template <typename CharIn, typename CharOut>
        [[nodiscard]] static std::expected<void, FMTResult> format_escaped_quoted_string(buf::StreamIO<CharOut>& buffer, buf::Stream<CharIn>& string_in) {
            SF_TRY(buf::ManipIO(buffer).pushback('"'));
            while (buf::Access(string_in).is_end_of_string() == false) {
                auto view = SF_TRY(buf::TestManip(string_in).view_until('\\'));
                SF_TRY(buf::WriteManip(buffer).fast_write_string(view));

                if (buf::Access(string_in).is_end_of_string()) break;

                // TODO
                SF_TRY(buf::TestManip(string_in).skip_one_of('\\'));
                switch (string_in.get()) {
                    // TODO : Do all others escape char
                    case '"':
                        SF_TRY(buf::ManipIO(buffer).pushback('"'));
                        break;
                    case 't':
                        SF_TRY(buf::ManipIO(buffer).pushback('\t'));
                        break;
                    case 'r':
                        SF_TRY(buf::ManipIO(buffer).pushback('\r'));
                        break;
                    case 'n':
                        SF_TRY(buf::ManipIO(buffer).pushback('\n'));
                        break;
                    default:
                        break;
                }
            }
            SF_TRY(buf::ManipIO(buffer).pushback('"'));

            return {};
        }
    };  // namespace utils
}  // namespace stream::fmt::buf
