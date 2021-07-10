#pragma once

#include "BasicVector3.h"

namespace EngineCore {

	//----------------------------------//
	//------------- Values -------------//
	//----------------------------------//

	template<typename T>
	inline constexpr T& BasicVector<3, T>::Data(const uint8_t idx) {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		}
	}

	template<typename T>
	inline constexpr const T& BasicVector<3, T>::Data(const uint8_t idx) const {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		}
	}

	template<typename T>
	inline constexpr T& BasicVector<3, T>::operator[](const uint8_t idx) {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		}
	}

	template<typename T>
	inline constexpr const T& BasicVector<3, T>::operator[](const uint8_t idx) const {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		}
	}

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

    template <typename T>
    inline constexpr BasicVector<3, T>::BasicVector()
        : x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)) {}


    template <typename T>
    template <typename K>
    inline constexpr BasicVector<3, T>::BasicVector(K scalar)
        : x(static_cast<T>(scalar)), y(static_cast<T>(scalar)), z(static_cast<T>(scalar)) {}

	template <typename T>
	template <typename K1, typename K2, typename K3>
	inline constexpr BasicVector<3, T>::BasicVector(const K1 valueX, const K2 valueY, const K3 valueZ)
		: x(static_cast<T>(valueX)), y(static_cast<T>(valueY)), z(static_cast<T>(valueZ)) {}

    template <typename T>
    template <typename K>
    inline constexpr BasicVector<3, T>::BasicVector(const BasicVector<3, K> &vec)
        :  x(static_cast<T>(vec.x)), y(static_cast<T>(vec.y)), z(static_cast<T>(vec.z)) {}

	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//

	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template<typename T>
	template<typename K>
	inline constexpr bool BasicVector<3, T>::operator==(const BasicVector<3, K>& rhs) {
		return this->x == rhs.x && this->y == rhs.y && this->z && rhs.z;
	}

	template<typename T>
	template<typename K>
	inline constexpr bool BasicVector<3, T>::operator!=(const BasicVector<3, K>& rhs) {
		return !(*this == rhs);
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template<typename T>
	inline constexpr BasicVector<3, T> BasicVector<3, T>::operator+() {
		return *this;
	}

	// operator -I
	template<typename T>
	inline constexpr BasicVector<3, T> BasicVector<3, T>::operator-() {
		return BasicVector<3, T>(-this->x, -this->y, -this->z);
	}

	// operator ++I
	template<typename T>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator++() {
		++this->x;
		++this->y;
		++this->z;
		return *this;
	}
	
	// operator --I
	template<typename T>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator--() {
		--this->x;
		--this->y;
		--this->z;
		return *this;
	}

	// operator I++
	template<typename T>
	inline constexpr BasicVector<3, T> BasicVector<3, T>::operator++(int) {
		BasicVector<3, T> res(*this);
		++* this;
		return res;
	}

	// operator I--
	template<typename T>
	inline constexpr BasicVector<3, T> BasicVector<3, T>::operator--(int) {
		BasicVector<3, T> res(*this);
		--* this;
		return res;
	}

	// operator =
	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator=(const K scalar) {
		this->x = static_cast<T>(scalar);
		this->y = static_cast<T>(scalar);
		this->z = static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator=(const BasicVector<3, K>& vec) {
		this->x = static_cast<T>(vec.x);
		this->y = static_cast<T>(vec.y);
		this->z = static_cast<T>(vec.z);
		return *this;
	}

	// operator +=
	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator+=(const K scalar) {
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		this->z += static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator+=(const BasicVector<3, K>& vec) {
		this->x += static_cast<T>(vec.x);
		this->y += static_cast<T>(vec.y);
		this->z += static_cast<T>(vec.z);
		return *this;
	}

	// operator -=
	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator-=(const K scalar) {
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		this->z -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator-=(const BasicVector<3, K>& vec) {
		this->x -= static_cast<T>(vec.x);
		this->y -= static_cast<T>(vec.y);
		this->z -= static_cast<T>(vec.z);
		return *this;
	}

	// operator *=
	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator*=(const K scalar) {
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		this->z *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator*=(const BasicVector<3, K>& vec) {
		this->x *= static_cast<T>(vec.x);
		this->y *= static_cast<T>(vec.y);
		this->z *= static_cast<T>(vec.z);
		return *this;
	}

	// operator /=
	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator/=(const K scalar) {
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		this->z /= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator/=(const BasicVector<3, K>& vec) {
		this->x /= static_cast<T>(vec.x);
		this->y /= static_cast<T>(vec.y);
		this->z /= static_cast<T>(vec.z);
		return *this;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// binary condition
	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T> BasicVector<3, T>::operator&&(const BasicVector<3, K>& rhs) {
		return BasicVector<3, T>(this->x && rhs.x, this->y && rhs.y, this->z && rhs.z);
	}

	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T> BasicVector<3, T>::operator||(const BasicVector<3, K>& rhs) {
		return BasicVector<3, T>(this->x || rhs.x, this->y || rhs.y, this->z || rhs.z);
	}

	// operator ~I
	template<typename T>
	inline constexpr BasicVector<3, T> BasicVector<3, T>::operator~() {
		return BasicVector<3, T>(~this->x, ~this->y, ~this->z);
	}

	// operator %=
	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator%=(const K scalar) {
		this->x %= static_cast<T>(scalar);
		this->y %= static_cast<T>(scalar);
		this->z %= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator%=(const BasicVector<3, K>& vec) {
		this->x %= static_cast<T>(vec.x);
		this->y %= static_cast<T>(vec.y);
		this->z %= static_cast<T>(vec.z);
		return *this;
	}

	// operator &=
	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator&=(const K scalar) {
		this->x &= static_cast<T>(scalar);
		this->y &= static_cast<T>(scalar);
		this->z &= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator&=(const BasicVector<3, K>& vec) {
		this->x &= static_cast<T>(vec.x);
		this->y &= static_cast<T>(vec.y);
		this->z &= static_cast<T>(vec.z);
		return *this;
	}

	// operator |=
	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator|=(const K scalar) {
		this->x |= static_cast<T>(scalar);
		this->y |= static_cast<T>(scalar);
		this->z |= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator|=(const BasicVector<3, K>& vec) {
		this->x |= static_cast<T>(vec.x);
		this->y |= static_cast<T>(vec.y);
		this->z |= static_cast<T>(vec.z);
		return *this;
	}

	// operator ^=
	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator^=(const K scalar) {
		this->x ^= static_cast<T>(scalar);
		this->y ^= static_cast<T>(scalar);
		this->z ^= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator^=(const BasicVector<3, K>& vec) {
		this->x ^= static_cast<T>(vec.x);
		this->y ^= static_cast<T>(vec.y);
		this->z ^= static_cast<T>(vec.z);
		return *this;
	}

	// operator <<=
	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator<<=(const K scalar) {
		this->x <<= static_cast<T>(scalar);
		this->y <<= static_cast<T>(scalar);
		this->z <<= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator<<=(const BasicVector<3, K>& vec) {
		this->x <<= static_cast<T>(vec.x);
		this->y <<= static_cast<T>(vec.y);
		this->z <<= static_cast<T>(vec.z);
		return *this;
	}

	// operator >>=
	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator>>=(const K scalar) {
		this->x >>= static_cast<T>(scalar);
		this->y >>= static_cast<T>(scalar);
		this->z >>= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr BasicVector<3, T>& BasicVector<3, T>::operator>>=(const BasicVector<3, K>& vec) {
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
	inline constexpr BasicVector<3, T> operator+(const BasicVector<3, T>& lhs, const K rhs) {
		return BasicVector<3, T>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator+(const K lhs, const BasicVector<3, T>& rhs) {
		return BasicVector<3, T>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator+(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) {
		return BasicVector<3, T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	// operator -
	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator-(const BasicVector<3, T>& lhs, const K rhs) {
		return BasicVector<3, T>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator-(const K lhs, const BasicVector<3, T>& rhs) {
		return BasicVector<3, T>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator-(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) {
		return BasicVector<3, T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	// operator *
	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator*(const BasicVector<3, T>& lhs, const K rhs) {
		return BasicVector<3, T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator*(const K lhs, const BasicVector<3, T>& rhs) {
		return BasicVector<3, T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator*(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) {
		return BasicVector<3, T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	// operator /
	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator/(const BasicVector<3, T>& lhs, const K rhs) {
		return BasicVector<3, T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator/(const K lhs, const BasicVector<3, T>& rhs) {
		return BasicVector<3, T>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator/(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) {
		return BasicVector<3, T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator%(const BasicVector<3, T>& lhs, const K rhs) {
		return BasicVector<3, T>(lhs.x % rhs, lhs.y % rhs, lhs.z % rhs);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator%(const K lhs, const BasicVector<3, T>& rhs) {
		return BasicVector<3, T>(lhs % rhs.x, lhs % rhs.y, lhs % rhs.z);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator%(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) {
		return BasicVector<3, T>(lhs.x % rhs.x, lhs.y % rhs.y, lhs.z % rhs.z);
	}

	// operator &
	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator&(const BasicVector<3, T>& lhs, const K rhs) {
		return BasicVector<3, T>(lhs.x & rhs, lhs.y & rhs, lhs.z & rhs);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator&(const K lhs, const BasicVector<3, T>& rhs) {
		return BasicVector<3, T>(lhs & rhs.x, lhs & rhs.y, lhs & rhs.z);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator&(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) {
		return BasicVector<3, T>(lhs.x & rhs.x, lhs.y & rhs.y, lhs.z & rhs.z);
	}

	// operator |
	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator|(const BasicVector<3, T>& lhs, const K rhs) {
		return BasicVector<3, T>(lhs.x | rhs, lhs.y | rhs, lhs.z | rhs);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator|(const K lhs, const BasicVector<3, T>& rhs) {
		return BasicVector<3, T>(lhs | rhs.x, lhs | rhs.y, lhs | rhs.z);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator|(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) {
		return BasicVector<3, T>(lhs.x | rhs.x, lhs.y | rhs.y, lhs.z | rhs.z);
	}

	// operator ^
	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator^(const BasicVector<3, T>& lhs, const K rhs) {
		return BasicVector<3, T>(lhs.x ^ rhs, lhs.y ^ rhs, lhs.z ^ rhs);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator^(const K lhs, const BasicVector<3, T>& rhs) {
		return BasicVector<3, T>(lhs ^ rhs.x, lhs ^ rhs.y, lhs ^ rhs.z);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator^(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) {
		return BasicVector<3, T>(lhs.x ^ rhs.x, lhs.y ^ rhs.y, lhs.z ^ rhs.z);
	}

	// operator <<
	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator<<(const BasicVector<3, T>& lhs, const K rhs) {
		return BasicVector<3, T>(lhs.x << rhs, lhs.y << rhs, lhs.z << rhs);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator<<(const K lhs, const BasicVector<3, T>& rhs) {
		return BasicVector<3, T>(lhs << rhs.x, rhs << rhs.y, rhs << rhs.z);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator<<(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) {
		return BasicVector<3, T>(lhs.x << rhs.x, lhs.y << rhs.y, lhs.z << rhs.z);
	}

	// operator >>
	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator>>(const BasicVector<3, T>& lhs, const K rhs) {
		return BasicVector<3, T>(lhs.x >> rhs, lhs.y >> rhs, lhs.z >> rhs);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator>>(const K lhs, const BasicVector<3, T>& rhs) {
		return BasicVector<3, T>(lhs >> rhs.x, lhs >> rhs.y, lhs >> rhs.z);
	}

	template<typename T, typename K>
	inline constexpr BasicVector<3, T> operator>>(const BasicVector<3, T>& lhs, const BasicVector<3, K>& rhs) {
		return BasicVector<3, T>(lhs.x >> rhs.x, lhs.y >> rhs.y, lhs.z >> rhs.z);
	}
}