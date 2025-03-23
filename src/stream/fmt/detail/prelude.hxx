#pragma once

#include "stream/core/prelude.hxx"
#include "types_traits.hxx"
#include "fmt_result.hxx"

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

namespace stream::fmt::context {
    template <typename TChar>
    class BasicContext;

    template <typename TChar>
    class BasicFormatterExecutor;

    struct ParserFMTError;

    template <typename TChar>
    class BasicParserExecutor;
}  // namespace stream::fmt::context
