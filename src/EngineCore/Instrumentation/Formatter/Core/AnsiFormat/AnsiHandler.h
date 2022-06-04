#pragma once

#include "BaseAnsiColor.h"
#include "BaseAnsiFront.h"
#include "BaseAnsiStyle.h"


namespace EngineCore::FMT::Detail {

	struct AnsiTextData {
		Detail::AnsiColor	Color;
		Detail::AnsiStyle	Style;
		Detail::AnsiFront	Front;
	};

} // EngineCore::FMT::Detail
