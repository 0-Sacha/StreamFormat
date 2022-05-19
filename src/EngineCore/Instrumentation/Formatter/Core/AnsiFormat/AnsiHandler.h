#include "BaseAnsiTextColor.h"
#include "BaseAnsiTextFront.h"
#include "BaseAnsiTextStyle.h"


namespace EngineCore::Instrumentation::FMT::Detail {
	struct AnsiFormatterChange {
	public:
		bool HasMadeChange = false;
	};
} // EngineCore::Instrumentation::FMT::Detail
