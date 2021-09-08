#pragma once

#include "../Vector.h"

namespace EngineCore {

	//----------------------------------//
	//------------- Values -------------//
	//----------------------------------//

	template<typename T>
	inline constexpr T& Vector<4, T>::Data(const uint8_t idx) {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
		}
	}

	template<typename T>
	inline constexpr const T& Vector<4, T>::Data(const uint8_t idx) const {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
		}
	}

	template<typename T>
	inline constexpr T& Vector<4, T>::operator[](const uint8_t idx) {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
		}
	}

	template<typename T>
	inline constexpr const T& Vector<4, T>::operator[](const uint8_t idx) const {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
		}
	}



	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

	template<typename T>
	inline constexpr Vector<4, T>::Vector()
		: x(0)
		, y(0)
		, z(0)
		, w(0)
	{
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>::Vector(K scalar)
		: x(static_cast<T>(scalar))
		, y(static_cast<T>(scalar))
		, z(static_cast<T>(scalar))
		, w(static_cast<T>(scalar))
	{}

	template<typename T>
	template<typename K1, typename K2, typename K3, typename K4>
	inline constexpr Vector<4, T>::Vector(K1 _x, K2 _y, K3 _z, K4 _w)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y))
		, z(static_cast<T>(_z))
		, w(static_cast<T>(_w))
	{}

	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>::Vector(const Vector<4, K>& vec)
		: x(static_cast<T>(vec.x))
		, y(static_cast<T>(vec.y))
		, z(static_cast<T>(vec.z))
		, w(static_cast<T>(vec.w))
	{}



	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//


	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template<typename T>
	inline constexpr bool Vector<4, T>::operator==(const Vector<4, T>& rhs) const {
		return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z && this->w;
	}

	template<typename T>
	inline constexpr bool Vector<4, T>::operator!=(const Vector<4, T>& rhs) const {
		return !(*this == rhs);
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template<typename T>
	inline constexpr Vector<4, T> Vector<4, T>::operator+() {
		return *this;
	}

	// operator -I
	template<typename T>
	inline constexpr Vector<4, T> Vector<4, T>::operator-() {
		return Vector<4, T>(-this->x, -this->y, -this->z, -this->w);
	}

	// operator ++I
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator++() {
		++this->x;
		++this->y;
		++this->z;
		++this->w;
		return *this;
	}

	// operator --I
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator--() {
		--this->x;
		--this->y;
		--this->z;
		--this->w;
		return *this;
	}

	// operator I++
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T> Vector<4, T>::operator++(int) {
		Vector<4, T> res(*this);
		++* this;
		return res;
	}

	// operator I--
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T> Vector<4, T>::operator--(int) {
		Vector<4, T> res(*this);
		--* this;
		return res;
	}

	// operator =
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator=(const K scalar) {
		this->x = static_cast<T>(scalar);
		this->y = static_cast<T>(scalar);
		this->z = static_cast<T>(scalar);
		this->w = static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator=(const Vector<4, K>& vec) {
		this->x = static_cast<T>(vec.x);
		this->y = static_cast<T>(vec.y);
		this->z = static_cast<T>(vec.z);
		this->w = static_cast<T>(vec.w);
		return *this;
	}

	// operator +=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator+=(const K scalar) {
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		this->z += static_cast<T>(scalar);
		this->w += static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator+=(const Vector<4, K>& vec) {
		this->x += static_cast<T>(vec.x);
		this->y += static_cast<T>(vec.y);
		this->z += static_cast<T>(vec.z);
		this->w += static_cast<T>(vec.w);
		return *this;
	}

	// operator -=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator-=(const K scalar) {
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		this->z -= static_cast<T>(scalar);
		this->w -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator-=(const Vector<4, K>& vec) {
		this->x -= static_cast<T>(vec.x);
		this->y -= static_cast<T>(vec.y);
		this->z -= static_cast<T>(vec.z);
		this->w -= static_cast<T>(vec.w);
		return *this;
	}

	// operator *=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator*=(const K scalar) {
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		this->z *= static_cast<T>(scalar);
		this->w *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator*=(const Vector<4, K>& vec) {
		this->x *= static_cast<T>(vec.x);
		this->y *= static_cast<T>(vec.y);
		this->z *= static_cast<T>(vec.z);
		this->w *= static_cast<T>(vec.w);
		return *this;
	}

	// operator /=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator/=(const K scalar) {
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		this->z /= static_cast<T>(scalar);
		this->w /= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator/=(const Vector<4, K>& vec) {
		this->x /= static_cast<T>(vec.x);
		this->y /= static_cast<T>(vec.y);
		this->z /= static_cast<T>(vec.z);
		this->w /= static_cast<T>(vec.w);
		return *this;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// binary condition
	template<typename T>
	inline constexpr Vector<4, T> Vector<4, T>::operator&&(const Vector<4, T>& rhs) {
		return Vector<4, T>(this->x && rhs.x, this->y && rhs.y, this->z && rhs.z, this->w && rhs.w);
	}

	template<typename T>
	inline constexpr Vector<4, T> Vector<4, T>::operator||(const Vector<4, T>& rhs) {
		return Vector<4, T>(this->x || rhs.x, this->y || rhs.y, this->z || rhs.z, this->w || rhs.w);
	}

	// operator ~I
	template<typename T>
	inline constexpr Vector<4, T> Vector<4, T>::operator~() {
		return Vector<4, T>(~this->x, ~this->y, ~this->z, ~this->w);
	}

	// operator %=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator%=(const K scalar) {
		this->x %= static_cast<T>(scalar);
		this->y %= static_cast<T>(scalar);
		this->z %= static_cast<T>(scalar);
		this->w %= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator%=(const Vector<4, K>& vec) {
		this->x %= static_cast<T>(vec.x);
		this->y %= static_cast<T>(vec.y);
		this->z %= static_cast<T>(vec.z);
		this->w %= static_cast<T>(vec.w);
		return *this;
	}

	// operator &=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator&=(const K scalar) {
		this->x &= static_cast<T>(scalar);
		this->y &= static_cast<T>(scalar);
		this->z &= static_cast<T>(scalar);
		this->w &= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator&=(const Vector<4, K>& vec) {
		this->x &= static_cast<T>(vec.x);
		this->y &= static_cast<T>(vec.y);
		this->z &= static_cast<T>(vec.z);
		this->w &= static_cast<T>(vec.w);
		return *this;
	}

	// operator |=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator|=(const K scalar) {
		this->x |= static_cast<T>(scalar);
		this->y |= static_cast<T>(scalar);
		this->z |= static_cast<T>(scalar);
		this->w |= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator|=(const Vector<4, K>& vec) {
		this->x |= static_cast<T>(vec.x);
		this->y |= static_cast<T>(vec.y);
		this->z |= static_cast<T>(vec.z);
		this->w |= static_cast<T>(vec.w);
		return *this;
	}

	// operator ^=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator^=(const K scalar) {
		this->x ^= static_cast<T>(scalar);
		this->y ^= static_cast<T>(scalar);
		this->z ^= static_cast<T>(scalar);
		this->w ^= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator^=(const Vector<4, K>& vec) {
		this->x ^= static_cast<T>(vec.x);
		this->y ^= static_cast<T>(vec.y);
		this->z ^= static_cast<T>(vec.z);
		this->w ^= static_cast<T>(vec.w);
		return *this;
	}

	// operator <<=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator<<=(const K scalar) {
		this->x <<= static_cast<T>(scalar);
		this->y <<= static_cast<T>(scalar);
		this->z <<= static_cast<T>(scalar);
		this->w <<= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator<<=(const Vector<4, K>& vec) {
		this->x <<= static_cast<T>(vec.x);
		this->y <<= static_cast<T>(vec.y);
		this->z <<= static_cast<T>(vec.z);
		this->w <<= static_cast<T>(vec.w);
		return *this;
	}

	// operator >>=
	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator>>=(const K scalar) {
		this->x >>= static_cast<T>(scalar);
		this->y >>= static_cast<T>(scalar);
		this->z >>= static_cast<T>(scalar);
		this->w >>= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<4, T>& Vector<4, T>::operator>>=(const Vector<4, K>& vec) {
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
	inline constexpr Vector<4, T> operator+(const Vector<4, T>& lhs, const K rhs) {
		return Vector<4, T>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator+(const K lhs, const Vector<4, T>& rhs) {
		return Vector<4, T>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator+(const Vector<4, T>& lhs, const Vector<4, K>& rhs) {
		return Vector<4, T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
	}

	// operator -
	template<typename T, typename K>
	inline constexpr Vector<4, T> operator-(const Vector<4, T>& lhs, const K rhs) {
		return Vector<4, T>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator-(const K lhs, const Vector<4, T>& rhs) {
		return Vector<4, T>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator-(const Vector<4, T>& lhs, const Vector<4, K>& rhs) {
		return Vector<4, T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
	}

	// operator *
	template<typename T, typename K>
	inline constexpr Vector<4, T> operator*(const Vector<4, T>& lhs, const K rhs) {
		return Vector<4, T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator*(const K lhs, const Vector<4, T>& rhs) {
		return Vector<4, T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator*(const Vector<4, T>& lhs, const Vector<4, K>& rhs) {
		return Vector<4, T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
	}

	// operator /
	template<typename T, typename K>
	inline constexpr Vector<4, T> operator/(const Vector<4, T>& lhs, const K rhs) {
		return Vector<4, T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator/(const K lhs, const Vector<4, T>& rhs) {
		return Vector<4, T>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator/(const Vector<4, T>& lhs, const Vector<4, K>& rhs) {
		return Vector<4, T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>
	inline constexpr Vector<4, T> operator%(const Vector<4, T>& lhs, const K rhs) {
		return Vector<4, T>(lhs.x % rhs, lhs.y % rhs, lhs.z % rhs, lhs.w % rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator%(const K lhs, const Vector<4, T>& rhs) {
		return Vector<4, T>(lhs % rhs.x, lhs % rhs.y, lhs % rhs.z, lhs % rhs.w);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator%(const Vector<4, T>& lhs, const Vector<4, K>& rhs) {
		return Vector<4, T>(lhs.x % rhs.x, lhs.y % rhs.y, lhs.z % rhs.z, lhs.w % rhs.w);
	}

	// operator &
	template<typename T, typename K>
	inline constexpr Vector<4, T> operator&(const Vector<4, T>& lhs, const K rhs) {
		return Vector<4, T>(lhs.x & rhs, lhs.y & rhs, lhs.z & rhs, lhs.w & rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator&(const K lhs, const Vector<4, T>& rhs) {
		return Vector<4, T>(lhs & rhs.x, lhs & rhs.y, lhs & rhs.z, lhs & rhs.w);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator&(const Vector<4, T>& lhs, const Vector<4, K>& rhs) {
		return Vector<4, T>(lhs.x & rhs.x, lhs.y & rhs.y, lhs.z & rhs.z, lhs.w & rhs.w);
	}

	// operator |
	template<typename T, typename K>
	inline constexpr Vector<4, T> operator|(const Vector<4, T>& lhs, const K rhs) {
		return Vector<4, T>(lhs.x | rhs, lhs.y | rhs, lhs.z | rhs, lhs.w | rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator|(const K lhs, const Vector<4, T>& rhs) {
		return Vector<4, T>(lhs | rhs.x, lhs | rhs.y, lhs | rhs.z, lhs | rhs.w);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator|(const Vector<4, T>& lhs, const Vector<4, K>& rhs) {
		return Vector<4, T>(lhs.x | rhs.x, lhs.y | rhs.y, lhs.z | rhs.z, lhs.w | rhs.w);
	}

	// operator ^
	template<typename T, typename K>
	inline constexpr Vector<4, T> operator^(const Vector<4, T>& lhs, const K rhs) {
		return Vector<4, T>(lhs.x ^ rhs, lhs.y ^ rhs, lhs.z ^ rhs, lhs.w ^ rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator^(const K lhs, const Vector<4, T>& rhs) {
		return Vector<4, T>(lhs ^ rhs.x, lhs ^ rhs.y, lhs ^ rhs.z, lhs ^ rhs.w);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator^(const Vector<4, T>& lhs, const Vector<4, K>& rhs) {
		return Vector<4, T>(lhs.x ^ rhs.x, lhs.y ^ rhs.y, lhs.z ^ rhs.z, lhs.w ^ rhs.w);
	}

	// operator <<
	template<typename T, typename K>
	inline constexpr Vector<4, T> operator<<(const Vector<4, T>& lhs, const K rhs) {
		return Vector<4, T>(lhs.x << rhs, lhs.y << rhs, lhs.z << rhs, lhs.w << rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator<<(const K lhs, const Vector<4, T>& rhs) {
		return Vector<4, T>(lhs << rhs.x, lhs << rhs.y, lhs << rhs.z, lhs << rhs.w);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator<<(const Vector<4, T>& lhs, const Vector<4, K>& rhs) {
		return Vector<4, T>(lhs.x << rhs.x, lhs.y << rhs.y, lhs.z << rhs.z, lhs.w << rhs.w);
	}

	// operator >>
	template<typename T, typename K>
	inline constexpr Vector<4, T> operator>>(const Vector<4, T>& lhs, const K rhs) {
		return Vector<4, T>(lhs.x >> rhs, lhs.y >> rhs, lhs.z >> rhs, lhs.w >> rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator>>(const K lhs, const Vector<4, T>& rhs) {
		return Vector<4, T>(lhs >> rhs.x, lhs >> rhs.y, lhs >> rhs.z, lhs >> rhs.w);
	}

	template<typename T, typename K>
	inline constexpr Vector<4, T> operator>>(const Vector<4, T>& lhs, const Vector<4, K>& rhs) {
		return Vector<4, T>(lhs.x >> rhs.x, lhs.y >> rhs.y, lhs.z >> rhs.z, lhs.w >> rhs.w);
	}
}























