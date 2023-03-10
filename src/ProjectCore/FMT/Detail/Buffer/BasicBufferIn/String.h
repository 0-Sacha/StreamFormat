#pragma once

#include "BasicBufferIn.h"
#include "ProjectCore/FMT/Detail/Buffer/Utils/PatternMatching/Glob/Glob.h"

namespace ProjectCore::FMT::Detail
{
    template<typename CharBuffer>
	template<typename CharPtr>
	void BasicBufferIn<CharBuffer>::FastReadCharPtr(CharPtr* str, std::size_t sizeContainer, std::size_t sizeToWrite)
    {
        if (sizeToWrite == 0)
            sizeToWrite = sizeContainer - 1;

        if (CanMoveForward(sizeToWrite) == false)
            return FastReadCharPtr(str, sizeContainer, GetBufferRemainingSize());

        if (sizeToWrite >= sizeContainer)
            sizeToWrite = sizeContainer - 1;

        // TODO : Opti with bigger types
        while (sizeToWrite-- != 0)
            *str++ = GetAndForward();
        *str = 0;
    }

    template<typename CharBuffer>
    template<typename CharPtr, typename CharPattern>
    void BasicBufferIn<CharBuffer>::FastReadCharPtrGlobber(CharPtr* str, std::size_t sizeContainer, std::basic_string_view<CharPattern> globPattern)
    {
        BasicBufferIn<CharPattern> globber;
        const CharBuffer* begin = GetBufferCurrentPos();
        Globber<CharBuffer, CharPattern>::BufferInExecGlob(*this, globber);
        const CharBuffer* end = GetBufferCurrentPos();

        BasicBufferIn<CharPattern> subContext(begin, end);
        subContext.FastReadCharPtr(str, sizeContainer);
    }

    template<typename CharBuffer>
    template<typename CharPtr, typename CharPattern>
    void BasicBufferIn<CharBuffer>::FastReadCharPtrRegex(CharPtr* str, std::size_t sizeContainer, std::basic_string_view<CharPattern> regexPattern)
    {
        throw FMTImplError{};
    }

}
