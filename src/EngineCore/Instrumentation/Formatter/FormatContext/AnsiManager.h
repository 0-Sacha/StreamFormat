#pragma once

#include "../Buffer/Buffer.h"
#include "AnsiHandler.h"

namespace EngineCore::Instrumentation::FMT::Detail {
	template<typename FormatContext>
	struct AnsiManager {

	public:
		AnsiManager(FormatContext& context)
			: Context(context)
		{}

	public:
		Detail::AnsiTextCurrentColor	AnsiTextCurrentColor;
		Detail::AnsiStyle	AnsiStyle;
		Detail::AnsiTextCurrentFront	AnsiTextCurrentFront;
		Detail::AnsiFormatterChange		AnsiFormatterChange;


	public:
		FormatContext& Context;
	};
}