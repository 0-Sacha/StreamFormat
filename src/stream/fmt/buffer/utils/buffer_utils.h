#pragma once

#include "stream/fmt/buffer/buffer_info.h"
#include "stream/fmt/buffer/buffer_out_manip.h"
#include "stream/fmt/buffer/buffer_test_manip.h"
#include "stream/fmt/buffer/buffer_write_manip.h"
#include "stream/fmt/buffer/buffer_read_manip.h"

#include "stream/fmt/buffer/buffer_out_manager/dynamic_buffer_out_manager.h"
#include "stream/fmt/buffer/buffer_out_manager/given_buffer_out_manager.h"
#include "stream/fmt/buffer/buffer_out_manager/static_buffer_out_manager.h"

namespace stream::fmt::detail
{
    template <typename TChar>
    class BufferUtilsManip
    {
    public:
        constexpr inline BufferUtilsManip(BufferInfo<TChar>& buffer_) noexcept : buffer(buffer_) {}
    public:
        BufferInfo<TChar>& buffer;

        using TConstChar = std::remove_const_t<TChar>;
    
    public:
        template <std::size_t SIZE>
        [[nodiscard]] std::expected<std::size_t, FMTResult> get_word_from_list(const std::basic_string_view<TConstChar> (&data)[SIZE])
        {
            for (std::size_t idx = 0; idx < SIZE; ++idx)
            {
                bool found = SF_TRY(BufferTestManip(buffer).is_same_forward(data[idx]));
                if (found) return idx;
            }
            return std::unexpected(FMTResult::Specifers_Invalid);
        }

        // TODO: use static map ?
        template <typename T>
        using DictPairs = std::pair<std::basic_string_view<TConstChar>, T>;
        
        template <typename T, std::size_t SIZE>
        [[nodiscard]] std::expected<T, FMTResult> get_word_from_dict_pairs(const DictPairs<T> (&data)[SIZE])
        {
            for (std::size_t idx = 0; idx < SIZE; ++idx)
            {
                bool found = SF_TRY(BufferTestManip(buffer).is_same_forward(data[idx].first));
                if (found)
                    return data[idx].second;
            }
            return std::unexpected(FMTResult::Specifers_Invalid);
        }
    };

    class BufferUtils
    {
    public:
        template <typename CharIn, typename CharOut>
        [[nodiscard]] static std::expected<void, FMTResult> parse_escaped_quoted_string(detail::BufferInfo<CharIn>& buffer, detail::BufferOutInfo<CharOut>& stringOut)
        {
            SF_TRY(detail::BufferTestManip(buffer).SkipOneOf('"'));
            while (detail::BufferAccess(buffer).IsEndOfString() == false)
            {
                auto view = SF_TRY(detail::BufferTestManip(buffer).ViewUntil('"', '\\'));
                SF_TRY(detail::BufferWriteManip(stringOut).FastWriteString(view));

                if (detail::BufferTestAccess(buffer).IsEqualTo('"'))
                    { break; }

                SF_TRY(detail::BufferTestManip(buffer).SkipOneOf('\\'));
                switch (buffer.Get())
                {
                    // TODO : Do all others escape char
                    case '"':
                        SF_TRY(detail::BufferOutManip(stringOut).Pushback('"'));
                        break;
                    case 't':
                        SF_TRY(detail::BufferOutManip(stringOut).Pushback('\t'));
                        break;
                    case 'r':
                        SF_TRY(detail::BufferOutManip(stringOut).Pushback('\r'));
                        break;
                    case 'n':
                        SF_TRY(detail::BufferOutManip(stringOut).Pushback('\n'));
                        break;
                    default:
                        break;
                }
            }
            SF_TRY(detail::BufferTestManip(buffer).SkipOneOf('"'));

            return {};
        }

        template <typename CharIn, typename CharOut>
        [[nodiscard]] static std::expected<void, FMTResult> FormatEscapedQuotedString(detail::BufferOutInfo<CharOut>& buffer, detail::BufferInfo<CharIn>& stringIn)
        {
            SF_TRY(detail::BufferOutManip(buffer).Pushback('"'));
            while (detail::BufferAccess(stringIn).IsEndOfString() == false)
            {
                auto view = SF_TRY(detail::BufferTestManip(stringIn).ViewUntil('\\'));
                SF_TRY(detail::BufferWriteManip(buffer).FastWriteString(view));

                if (detail::BufferAccess(stringIn).IsEndOfString()) break;

                // TODO
                SF_TRY(detail::BufferTestManip(stringIn).SkipOneOf('\\'));
                switch (stringIn.Get())
                {
                    // TODO : Do all others escape char
                    case '"':
                        SF_TRY(detail::BufferOutManip(buffer).Pushback('"'));
                        break;
                    case 't':
                        SF_TRY(detail::BufferOutManip(buffer).Pushback('\t'));
                        break;
                    case 'r':
                        SF_TRY(detail::BufferOutManip(buffer).Pushback('\r'));
                        break;
                    case 'n':
                        SF_TRY(detail::BufferOutManip(buffer).Pushback('\n'));
                        break;
                    default:
                        break;
                }
            }
            SF_TRY(detail::BufferOutManip(buffer).Pushback('"'));

            return {};
        }
    };
}
