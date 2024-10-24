#pragma once

#include "StreamFormat/Core/Core.h"

#include "TypesTraits.h"

#include "Exception.h"
#include "IndentHandlers.h"
#include "Specifiers.h"

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

namespace StreamFormat::FMT::Context
{
    template <typename TChar>
    class BasicContext;

    template <typename TChar>
    class BasicFormatterExecutor;

    struct ParserContextError;

    template <typename TChar>
    class BasicParserExecutor;
}
