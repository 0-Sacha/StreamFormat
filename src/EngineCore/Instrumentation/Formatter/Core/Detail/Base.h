#pragma once

#include "EngineCore/Core.h"


namespace EngineCore::Instrumentation::FMT::Detail {

	using DataType	= std::int32_t;

	static inline constexpr DataType FORMAT_DATA_NOT_SPECIFIED		= (std::numeric_limits<DataType>::max)();
	static inline constexpr DataType SHIFT_NOT_SPECIFIED				= 0;
	static inline constexpr DataType DIGIT_SIZE_NOT_SPECIFIED			= FORMAT_DATA_NOT_SPECIFIED;
	static inline constexpr DataType FLOAT_PRECISION_NOT_SPECIFIED	= 2;

	struct FormatIndex
	{
	public:
		using BaseType = std::int32_t;

	public:
		static inline constexpr DataType FORMAT_INDEX_NOT_SET	= -1;

	public:
		explicit FormatIndex(const BaseType index)
			: Index(index)
			, MaxValue((std::numeric_limits<BaseType>::max)())
		{}

		explicit FormatIndex(const BaseType index, const BaseType maxValue)
			: Index(index)
			, MaxValue(maxValue)
		{}

	public:
		BaseType Index;
		BaseType MaxValue;

	public:
		bool IsValid() 				{ return Index != FORMAT_INDEX_NOT_SET && Index < MaxValue; }

	public:
		FormatIndex Get() 			{ return *this; }
		FormatIndex GetAndNext() 	{ FormatIndex old = *this; ++Value; return old; }
		FormatIndex NextAndGet() 	{ ++Value; return *this; }
	}
} // namespace EngineCore::Instrumentation::FMT::Detail


namespace EngineCore::Instrumentation::FMT::Detail {

	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE>
	struct BasicCustomDataType {
	public:
		static constexpr T DEFAULT		= DEFAULT_VALUE;
		static constexpr T NON_VALID	= NON_VALID_VALUE;

	public:
		T Value;

	public:
		BasicCustomDataType(const T& value = DEFAULT_VALUE)
			: Value(index)
		{}

	public:
		bool IsValid() { return Value != NON_VALID; };
	};
	using FormatString		= BasicCustomDataType<std::basic_string_view<T>, "", nullptr>;
} // namespace EngineCore::Instrumentation::FMT::Detail