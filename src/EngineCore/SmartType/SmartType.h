#pragma once

#include "EngineCore/Core/Core.h"

// This is a test

namespace EngineCore {

	template <typename From, typename T>
	concept SmartTypeConvertible = requires(From to) {
		requires std::is_convertible_v<From, T> || std::is_convertible_v<typename From::ValueType, T>;
	};

	template <typename Type>
	struct SmartType {


		//************* Using *************//
		using ValueType = Type;
		using Reference = ValueType&;
		using Pointer = ValueType*;
		template <std::size_t SIZE> using Array = std::array<ValueType, SIZE>;


		//************* Value *************//
		ValueType Value;


		//************* Custom Function *************//
		static inline constexpr ValueType MaxValue() { return std::numeric_limits<ValueType>::max(); }
		static inline constexpr ValueType MinValue() { return std::numeric_limits<ValueType>::min(); }

		inline constexpr void Dump() { CPPTools::Fmt::FilePrintLn(std::cout, Value); }




		//************* Base Function *************//
		inline constexpr SmartType() : Value{} {}
		inline constexpr SmartType(const SmartTypeConvertible<ValueType> auto i) : Value(static_cast<ValueType>(i)) {}

		template <typename T>
		inline constexpr operator T() const requires std::is_convertible_v<ValueType, T> {
			return static_cast<T>(Value);
		}

		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//
		inline constexpr bool operator==(const SmartTypeConvertible<ValueType> auto rhs) { return Value == (ValueType)rhs; }
		inline constexpr bool operator!=(const SmartTypeConvertible<ValueType> auto rhs) { return Value != (ValueType)rhs; }

		inline constexpr SmartType<ValueType> operator&&(const SmartTypeConvertible<ValueType> auto rhs) { return SmartType<ValueType>(Value && (ValueType)rhs); }
		inline constexpr SmartType<ValueType> operator||(const SmartTypeConvertible<ValueType> auto rhs) { return SmartType<ValueType>(Value || (ValueType)rhs); }

		// operator +I
		inline constexpr SmartType<ValueType>  operator+() const { return SmartType<ValueType>(Value); }
		// operator -I
		inline constexpr SmartType<ValueType>  operator-() const { return SmartType<ValueType>(-Value); }
		// operator ~I
		inline constexpr SmartType<ValueType>  operator~() const { return SmartType<ValueType>(~Value); }

		// operator ++I
		inline constexpr SmartType<ValueType>& operator++() { ++Value; return *this; }
		// operator --I
		inline constexpr SmartType<ValueType>& operator--() { --Value; return *this; }
		// operator I++
		inline constexpr SmartType<ValueType>  operator++(int) { SmartType<ValueType> res(Value); ++Value; return res; }
		// operator I--
		inline constexpr SmartType<ValueType>  operator--(int) { SmartType<ValueType> res(Value); --Value; return res; }
	
		// operator =
		inline constexpr auto& operator=(const SmartTypeConvertible<ValueType> auto i)	{ Value = static_cast<ValueType>(i); return *this; }

		// operator +=
		inline constexpr auto& operator+=(const SmartTypeConvertible<ValueType> auto i)	{ Value += static_cast<ValueType>(i); return *this; }

		// operator -=
		inline constexpr auto& operator-=(const SmartTypeConvertible<ValueType> auto i)	{ Value *= static_cast<ValueType>(i); return *this; }

		// operator *=
		inline constexpr auto& operator*=(const SmartTypeConvertible<ValueType> auto i)	{ Value *= static_cast<ValueType>(i); return *this; }

		// operator /=
		inline constexpr auto& operator/=(const SmartTypeConvertible<ValueType> auto i)	{ Value /= static_cast<ValueType>(i); return *this; }

		//-------------------------------------------//
		//------------- binary operator -------------//
		//-------------------------------------------//
		// 
		// operator %=
		inline constexpr auto& operator%=(const SmartTypeConvertible<ValueType> auto i)	{ Value %= static_cast<ValueType>(i); return *this; }

		// operator &=
		inline constexpr auto& operator&=(const SmartTypeConvertible<ValueType> auto i)	{ Value &= static_cast<ValueType>(i); return *this; }

		// operator |=
		inline constexpr auto& operator|=(const SmartTypeConvertible<ValueType> auto i)	{ Value |= static_cast<ValueType>(i); return *this; }

		// operator ^=
		inline constexpr auto& operator^=(const SmartTypeConvertible<ValueType> auto i)	{ Value ^= static_cast<ValueType>(i); return *this; }

		// operator <<=
		inline constexpr auto& operator<<=(const SmartTypeConvertible<ValueType> auto i)	{ Value <<= static_cast<ValueType>(i); return *this; }

		// operator >>=
		inline constexpr auto& operator>>=(const SmartTypeConvertible<ValueType> auto i)	{ Value >>= static_cast<ValueType>(i); return *this; }

	};

	// operator +
	template <typename ValueType> inline constexpr SmartType<ValueType> operator+(const SmartTypeConvertible<ValueType> auto lhs, const SmartType<ValueType> rhs)	{ return SmartType<ValueType>((ValueType)lhs + rhs.Value); }
	template <typename ValueType> inline constexpr SmartType<ValueType> operator+(const SmartType<ValueType> lhs, const SmartTypeConvertible<ValueType> auto rhs)	{ return SmartType<ValueType>(lhs.Value + (ValueType)rhs); }

	// operator -
	template <typename ValueType> inline constexpr SmartType<ValueType> operator-(const SmartTypeConvertible<ValueType> auto lhs, const SmartType<ValueType> rhs)	{ return SmartType<ValueType>((ValueType)lhs - rhs.Value); }
	template <typename ValueType> inline constexpr SmartType<ValueType> operator-(const SmartType<ValueType> lhs, const SmartTypeConvertible<ValueType> auto rhs)	{ return SmartType<ValueType>(lhs.Value - (ValueType)rhs); }

	// operator *
	template <typename ValueType> inline constexpr SmartType<ValueType> operator*(const SmartTypeConvertible<ValueType> auto lhs, const SmartType<ValueType> rhs)	{ return SmartType<ValueType>((ValueType)lhs * rhs.Value); }
	template <typename ValueType> inline constexpr SmartType<ValueType> operator*(const SmartType<ValueType> lhs, const SmartTypeConvertible<ValueType> auto rhs)	{ return SmartType<ValueType>(lhs.Value * (ValueType)rhs); }

	// operator /
	template <typename ValueType> inline constexpr SmartType<ValueType> operator/(const SmartTypeConvertible<ValueType> auto lhs, const SmartType<ValueType> rhs)	{ return SmartType<ValueType>((ValueType)lhs / rhs.Value); }
	template <typename ValueType> inline constexpr SmartType<ValueType> operator/(const SmartType<ValueType> lhs, const SmartTypeConvertible<ValueType> auto rhs)	{ return SmartType<ValueType>(lhs.Value / (ValueType)rhs); }



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template <typename ValueType> inline constexpr SmartType<ValueType> operator%(const SmartTypeConvertible<ValueType> auto lhs, const SmartType<ValueType> rhs)	{ return SmartType<ValueType>((ValueType)lhs % rhs.Value); }
	template <typename ValueType> inline constexpr SmartType<ValueType> operator%(const SmartType<ValueType> lhs, const SmartTypeConvertible<ValueType> auto rhs)	{ return SmartType<ValueType>(lhs.Value % (ValueType)rhs); }

	// operator &
	template <typename ValueType> inline constexpr SmartType<ValueType> operator&(const SmartTypeConvertible<ValueType> auto lhs, const SmartType<ValueType> rhs)	{ return SmartType<ValueType>((ValueType)lhs & rhs.Value); }
	template <typename ValueType> inline constexpr SmartType<ValueType> operator&(const SmartType<ValueType> lhs, const SmartTypeConvertible<ValueType> auto rhs)	{ return SmartType<ValueType>(lhs.Value & (ValueType)rhs); }

	// operator |
	template <typename ValueType> inline constexpr SmartType<ValueType> operator|(const SmartTypeConvertible<ValueType> auto lhs, const SmartType<ValueType> rhs)	{ return SmartType<ValueType>((ValueType)lhs | rhs.Value); }
	template <typename ValueType> inline constexpr SmartType<ValueType> operator|(const SmartType<ValueType> lhs, const SmartTypeConvertible<ValueType> auto rhs)	{ return SmartType<ValueType>(lhs.Value | (ValueType)rhs); }

	// operator ^
	template <typename ValueType> inline constexpr SmartType<ValueType> operator^(const SmartTypeConvertible<ValueType> auto lhs, const SmartType<ValueType> rhs)	{ return SmartType<ValueType>((ValueType)lhs ^ rhs.Value); }
	template <typename ValueType> inline constexpr SmartType<ValueType> operator^(const SmartType<ValueType> lhs, const SmartTypeConvertible<ValueType> auto rhs)	{ return SmartType<ValueType>(lhs.Value ^ (ValueType)rhs); }

	// operator <<
	template <typename ValueType> inline constexpr SmartType<ValueType> operator<<(const SmartTypeConvertible<ValueType> auto lhs, const SmartType<ValueType> rhs) { return SmartType<ValueType>((ValueType)lhs << rhs.Value); }
	template <typename ValueType> inline constexpr SmartType<ValueType> operator<<(const SmartType<ValueType> lhs, const SmartTypeConvertible<ValueType> auto rhs) { return SmartType<ValueType>(lhs.Value << (ValueType)rhs); }

	// operator >>
	template <typename ValueType> inline constexpr SmartType<ValueType> operator>>(const SmartTypeConvertible<ValueType> auto lhs, const SmartType<ValueType> rhs)		{ return SmartType<ValueType>((ValueType)lhs >> rhs.Value); }
	template <typename ValueType> inline constexpr SmartType<ValueType> operator>>(const SmartType<ValueType> lhs, const SmartTypeConvertible<ValueType> auto rhs)	{ return SmartType<ValueType>(lhs.Value >> (ValueType)rhs); }
}


namespace EngineCore {
	using Float		= SmartType<float>;
	using Double	= SmartType<double>;
	using Int		= SmartType<int>;
	using UInt		= SmartType<unsigned int>;

	using Int8		= SmartType<int8_t>;
	using UInt8		= SmartType<uint8_t>;
	using Int16		= SmartType<int16_t>;
	using UInt16	= SmartType<uint16_t>;
	using Int32		= SmartType<int32_t>;
	using UInt32	= SmartType<uint32_t>;
	using Int64		= SmartType<int64_t>;
	using UInt64	= SmartType<uint64_t>;
}



template <typename T, typename FormatContext>
struct CPPTools::Fmt::FormatType<EngineCore::SmartType<T>, FormatContext> {
	inline static void Write(const EngineCore::SmartType<T>& i, FormatContext& context) {
		CPPTools::Fmt::FormatType<T, FormatContext>::Write(i.Value, context);
	}
};