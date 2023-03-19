#pragma once

#include "ProjectCore/FMT/Detail/Buffer/BasicBufferIn/BasicBufferIn.h"

namespace ProjectCore::FMT::Detail
{
    template <typename CharBuffer, typename CharPattern>
    class Globber
    {
    public:
        using BufferInType = BasicBufferIn<CharBuffer>;
        using PatternType = BasicBufferIn<CharBuffer>;

    public:
        enum class PatternMatchType
        {
            MatchBiggest,
            MatchSmallest
        };

    private:
        static const CharBuffer* BufferInExecGlob_(BufferInType bufferIn, PatternType glob)
        {
            if (glob.IsEnd())
                return bufferIn.GetBufferCurrentPos();

            if (bufferIn.IsEnd())
                return nullptr;

            if (glob.IsEqualTo('?'))
            {
                glob.Forward();
                bufferIn.Forward();
                return BufferInExecGlob_(bufferIn, glob);
            }
            else if (glob.IsEqualTo('*'))
            {
                glob.Forward();
                const CharBuffer* further = BufferInExecGlob_(bufferIn, glob);
                while (bufferIn.CanMoveForward())
                {
                    bufferIn.Forward();
                    const CharBuffer* last = BufferInExecGlob_(bufferIn, glob);
                    if (last > further || further == nullptr)
                        further = last;
                } 
                return further;
            }
            else if (glob.IsEqualTo('['))
            {
                glob.Forward();
                const CharPattern* begin = glob.GetBufferCurrentPos();
                glob.GoToForward(']');
                const CharPattern* end = glob.GetBufferCurrentPos();

                PatternType charSet(begin, end); 

                bool is_inverted = glob.IsEqualToForward('!');
                CharBuffer toMatch = bufferIn.GetAndForward();
                bool found = false;

                while (found == false && charSet.CanMoveForward())
                {
                    if (charSet.IsEqualTo(toMatch))
                    {
                        found = true;
                        break;
                    }

                    if (charSet.IsEqualTo('-'))
                    {
                        CharPattern beginSubSet = charSet.GetPrev();
                        CharPattern endSubSet = charSet.GetNext();
                        if (toMatch >= beginSubSet && toMatch <= endSubSet)
                        {
                            found = true;
                            break;
                        }
                    }

                    charSet.Forward();
                }

                if (found && is_inverted == false)
                    return BufferInExecGlob_(bufferIn, glob);
                else if (found == false && is_inverted == true)
                    return BufferInExecGlob_(bufferIn, glob);
                return nullptr;
            }

            if (bufferIn.Get() == glob.Get())
            {
				glob.Forward();
				bufferIn.Forward();
                return BufferInExecGlob_(bufferIn, glob);
            }
            return nullptr;
        }

    public:
        static void BufferInExecGlob(BufferInType& bufferIn, PatternType glob, PatternMatchType patternMatchtype = PatternMatchType::MatchBiggest)
        {
            const CharBuffer* furtherPointMatched = BufferInExecGlob_(bufferIn, glob);
            if (furtherPointMatched != nullptr)
                bufferIn.SetBufferCurrentPos(furtherPointMatched);
        }
    };
}
