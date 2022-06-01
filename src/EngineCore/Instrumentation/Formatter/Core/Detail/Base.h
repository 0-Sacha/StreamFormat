#pragma once

#include "EngineCore/Core.h"


namespace EngineCore::Instrumentation::FMT::Detail {

	using DataType	= std::int32_t;

	static inline constexpr DataType FORMAT_DATA_NOT_SPECIFIED		= (std::numeric_limits<DataType>::max)();
	static inline constexpr DataType SHIFT_NOT_SPECIFIED			= 0;
	static inline constexpr DataType DIGIT_SIZE_NOT_SPECIFIED		= FORMAT_DATA_NOT_SPECIFIED;
	static inline constexpr DataType FLOAT_PRECISION_NOT_SPECIFIED	= 2;

	struct FormatIndex
	{
	public:
		using BaseType = std::int32_t;

	public:
		static inline constexpr DataType FORMAT_INDEX_NOT_SET	= -1;

	public:
		explicit constexpr FormatIndex(const BaseType index = FORMAT_INDEX_NOT_SET)
			: Index(index)
			, MaxValue((std::numeric_limits<BaseType>::max)())
		{}

		constexpr FormatIndex(const BaseType index, const BaseType maxValue)
			: Index(index)
			, MaxValue(maxValue)
		{}

	public:
		BaseType Index;
		BaseType MaxValue;

	public:
		constexpr bool IsValid() 	const		{ return Index >= 0 && Index < MaxValue; }
		constexpr bool Is0() 		const		{ return Index == 0; }

	public:
		constexpr FormatIndex& Next()			{ ++Index; return *this; }
		constexpr FormatIndex& Prev()			{ --Index; return *this; }

		constexpr FormatIndex Get() const		{ return *this; }
		constexpr FormatIndex GetAndNext() 		{ FormatIndex old = *this; ++Index; return old; }
		constexpr FormatIndex NextAndGet() 		{ ++Index; return *this; }
		constexpr FormatIndex GetNext() const	{ FormatIndex res = *this; ++res.Index; return res; }

		constexpr FormatIndex GetAndPrev() 		{ FormatIndex old = *this; --Index; return old; }
		constexpr FormatIndex PrevAndGet() 		{ --Index; return *this; }
		constexpr FormatIndex GetPrev() const	{ FormatIndex res = *this; --res.Index; return res; }

		void SetContext(FormatIndex sameContext)
		{
			MaxValue = sameContext.MaxValue;
		}
	};
} // namespace EngineCore::Instrumentation::FMT::Detail
