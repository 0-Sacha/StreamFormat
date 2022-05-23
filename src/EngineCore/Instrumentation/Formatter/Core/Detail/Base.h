#pragma once

#include "EngineCore/Core.h"

namespace EngineCore::Instrumentation::FMT::Detail {

	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE>
	struct BasicCustomDataType {
	public:
		static constexpr T DEFAULT		= DEFAULT_VALUE;
		static constexpr T NON_VALID	= NON_VALID_VALUE;

	public:
		T Value;

	public:
		DataType(const T& value = DEFAULT_VALUE)
			: Value(index)
		{}

	public:
		bool IsValid() { return Value != NON_VALID; };
	};

	using DataType	= std::int32_t;
	using FormatIndex		= BasicCustomDataType<std::int32_t, -1, -1>;
	
	template <typename T>
	using Formating		= BasicCustomDataType<std::basic_string_view<T>, "", nullptr>;

	static inline constexpr DataType FORMAT_DATA_NOT_SPECIFIED		= (std::numeric_limits<DataType>::max)();
	static inline constexpr DataType SHIFT_NOT_SPECIFIED				= 0;
	static inline constexpr DataType DIGIT_SIZE_NOT_SPECIFIED			= FORMAT_DATA_NOT_SPECIFIED;
	static inline constexpr DataType FLOAT_PRECISION_NOT_SPECIFIED	= 2;

} // namespace EngineCore::Instrumentation::FMT::Detail
