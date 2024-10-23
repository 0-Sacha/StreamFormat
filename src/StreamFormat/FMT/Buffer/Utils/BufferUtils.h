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
        static constexpr std::size_t GET_WORD_FROM_LIST_NOT_FOUND = (std::numeric_limits<std::size_t>::max)();
        
        template <std::size_t SIZE>
        std::size_t GetWordFromList(const std::basic_string_view<TConstChar> (&data)[SIZE], const std::size_t defaultValue = GET_WORD_FROM_LIST_NOT_FOUND)
        {
            for (std::size_t idx = 0; idx < SIZE; ++idx)
                if (BufferTestManip(Buffer).IsSameForward(data[idx])) return idx;
            return defaultValue;
        }

        // TODO: use static map ?
        template <typename T>
        using DictPairs = std::pair<std::basic_string_view<TConstChar>, T>;
        
        template <typename T, std::size_t SIZE>
        T GetWordFromDictPairs(const DictPairs<T> (&data)[SIZE], std::convertible_to<T> auto defaultValue = T{})
        {
            for (std::size_t idx = 0; idx < SIZE; ++idx)
                if (BufferTestManip(Buffer).IsSameForward(data[idx].first)) return data[idx].second;
            return defaultValue;
        }
    };

    class BufferUtils
    {
    public:
        template <typename CharIn, typename CharOut>
        static void ParseEscapedQuotedString(Detail::BufferInfo<CharIn>& buffer, Detail::BufferOutInfo<CharOut>& stringOut)
        {
            Detail::BufferTestManip(buffer).Skip('"');
            while (Detail::BufferAccess(buffer).IsEndOfString() == false)
            {
                Detail::BufferWriteManip(stringOut).FastWriteString(
                    Detail::BufferTestManip(buffer).ViewUntil('"', '\\')
                );

                if (Detail::BufferTestAccess(buffer).IsEqualTo('"')) break;

                Detail::BufferTestManip(buffer).Skip('\\');
                switch (buffer.Get())
                {
                    // TODO : Do all others escape char
                    case '"':
                        Detail::BufferOutManip(stringOut).Pushback('"');
                        break;
                    case 't':
                        Detail::BufferOutManip(stringOut).Pushback('\t');
                        break;
                    case 'r':
                        Detail::BufferOutManip(stringOut).Pushback('\r');
                        break;
                    case 'n':
                        Detail::BufferOutManip(stringOut).Pushback('\n');
                        break;
                    default:
                        break;
                }
            }
            Detail::BufferTestManip(buffer).Skip('"');
        }

        template <typename CharIn, typename CharOut>
        static void FormatEscapedQuotedString(Detail::BufferOutInfo<CharOut>& buffer, Detail::BufferInfo<CharIn>& stringIn)
        {
            Detail::BufferOutManip(buffer).Pushback('"');
            while (Detail::BufferAccess(stringIn).IsEndOfString() == false)
            {
                Detail::BufferWriteManip(buffer).FastWriteString(
                    Detail::BufferTestManip(stringIn).ViewUntil('\\')
                );

                if (Detail::BufferAccess(stringIn).IsEndOfString()) break;

                Detail::BufferTestManip(stringIn).Skip('\\');
                switch (stringIn.Get())
                {
                    // TODO : Do all others escape char
                    case '"':
                        Detail::BufferOutManip(buffer).Pushback('"');
                        break;
                    case 't':
                        Detail::BufferOutManip(buffer).Pushback('\t');
                        break;
                    case 'r':
                        Detail::BufferOutManip(buffer).Pushback('\r');
                        break;
                    case 'n':
                        Detail::BufferOutManip(buffer).Pushback('\n');
                        break;
                    default:
                        break;
                }
            }
            Detail::BufferOutManip(buffer).Pushback('"');
        }
    };
}
