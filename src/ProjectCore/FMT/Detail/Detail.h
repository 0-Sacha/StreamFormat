#pragma once

#include "ProjectCore/Core/Core.h"

#include "ContextTypes.h"
#include "TypesTraits.h"

#include "Exception.h"
#include "Specifiers.h"
#include "IndentHandlers.h"

#define UNKOWN_TYPE_MESSAGE

// TODO :
//
//        Check for escape char
//
//        Macro PackSave ; PackSave (foreshadowing for constexpr)
//
//        TOKENIZER bufferIn
//
//        GLOBBER
// 
//        REGEX        
//            {I:REGEX}
//            {:regex=REGEX} (string / char array)
//            {}
//
//        End writing all writer and reader (string / char pt)
//        

namespace ProjectCore::FMT::Context
{
    template <typename CharFormat = char, typename CharBuffer = CharFormat>
    class BasicFormatterContext;

    struct ParserContextError;

    template <typename CharFormat = char, typename CharBuffer = CharFormat>
    class BasicParserContext;
}
