#pragma once

namespace StreamFormat::FMT
{
    enum class FMTResult
    {
        FunctionNotImpl,

        Buffer_NonValid,
        Buffer_OutOfBoundAccess,
        Buffer_UnableToReserveMemory,
        Parse_NonValidDigit,

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
