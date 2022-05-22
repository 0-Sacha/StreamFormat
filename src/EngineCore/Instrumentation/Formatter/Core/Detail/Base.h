#pragma once

#include "EngineCore/Core.h"

namespace EngineCore::Instrumentation::FMT::Detail {

	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE>
	struct BasicCustomFormatDataType {
	public:
		static constexpr T DEFAULT		= DEFAULT_VALUE;
		static constexpr T NON_VALID	= NON_VALID_VALUE;

	public:
		T Value;

	public:
		FormatDataType(const T& value = DEFAULT_VALUE)
			: Value(index)
		{}

	public:
		bool IsValid() { return Value != NON_VALID; };
	};

	using FormatDataType	= std::int32_t;
	using FormatIndex		= BasicCustomFormatDataType<std::int32_t, -1, -1>;
	
	template <typename T>
	using FormatString		= BasicCustomFormatDataType<std::basic_string_view<T>, "", nullptr>;

	static inline constexpr FormatDataType FORMAT_DATA_NOT_SPECIFIED		= (std::numeric_limits<FormatDataType>::max)();
	static inline constexpr FormatDataType SHIFT_NOT_SPECIFIED				= 0;
	static inline constexpr FormatDataType DIGIT_SIZE_NOT_SPECIFIED			= FORMAT_DATA_NOT_SPECIFIED;
	static inline constexpr FormatDataType FLOAT_PRECISION_NOT_SPECIFIED	= 2;

} // namespace EngineCore::Instrumentation::FMT::Detail
