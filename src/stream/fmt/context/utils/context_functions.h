#pragma once

#include "stream/fmt/detail/specifiers.h"

namespace stream::fmt::detail
{
    template <typename FormatterExecutor>
    struct FunctionapplyNextOverride
    {
        inline explicit FunctionapplyNextOverride(FormatterExecutor& executor)
            : executor(executor)
            , formatdata(executor.data)
        {
            executor.formatdata_apply_next_override();
        }

        inline ~FunctionapplyNextOverride() { executor.data = formatdata; }

        FormatterExecutor& executor;
        detail::FormatData<typename FormatterExecutor::TChar> formatdata;
    };
}
