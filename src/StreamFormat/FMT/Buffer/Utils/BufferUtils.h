#pragma once

#include "StreamFormat/FMT/Buffer/BufferInfo.h"
#include "StreamFormat/FMT/Buffer/BufferOutManip.h"
#include "StreamFormat/FMT/Buffer/BufferTestManip.h"
#include "StreamFormat/FMT/Buffer/BufferWriteManip.h"
#include "StreamFormat/FMT/Buffer/BufferReadManip.h"

#include "StreamFormat/FMT/Buffer/BufferOutManager/DynamicBufferOutManager.h"
#include "StreamFormat/FMT/Buffer/BufferOutManager/GivenBufferOutManager.h"
#include "StreamFormat/FMT/Buffer/BufferOutManager/StaticBufferOutManager.h"

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    class BufferUtilsManip
    {
    public:
        constexpr inline BufferUtilsManip(BufferInfo<TChar>& buffer) noexcept : Buffer(buffer) {}
    public:
        BufferInfo<TChar>& Buffer;

        using TConstChar = std::remove_const_t<TChar>;
    
    public:
        template <std::size_t SIZE>
        [[nodiscard]] std::expected<std::size_t, FMTResult> GetWordFromList(const std::basic_string_view<TConstChar> (&data)[SIZE])
        {
            for (std::size_t idx = 0; idx < SIZE; ++idx)
            {
                bool found = SF_TRY(BufferTestManip(Buffer).IsSameForward(data[idx]));
                if (found) return idx;
            }
            return std::unexpected(FMTResult::Specifers_Invalid);
        }

        // TODO: use static map ?
        template <typename T>
        using DictPairs = std::pair<std::basic_string_view<TConstChar>, T>;
        
        template <typename T, std::size_t SIZE>
        [[nodiscard]] std::expected<T, FMTResult> GetWordFromDictPairs(const DictPairs<T> (&data)[SIZE])
        {
            for (std::size_t idx = 0; idx < SIZE; ++idx)
            {
                bool found = SF_TRY(BufferTestManip(Buffer).IsSameForward(data[idx].first));
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
        [[nodiscard]] static std::expected<void, FMTResult> ParseEscapedQuotedString(Detail::BufferInfo<CharIn>& buffer, Detail::BufferOutInfo<CharOut>& stringOut)
        {
            SF_TRY(Detail::BufferTestManip(buffer).SkipOneOf('"'));
            while (Detail::BufferAccess(buffer).IsEndOfString() == false)
            {
                auto view = SF_TRY(Detail::BufferTestManip(buffer).ViewUntil('"', '\\'));
                SF_TRY(Detail::BufferWriteManip(stringOut).FastWriteString(view));

                if (Detail::BufferTestAccess(buffer).IsEqualTo('"')) break;

                Detail::BufferTestManip(buffer).SkipOneOf('\\');
                switch (buffer.Get())
                {
                    // TODO : Do all others escape char
                    case '"':
                        SF_TRY(Detail::BufferOutManip(stringOut).Pushback('"'));
                        break;
                    case 't':
                        SF_TRY(Detail::BufferOutManip(stringOut).Pushback('\t'));
                        break;
                    case 'r':
                        SF_TRY(Detail::BufferOutManip(stringOut).Pushback('\r'));
                        break;
                    case 'n':
                        SF_TRY(Detail::BufferOutManip(stringOut).Pushback('\n'));
                        break;
                    default:
                        break;
                }
            }
            SF_TRY(Detail::BufferTestManip(buffer).SkipOneOf('"'));
        }

        template <typename CharIn, typename CharOut>
        [[nodiscard]] static std::expected<void, FMTResult> FormatEscapedQuotedString(Detail::BufferOutInfo<CharOut>& buffer, Detail::BufferInfo<CharIn>& stringIn)
        {
            SF_TRY(Detail::BufferOutManip(buffer).Pushback('"'));
            while (Detail::BufferAccess(stringIn).IsEndOfString() == false)
            {
                auto view = SF_TRY(Detail::BufferTestManip(stringIn).ViewUntil('\\'));
                SF_TRY(Detail::BufferWriteManip(buffer).FastWriteString(view));

                if (Detail::BufferAccess(stringIn).IsEndOfString()) break;

                SF_TRY(Detail::BufferTestManip(stringIn).SkipOneOf('\\'));
                switch (stringIn.Get())
                {
                    // TODO : Do all others escape char
                    case '"':
                        SF_TRY(Detail::BufferOutManip(buffer).Pushback('"'));
                        break;
                    case 't':
                        SF_TRY(Detail::BufferOutManip(buffer).Pushback('\t'));
                        break;
                    case 'r':
                        SF_TRY(Detail::BufferOutManip(buffer).Pushback('\r'));
                        break;
                    case 'n':
                        SF_TRY(Detail::BufferOutManip(buffer).Pushback('\n'));
                        break;
                    default:
                        break;
                }
            }
            SF_TRY(Detail::BufferOutManip(buffer).Pushback('"'));
        }
    };
}
