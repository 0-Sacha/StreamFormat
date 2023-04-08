#pragma once

#include "BasicParserContext.h"
#include "BasicParserContextCoreImpl.h"

namespace ProjectCore::FMT::Context
{
    /////---------- AAHHHHHHHHH ----------/////
    template<typename CharFormat, typename CharBuffer>
    void BasicParserContext<CharFormat, CharBuffer>::ParseTimer() {
        std::chrono::nanoseconds ns = std::chrono::high_resolution_clock::now() - Detail::FormatterHandler::GetInstance().GetTimeShift();
        RunType(ns);
    }

    template<typename CharFormat, typename CharBuffer>
    void BasicParserContext<CharFormat, CharBuffer>::ParseDate() {
        std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()) + Detail::FormatterHandler::GetInstance().GetHoursShift();
        RunType(ns);
    }

    template<typename CharFormat, typename CharBuffer>
    void BasicParserContext<CharFormat, CharBuffer>::ParseSetter() {
    }
}
