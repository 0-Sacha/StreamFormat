#pragma once

#include "StreamFormat/FMT/Detail/Specifiers.h"

namespace StreamFormat::FMT::Detail
{
    template <typename FormatterExecutor>
    struct FunctionApplyNextOverride
    {
        inline explicit FunctionApplyNextOverride(FormatterExecutor& executor)
            : Executor(executor)
            , FormatData(executor.Data)
        {
            Executor.FormatDataApplyNextOverride();
        }

        inline ~FunctionApplyNextOverride() { Executor.Data = FormatData; }

        FormatterExecutor& Executor;
        Detail::FormatData<typename FormatterExecutor::TChar> FormatData;
    };
}
