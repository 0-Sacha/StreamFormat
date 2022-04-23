#pragma once

#include "Vector2BasicImpl.h"

namespace EngineCore::EngineCompute {

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

    template <typename ValueType>
    inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Vector()
		: x{}, y{} {}

	// S
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto scalar)
		: x{ static_cast<ValueType>(scalar) }, y{ static_cast<ValueType>(scalar) } {}

	// S - S
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto x, const std::convertible_to<ValueType> auto y)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y) } {}

	// V2
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Vector(const VectorConvertibleTo<2, ValueType> auto& vec)
		: x{ static_cast<ValueType>(vec.x) }, y{ static_cast<ValueType>(vec.y) } {}

	//--------------------------------------------------------------------//
	//------------- Conversion From Other Vector Constructor -------------//
	//--------------------------------------------------------------------//


	// From Vector<1, T, C>
	// V1 as S
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Vector(const VectorConvertibleTo<1, ValueType> auto& scalar)
		: x{ static_cast<ValueType>(scalar) }, y{ static_cast<ValueType>(scalar) } {}

	// V1 - S
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Vector(const VectorConvertibleTo<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(y) } {}

	// S - V1
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto x, const VectorConvertibleTo<1, ValueType> auto& y)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y.y) } {}

	// V1 - V
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Vector(const VectorConvertibleTo<1, ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto& y)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(y.y) } {}


	// From Vector<3, T, C>
	// V3
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Vector(const VectorConvertibleTo<3, ValueType> auto& vec)
		: x{ static_cast<ValueType>(vec.x) }, y{ static_cast<ValueType>(vec.y) } {}

	// From Vector<4, T, C>
	// V4
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Vector(const VectorConvertibleTo<4, ValueType> auto& vec)
		: x{ static_cast<ValueType>(vec.x) }, y{ static_cast<ValueType>(vec.y) } {}



	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template <typename ValueType>
	inline constexpr bool Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator==(const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return this->x == rhs.x && this->y == rhs.y;
	}

	template <typename ValueType>
	inline constexpr bool Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator!=(const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return this->x != rhs.x || this->y != rhs.y;
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator&&(const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(this->x && rhs.x, this->y && rhs.y);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator||(const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(this->x || rhs.x, this->y || rhs.y);
	}

	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator+() const {
		return *this;
	}

	// operator -I
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator-() const {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(-this->x, -this->y);
	}

	// operator ~I
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator~() const {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(~this->x, ~this->y);
	}


	// operator ++I
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator++() {
		++this->x;
		++this->y;
		return *this;
	}
	
	// operator --I
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator--() {
		--this->x;
		--this->y;
		return *this;
	}

	// operator I++
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator++(int) {
		Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> res(*this);
		++* this;
		return res;
	}

	// operator I--
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator--(int) {
		Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> res(*this);
		--* this;
		return res;
	}


	// operator =
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator=(const std::convertible_to<ValueType> auto scalar) {
		this->x = static_cast<ValueType>(scalar);
		this->y = static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator=(const VectorConvertibleTo<2, ValueType> auto& vec) {
		this->x = static_cast<ValueType>(vec.x);
		this->y = static_cast<ValueType>(vec.y);
		return *this;
	}

	// operator +=
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator+=(const std::convertible_to<ValueType> auto scalar) {
		this->x += static_cast<ValueType>(scalar);
		this->y += static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator+=(const VectorConvertibleTo<2, ValueType> auto& vec) {
		this->x += static_cast<ValueType>(vec.x);
		this->y += static_cast<ValueType>(vec.y);
		return *this;
	}

	// operator -=
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator-=(const std::convertible_to<ValueType> auto scalar) {
		this->x -= static_cast<ValueType>(scalar);
		this->y -= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator-=(const VectorConvertibleTo<2, ValueType> auto& vec) {
		this->x -= static_cast<ValueType>(vec.x);
		this->y -= static_cast<ValueType>(vec.y);
		return *this;
	}

	// operator *=
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator*=(const std::convertible_to<ValueType> auto scalar) {
		this->x *= static_cast<ValueType>(scalar);
		this->y *= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator*=(const VectorConvertibleTo<2, ValueType> auto& vec) {
		this->x *= static_cast<ValueType>(vec.x);
		this->y *= static_cast<ValueType>(vec.y);
		return *this;
	}

	// operator /=
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator/=(const std::convertible_to<ValueType> auto scalar) {
		this->x /= static_cast<ValueType>(scalar);
		this->y /= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator/=(const VectorConvertibleTo<2, ValueType> auto& vec) {
		this->x /= static_cast<ValueType>(vec.x);
		this->y /= static_cast<ValueType>(vec.y);
		return *this;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %=
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator%=(const std::convertible_to<ValueType> auto scalar) {
		this->x %= static_cast<ValueType>(scalar);
		this->y %= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator%=(const VectorConvertibleTo<2, ValueType> auto& vec) {
		this->x %= static_cast<ValueType>(vec.x);
		this->y %= static_cast<ValueType>(vec.y);
		return *this;
	}

	// operator &=
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator&=(const std::convertible_to<ValueType> auto scalar) {
		this->x &= static_cast<ValueType>(scalar);
		this->y &= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator&=(const VectorConvertibleTo<2, ValueType> auto& vec) {
		this->x &= static_cast<ValueType>(vec.x);
		this->y &= static_cast<ValueType>(vec.y);
		return *this;
	}

	// operator |=
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator|=(const std::convertible_to<ValueType> auto scalar) {
		this->x |= static_cast<ValueType>(scalar);
		this->y |= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator|=(const VectorConvertibleTo<2, ValueType> auto& vec) {
		this->x |= static_cast<ValueType>(vec.x);
		this->y |= static_cast<ValueType>(vec.y);
		return *this;
	}

	// operator ^=
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator^=(const std::convertible_to<ValueType> auto scalar) {
		this->x ^= static_cast<ValueType>(scalar);
		this->y ^= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator^=(const VectorConvertibleTo<2, ValueType> auto& vec) {
		this->x ^= static_cast<ValueType>(vec.x);
		this->y ^= static_cast<ValueType>(vec.y);
		return *this;
	}

	// operator <<=
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator<<=(const std::convertible_to<ValueType> auto scalar) {
		this->x <<= static_cast<ValueType>(scalar);
		this->y <<= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator<<=(const VectorConvertibleTo<2, ValueType> auto& vec) {
		this->x <<= static_cast<ValueType>(vec.x);
		this->y <<= static_cast<ValueType>(vec.y);
		return *this;
	}

	// operator >>=
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator>>=(const std::convertible_to<ValueType> auto scalar) {
		this->x >>= static_cast<ValueType>(scalar);
		this->y >>= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator>>=(const VectorConvertibleTo<2, ValueType> auto& vec) {
		this->x >>= static_cast<ValueType>(vec.x);
		this->y >>= static_cast<ValueType>(vec.y);
		return *this;
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator+(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x + rhs, lhs.y + rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator+(const std::convertible_to<ValueType> auto lhs, const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs + rhs.x, lhs + rhs.y);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator+(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	// operator -
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator-(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x - rhs, lhs.y - rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator-(const std::convertible_to<ValueType> auto lhs, const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs - rhs.x, lhs - rhs.y);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator-(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	// operator *
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x * rhs, lhs.y * rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const std::convertible_to<ValueType> auto lhs, const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs * rhs.x, lhs * rhs.y);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x * rhs.x, lhs.y * rhs.y);
	}

	// operator /
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator/(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x / rhs, lhs.y / rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator/(const std::convertible_to<ValueType> auto lhs, const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs / rhs.x, lhs / rhs.y);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator/(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x / rhs.x, lhs.y / rhs.y);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator%(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x % rhs, lhs.y % rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator%(const std::convertible_to<ValueType> auto lhs, const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs % rhs.x, lhs % rhs.y);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator%(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x % rhs.x, lhs.y % rhs.y);
	}

	// operator &
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator&(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x & rhs, lhs.y & rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator&(const std::convertible_to<ValueType> auto lhs, const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs & rhs.x, lhs & rhs.y);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator&(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x & rhs.x, lhs.y & rhs.y);
	}

	// operator |
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator|(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x | rhs, lhs.y | rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator|(const std::convertible_to<ValueType> auto lhs, const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs | rhs.x, lhs | rhs.y);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator|(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x | rhs.x, lhs.y | rhs.y);
	}

	// operator ^
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator^(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x ^ rhs, lhs.y ^ rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator^(const std::convertible_to<ValueType> auto lhs, const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs ^ rhs.x, lhs ^ rhs.y);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator^(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x ^ rhs.x, lhs.y ^ rhs.y);
	}

	// operator <<
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator<<(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x << rhs, lhs.y << rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator<<(const std::convertible_to<ValueType> auto lhs, const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs << rhs.x, rhs << rhs.y);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator<<(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x << rhs.x, lhs.y << rhs.y);
	}

	// operator >>
	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator>>(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x >> rhs, lhs.y >> rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator>>(const std::convertible_to<ValueType> auto lhs, const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs >> rhs.x, lhs >> rhs.y);
	}

	template <typename ValueType>
	inline constexpr Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator>>(const Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return Vector<2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.x >> rhs.x, lhs.y >> rhs.y);
	}
}