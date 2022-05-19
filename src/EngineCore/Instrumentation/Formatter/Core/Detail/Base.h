#pragma once

#include "EngineCore/Core.h"

namespace EngineCore::Instrumentation::FMT::Detail {
	using FormatDataType	= std::int16_t;
	static inline constexpr FormatDataType FORMAT_DATA_NOT_SPECIFIED	= (std::numeric_limits<FormatDataType>::max)();
	static inline constexpr FormatDataType SHIFT_NOT_SPECIFIED			= 0;
	static inline constexpr FormatDataType DIGIT_SIZE_NOT_SPECIFIED			= FORMAT_DATA_NOT_SPECIFIED;
	static inline constexpr FormatDataType FLOAT_PRECISION_NOT_SPECIFIED	= 2;
} // namespace EngineCore::Instrumentation::FMT::Detail
