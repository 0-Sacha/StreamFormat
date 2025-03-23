#pragma once

#include "stream/core/prelude.h"
#include "types_traits.h"
#include "fmt_result.h"

#define UNKOWN_TYPE_MESSAGE

// TODO :
//
//        Check for escape char
//
//        Macro PackSave ; PackSave (foreshadowing for constexpr)
//
//        TOKENIZER istream
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

namespace stream::fmt::context
{
    template <typename TChar>
    class BasicContext;

    template <typename TChar>
    class BasicFormatterExecutor;

    struct ParserFMTError;

    template <typename TChar>
    class BasicParserExecutor;
}
