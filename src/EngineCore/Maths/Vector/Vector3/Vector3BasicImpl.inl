#pragma once

#include "Vector3BasicImpl.h"

namespace EngineCore {

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

    template <typename ValueType>
    inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector()
		: x{}, y{}, z{} {}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto scalar)
		: x{ static_cast<ValueType>(scalar) }, y{ static_cast<ValueType>(scalar) }, z{ static_cast<ValueType>(scalar) } {}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto x, const std::convertible_to<ValueType> auto y, const std::convertible_to<ValueType> auto z)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y) }, z{ static_cast<ValueType>(z) } {}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertibleTo<3, ValueType> auto& vec)
		: x{ static_cast<ValueType>(vec.x) }, y{ static_cast<ValueType>(vec.y) }, z{ static_cast<ValueType>(vec.z) } {}

	//--------------------------------------------------------------------//
	//------------- Conversion From Other Vector Constructor -------------//
	//--------------------------------------------------------------------//

	// From Vector<1, T, C>
	// V1 as S
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertibleTo<1, ValueType> auto& scalar)
		: x{ static_cast<ValueType>(scalar) }, y{ static_cast<ValueType>(scalar) }, z{ static_cast<ValueType>(scalar) } {}

	// V1 - S  - S
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertibleTo<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y, const std::convertible_to<ValueType> auto z)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(y) }, z{ static_cast<ValueType>(z) } {}
	
	// S  - V1 - S
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const std::convertible_to<ValueType> auto z)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y.y) }, z{ static_cast<ValueType>(z) } {}
	
	// V1 - V1 - S 
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertibleTo<1, ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const std::convertible_to<ValueType> auto z)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(y.y) }, z{ static_cast<ValueType>(z) } {}
	
	// S  - S  - V1
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertibleTo<1, ValueType> auto z)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y) }, z{ static_cast<ValueType>(z.z) } {}
	
	// V1 - S  - V1
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertibleTo<1, ValueType> auto& x, const std::convertible_to<ValueType> auto y, const VectorConvertibleTo<1, ValueType> auto z)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(y) }, z{ static_cast<ValueType>(z.z) } {}
	
	// S  - V1 - V1
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const VectorConvertibleTo<1, ValueType> auto z)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(y.y) }, z{ static_cast<ValueType>(z.z) } {}
	
	// V1 - V1 - V1
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertibleTo<1, ValueType> auto& x, const VectorConvertibleTo<1, ValueType> auto y, const VectorConvertibleTo<1, ValueType> auto z)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(y.y) }, z{ static_cast<ValueType>(z.z) } {}


	// From Vector<2, T, C>
	// V2 - S
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertibleTo<2, ValueType> auto& xy, const std::convertible_to<ValueType> auto z)
		: x{ static_cast<ValueType>(xy.x) }, y{ static_cast<ValueType>(xy.y) }, z{ static_cast<ValueType>(z) } {}
	
	// V2 - V1
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertibleTo<2, ValueType> auto& xy, const VectorConvertibleTo<1, ValueType> auto z)
		: x{ static_cast<ValueType>(xy.x) }, y{ static_cast<ValueType>(xy.y) }, z{ static_cast<ValueType>(z.z) } {}
	
	// S  - V2
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector(const std::convertible_to<ValueType> auto& x, const VectorConvertibleTo<2, ValueType> auto yz)
		: x{ static_cast<ValueType>(x) }, y{ static_cast<ValueType>(yz.y) }, z{ static_cast<ValueType>(yz.z) } {}
	
	// V1 - V2
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertibleTo<1, ValueType> auto& x, const VectorConvertibleTo<2, ValueType> auto yz)
		: x{ static_cast<ValueType>(x.x) }, y{ static_cast<ValueType>(yz.y) }, z{ static_cast<ValueType>(yz.z) } {}

	// From Vector<4, T, C>
	// V4
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>::Vector(const VectorConvertibleTo<4, ValueType> auto& vec)
		: x{ static_cast<ValueType>(vec.x) }, y{ static_cast<ValueType>(vec.y) }, z{ static_cast<ValueType>(vec.z) } {}

	//-----------------------------------------------//
	//------------- Conversion Operator -------------//
	//-----------------------------------------------//
	

	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template <typename ValueType>
	inline constexpr bool Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator==(const VectorConvertibleTo<3, ValueType> auto& rhs) {
		return this->x == rhs.x && this->y == rhs.y && this->z && rhs.z;
	}

	template <typename ValueType>
	inline constexpr bool Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator!=(const VectorConvertibleTo<3, ValueType> auto& rhs) {
		return !(*this == rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator&&(const VectorConvertibleTo<3, ValueType> auto& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(this->x && rhs.x, this->y && rhs.y, this->z && rhs.z);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator||(const VectorConvertibleTo<3, ValueType> auto& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(this->x || rhs.x, this->y || rhs.y, this->z || rhs.z);
	}

	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator+() const {
		return *this;
	}

	// operator -I
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator-() const {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(-this->x, -this->y, -this->z);
	}

	// operator ~I
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator~() const {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(~this->x, ~this->y, ~this->z);
	}


	// operator ++I
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator++() {
		++this->x;
		++this->y;
		++this->z;
		return *this;
	}
	
	// operator --I
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator--() {
		--this->x;
		--this->y;
		--this->z;
		return *this;
	}

	// operator I++
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator++(int) {
		Vector<3, ValueType, EngineCompute::EngineComputeBasic> res(*this);
		++* this;
		return res;
	}

	// operator I--
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator--(int) {
		Vector<3, ValueType, EngineCompute::EngineComputeBasic> res(*this);
		--* this;
		return res;
	}

	// operator =
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator=(const std::convertible_to<ValueType> auto scalar) {
		this->x = static_cast<ValueType>(scalar);
		this->y = static_cast<ValueType>(scalar);
		this->z = static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator=(const VectorConvertibleTo<3, ValueType> auto& vec) {
		this->x = static_cast<ValueType>(vec.x);
		this->y = static_cast<ValueType>(vec.y);
		this->z = static_cast<ValueType>(vec.z);
		return *this;
	}

	// operator +=
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator+=(const std::convertible_to<ValueType> auto scalar) {
		this->x += static_cast<ValueType>(scalar);
		this->y += static_cast<ValueType>(scalar);
		this->z += static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator+=(const VectorConvertibleTo<3, ValueType> auto& vec) {
		this->x += static_cast<ValueType>(vec.x);
		this->y += static_cast<ValueType>(vec.y);
		this->z += static_cast<ValueType>(vec.z);
		return *this;
	}

	// operator -=
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator-=(const std::convertible_to<ValueType> auto scalar) {
		this->x -= static_cast<ValueType>(scalar);
		this->y -= static_cast<ValueType>(scalar);
		this->z -= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator-=(const VectorConvertibleTo<3, ValueType> auto& vec) {
		this->x -= static_cast<ValueType>(vec.x);
		this->y -= static_cast<ValueType>(vec.y);
		this->z -= static_cast<ValueType>(vec.z);
		return *this;
	}

	// operator *=
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator*=(const std::convertible_to<ValueType> auto scalar) {
		this->x *= static_cast<ValueType>(scalar);
		this->y *= static_cast<ValueType>(scalar);
		this->z *= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator*=(const VectorConvertibleTo<3, ValueType> auto& vec) {
		this->x *= static_cast<ValueType>(vec.x);
		this->y *= static_cast<ValueType>(vec.y);
		this->z *= static_cast<ValueType>(vec.z);
		return *this;
	}

	// operator /=
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator/=(const std::convertible_to<ValueType> auto scalar) {
		this->x /= static_cast<ValueType>(scalar);
		this->y /= static_cast<ValueType>(scalar);
		this->z /= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator/=(const VectorConvertibleTo<3, ValueType> auto& vec) {
		this->x /= static_cast<ValueType>(vec.x);
		this->y /= static_cast<ValueType>(vec.y);
		this->z /= static_cast<ValueType>(vec.z);
		return *this;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//
	// 
	// operator %=
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator%=(const std::convertible_to<ValueType> auto scalar) {
		this->x %= static_cast<ValueType>(scalar);
		this->y %= static_cast<ValueType>(scalar);
		this->z %= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator%=(const VectorConvertibleTo<3, ValueType> auto& vec) {
		this->x %= static_cast<ValueType>(vec.x);
		this->y %= static_cast<ValueType>(vec.y);
		this->z %= static_cast<ValueType>(vec.z);
		return *this;
	}

	// operator &=
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator&=(const std::convertible_to<ValueType> auto scalar) {
		this->x &= static_cast<ValueType>(scalar);
		this->y &= static_cast<ValueType>(scalar);
		this->z &= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator&=(const VectorConvertibleTo<3, ValueType> auto& vec) {
		this->x &= static_cast<ValueType>(vec.x);
		this->y &= static_cast<ValueType>(vec.y);
		this->z &= static_cast<ValueType>(vec.z);
		return *this;
	}

	// operator |=
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator|=(const std::convertible_to<ValueType> auto scalar) {
		this->x |= static_cast<ValueType>(scalar);
		this->y |= static_cast<ValueType>(scalar);
		this->z |= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator|=(const VectorConvertibleTo<3, ValueType> auto& vec) {
		this->x |= static_cast<ValueType>(vec.x);
		this->y |= static_cast<ValueType>(vec.y);
		this->z |= static_cast<ValueType>(vec.z);
		return *this;
	}

	// operator ^=
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator^=(const std::convertible_to<ValueType> auto scalar) {
		this->x ^= static_cast<ValueType>(scalar);
		this->y ^= static_cast<ValueType>(scalar);
		this->z ^= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator^=(const VectorConvertibleTo<3, ValueType> auto& vec) {
		this->x ^= static_cast<ValueType>(vec.x);
		this->y ^= static_cast<ValueType>(vec.y);
		this->z ^= static_cast<ValueType>(vec.z);
		return *this;
	}

	// operator <<=
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator<<=(const std::convertible_to<ValueType> auto scalar) {
		this->x <<= static_cast<ValueType>(scalar);
		this->y <<= static_cast<ValueType>(scalar);
		this->z <<= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator<<=(const VectorConvertibleTo<3, ValueType> auto& vec) {
		this->x <<= static_cast<ValueType>(vec.x);
		this->y <<= static_cast<ValueType>(vec.y);
		this->z <<= static_cast<ValueType>(vec.z);
		return *this;
	}

	// operator >>=
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator>>=(const std::convertible_to<ValueType> auto scalar) {
		this->x >>= static_cast<ValueType>(scalar);
		this->y >>= static_cast<ValueType>(scalar);
		this->z >>= static_cast<ValueType>(scalar);
		return *this;
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic>& Vector<3, ValueType, EngineCompute::EngineComputeBasic>::operator>>=(const VectorConvertibleTo<3, ValueType> auto& vec) {
		this->x >>= static_cast<ValueType>(vec.x);
		this->y >>= static_cast<ValueType>(vec.y);
		this->z >>= static_cast<ValueType>(vec.z);
		return *this;
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator+(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator+(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator+(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	// operator -
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator-(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator-(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator-(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	// operator *
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator*(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator*(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator*(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	// operator /
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator/(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator/(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator/(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator%(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x % rhs, lhs.y % rhs, lhs.z % rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator%(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs % rhs.x, lhs % rhs.y, lhs % rhs.z);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator%(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x % rhs.x, lhs.y % rhs.y, lhs.z % rhs.z);
	}

	// operator &
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator&(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x & rhs, lhs.y & rhs, lhs.z & rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator&(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs & rhs.x, lhs & rhs.y, lhs & rhs.z);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator&(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x & rhs.x, lhs.y & rhs.y, lhs.z & rhs.z);
	}

	// operator |
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator|(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x | rhs, lhs.y | rhs, lhs.z | rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator|(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs | rhs.x, lhs | rhs.y, lhs | rhs.z);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator|(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x | rhs.x, lhs.y | rhs.y, lhs.z | rhs.z);
	}

	// operator ^
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator^(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x ^ rhs, lhs.y ^ rhs, lhs.z ^ rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator^(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs ^ rhs.x, lhs ^ rhs.y, lhs ^ rhs.z);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator^(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x ^ rhs.x, lhs.y ^ rhs.y, lhs.z ^ rhs.z);
	}

	// operator <<
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator<<(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x << rhs, lhs.y << rhs, lhs.z << rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator<<(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs << rhs.x, rhs << rhs.y, rhs << rhs.z);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator<<(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x << rhs.x, lhs.y << rhs.y, lhs.z << rhs.z);
	}

	// operator >>
	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator>>(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x >> rhs, lhs.y >> rhs, lhs.z >> rhs);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator>>(const std::convertible_to<ValueType> auto lhs, const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs >> rhs.x, lhs >> rhs.y, lhs >> rhs.z);
	}

	template <typename ValueType>
	inline constexpr Vector<3, ValueType, EngineCompute::EngineComputeBasic> operator>>(const Vector<3, ValueType, EngineCompute::EngineComputeBasic>& lhs, const VectorConvertibleTo<3, ValueType> auto& rhs) {
		return Vector<3, ValueType, EngineCompute::EngineComputeBasic>(lhs.x >> rhs.x, lhs.y >> rhs.y, lhs.z >> rhs.z);
	}
}