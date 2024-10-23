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
        static const TChar* BufferInExecGlob_(BufferInfo<TChar>& bufferIn, BufferInfo<TChar>& glob)
        {
            if (BufferAccess(glob).IsEndOfString()) return bufferIn.CurrentPos;

            if (BufferAccess(bufferIn).IsEndOfString()) return nullptr;

            if (BufferTestAccess(glob).IsEqualTo('?'))
            {
                BufferManip(glob).Forward();
                BufferManip(bufferIn).Forward();
                return BufferInExecGlob_(bufferIn, glob);
            }
            else if (BufferTestAccess(glob).IsEqualTo('*'))
            {
                BufferManip(glob).Forward();
                const TChar* further = BufferInExecGlob_(bufferIn, glob);
                while (BufferAccess(bufferIn).CanMoveForward())
                {
                    BufferManip(bufferIn).Forward();
                    const TChar* last = BufferInExecGlob_(bufferIn, glob);
                    if (last > further || further == nullptr) further = last;
                }
                return further;
            }
            else if (BufferTestAccess(glob).IsEqualTo('['))
            {
                BufferManip(bufferIn).Forward();
                const TChar* begin = glob.CurrentPos;
                BufferTestManip(glob).GoToForward(']');
                const TChar* end = glob.CurrentPos;

                BufferInfoView<TChar> charSet(begin, end - begin);

                bool is_inverted = BufferTestManip(glob).IsEqualToForward('!');
                TChar toMatch = BufferManipException(bufferIn).GetAndForward();
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
                BufferManip(glob).Forward();
                BufferManip(bufferIn).Forward();
                return BufferInExecGlob_(bufferIn, glob);
            }
            return nullptr;
        }

    public:
        static void BufferInExecGlob(BufferInfo<TChar>& bufferIn, BufferInfo<TChar>& glob, [[maybe_unused]] PatternMatchType patternMatchtype = PatternMatchType::MatchBiggest)
        {
            const TChar* furtherPointMatched = BufferInExecGlob_(bufferIn, glob);
            if (furtherPointMatched != nullptr)
                bufferIn.CurrentPos = furtherPointMatched;
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
        BufferManipResult FastReadCharPtrGlobber(std::basic_string_view<TChar> globPattern, TChar* str, std::size_t sizeToCopy)
        {
            BufferInfo<TChar> globber(globPattern);
            const TChar* begin = Buffer.CurrentPos;
            Globber<TChar>::BufferInExecGlob(*this, globber);
            const TChar* end = Buffer.CurrentPos;

            BufferInfo<TChar> subContext(begin, end);
            return BufferReadManip(subContext).FastReadCharPtr(str, sizeToCopy);
        }

        BufferManipResult FastReadCharPtrRegex(std::basic_string_view<TChar> regexPattern, TChar* str, std::size_t sizeToCopy)
        {
            throw FMTImplError{};
        }
    };
}
