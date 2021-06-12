#pragma once

#include "../Vector.h"

namespace EngineCore {

	//----------------------------------//
	//------------- Values -------------//
	//----------------------------------//

	template<typename T>
	inline constexpr T& Vector<2, T>::Data(const uint8_t idx) {
		ENGINE_CORE_ASSERT(idx < Count());

		switch(idx) {
			case 0: return x;
			case 1: return y;
		}
	}

	template<typename T>
	inline constexpr const T& Vector<2, T>::Data(const uint8_t idx) const {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
			case 0: return x;
			case 1: return y;
		}
	}

	template<typename T>
	inline constexpr T& Vector<2, T>::operator[](const uint8_t idx) {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
			case 0: return x;
			case 1: return y;
		}
	}

	template<typename T>
	inline constexpr const T& Vector<2, T>::operator[](const uint8_t idx) const {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
			case 0: return x;
			case 1: return y;
		}
	}



	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

	template<typename T>
	inline constexpr Vector<2, T>::Vector()
		: x(0)
		, y(0)
	{
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>::Vector(K scalar)
		: x(static_cast<T>(scalar))
		, y(static_cast<T>(scalar))
	{}

	template<typename T>
	template<typename K1, typename K2>
	inline constexpr Vector<2, T>::Vector(K1 _x, K2 _y)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y))
	{}

	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>::Vector(const Vector<2, K>& vec)
		: x(static_cast<T>(vec.x))
		, y(static_cast<T>(vec.y))
	{}



	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//

	// From Vector<1, K>
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>::Vector(const Vector<1, K>& vec)
		: x(static_cast<T>(vec.x))
		, y(0)
	{}

	template<typename T>
	template<typename K1, typename K2>
	inline constexpr Vector<2, T>::Vector(const Vector<1, K1>& _x, const K2 _y)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y))
	{}

	template<typename T>
	template<typename K1, typename K2>
	inline constexpr Vector<2, T>::Vector(const K1 _x, const Vector<1, K2>& _y)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y.x))
	{}

	template<typename T>
	template<typename K1, typename K2>
	inline constexpr Vector<2, T>::Vector(const Vector<1, K1>& _x, const Vector<1, K2>& _y)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y.x))
	{}



	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template<typename T>
	inline constexpr bool Vector<2, T>::operator==(const Vector<2, T>& rhs) {
		return this->x == rhs.x && this->y == rhs.y;
	}

	template<typename T>
	inline constexpr bool Vector<2, T>::operator!=(const Vector<2, T>& rhs) {
		return !(*this == rhs);
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template<typename T>
	inline constexpr Vector<2, T> Vector<2, T>::operator+() {
		return *this;
	}

	// operator -I
	template<typename T>
	inline constexpr Vector<2, T> Vector<2, T>::operator-() {
		return Vector<2, T>(-this->x, -this->y);
	}

	// operator ++I
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator++() {
		++this->x;
		++this->y;
		return *this;
	}

	// operator --I
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator--() {
		--this->x;
		--this->y;
		return *this;
	}

	// operator I++
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T> Vector<2, T>::operator++(int) {
		Vector<2, T> res(*this);
		++*this;
		return res;
	}

	// operator I--
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T> Vector<2, T>::operator--(int) {
		Vector<2, T> res(*this);
		--*this;
		return res;
	}

	// operator =
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator=(const K scalar) {
		this->x = static_cast<T>(scalar);
		this->y = static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator=(const Vector<2, K>& vec) {
		this->x = static_cast<T>(vec.x);
		this->y = static_cast<T>(vec.y);
		return *this;
	}

	// operator +=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator+=(const K scalar) {
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator+=(const Vector<2, K>& vec) {
		this->x += static_cast<T>(vec.x);
		this->y += static_cast<T>(vec.y);
		return *this;
	}

	// operator -=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator-=(const K scalar) {
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator-=(const Vector<2, K>& vec) {
		this->x -= static_cast<T>(vec.x);
		this->y -= static_cast<T>(vec.y);
		return *this;
	}

	// operator *=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator*=(const K scalar) {
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator*=(const Vector<2, K>& vec) {
		this->x *= static_cast<T>(vec.x);
		this->y *= static_cast<T>(vec.y);
		return *this;
	}

	// operator /=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator/=(const K scalar) {
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator/=(const Vector<2, K>& vec) {
		this->x /= static_cast<T>(vec.x);
		this->y /= static_cast<T>(vec.y);
		return *this;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//
	
	// binary condition
	template<typename T>
	inline constexpr Vector<2, T> Vector<2, T>::operator&&(const Vector<2, T>& rhs) {
		return Vector<2, T>(this->x && rhs.x, this->y && rhs.y);
	}

	template<typename T>
	inline constexpr Vector<2, T> Vector<2, T>::operator||(const Vector<2, T>& rhs) {
		return Vector<2, T>(this->x || rhs.x, this->y || rhs.y);
	}

	// operator ~I
	template<typename T>
	inline constexpr Vector<2, T> Vector<2, T>::operator~() {
		return Vector<2, T>(~this->x, ~this->y);
	}

	// operator %=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator%=(const K scalar) {
		this->x %= static_cast<T>(scalar);
		this->y %= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator%=(const Vector<2, K>& vec) {
		this->x %= static_cast<T>(vec.x);
		this->y %= static_cast<T>(vec.y);
		return *this;
	}

	// operator &=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator&=(const K scalar) {
		this->x &= static_cast<T>(scalar);
		this->y &= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator&=(const Vector<2, K>& vec) {
		this->x &= static_cast<T>(vec.x);
		this->y &= static_cast<T>(vec.y);
		return *this;
	}

	// operator |=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator|=(const K scalar) {
		this->x |= static_cast<T>(scalar);
		this->y |= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator|=(const Vector<2, K>& vec) {
		this->x |= static_cast<T>(vec.x);
		this->y |= static_cast<T>(vec.y);
		return *this;
	}

	// operator ^=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator^=(const K scalar) {
		this->x ^= static_cast<T>(scalar);
		this->y ^= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator^=(const Vector<2, K>& vec) {
		this->x ^= static_cast<T>(vec.x);
		this->y ^= static_cast<T>(vec.y);
		return *this;
	}

	// operator <<=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator<<=(const K scalar) {
		this->x <<= static_cast<T>(scalar);
		this->y <<= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator<<=(const Vector<2, K>& vec) {
		this->x <<= static_cast<T>(vec.x);
		this->y <<= static_cast<T>(vec.y);
		return *this;
	}

	// operator >>=
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator>>=(const K scalar) {
		this->x >>= static_cast<T>(scalar);
		this->y >>= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<2, T>& Vector<2, T>::operator>>=(const Vector<2, K>& vec) {
		this->x >>= static_cast<T>(vec.x);
		this->y >>= static_cast<T>(vec.y);
		return *this;
	}

	








	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator+(const Vector<2, T>& lhs, const K rhs) {
		return Vector<2, T>(lhs.x + rhs, lhs.y + rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator+(const K lhs, const Vector<2, T>& rhs) {
		return Vector<2, T>(lhs + rhs.x, lhs + rhs.y);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator+(const Vector<2, T>& lhs, const Vector<2, K>& rhs) {
		return Vector<2, T>(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	// operator -
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator-(const Vector<2, T>& lhs, const K rhs) {
		return Vector<2, T>(lhs.x - rhs, lhs.y - rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator-(const K lhs, const Vector<2, T>& rhs) {
		return Vector<2, T>(lhs - rhs.x, lhs - rhs.y);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator-(const Vector<2, T>& lhs, const Vector<2, K>& rhs) {
		return Vector<2, T>(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	// operator *
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator*(const Vector<2, T>& lhs, const K rhs) {
		return Vector<2, T>(lhs.x * rhs, lhs.y * rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator*(const K lhs, const Vector<2, T>& rhs) {
		return Vector<2, T>(lhs * rhs.x, lhs * rhs.y);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator*(const Vector<2, T>& lhs, const Vector<2, K>& rhs) {
		return Vector<2, T>(lhs.x * rhs.x, lhs.y * rhs.y);
	}

	// operator /
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator/(const Vector<2, T>& lhs, const K rhs) {
		return Vector<2, T>(lhs.x / rhs, lhs.y / rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator/(const K lhs, const Vector<2, T>& rhs) {
		return Vector<2, T>(lhs / rhs.x, lhs / rhs.y);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator/(const Vector<2, T>& lhs, const Vector<2, K>& rhs) {
		return Vector<2, T>(lhs.x / rhs.x, lhs.y / rhs.y);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator%(const Vector<2, T>& lhs, const K rhs) {
		return Vector<2, T>(lhs.x % rhs, lhs.y % rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator%(const K lhs, const Vector<2, T>& rhs) {
		return Vector<2, T>(lhs % rhs.x, lhs % rhs.y);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator%(const Vector<2, T>& lhs, const Vector<2, K>& rhs) {
		return Vector<2, T>(lhs.x % rhs.x, lhs.y % rhs.y);
	}

	// operator &
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator&(const Vector<2, T>& lhs, const K rhs) {
		return Vector<2, T>(lhs.x & rhs, lhs.y & rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator&(const K lhs, const Vector<2, T>& rhs) {
		return Vector<2, T>(lhs & rhs.x, lhs & rhs.y);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator&(const Vector<2, T>& lhs, const Vector<2, K>& rhs) {
		return Vector<2, T>(lhs.x & rhs.x, lhs.y & rhs.y);
	}

	// operator |
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator|(const Vector<2, T>& lhs, const K rhs) {
		return Vector<2, T>(lhs.x | rhs, lhs.y | rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator|(const K lhs, const Vector<2, T>& rhs) {
		return Vector<2, T>(lhs | rhs.x, lhs | rhs.y);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<2, T> operator|(const Vector<2, T>& lhs, const Vector<2, K>& rhs) {
		return Vector<2, T>(lhs.x | rhs.x, lhs.y | rhs.y);
	}

	// operator ^
	template<typename T, typename K> 
	inline constexpr Vector<2, T> operator^(const Vector<2, T>& lhs, const K rhs) {
		return Vector<2, T>(lhs.x ^ rhs, lhs.y ^ rhs);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<2, T> operator^(const K lhs, const Vector<2, T>& rhs) {
		return Vector<2, T>(lhs ^ rhs.x, lhs ^ rhs.y);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<2, T> operator^(const Vector<2, T>& lhs, const Vector<2, K>& rhs) {
		return Vector<2, T>(lhs.x ^ rhs.x, lhs.y ^ rhs.y);
	}

	// operator <<
	template<typename T, typename K> 
	inline constexpr Vector<2, T> operator<<(const Vector<2, T>& lhs, const K rhs) {
		return Vector<2, T>(lhs.x << rhs, lhs.y << rhs);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<2, T> operator<<(const K lhs, const Vector<2, T>& rhs) {
		return Vector<2, T>(lhs << rhs.x, lhs << rhs.y);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<2, T> operator<<(const Vector<2, T>& lhs, const Vector<2, K>& rhs) {
		return Vector<2, T>(lhs.x << rhs.x, lhs.y << rhs.y);
	}

	// operator >>
	template<typename T, typename K> 
	inline constexpr Vector<2, T> operator>>(const Vector<2, T>& lhs, const K rhs) {
		return Vector<2, T>(lhs.x >> rhs, lhs.y >> rhs);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<2, T> operator>>(const K lhs, const Vector<2, T>& rhs) {
		return Vector<2, T>(lhs >> rhs.x, lhs >> rhs.y);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<2, T> operator>>(const Vector<2, T>& lhs, const Vector<2, K>& rhs) {
		return Vector<2, T>(lhs.x >> rhs.x, lhs.y >> rhs.y);
	}
}























