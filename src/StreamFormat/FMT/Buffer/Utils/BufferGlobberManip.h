#pragma once

#include "StreamFormat/FMT/Buffer/BufferInfo.h"
#include "StreamFormat/FMT/Buffer/BufferManip.h"

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    class Globber
    {
    public:
        enum class PatternMatchType
        {
            MatchBiggest,
            MatchSmallest
        };

    private:
        [[nodiscard]] static std::expected<const TChar*, FMTResult> BufferInExecGlob_(BufferInfo<TChar>& bufferIn, BufferInfo<TChar>& glob)
        {
            if (BufferAccess(glob).IsEndOfString()) { return bufferIn.CurrentPos; }

            if (BufferAccess(bufferIn).IsEndOfString()) { return nullptr; }

            if (BufferTestAccess(glob).IsEqualTo('?'))
            {
                SF_TRY(BufferManip(glob).Forward());
                SF_TRY(BufferManip(bufferIn).Forward());
                return BufferInExecGlob_(bufferIn, glob);
            }
            else if (BufferTestAccess(glob).IsEqualTo('*'))
            {
                SF_TRY(BufferManip(glob).Forward());
                const TChar* further = SF_TRY(BufferInExecGlob_(bufferIn, glob));
                while (BufferAccess(bufferIn).CanMoveForward())
                {
                    SF_TRY(BufferManip(bufferIn).Forward());
                    const TChar* last = SF_TRY(BufferInExecGlob_(bufferIn, glob));
                    if (last > further || further == nullptr) further = last;
                }
                return further;
            }
            else if (BufferTestAccess(glob).IsEqualTo('['))
            {
                SF_TRY(BufferManip(bufferIn).Forward());
                const TChar* begin = glob.CurrentPos;
                SF_TRY(BufferTestManip(glob).GoToForward(']'));
                const TChar* end = glob.CurrentPos;

                BufferInfoView<TChar> charSet(begin, end - begin);

                bool is_inverted = SF_TRY(BufferTestManip(glob).IsEqualToForward('!'));
                TChar toMatch = SF_TRY(BufferManip(bufferIn).GetAndForward());
                bool found = false;

                while (found == false && BufferAccess(charSet).CanMoveForward())
                {
                    if (BufferTestAccess(charSet).IsEqualTo(toMatch))
                    {
                        found = true;
                        break;
                    }

                    if (BufferTestAccess(charSet).IsEqualTo('-'))
                    {
                        TChar beginSubSet = BufferAccess(charSet).GetPrevForce();
                        TChar endSubSet = BufferAccess(charSet).GetNextForce();
                        if (toMatch >= beginSubSet && toMatch <= endSubSet)
                        {
                            found = true;
                            break;
                        }
                    }

                    BufferManip(charSet).Forward();
                }

                if (found && is_inverted == false)
                    return BufferInExecGlob_(bufferIn, glob);
                else if (found == false && is_inverted == true)
                    return BufferInExecGlob_(bufferIn, glob);
                return nullptr;
            }

            if (bufferIn.Get() == glob.Get())
            {
                SF_TRY(BufferManip(glob).Forward());
                SF_TRY(BufferManip(bufferIn).Forward());
                return BufferInExecGlob_(bufferIn, glob);
            }
            return nullptr;
        }

    public:
        [[nodiscard]] static std::expected<void, FMTResult> BufferInExecGlob(BufferInfo<TChar>& bufferIn, BufferInfo<TChar>& glob, [[maybe_unused]] PatternMatchType patternMatchtype = PatternMatchType::MatchBiggest)
        {
            const TChar* furtherPointMatched = SF_TRY(BufferInExecGlob_(bufferIn, glob));
            if (furtherPointMatched != nullptr)
                bufferIn.CurrentPos = furtherPointMatched;
            return {};
        }
    };

    template <typename TChar>
    class BufferGlobberManip
    {
    public:
        constexpr inline BufferGlobberManip(BufferInfo<TChar>& buffer) noexcept : Buffer(buffer) {}
    public:
        BufferInfo<TChar>& Buffer;
    
    public:
        [[nodiscard]] std::expected<void, FMTResult> FastReadCharPtrGlobber(std::basic_string_view<TChar> globPattern, TChar* str, std::size_t sizeToCopy)
        {
            BufferInfo<TChar> globber(globPattern);
            const TChar* begin = Buffer.CurrentPos;
            Globber<TChar>::BufferInExecGlob(*this, globber);
            const TChar* end = Buffer.CurrentPos;

            BufferInfo<TChar> subContext(begin, end);
            return BufferReadManip(subContext).FastReadCharPtr(str, sizeToCopy);
        }

        [[nodiscard]] std::expected<void, FMTResult> FastReadCharPtrRegex(std::basic_string_view<TChar> regexPattern, TChar* str, std::size_t sizeToCopy)
        {
            return std::unexpected(FMTResult::FunctionNotImpl);
        }
    };
}
