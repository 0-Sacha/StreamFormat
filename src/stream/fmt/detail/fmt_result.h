#pragma once

#include "stream/core/prelude.h"

namespace stream::fmt
{
    enum class FMTResult
    {
        FunctionNotImpl,

        Buffer_NonValid,
        Buffer_OutOfBoundAccess,
        Buffer_UnableToReserveMemory,
        Parse_NonValidDigit,
        Parse_TokenNotExpected,

        ArgsInterface_Unavaible,
        ArgsInterface_InvalidTypeID,
        ArgsInterface_InvalidConversion,
        ArgsInterface_CantMatchNamedArgs,
        ArgsInterface_IndexOutOfBounds,

        Specifiers_Full,
        Specifiers_Invalid,
        Specifiers_DoesNotExist,

        Context_ParsingFormat,
        Context_ArgumentIndexResolution,
        Context_ArgumentIndexExpected,
        Context_CannotapplyType,
        
        GivenArgs_UnableToDeduceSize,

        Manager_StaticMemory,
        Manager_AllocationFailed,
    };
}

namespace stream::detail
{
    template<>
    inline fmt::FMTResult forward_error<fmt::FMTResult>(fmt::FMTResult t)
    {
        if (t == fmt::FMTResult::ArgsInterface_CantMatchNamedArgs)
            return t;
        if (t == fmt::FMTResult::Manager_StaticMemory)
            return t;
        return t;
    }
}
