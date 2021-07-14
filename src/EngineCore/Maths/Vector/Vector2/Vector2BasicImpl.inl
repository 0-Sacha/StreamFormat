#pragma once

#include "Vector2BasicImpl.h"

namespace EngineCore {

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

    template <typename T>
    inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>::Vector()
		: x{}, y{} {}


    template <typename T>
    inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>::Vector(const T scalar)
		: x{ scalar }, y{ scalar } {}

	template <typename T>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>::Vector(const T valueX, const T valueY)
		: x{ valueX }, y{ valueY } {}

    template <typename T>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>::Vector(const Vector<2, T, EngineCompute::EngineComputeBasic>& vec) = default;

	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//

	template <typename T>
	template <typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>::Vector(const K scalar)
		: x{ static_cast<T>(scalar) }, y{ static_cast<T>(scalar) } {}

	template <typename T>
	template <typename K1, typename K2>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>::Vector(const K1 valueX, const K2 valueY)
		: x{ static_cast<T>(valueX) }, y{ static_cast<T>(valueY) } {}

	template <typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>::Vector(const Vector<2, K, ComputeAlgoritmClient>& vec)
		: x{ static_cast<T>(vec.x) }, y{ static_cast<T>(vec.y) } {}


	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr bool Vector<2, T, EngineCompute::EngineComputeBasic>::operator==(const Vector<2, K, ComputeAlgoritmClient>& rhs) {
		return this->x == rhs.x && this->y == rhs.y;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr bool Vector<2, T, EngineCompute::EngineComputeBasic>::operator!=(const Vector<2, K, ComputeAlgoritmClient>& rhs) {
		return !(*this == rhs);
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> Vector<2, T, EngineCompute::EngineComputeBasic>::operator&&(const Vector<2, K, ComputeAlgoritmClient>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(this->x && rhs.x, this->y && rhs.y);
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> Vector<2, T, EngineCompute::EngineComputeBasic>::operator||(const Vector<2, K, ComputeAlgoritmClient>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(this->x || rhs.x, this->y || rhs.y);
	}

	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template<typename T>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> Vector<2, T, EngineCompute::EngineComputeBasic>::operator+() {
		return *this;
	}

	// operator -I
	template<typename T>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> Vector<2, T, EngineCompute::EngineComputeBasic>::operator-() {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(-this->x, -this->y);
	}

	// operator ~I
	template<typename T>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> Vector<2, T, EngineCompute::EngineComputeBasic>::operator~() {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(~this->x, ~this->y);
	}


	// operator ++I
	template<typename T>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator++() {
		++this->x;
		++this->y;
		return *this;
	}
	
	// operator --I
	template<typename T>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator--() {
		--this->x;
		--this->y;
		return *this;
	}

	// operator I++
	template<typename T>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> Vector<2, T, EngineCompute::EngineComputeBasic>::operator++(int) {
		Vector<2, T, EngineCompute::EngineComputeBasic> res(*this);
		++* this;
		return res;
	}

	// operator I--
	template<typename T>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> Vector<2, T, EngineCompute::EngineComputeBasic>::operator--(int) {
		Vector<2, T, EngineCompute::EngineComputeBasic> res(*this);
		--* this;
		return res;
	}


	// operator =
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator=(const K scalar) {
		this->x = static_cast<T>(scalar);
		this->y = static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator=(const Vector<2, K, ComputeAlgoritmClient>& vec) {
		this->x = static_cast<T>(vec.x);
		this->y = static_cast<T>(vec.y);
		return *this;
	}

	// operator +=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator+=(const K scalar) {
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator+=(const Vector<2, K, ComputeAlgoritmClient>& vec) {
		this->x += static_cast<T>(vec.x);
		this->y += static_cast<T>(vec.y);
		return *this;
	}

	// operator -=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator-=(const K scalar) {
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator-=(const Vector<2, K, ComputeAlgoritmClient>& vec) {
		this->x -= static_cast<T>(vec.x);
		this->y -= static_cast<T>(vec.y);
		return *this;
	}

	// operator *=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator*=(const K scalar) {
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator*=(const Vector<2, K, ComputeAlgoritmClient>& vec) {
		this->x *= static_cast<T>(vec.x);
		this->y *= static_cast<T>(vec.y);
		return *this;
	}

	// operator /=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator/=(const K scalar) {
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator/=(const Vector<2, K, ComputeAlgoritmClient>& vec) {
		this->x /= static_cast<T>(vec.x);
		this->y /= static_cast<T>(vec.y);
		return *this;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator%=(const K scalar) {
		this->x %= static_cast<T>(scalar);
		this->y %= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator%=(const Vector<2, K, ComputeAlgoritmClient>& vec) {
		this->x %= static_cast<T>(vec.x);
		this->y %= static_cast<T>(vec.y);
		return *this;
	}

	// operator &=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator&=(const K scalar) {
		this->x &= static_cast<T>(scalar);
		this->y &= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator&=(const Vector<2, K, ComputeAlgoritmClient>& vec) {
		this->x &= static_cast<T>(vec.x);
		this->y &= static_cast<T>(vec.y);
		return *this;
	}

	// operator |=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator|=(const K scalar) {
		this->x |= static_cast<T>(scalar);
		this->y |= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator|=(const Vector<2, K, ComputeAlgoritmClient>& vec) {
		this->x |= static_cast<T>(vec.x);
		this->y |= static_cast<T>(vec.y);
		return *this;
	}

	// operator ^=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator^=(const K scalar) {
		this->x ^= static_cast<T>(scalar);
		this->y ^= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator^=(const Vector<2, K, ComputeAlgoritmClient>& vec) {
		this->x ^= static_cast<T>(vec.x);
		this->y ^= static_cast<T>(vec.y);
		return *this;
	}

	// operator <<=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator<<=(const K scalar) {
		this->x <<= static_cast<T>(scalar);
		this->y <<= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator<<=(const Vector<2, K, ComputeAlgoritmClient>& vec) {
		this->x <<= static_cast<T>(vec.x);
		this->y <<= static_cast<T>(vec.y);
		return *this;
	}

	// operator >>=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator>>=(const K scalar) {
		this->x >>= static_cast<T>(scalar);
		this->y >>= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic>& Vector<2, T, EngineCompute::EngineComputeBasic>::operator>>=(const Vector<2, K, ComputeAlgoritmClient>& vec) {
		this->x >>= static_cast<T>(vec.x);
		this->y >>= static_cast<T>(vec.y);
		return *this;
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator+(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x + rhs, lhs.y + rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator+(const K lhs, const Vector<2, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs + rhs.x, lhs + rhs.y);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator+(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<2, K, ComputeAlgoritmClient>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	// operator -
	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator-(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x - rhs, lhs.y - rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator-(const K lhs, const Vector<2, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs - rhs.x, lhs - rhs.y);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator-(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<2, K, ComputeAlgoritmClient>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	// operator *
	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator*(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x * rhs, lhs.y * rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator*(const K lhs, const Vector<2, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs * rhs.x, lhs * rhs.y);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator*(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<2, K, ComputeAlgoritmClient>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x * rhs.x, lhs.y * rhs.y);
	}

	// operator /
	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator/(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x / rhs, lhs.y / rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator/(const K lhs, const Vector<2, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs / rhs.x, lhs / rhs.y);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator/(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<2, K, ComputeAlgoritmClient>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x / rhs.x, lhs.y / rhs.y);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator%(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x % rhs, lhs.y % rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator%(const K lhs, const Vector<2, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs % rhs.x, lhs % rhs.y);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator%(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<2, K, ComputeAlgoritmClient>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x % rhs.x, lhs.y % rhs.y);
	}

	// operator &
	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator&(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x & rhs, lhs.y & rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator&(const K lhs, const Vector<2, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs & rhs.x, lhs & rhs.y);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator&(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<2, K, ComputeAlgoritmClient>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x & rhs.x, lhs.y & rhs.y);
	}

	// operator |
	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator|(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x | rhs, lhs.y | rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator|(const K lhs, const Vector<2, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs | rhs.x, lhs | rhs.y);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator|(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<2, K, ComputeAlgoritmClient>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x | rhs.x, lhs.y | rhs.y);
	}

	// operator ^
	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator^(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x ^ rhs, lhs.y ^ rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator^(const K lhs, const Vector<2, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs ^ rhs.x, lhs ^ rhs.y);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator^(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<2, K, ComputeAlgoritmClient>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x ^ rhs.x, lhs.y ^ rhs.y);
	}

	// operator <<
	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator<<(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x << rhs, lhs.y << rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator<<(const K lhs, const Vector<2, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs << rhs.x, rhs << rhs.y);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator<<(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<2, K, ComputeAlgoritmClient>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x << rhs.x, lhs.y << rhs.y);
	}

	// operator >>
	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator>>(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x >> rhs, lhs.y >> rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator>>(const K lhs, const Vector<2, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs >> rhs.x, lhs >> rhs.y);
	}

	template<typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<2, T, EngineCompute::EngineComputeBasic> operator>>(const Vector<2, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<2, K, ComputeAlgoritmClient>& rhs) {
		return Vector<2, T, EngineCompute::EngineComputeBasic>(lhs.x >> rhs.x, lhs.y >> rhs.y);
	}
}