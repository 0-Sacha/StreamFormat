#pragma once

#include "ProjectCore/Core/Core.h"

#include "Types/Types.h"
#include "Types/TypesInfo.h"
#include "Types/TypesTraits.h"

#include "Exception.h"
#include "Specifiers.h"
#include "IndentHandlers.h"
#include "UtilsContextsFunctions.h"

#include "TextProperties/TextProperties.h"

// TODO :
//
//         Check for escape char
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
    template<typename CharFormat = char, typename CharBuffer = CharFormat>
    class BasicFormatterContext;

    struct ParserContextError;

    template<typename CharFormat = char, typename CharBuffer = CharFormat>
    class BasicParserContext;
}
