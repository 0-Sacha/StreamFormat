#include "BaseAnsiTextColor.h"
#include "BaseAnsiFront.h"
#include "BaseAnsiTextStyle.h"


namespace EngineCore::Instrumentation::FMT::Detail {

	struct AnsiTextData {
		Detail::AnsiColor	Color;
		Detail::AnsiStyle	Style;
		Detail::AnsiFront	Front;
	};

} // EngineCore::Instrumentation::FMT::Detail
