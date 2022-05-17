#pragma once

#include "Vector1BasicImpl.h"

namespace EngineCore::TNX {

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>::Vector()
		: x{} {}

	// S
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>::Vector(const std::convertible_to<ValueType> auto scalar)
		: x{ static_cast<ValueType>(scalar) } {}

	// V1
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>::Vector(const VectorConvertibleTo<1, ValueType> auto& vec)
		: x{ static_cast<ValueType>(vec.x) } {}

	//--------------------------------------------------------------------//
	//------------- Conversion From Other Vector Constructor -------------//
	//--------------------------------------------------------------------//

	// From Vector<2, T, C>
	// V2
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>::Vector(const VectorConvertibleTo<2, ValueType> auto& vec)
		: x{ static_cast<ValueType>(vec.x) } {}
	
	// From Vector<3, T, C>
	// V3
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>::Vector(const VectorConvertibleTo<3, ValueType> auto& vec)
		: x{ static_cast<ValueType>(vec.x) } {}
	
	// From Vector<4, T, C>
	// V4
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>::Vector(const VectorConvertibleTo<4, ValueType> auto& vec)
		: x{ static_cast<ValueType>(vec.x) } {}


	//-----------------------------------------------//
	//------------- Conversion Operator -------------//
	//-----------------------------------------------//
 
 
	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template <typename ValueType>
	inline constexpr bool Vector<1, ValueType, TNXType::TNXBasic>::operator==(const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return this->x == rhs.x;
	}


	template <typename ValueType>
	inline constexpr bool Vector<1, ValueType, TNXType::TNXBasic>::operator!=(const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return this->x != rhs.x;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> Vector<1, ValueType, TNXType::TNXBasic>::operator&&(const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(this->x && rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> Vector<1, ValueType, TNXType::TNXBasic>::operator||(const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(this->x || rhs.x);
	}


	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> Vector<1, ValueType, TNXType::TNXBasic>::operator+() const {
		return *this;
	}

	// operator -I
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> Vector<1, ValueType, TNXType::TNXBasic>::operator-() const {
		return Vector<1, ValueType, TNXType::TNXBasic>(-this->x);
	}

	// operator ~I
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> Vector<1, ValueType, TNXType::TNXBasic>::operator~() const {
		return Vector<1, ValueType, TNXType::TNXBasic>(~this->x);
	}


	// operator ++I
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator++() {
		++this->x;
		return *this;
	}

	// operator --I
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator--() {
		--this->x;
		return *this;
	}

	// operator I++
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> Vector<1, ValueType, TNXType::TNXBasic>::operator++(int) {
		Vector<1, ValueType, TNXType::TNXBasic> res(*this);
		++* this;
		return res;
	}

	// operator I--
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> Vector<1, ValueType, TNXType::TNXBasic>::operator--(int) {
		Vector<1, ValueType, TNXType::TNXBasic> res(*this);
		--* this;
		return res;
	}

	// operator =
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator=(const std::convertible_to<ValueType> auto scalar) {
		this->x = static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x = static_cast<ValueType>(vec.x);
		return *this;
	}


	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator=(const VectorConvertibleTo<2, ValueType> auto& vec) {
		this->x = static_cast<ValueType>(vec.x);
		return *this;
	}
	
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator=(const VectorConvertibleTo<3, ValueType> auto& vec) {
		this->x = static_cast<ValueType>(vec.x);
		return *this;
	}
	
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator=(const VectorConvertibleTo<4, ValueType> auto& vec) {
		this->x = static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator +=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator+=(const std::convertible_to<ValueType> auto scalar) {
		this->x += static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator+=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x += static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator -=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator-=(const std::convertible_to<ValueType> auto scalar) {
		this->x -= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator-=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x -= static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator *=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator*=(const std::convertible_to<ValueType> auto scalar) {
		this->x *= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator*=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x *= static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator /=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator/=(const std::convertible_to<ValueType> auto scalar) {
		this->x /= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator/=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x /= static_cast<ValueType>(vec.x);
		return *this;
	}

	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//
	// 
	// operator %=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator%=(const std::convertible_to<ValueType> auto scalar) {
		this->x %= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator%=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x %= static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator &=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator&=(const std::convertible_to<ValueType> auto scalar) {
		this->x &= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator&=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x &= static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator |=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator|=(const std::convertible_to<ValueType> auto scalar) {
		this->x |= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator|=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x |= static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator ^=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator^=(const std::convertible_to<ValueType> auto scalar) {
		this->x ^= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator^=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x ^= static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator <<=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator<<=(const std::convertible_to<ValueType> auto scalar) {
		this->x <<= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator<<=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x <<= static_cast<ValueType>(vec.x);
		return *this;
	}

	// operator >>=
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator>>=(const std::convertible_to<ValueType> auto scalar) {
		this->x >>= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic>& Vector<1, ValueType, TNXType::TNXBasic>::operator>>=(const VectorConvertibleTo<1, ValueType> auto& vec) {
		this->x >>= static_cast<ValueType>(vec.x);
		return *this;
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator+(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x + rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator+(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, TNXType::TNXBasic>& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs + rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator+(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x + rhs.x);
	}

	// operator -
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator-(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x - rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator-(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, TNXType::TNXBasic>& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs - rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator-(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x - rhs.x);
	}

	// operator *
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator*(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x * rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator*(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, TNXType::TNXBasic>& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs * rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator*(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x * rhs.x);
	}

	// operator /
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator/(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x / rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator/(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, TNXType::TNXBasic>& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs / rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator/(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x / rhs.x);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator%(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x % rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator%(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, TNXType::TNXBasic>& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs % rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator%(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x % rhs.x);
	}

	// operator &
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator&(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x & rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator&(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, TNXType::TNXBasic>& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs & rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator&(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x & rhs.x);
	}

	// operator |
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator|(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x | rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator|(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, TNXType::TNXBasic>& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs | rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator|(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x | rhs.x);
	}

	// operator ^
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator^(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x ^ rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator^(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, TNXType::TNXBasic>& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs ^ rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator^(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x ^ rhs.x);
	}

	// operator <<
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator<<(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x << rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator<<(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, TNXType::TNXBasic>& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs << rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator<<(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x << rhs.x);
	}

	// operator >>
	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator>>(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x >> rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator>>(const std::convertible_to<ValueType> auto lhs, const Vector<1, ValueType, TNXType::TNXBasic>& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs >> rhs.x);
	}

	template <typename ValueType>
	inline constexpr Vector<1, ValueType, TNXType::TNXBasic> operator>>(const Vector<1, ValueType, TNXType::TNXBasic>& lhs, const VectorConvertibleTo<1, ValueType> auto& rhs) {
		return Vector<1, ValueType, TNXType::TNXBasic>(lhs.x >> rhs.x);
	}
}