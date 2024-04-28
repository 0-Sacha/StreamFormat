#pragma once

#include "BasicBufferIn.h"
#include "ProjectCore/FMT/Buffer/Utils/PatternMatching/Glob/Glob.h"

namespace ProjectCore::FMT::Detail
{
    template<typename CharBuffer>
    template<typename CharPtr>
    bool BasicBufferIn<CharBuffer>::FastReadCharPtr(CharPtr* str, std::size_t sizeToCopy, bool isZeroEnded)
    {
        if (CanMoveForward(sizeToCopy) == false)
            return FastReadCharPtr(str, GetBufferRemainingSize(), isZeroEnded);

        // TODO : Opti with bigger types
        while (sizeToCopy-- != 0)
            *str++ = GetAndForward();
        if (isZeroEnded)
            *str = 0;

        return true;
    }

    template<typename CharBuffer>
    template<typename CharPtr, typename CharPattern>
    bool BasicBufferIn<CharBuffer>::FastReadCharPtrGlobber(std::basic_string_view<CharPattern> globPattern, CharPtr* str, std::size_t sizeToCopy, [[maybe_unused]] bool isZeroEnded)
    {
        BasicBufferIn<CharPattern> globber(globPattern);
        const CharBuffer* begin = GetBufferCurrentPos();
        Globber<CharBuffer, CharPattern>::BufferInExecGlob(*this, globber);
        const CharBuffer* end = GetBufferCurrentPos();

        BasicBufferIn<CharPattern> subContext(begin, end);
        return subContext.FastReadCharPtr(str, sizeToCopy);
    }

    template<typename CharBuffer>
    template<typename CharPtr, typename CharPattern>
    bool BasicBufferIn<CharBuffer>::FastReadCharPtrRegex([[maybe_unused]] std::basic_string_view<CharPattern> regexPattern, [[maybe_unused]] CharPtr* str, [[maybe_unused]] std::size_t sizeToCopy, [[maybe_unused]] bool isZeroEnded)
    {
        throw FMTImplError{};
    }
}
