#pragma once

#include "Vector4BasicImpl.h"

namespace EngineCore {

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

	template <typename T>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>::Vector()
		: x{}, y{}, z{}, w{} {}

	template <typename T>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>::Vector(const T scalar)
		: x{ scalar }, y{ scalar }, z{ scalar }, w{ scalar } {}

	template <typename T>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>::Vector(const T valueX, const T valueY, const T valueZ, const T valueW)
		: x{ valueX }, y{ valueY }, z{ valueY }, w{ valueW } {}

	template <typename T>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>::Vector(const Vector<4, T, EngineCompute::EngineComputeBasic>& vec) = default;


	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//

	template <typename T>
	template <typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>::Vector(K scalar)
		: x{ static_cast<T>(scalar) }, y{ static_cast<T>(scalar) }, z{ static_cast<T>(scalar) }, w{ static_cast<T>(scalar) } {}

	template <typename T>
	template <typename K1, typename K2, typename K3, typename K4>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>::Vector(const K1 valueX, const K2 valueY, const K3 valueZ, const K4 valueW)
		: x{ static_cast<T>(valueX) }, y{ static_cast<T>(valueY) }, z{ static_cast<T>(valueZ) }, w{ static_cast<T>(valueW) } {}

	template <typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>::Vector(const Vector<4, K, ComputeAlgoritmClient>& vec)
		: x{ static_cast<T>(vec.x) }, y{ static_cast<T>(vec.y) }, z{ static_cast<T>(vec.z) }, w{ static_cast<T>(vec.w) } {}

	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr bool Vector<4, T, EngineCompute::EngineComputeBasic>::operator==(const Vector<4, K, ComputeAlgoritmClient>& rhs) {
		return this->x == rhs.x && this->y == rhs.y && this->z && rhs.z && this->w && rhs.w;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr bool Vector<4, T, EngineCompute::EngineComputeBasic>::operator!=(const Vector<4, K, ComputeAlgoritmClient>& rhs) {
		return !(*this == rhs);
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> Vector<4, T, EngineCompute::EngineComputeBasic>::operator&&(const Vector<4, K, ComputeAlgoritmClient>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(this->x && rhs.x, this->y && rhs.y, this->z && rhs.z, this->w && rhs.w);
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> Vector<4, T, EngineCompute::EngineComputeBasic>::operator||(const Vector<4, K, ComputeAlgoritmClient>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(this->x || rhs.x, this->y || rhs.y, this->z || rhs.z, this->w || rhs.w);
	}

	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template<typename T>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> Vector<4, T, EngineCompute::EngineComputeBasic>::operator+() {
		return *this;
	}

	// operator -I
	template<typename T>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> Vector<4, T, EngineCompute::EngineComputeBasic>::operator-() {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(-this->x, -this->y, -this->z, -this->w);
	}

	// operator ~I
	template<typename T>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> Vector<4, T, EngineCompute::EngineComputeBasic>::operator~() {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(~this->x, ~this->y, ~this->z, ~this->w);
	}


	// operator ++I
	template<typename T>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator++() {
		++this->x;
		++this->y;
		++this->z;
		++this->w;
		return *this;
	}

	// operator --I
	template<typename T>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator--() {
		--this->x;
		--this->y;
		--this->z;
		--this->w;
		return *this;
	}

	// operator I++
	template<typename T>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> Vector<4, T, EngineCompute::EngineComputeBasic>::operator++(int) {
		Vector<4, T, EngineCompute::EngineComputeBasic> res(*this);
		++* this;
		return res;
	}

	// operator I--
	template<typename T>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> Vector<4, T, EngineCompute::EngineComputeBasic>::operator--(int) {
		Vector<4, T, EngineCompute::EngineComputeBasic> res(*this);
		--* this;
		return res;
	}

	// operator =
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator=(const K scalar) {
		this->x = static_cast<T>(scalar);
		this->y = static_cast<T>(scalar);
		this->z = static_cast<T>(scalar);
		this->w = static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator=(const Vector<4, K, ComputeAlgoritmClient>& vec) {
		this->x = static_cast<T>(vec.x);
		this->y = static_cast<T>(vec.y);
		this->z = static_cast<T>(vec.z);
		this->w = static_cast<T>(vec.w);
		return *this;
	}

	// operator +=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator+=(const K scalar) {
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		this->z += static_cast<T>(scalar);
		this->w += static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator+=(const Vector<4, K, ComputeAlgoritmClient>& vec) {
		this->x += static_cast<T>(vec.x);
		this->y += static_cast<T>(vec.y);
		this->z += static_cast<T>(vec.z);
		this->w += static_cast<T>(vec.w);
		return *this;
	}

	// operator -=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator-=(const K scalar) {
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		this->z -= static_cast<T>(scalar);
		this->w -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator-=(const Vector<4, K, ComputeAlgoritmClient>& vec) {
		this->x -= static_cast<T>(vec.x);
		this->y -= static_cast<T>(vec.y);
		this->z -= static_cast<T>(vec.z);
		this->w -= static_cast<T>(vec.w);
		return *this;
	}

	// operator *=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator*=(const K scalar) {
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		this->z *= static_cast<T>(scalar);
		this->w *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator*=(const Vector<4, K, ComputeAlgoritmClient>& vec) {
		this->x *= static_cast<T>(vec.x);
		this->y *= static_cast<T>(vec.y);
		this->z *= static_cast<T>(vec.z);
		this->w *= static_cast<T>(vec.w);
		return *this;
	}

	// operator /=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator/=(const K scalar) {
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		this->z /= static_cast<T>(scalar);
		this->w /= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator/=(const Vector<4, K, ComputeAlgoritmClient>& vec) {
		this->x /= static_cast<T>(vec.x);
		this->y /= static_cast<T>(vec.y);
		this->z /= static_cast<T>(vec.z);
		this->w /= static_cast<T>(vec.w);
		return *this;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator%=(const K scalar) {
		this->x %= static_cast<T>(scalar);
		this->y %= static_cast<T>(scalar);
		this->z %= static_cast<T>(scalar);
		this->w %= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator%=(const Vector<4, K, ComputeAlgoritmClient>& vec) {
		this->x %= static_cast<T>(vec.x);
		this->y %= static_cast<T>(vec.y);
		this->z %= static_cast<T>(vec.z);
		this->w %= static_cast<T>(vec.w);
		return *this;
	}

	// operator &=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator&=(const K scalar) {
		this->x &= static_cast<T>(scalar);
		this->y &= static_cast<T>(scalar);
		this->z &= static_cast<T>(scalar);
		this->w &= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator&=(const Vector<4, K, ComputeAlgoritmClient>& vec) {
		this->x &= static_cast<T>(vec.x);
		this->y &= static_cast<T>(vec.y);
		this->z &= static_cast<T>(vec.z);
		this->w &= static_cast<T>(vec.w);
		return *this;
	}

	// operator |=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator|=(const K scalar) {
		this->x |= static_cast<T>(scalar);
		this->y |= static_cast<T>(scalar);
		this->z |= static_cast<T>(scalar);
		this->w |= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator|=(const Vector<4, K, ComputeAlgoritmClient>& vec) {
		this->x |= static_cast<T>(vec.x);
		this->y |= static_cast<T>(vec.y);
		this->z |= static_cast<T>(vec.z);
		this->w |= static_cast<T>(vec.w);
		return *this;
	}

	// operator ^=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator^=(const K scalar) {
		this->x ^= static_cast<T>(scalar);
		this->y ^= static_cast<T>(scalar);
		this->z ^= static_cast<T>(scalar);
		this->w ^= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator^=(const Vector<4, K, ComputeAlgoritmClient>& vec) {
		this->x ^= static_cast<T>(vec.x);
		this->y ^= static_cast<T>(vec.y);
		this->z ^= static_cast<T>(vec.z);
		this->w ^= static_cast<T>(vec.w);
		return *this;
	}

	// operator <<=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator<<=(const K scalar) {
		this->x <<= static_cast<T>(scalar);
		this->y <<= static_cast<T>(scalar);
		this->z <<= static_cast<T>(scalar);
		this->w <<= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator<<=(const Vector<4, K, ComputeAlgoritmClient>& vec) {
		this->x <<= static_cast<T>(vec.x);
		this->y <<= static_cast<T>(vec.y);
		this->z <<= static_cast<T>(vec.z);
		this->w <<= static_cast<T>(vec.w);
		return *this;
	}

	// operator >>=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator>>=(const K scalar) {
		this->x >>= static_cast<T>(scalar);
		this->y >>= static_cast<T>(scalar);
		this->z >>= static_cast<T>(scalar);
		this->w >>= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic>& Vector<4, T, EngineCompute::EngineComputeBasic>::operator>>=(const Vector<4, K, ComputeAlgoritmClient>& vec) {
		this->x >>= static_cast<T>(vec.x);
		this->y >>= static_cast<T>(vec.y);
		this->z >>= static_cast<T>(vec.z);
		this->w >>= static_cast<T>(vec.w);
		return *this;
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator+(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator+(const K lhs, const Vector<4, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator+(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<4, K, ComputeAlgoritmClient>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
	}

	// operator -
	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator-(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator-(const K lhs, const Vector<4, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator-(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<4, K, ComputeAlgoritmClient>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
	}

	// operator *
	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator*(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator*(const K lhs, const Vector<4, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator*(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<4, K, ComputeAlgoritmClient>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
	}

	// operator /
	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator/(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator/(const K lhs, const Vector<4, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator/(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<4, K, ComputeAlgoritmClient>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator%(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x % rhs, lhs.y % rhs, lhs.z % rhs, lhs.w % rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator%(const K lhs, const Vector<4, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs % rhs.x, lhs % rhs.y, lhs % rhs.z, lhs % rhs.w);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator%(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<4, K, ComputeAlgoritmClient>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x % rhs.x, lhs.y % rhs.y, lhs.z % rhs.z, lhs.w % rhs.w);
	}

	// operator &
	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator&(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x & rhs, lhs.y & rhs, lhs.z & rhs, lhs.w & rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator&(const K lhs, const Vector<4, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs & rhs.x, lhs & rhs.y, lhs & rhs.z, lhs & rhs.w);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator&(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<4, K, ComputeAlgoritmClient>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x & rhs.x, lhs.y & rhs.y, lhs.z & rhs.z, lhs.w & rhs.w);
	}

	// operator |
	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator|(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x | rhs, lhs.y | rhs, lhs.z | rhs, lhs.w | rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator|(const K lhs, const Vector<4, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs | rhs.x, lhs | rhs.y, lhs | rhs.z, lhs | rhs.w);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator|(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<4, K, ComputeAlgoritmClient>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x | rhs.x, lhs.y | rhs.y, lhs.z | rhs.z, lhs.w | rhs.w);
	}

	// operator ^
	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator^(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x ^ rhs, lhs.y ^ rhs, lhs.z ^ rhs, lhs.w ^ rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator^(const K lhs, const Vector<4, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs ^ rhs.x, lhs ^ rhs.y, lhs ^ rhs.z, lhs ^ rhs.w);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator^(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<4, K, ComputeAlgoritmClient>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x ^ rhs.x, lhs.y ^ rhs.y, lhs.z ^ rhs.z, lhs.w ^ rhs.w);
	}

	// operator <<
	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator<<(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x << rhs, lhs.y << rhs, lhs.z << rhs, lhs.w << rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator<<(const K lhs, const Vector<4, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs << rhs.x, rhs << rhs.y, rhs << rhs.z, rhs << rhs.w);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator<<(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<4, K, ComputeAlgoritmClient>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x << rhs.x, lhs.y << rhs.y, lhs.z << rhs.z, lhs.w << rhs.w);
	}

	// operator >>
	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator>>(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x >> rhs, lhs.y >> rhs, lhs.z >> rhs, lhs.w >> rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator>>(const K lhs, const Vector<4, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs >> rhs.x, lhs >> rhs.y, lhs >> rhs.z, lhs >> rhs.w);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<4, T, EngineCompute::EngineComputeBasic> operator>>(const Vector<4, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<4, K, ComputeAlgoritmClient>& rhs) {
		return Vector<4, T, EngineCompute::EngineComputeBasic>(lhs.x >> rhs.x, lhs.y >> rhs.y, lhs.z >> rhs.z, lhs.w >> rhs.w);
	}
}