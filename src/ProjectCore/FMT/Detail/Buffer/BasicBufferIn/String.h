#pragma once

#include "BasicBufferIn.h"
#include "ProjectCore/FMT/Detail/Buffer/Utils/PatternMatching/Glob/Glob.h"

namespace ProjectCore::FMT::Detail
{
    template<typename CharBuffer>
	template<typename CharPtr>
	bool BasicBufferIn<CharBuffer>::FastReadCharPtr(CharPtr* str, std::size_t sizeToCopy, bool addZero)
    {
        if (CanMoveForward(sizeToCopy) == false)
            return FastReadCharPtr(str, GetBufferRemainingSize(), addZero);

        // TODO : Opti with bigger types
        while (sizeToCopy-- != 0)
            *str++ = GetAndForward();
        if (addZero)
            *str = 0;

        return true;
    }

    template<typename CharBuffer>
    template<typename CharPtr, typename CharPattern>
    bool BasicBufferIn<CharBuffer>::FastReadCharPtrGlobber(std::basic_string_view<CharPattern> globPattern, CharPtr* str, std::size_t sizeToCopy, [[maybe_unused]] bool addZero)
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
    bool BasicBufferIn<CharBuffer>::FastReadCharPtrRegex([[maybe_unused]] std::basic_string_view<CharPattern> regexPattern, [[maybe_unused]] CharPtr* str, [[maybe_unused]] std::size_t sizeToCopy, [[maybe_unused]] bool addZero)
    {
        throw FMTImplError{};
    }

}
