#pragma once

#include "Vector1BasicImpl.h"

namespace EngineCore {

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>::Vector()
		: x{} {}

	// S
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto scalar)
		: x{ static_cast<ValueType>(scalar) } {}

	// V1
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertibleTo<1, ValueType> auto& vec)
		: x{ static_cast<ValueType>(vec.x) } {}

	//--------------------------------------------------------------------//
	//------------- Conversion From Other Vector Constructor -------------//
	//--------------------------------------------------------------------//

	// From Vector<2, T, C>
	// V2
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertibleTo<2, ValueType> auto& vec)
		: x{ static_cast<ValueType>(vec.x) } {}
	
	// From Vector<3, T, C>
	// V3
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertibleTo<3, ValueType> auto& vec)
		: x{ static_cast<ValueType>(vec.x) } {}
	
	// From Vector<4, T, C>
	// V4
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertibleTo<4, ValueType> auto& vec)
		: x{ static_cast<ValueType>(vec.x) } {}


	//-----------------------------------------------//
	//------------- Conversion Operator -------------//
	//-----------------------------------------------//
 
 
	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template <typename ValueType>
	inline constexpr bool Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator==(const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return this->x == rhs.x;
	}


	template <typename ValueType>
	inline constexpr bool Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator!=(const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return this->x != rhs.x;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator&&(const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(this->x && rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator||(const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(this->x || rhs.x);
	}


	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator+() const {
		return *this;
	}

	// operator -I
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator-() const {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(-this->x);
	}

	// operator ~I
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator~() const {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(~this->x);
	}


	// operator ++I
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator++() {
		++this->x;
		return *this;
	}

	// operator --I
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator--() {
		--this->x;
		return *this;
	}

	// operator I++
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator++(int) {
		Vector<1, ValueType, EngineCompute::EngineComputeBasic> res(*this);
		++* this;
		return res;
	}

	// operator I--
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator--(int) {
		Vector<1, ValueType, EngineCompute::EngineComputeBasic> res(*this);
		--* this;
		return res;
	}

	// operator =
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator=(const std::convertible_to<ValueType> auto scalar) {
		this->x = static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x = static_cast<ValueType>(vec.x);
		return *this;
	}


	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator=(const VectorConvertibleTo<2, ValueType> auto& vec) {
		this->x = static_cast<ValueType>(vec.x);
		return *this;
	}
	
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator=(const VectorConvertibleTo<3, ValueType> auto& vec) {
		this->x = static_cast<ValueType>(vec.x);
		return *this;
	}
	
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator=(const VectorConvertibleTo<4, ValueType> auto& vec) {
		this->x = static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator +=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator+=(const std::convertible_to<ValueType> auto scalar) {
		this->x += static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator+=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x += static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator -=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator-=(const std::convertible_to<ValueType> auto scalar) {
		this->x -= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator-=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x -= static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator *=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator*=(const std::convertible_to<ValueType> auto scalar) {
		this->x *= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator*=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x *= static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator /=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator/=(const std::convertible_to<ValueType> auto scalar) {
		this->x /= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator/=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x /= static_cast<ValueType>(vec.x);
		return *this;
	}

	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//
	// 
	// operator %=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator%=(const std::convertible_to<ValueType> auto scalar) {
		this->x %= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator%=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x %= static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator &=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator&=(const std::convertible_to<ValueType> auto scalar) {
		this->x &= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator&=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x &= static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator |=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator|=(const std::convertible_to<ValueType> auto scalar) {
		this->x |= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator|=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x |= static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator ^=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator^=(const std::convertible_to<ValueType> auto scalar) {
		this->x ^= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator^=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x ^= static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator <<=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator<<=(const std::convertible_to<ValueType> auto scalar) {
		this->x <<= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator<<=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x <<= static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator >>=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator>>=(const std::convertible_to<ValueType> auto scalar) {
		this->x >>= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic>& Vector<1, ValueType, EngineCompute::EngineComputeBasic>::operator>>=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x >>= static_cast<ValueType>(vec.x);
		return *this;
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator+(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x + rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator+(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs + rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator+(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x + rhs.x);
	}

	// operator -
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator-(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x - rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator-(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs - rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator-(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x - rhs.x);
	}

	// operator *
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator*(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x * rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator*(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs * rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator*(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x * rhs.x);
	}

	// operator /
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator/(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x / rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator/(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs / rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator/(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x / rhs.x);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator%(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x % rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator%(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs % rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator%(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x % rhs.x);
	}

	// operator &
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator&(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x & rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator&(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs & rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator&(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x & rhs.x);
	}

	// operator |
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator|(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x | rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator|(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs | rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator|(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x | rhs.x);
	}

	// operator ^
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator^(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x ^ rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator^(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs ^ rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator^(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x ^ rhs.x);
	}

	// operator <<
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator<<(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x << rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator<<(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs << rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator<<(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x << rhs.x);
	}

	// operator >>
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator>>(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x >> rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator>>(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs >> rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, EngineCompute::EngineComputeBasic> operator>>(const Vector<1, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, EngineCompute::EngineComputeBasic>(lhs.x >> rhs.x);
	}
}