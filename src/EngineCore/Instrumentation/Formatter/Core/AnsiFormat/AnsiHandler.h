#pragma once

#include "BaseAnsiColor.h"
#include "BaseAnsiFront.h"
#include "BaseAnsiStyle.h"


namespace EngineCore::Instrumentation::FMT::Detail {

	struct AnsiTextData {
		Detail::AnsiColor	Color;
		Detail::AnsiStyle	Style;
		Detail::AnsiFront	Front;
	};

} // EngineCore::Instrumentation::FMT::Detail
