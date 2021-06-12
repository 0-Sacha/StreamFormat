#pragma once

#include "../Vector.h"

namespace EngineCore {

	//----------------------------------//
	//------------- Values -------------//
	//----------------------------------//

	template<typename T>
	inline constexpr T& Vector<3, T>::Data(const uint8_t idx) {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
		}
	}

	template<typename T>
	inline constexpr const T& Vector<3, T>::Data(const uint8_t idx) const {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
		}
	}

	template<typename T>
	inline constexpr T& Vector<3, T>::operator[](const uint8_t idx) {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
		}
	}

	template<typename T>
	inline constexpr const T& Vector<3, T>::operator[](const uint8_t idx) const {
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

	template<typename T>
	inline constexpr Vector<3, T>::Vector()
		: x(0)
		, y(0)
		, z(0)
	{
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>::Vector(K scalar)
		: x(static_cast<T>(scalar))
		, y(static_cast<T>(scalar))
		, z(static_cast<T>(scalar))
	{}

	template<typename T>
	template<typename K1, typename K2, typename K3>
	inline constexpr Vector<3, T>::Vector(K1 _x, K2 _y, K3 _z)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y))
		, z(static_cast<T>(_z))
	{}

	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>::Vector(const Vector<3, K>& vec)
		: x(static_cast<T>(vec.x))
		, y(static_cast<T>(vec.y))
		, z(static_cast<T>(vec.z))
	{}



	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//


	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template<typename T>
	inline constexpr bool Vector<3, T>::operator==(const Vector<3, T>& rhs) {
		return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
	}

	template<typename T>
	inline constexpr bool Vector<3, T>::operator!=(const Vector<3, T>& rhs) {
		return !(*this == rhs);
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template<typename T>
	inline constexpr Vector<3, T> Vector<3, T>::operator+() {
		return *this;
	}

	// operator -I
	template<typename T>
	inline constexpr Vector<3, T> Vector<3, T>::operator-() {
		return Vector<3, T>(-this->x, -this->y, -this->z);
	}

	// operator ++I
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator++() {
		++this->x;
		++this->y;
		++this->z;
		return *this;
	}

	// operator --I
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator--() {
		--this->x;
		--this->y;
		--this->z;
		return *this;
	}

	// operator I++
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T> Vector<3, T>::operator++(int) {
		Vector<3, T> res(*this);
		++*this;
		return res;
	}

	// operator I--
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T> Vector<3, T>::operator--(int) {
		Vector<3, T> res(*this);
		--*this;
		return res;
	}

	// operator =
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator=(const K scalar) {
		this->x = static_cast<T>(scalar);
		this->y = static_cast<T>(scalar);
		this->z = static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator=(const Vector<3, K>& vec) {
		this->x = static_cast<T>(vec.x);
		this->y = static_cast<T>(vec.y);
		this->z = static_cast<T>(vec.z);
		return *this;
	}

	// operator +=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator+=(const K scalar) {
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		this->z += static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator+=(const Vector<3, K>& vec) {
		this->x += static_cast<T>(vec.x);
		this->y += static_cast<T>(vec.y);
		this->z += static_cast<T>(vec.z);
		return *this;
	}

	// operator -=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator-=(const K scalar) {
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		this->z -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator-=(const Vector<3, K>& vec) {
		this->x -= static_cast<T>(vec.x);
		this->y -= static_cast<T>(vec.y);
		this->z -= static_cast<T>(vec.z);
		return *this;
	}

	// operator *=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator*=(const K scalar) {
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		this->z *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator*=(const Vector<3, K>& vec) {
		this->x *= static_cast<T>(vec.x);
		this->y *= static_cast<T>(vec.y);
		this->z *= static_cast<T>(vec.z);
		return *this;
	}

	// operator /=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator/=(const K scalar) {
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		this->z /= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator/=(const Vector<3, K>& vec) {
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
	inline constexpr Vector<3, T> Vector<3, T>::operator&&(const Vector<3, T>& rhs) {
		return Vector<3, T>(this->x && rhs.x, this->y && rhs.y, this->z && rhs.z);
	}

	template<typename T>
	inline constexpr Vector<3, T> Vector<3, T>::operator||(const Vector<3, T>& rhs) {
		return Vector<3, T>(this->x || rhs.x, this->y || rhs.y, this->z || rhs.z);
	}

	// operator ~I
	template<typename T>
	inline constexpr Vector<3, T> Vector<3, T>::operator~() {
		return Vector<3, T>(~this->x, ~this->y, ~this->z);
	}

	// operator %=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator%=(const K scalar) {
		this->x %= static_cast<T>(scalar);
		this->y %= static_cast<T>(scalar);
		this->z %= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator%=(const Vector<3, K>& vec) {
		this->x %= static_cast<T>(vec.x);
		this->y %= static_cast<T>(vec.y);
		this->z %= static_cast<T>(vec.z);
		return *this;
	}

	// operator &=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator&=(const K scalar) {
		this->x &= static_cast<T>(scalar);
		this->y &= static_cast<T>(scalar);
		this->z &= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator&=(const Vector<3, K>& vec) {
		this->x &= static_cast<T>(vec.x);
		this->y &= static_cast<T>(vec.y);
		this->z &= static_cast<T>(vec.z);
		return *this;
	}

	// operator |=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator|=(const K scalar) {
		this->x |= static_cast<T>(scalar);
		this->y |= static_cast<T>(scalar);
		this->z |= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator|=(const Vector<3, K>& vec) {
		this->x |= static_cast<T>(vec.x);
		this->y |= static_cast<T>(vec.y);
		this->z |= static_cast<T>(vec.z);
		return *this;
	}

	// operator ^=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator^=(const K scalar) {
		this->x ^= static_cast<T>(scalar);
		this->y ^= static_cast<T>(scalar);
		this->z ^= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator^=(const Vector<3, K>& vec) {
		this->x ^= static_cast<T>(vec.x);
		this->y ^= static_cast<T>(vec.y);
		this->z ^= static_cast<T>(vec.z);
		return *this;
	}

	// operator <<=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator<<=(const K scalar) {
		this->x <<= static_cast<T>(scalar);
		this->y <<= static_cast<T>(scalar);
		this->z <<= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator<<=(const Vector<3, K>& vec) {
		this->x <<= static_cast<T>(vec.x);
		this->y <<= static_cast<T>(vec.y);
		this->z <<= static_cast<T>(vec.z);
		return *this;
	}

	// operator >>=
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator>>=(const K scalar) {
		this->x >>= static_cast<T>(scalar);
		this->y >>= static_cast<T>(scalar);
		this->z >>= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<3, T>& Vector<3, T>::operator>>=(const Vector<3, K>& vec) {
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
	inline constexpr Vector<3, T> operator+(const Vector<3, T>& lhs, const K rhs) {
		return Vector<3, T>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator+(const K lhs, const Vector<3, T>& rhs) {
		return Vector<3, T>(lhs + rhs.x, lhs + rhs.y, rhs + lhs.z);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator+(const Vector<3, T>& lhs, const Vector<3, K>& rhs) {
		return Vector<3, T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	// operator -
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator-(const Vector<3, T>& lhs, const K rhs) {
		return Vector<3, T>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator-(const K lhs, const Vector<3, T>& rhs) {
		return Vector<3, T>(lhs - rhs.x, lhs - rhs.y, rhs - lhs.z);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator-(const Vector<3, T>& lhs, const Vector<3, K>& rhs) {
		return Vector<3, T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	// operator *
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator*(const Vector<3, T>& lhs, const K rhs) {
		return Vector<3, T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator*(const K lhs, const Vector<3, T>& rhs) {
		return Vector<3, T>(lhs * rhs.x, lhs * rhs.y, rhs * lhs.z);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator*(const Vector<3, T>& lhs, const Vector<3, K>& rhs) {
		return Vector<3, T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	// operator /
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator/(const Vector<3, T>& lhs, const K rhs) {
		return Vector<3, T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator/(const K lhs, const Vector<3, T>& rhs) {
		return Vector<3, T>(lhs / rhs.x, lhs / rhs.y, rhs / lhs.z);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator/(const Vector<3, T>& lhs, const Vector<3, K>& rhs) {
		return Vector<3, T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator%(const Vector<3, T>& lhs, const K rhs) {
		return Vector<3, T>(lhs.x % rhs, lhs.y % rhs, lhs.z % rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator%(const K lhs, const Vector<3, T>& rhs) {
		return Vector<3, T>(lhs % rhs.x, lhs % rhs.y, rhs % lhs.z);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator%(const Vector<3, T>& lhs, const Vector<3, K>& rhs) {
		return Vector<3, T>(lhs.x % rhs.x, lhs.y % rhs.y, lhs.z % rhs.z);
	}

	// operator &
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator&(const Vector<3, T>& lhs, const K rhs) {
		return Vector<3, T>(lhs.x & rhs, lhs.y & rhs, lhs.z & rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator&(const K lhs, const Vector<3, T>& rhs) {
		return Vector<3, T>(lhs & rhs.x, lhs & rhs.y, rhs & lhs.z);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator&(const Vector<3, T>& lhs, const Vector<3, K>& rhs) {
		return Vector<3, T>(lhs.x & rhs.x, lhs.y & rhs.y, lhs.z & rhs.z);
	}

	// operator |
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator|(const Vector<3, T>& lhs, const K rhs) {
		return Vector<3, T>(lhs.x | rhs, lhs.y | rhs, lhs.z | rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator|(const K lhs, const Vector<3, T>& rhs) {
		return Vector<3, T>(lhs | rhs.x, lhs | rhs.y, rhs | lhs.z);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<3, T> operator|(const Vector<3, T>& lhs, const Vector<3, K>& rhs) {
		return Vector<3, T>(lhs.x | rhs.x, lhs.y | rhs.y, lhs.z | rhs.z);
	}

	// operator ^
	template<typename T, typename K> 
	inline constexpr Vector<3, T> operator^(const Vector<3, T>& lhs, const K rhs) {
		return Vector<3, T>(lhs.x ^ rhs, lhs.y ^ rhs, lhs.z ^ rhs);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<3, T> operator^(const K lhs, const Vector<3, T>& rhs) {
		return Vector<3, T>(lhs ^ rhs.x, lhs ^ rhs.y, rhs ^ lhs.z);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<3, T> operator^(const Vector<3, T>& lhs, const Vector<3, K>& rhs) {
		return Vector<3, T>(lhs.x ^ rhs.x, lhs.y ^ rhs.y, lhs.z ^ rhs.z);
	}

	// operator <<
	template<typename T, typename K> 
	inline constexpr Vector<3, T> operator<<(const Vector<3, T>& lhs, const K rhs) {
		return Vector<3, T>(lhs.x << rhs, lhs.y << rhs, lhs.z << rhs);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<3, T> operator<<(const K lhs, const Vector<3, T>& rhs) {
		return Vector<3, T>(lhs << rhs.x, lhs << rhs.y, rhs << lhs.z);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<3, T> operator<<(const Vector<3, T>& lhs, const Vector<3, K>& rhs) {
		return Vector<3, T>(lhs.x << rhs.x, lhs.y << rhs.y, lhs.z << rhs.z);
	}

	// operator >>
	template<typename T, typename K> 
	inline constexpr Vector<3, T> operator>>(const Vector<3, T>& lhs, const K rhs) {
		return Vector<3, T>(lhs.x >> rhs, lhs.y >> rhs, lhs.z >> rhs);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<3, T> operator>>(const K lhs, const Vector<3, T>& rhs) {
		return Vector<3, T>(lhs >> rhs.x, lhs >> rhs.y, rhs >> lhs.z);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<3, T> operator>>(const Vector<3, T>& lhs, const Vector<3, K>& rhs) {
		return Vector<3, T>(lhs.x >> rhs.x, lhs.y >> rhs.y, lhs.z >> rhs.z);
	}
}























