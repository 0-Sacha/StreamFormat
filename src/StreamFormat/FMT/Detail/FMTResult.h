#pragma once

#include "StreamFormat/Core/Prelude.h"

namespace StreamFormat::FMT
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

        Specifers_Full,
        Specifers_Invalid,
        Specifers_DoesNotExist,

        Context_ParsingFormat,
        Context_ArgumentIndexResolution,
        Context_ArgumentIndexExpected,
        Context_CannotApplyType,
        
        GivenArgs_UnableToDeduceSize,

        Manager_StaticMemory,
        Manager_AllocationFailed,
    };
}

namespace StreamFormat::Detail
{
    template<>
    inline FMT::FMTResult forward_error<FMT::FMTResult>(FMT::FMTResult t)
    {
        if (t == FMT::FMTResult::ArgsInterface_CantMatchNamedArgs)
            return t;
        if (t == FMT::FMTResult::Manager_StaticMemory)
            return t;
        return t;
    }
}
