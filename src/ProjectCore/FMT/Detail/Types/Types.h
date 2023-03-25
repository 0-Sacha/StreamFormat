#pragma once

#include "ProjectCore/Core/Core.h"

#include <limits>

namespace ProjectCore::FMT::Detail
{
	using DataType	= std::int32_t;
	static inline constexpr DataType FORMAT_DATA_NOT_SPECIFIED = (std::numeric_limits<DataType>::max)();

	struct FormatIndex
	{
	public:
		using BaseType = std::int32_t;

	public:
		static inline constexpr DataType FORMAT_INDEX_NOT_SET = -1;

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

		constexpr void SetContext(FormatIndex sameContext)
		{
			MaxValue = sameContext.MaxValue;
		}		
	};

	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE>
	struct BasicCustomDataType {
	public:
		using ValueType = T;
		
	public:
		static constexpr T DEFAULT		= DEFAULT_VALUE;
		static constexpr T NON_VALID	= NON_VALID_VALUE;

	public:
		T Value;

	public:
		inline constexpr BasicCustomDataType(const T value = DEFAULT)
			: Value(value)
		{}

	public:
		inline constexpr bool IsValid() 	{ return Value != NON_VALID; };
		inline constexpr bool IsDefault() 	{ return Value == DEFAULT; };

	public:
		template <typename K>
		inline constexpr operator K() const requires std::is_convertible_v<T, K> {
			return static_cast<K>(Value);
		}
		
		inline constexpr bool operator==(const T rhs) const { return Value == rhs; }
		inline constexpr bool operator!=(const T rhs) const { return Value != rhs; }
		inline constexpr bool operator<(const T rhs) const	{ return Value < rhs; }
		inline constexpr bool operator>(const T rhs) const	{ return Value > rhs; }
		inline constexpr bool operator<=(const T rhs) const { return Value <= rhs; }
		inline constexpr bool operator>=(const T rhs) const { return Value >= rhs; }

		// operator +I
		inline constexpr BasicCustomDataType  operator+() const { return BasicCustomDataType(Value); }
		// operator -I
		inline constexpr BasicCustomDataType  operator-() const { return BasicCustomDataType(-Value); }

		// operator ++I
		inline constexpr BasicCustomDataType& operator++() { ++Value; return *this; }
		// operator --I
		inline constexpr BasicCustomDataType& operator--() { --Value; return *this; }
		// operator I++
		inline constexpr BasicCustomDataType  operator++(int) { BasicCustomDataType res(Value); ++Value; return res; }
		// operator I--
		inline constexpr BasicCustomDataType  operator--(int) { BasicCustomDataType res(Value); --Value; return res; }
	
		// operator =
		template <typename K>
		requires std::is_convertible_v<T, K>
		inline constexpr BasicCustomDataType& operator=(const K i)	{ Value = static_cast<T>(i); return *this; }
		// operator +=
		template <typename K>
		requires std::is_convertible_v<T, K>
		inline constexpr BasicCustomDataType& operator+=(const K i)	{ Value += static_cast<T>(i); return *this; }
		// operator -=
		template <typename K>
		requires std::is_convertible_v<T, K>
		inline constexpr BasicCustomDataType& operator-=(const K i)	{ Value -= static_cast<T>(i); return *this; }
		// operator *=
		template <typename K>
		requires std::is_convertible_v<T, K>
		inline constexpr BasicCustomDataType& operator*=(const K i)	{ Value *= static_cast<T>(i); return *this; }
		// operator /=
		template <typename K>
		requires std::is_convertible_v<T, K>
		inline constexpr BasicCustomDataType& operator/=(const K i)	{ Value /= static_cast<T>(i); return *this; }

		// operator =
		template <typename K, K KDEFAULT, K KNON_VALID>
		requires std::is_convertible_v<T, K>
		inline constexpr BasicCustomDataType& operator=(const BasicCustomDataType<K, KDEFAULT, KNON_VALID>& i)	{ Value = static_cast<T>(i.Value); return *this; }
		// operator +=
		template <typename K, K KDEFAULT, K KNON_VALID>
		requires std::is_convertible_v<T, K>
		inline constexpr BasicCustomDataType& operator+=(const BasicCustomDataType<K, KDEFAULT, KNON_VALID>& i)	{ Value += static_cast<T>(i.Value); return *this; }
		// operator -=
		template <typename K, K KDEFAULT, K KNON_VALID>
		requires std::is_convertible_v<T, K>
		inline constexpr BasicCustomDataType& operator-=(const BasicCustomDataType<K, KDEFAULT, KNON_VALID>& i)	{ Value -= static_cast<T>(i.Value); return *this; }
		// operator *=
		template <typename K, K KDEFAULT, K KNON_VALID>
		requires std::is_convertible_v<T, K>
		inline constexpr BasicCustomDataType& operator*=(const BasicCustomDataType<K, KDEFAULT, KNON_VALID>& i)	{ Value *= static_cast<T>(i.Value); return *this; }
		// operator /=
		template <typename K, K KDEFAULT, K KNON_VALID>
		requires std::is_convertible_v<T, K>
		inline constexpr BasicCustomDataType& operator/=(const BasicCustomDataType<K, KDEFAULT, KNON_VALID>& i)	{ Value /= static_cast<T>(i.Value); return *this; }
	};

	// operator +
	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE> inline constexpr BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE> operator+(const T lhs, const BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>& rhs)	{ return BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>(static_cast<T>(lhs) + rhs.Value); }
	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE> inline constexpr BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE> operator+(const BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>& lhs, const T rhs)	{ return BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>(lhs.Value + static_cast<T>(rhs)); }
	// operator -
	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE> inline constexpr BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE> operator-(const T lhs, const BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>& rhs)	{ return BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>(static_cast<T>(lhs) - rhs.Value); }
	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE> inline constexpr BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE> operator-(const BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>& lhs, const T rhs)	{ return BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>(lhs.Value - static_cast<T>(rhs)); }
	// operator *
	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE> inline constexpr BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE> operator*(const T lhs, const BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>& rhs)	{ return BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>(static_cast<T>(lhs) * rhs.Value); }
	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE> inline constexpr BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE> operator*(const BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>& lhs, const T rhs)	{ return BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>(lhs.Value * static_cast<T>(rhs)); }
	// operator /
	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE> inline constexpr BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE> operator/(const T lhs, const BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>& rhs)	{ return BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>(static_cast<T>(lhs) / rhs.Value); }
	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE> inline constexpr BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE> operator/(const BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>& lhs, const T rhs)	{ return BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>(lhs.Value / static_cast<T>(rhs)); }

	// operator +
	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE, typename K, K KDEFAULT, K KNON_VALID> inline constexpr BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE> operator+(const BasicCustomDataType<K, KDEFAULT, KNON_VALID>& lhs, const BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>& rhs)	{ return BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>(static_cast<T>(lhs.Value) + rhs.Value); }
	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE, typename K, K KDEFAULT, K KNON_VALID> inline constexpr BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE> operator+(const BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>& lhs, const BasicCustomDataType<K, KDEFAULT, KNON_VALID>& rhs)	{ return BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>(lhs.Value + static_cast<T>(rhs.Value)); }
	// operator -
	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE, typename K, K KDEFAULT, K KNON_VALID> inline constexpr BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE> operator-(const BasicCustomDataType<K, KDEFAULT, KNON_VALID>& lhs, const BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>& rhs)	{ return BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>(static_cast<T>(lhs.Value) - rhs.Value); }
	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE, typename K, K KDEFAULT, K KNON_VALID> inline constexpr BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE> operator-(const BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>& lhs, const BasicCustomDataType<K, KDEFAULT, KNON_VALID>& rhs)	{ return BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>(lhs.Value - static_cast<T>(rhs.Value)); }
	// operator *
	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE, typename K, K KDEFAULT, K KNON_VALID> inline constexpr BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE> operator*(const BasicCustomDataType<K, KDEFAULT, KNON_VALID>& lhs, const BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>& rhs)	{ return BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>(static_cast<T>(lhs.Value) * rhs.Value); }
	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE, typename K, K KDEFAULT, K KNON_VALID> inline constexpr BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE> operator*(const BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>& lhs, const BasicCustomDataType<K, KDEFAULT, KNON_VALID>& rhs)	{ return BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>(lhs.Value * static_cast<T>(rhs.Value)); }
	// operator /
	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE, typename K, K KDEFAULT, K KNON_VALID> inline constexpr BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE> operator/(const BasicCustomDataType<K, KDEFAULT, KNON_VALID>& lhs, const BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>& rhs)	{ return BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>(static_cast<T>(lhs.Value) / rhs.Value); }
	template <typename T, T DEFAULT_VALUE, T NON_VALID_VALUE, typename K, K KDEFAULT, K KNON_VALID> inline constexpr BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE> operator/(const BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>& lhs, const BasicCustomDataType<K, KDEFAULT, KNON_VALID>& rhs)	{ return BasicCustomDataType<T, DEFAULT_VALUE, NON_VALID_VALUE>(lhs.Value / static_cast<T>(rhs.Value)); }
}
