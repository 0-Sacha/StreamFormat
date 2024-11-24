#pragma once

#include "StreamFormat/Core/Prelude.h"
#include "TypesTraits.h"
#include "FMTResult.h"

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

    struct ParserFMTError;

    template <typename TChar>
    class BasicParserExecutor;
}
