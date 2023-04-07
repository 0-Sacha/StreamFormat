#pragma once

namespace ProjectCore::FMT::Detail {
	template <typename FormatterContext>
	struct ApplyNextOverrideForThisFunction {
		inline explicit ApplyNextOverrideForThisFunction(FormatterContext& context)
			: Context(context)
			, FormatData(context.GetFormatData())
		{
            Context.FormatDataApplyNextOverride();
        }

		inline ~ApplyNextOverrideForThisFunction()
        {
            Context.SetFormatData(FormatData);
		}

		FormatterContext&							Context;
        typename FormatterContext::FormatDataType  FormatData;
	};

}
