#pragma once

#include "Vector3BasicImpl.h"

namespace EngineCore {

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

    template <typename T>
    inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>::Vector()
		: x{}, y{}, z{} {}

	template <typename T>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>::Vector(const T scalar)
		: x{ scalar }, y{ scalar }, z{ scalar } {}

	template <typename T>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>::Vector(const T valueX, const T valueY, const T valueZ)
		: x{ valueX }, y{ valueY }, z{ valueZ } {}

	template <typename T>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>::Vector(const Vector<3, T, EngineCompute::EngineComputeBasic>& vec) = default;


	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//

	template <typename T>
	template <typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>::Vector(const K scalar)
		: x{ static_cast<T>(scalar) }, y{ static_cast<T>(scalar) }, z{ static_cast<T>(scalar) } {}

	template <typename T>
	template <typename K1, typename K2, typename K3>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>::Vector(const K1 valueX, const K2 valueY, const K3 valueZ)
		: x{ static_cast<T>(valueX) }, y{ static_cast<T>(valueY) }, z{ static_cast<T>(valueZ) } {}

	template <typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>::Vector(const Vector<3, K, ComputeAlgoritmClient>& vec)
		: x{ static_cast<T>(vec.x) }, y{ static_cast<T>(vec.y) }, z{ static_cast<T>(vec.z) } {}

	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr bool Vector<3, T, EngineCompute::EngineComputeBasic>::operator==(const Vector<3, K, ComputeAlgoritmClient>& rhs) {
		return this->x == rhs.x && this->y == rhs.y && this->z && rhs.z;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr bool Vector<3, T, EngineCompute::EngineComputeBasic>::operator!=(const Vector<3, K, ComputeAlgoritmClient>& rhs) {
		return !(*this == rhs);
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> Vector<3, T, EngineCompute::EngineComputeBasic>::operator&&(const Vector<3, K, ComputeAlgoritmClient>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(this->x && rhs.x, this->y && rhs.y, this->z && rhs.z);
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> Vector<3, T, EngineCompute::EngineComputeBasic>::operator||(const Vector<3, K, ComputeAlgoritmClient>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(this->x || rhs.x, this->y || rhs.y, this->z || rhs.z);
	}

	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template<typename T>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> Vector<3, T, EngineCompute::EngineComputeBasic>::operator+() {
		return *this;
	}

	// operator -I
	template<typename T>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> Vector<3, T, EngineCompute::EngineComputeBasic>::operator-() {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(-this->x, -this->y, -this->z);
	}

	// operator ~I
	template<typename T>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> Vector<3, T, EngineCompute::EngineComputeBasic>::operator~() {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(~this->x, ~this->y, ~this->z);
	}


	// operator ++I
	template<typename T>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator++() {
		++this->x;
		++this->y;
		++this->z;
		return *this;
	}
	
	// operator --I
	template<typename T>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator--() {
		--this->x;
		--this->y;
		--this->z;
		return *this;
	}

	// operator I++
	template<typename T>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> Vector<3, T, EngineCompute::EngineComputeBasic>::operator++(int) {
		Vector<3, T, EngineCompute::EngineComputeBasic> res(*this);
		++* this;
		return res;
	}

	// operator I--
	template<typename T>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> Vector<3, T, EngineCompute::EngineComputeBasic>::operator--(int) {
		Vector<3, T, EngineCompute::EngineComputeBasic> res(*this);
		--* this;
		return res;
	}

	// operator =
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator=(const K scalar) {
		this->x = static_cast<T>(scalar);
		this->y = static_cast<T>(scalar);
		this->z = static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator=(const Vector<3, K, ComputeAlgoritmClient>& vec) {
		this->x = static_cast<T>(vec.x);
		this->y = static_cast<T>(vec.y);
		this->z = static_cast<T>(vec.z);
		return *this;
	}

	// operator +=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator+=(const K scalar) {
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		this->z += static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator+=(const Vector<3, K, ComputeAlgoritmClient>& vec) {
		this->x += static_cast<T>(vec.x);
		this->y += static_cast<T>(vec.y);
		this->z += static_cast<T>(vec.z);
		return *this;
	}

	// operator -=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator-=(const K scalar) {
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		this->z -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator-=(const Vector<3, K, ComputeAlgoritmClient>& vec) {
		this->x -= static_cast<T>(vec.x);
		this->y -= static_cast<T>(vec.y);
		this->z -= static_cast<T>(vec.z);
		return *this;
	}

	// operator *=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator*=(const K scalar) {
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		this->z *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator*=(const Vector<3, K, ComputeAlgoritmClient>& vec) {
		this->x *= static_cast<T>(vec.x);
		this->y *= static_cast<T>(vec.y);
		this->z *= static_cast<T>(vec.z);
		return *this;
	}

	// operator /=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator/=(const K scalar) {
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		this->z /= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator/=(const Vector<3, K, ComputeAlgoritmClient>& vec) {
		this->x /= static_cast<T>(vec.x);
		this->y /= static_cast<T>(vec.y);
		this->z /= static_cast<T>(vec.z);
		return *this;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//
	// 
	// operator %=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator%=(const K scalar) {
		this->x %= static_cast<T>(scalar);
		this->y %= static_cast<T>(scalar);
		this->z %= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator%=(const Vector<3, K, ComputeAlgoritmClient>& vec) {
		this->x %= static_cast<T>(vec.x);
		this->y %= static_cast<T>(vec.y);
		this->z %= static_cast<T>(vec.z);
		return *this;
	}

	// operator &=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator&=(const K scalar) {
		this->x &= static_cast<T>(scalar);
		this->y &= static_cast<T>(scalar);
		this->z &= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator&=(const Vector<3, K, ComputeAlgoritmClient>& vec) {
		this->x &= static_cast<T>(vec.x);
		this->y &= static_cast<T>(vec.y);
		this->z &= static_cast<T>(vec.z);
		return *this;
	}

	// operator |=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator|=(const K scalar) {
		this->x |= static_cast<T>(scalar);
		this->y |= static_cast<T>(scalar);
		this->z |= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator|=(const Vector<3, K, ComputeAlgoritmClient>& vec) {
		this->x |= static_cast<T>(vec.x);
		this->y |= static_cast<T>(vec.y);
		this->z |= static_cast<T>(vec.z);
		return *this;
	}

	// operator ^=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator^=(const K scalar) {
		this->x ^= static_cast<T>(scalar);
		this->y ^= static_cast<T>(scalar);
		this->z ^= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator^=(const Vector<3, K, ComputeAlgoritmClient>& vec) {
		this->x ^= static_cast<T>(vec.x);
		this->y ^= static_cast<T>(vec.y);
		this->z ^= static_cast<T>(vec.z);
		return *this;
	}

	// operator <<=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator<<=(const K scalar) {
		this->x <<= static_cast<T>(scalar);
		this->y <<= static_cast<T>(scalar);
		this->z <<= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator<<=(const Vector<3, K, ComputeAlgoritmClient>& vec) {
		this->x <<= static_cast<T>(vec.x);
		this->y <<= static_cast<T>(vec.y);
		this->z <<= static_cast<T>(vec.z);
		return *this;
	}

	// operator >>=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator>>=(const K scalar) {
		this->x >>= static_cast<T>(scalar);
		this->y >>= static_cast<T>(scalar);
		this->z >>= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic>& Vector<3, T, EngineCompute::EngineComputeBasic>::operator>>=(const Vector<3, K, ComputeAlgoritmClient>& vec) {
		this->x >>= static_cast<T>(vec.x);
		this->y >>= static_cast<T>(vec.y);
		this->z >>= static_cast<T>(vec.z);
		return *this;
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator+(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator+(const K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator+(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	// operator -
	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator-(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator-(const K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator-(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	// operator *
	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator*(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator*(const K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator*(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	// operator /
	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator/(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator/(const K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator/(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator%(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x % rhs, lhs.y % rhs, lhs.z % rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator%(const K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs % rhs.x, lhs % rhs.y, lhs % rhs.z);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator%(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x % rhs.x, lhs.y % rhs.y, lhs.z % rhs.z);
	}

	// operator &
	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator&(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x & rhs, lhs.y & rhs, lhs.z & rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator&(const K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs & rhs.x, lhs & rhs.y, lhs & rhs.z);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator&(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x & rhs.x, lhs.y & rhs.y, lhs.z & rhs.z);
	}

	// operator |
	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator|(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x | rhs, lhs.y | rhs, lhs.z | rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator|(const K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs | rhs.x, lhs | rhs.y, lhs | rhs.z);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator|(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x | rhs.x, lhs.y | rhs.y, lhs.z | rhs.z);
	}

	// operator ^
	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator^(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x ^ rhs, lhs.y ^ rhs, lhs.z ^ rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator^(const K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs ^ rhs.x, lhs ^ rhs.y, lhs ^ rhs.z);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator^(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x ^ rhs.x, lhs.y ^ rhs.y, lhs.z ^ rhs.z);
	}

	// operator <<
	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator<<(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x << rhs, lhs.y << rhs, lhs.z << rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator<<(const K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs << rhs.x, rhs << rhs.y, rhs << rhs.z);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator<<(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x << rhs.x, lhs.y << rhs.y, lhs.z << rhs.z);
	}

	// operator >>
	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator>>(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x >> rhs, lhs.y >> rhs, lhs.z >> rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator>>(const K lhs, const Vector<3, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs >> rhs.x, lhs >> rhs.y, lhs >> rhs.z);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<3, T, EngineCompute::EngineComputeBasic> operator>>(const Vector<3, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<3, K, ComputeAlgoritmClient>& rhs) {
		return Vector<3, T, EngineCompute::EngineComputeBasic>(lhs.x >> rhs.x, lhs.y >> rhs.y, lhs.z >> rhs.z);
	}
}