#pragma once

#include "stream/fmt/detail/specifiers.h"

namespace stream::fmt::detail
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
        detail::FormatData<typename FormatterExecutor::TChar> FormatData;
    };
}
