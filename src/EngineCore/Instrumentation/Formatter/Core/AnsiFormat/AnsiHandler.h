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

	inline bool operator==(const AnsiTextData& lhs, const AnsiTextData& rhs)
	{
		return lhs.Color == rhs.Color && lhs.Style == rhs.Style && lhs.Front == rhs.Front;
	}
} // EngineCore::FMT::Detail
