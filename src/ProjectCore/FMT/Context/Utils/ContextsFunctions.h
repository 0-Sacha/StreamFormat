#pragma once

namespace ProjectCore::FMT::Detail
{
    template <typename FormatterContext>
    struct FunctionApplyNextOverride
    {
        inline explicit FunctionApplyNextOverride(FormatterContext& context)
            : Context(context)
            , FormatData(context.GetFormatData())
        {
            Context.FormatDataApplyNextOverride();
        }

        inline ~FunctionApplyNextOverride() { Context.SetFormatData(FormatData); }

        FormatterContext&                         Context;
        typename FormatterContext::FormatDataType FormatData;
    };
}
