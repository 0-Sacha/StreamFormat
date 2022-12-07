#pragma once

namespace EngineCore::FMT::Detail {
	template <typename FormatContext>
	struct ApplyNextOverrideForThisFunction {
		inline explicit ApplyNextOverrideForThisFunction(FormatContext& context)
			: Context(context)
			, FormatData(context.GetFormatData())
		{
            Context.FormatDataApplyNextOverride();
        }

		inline ~ApplyNextOverrideForThisFunction()
        {
            Context.SetFormatData(FormatData);
		}

		FormatContext&							Context;
        typename FormatContext::FormatDataType  FormatData;
	};
}