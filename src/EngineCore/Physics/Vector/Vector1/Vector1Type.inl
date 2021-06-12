#pragma once

#include "../Vector.h"

namespace EngineCore {
	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

	template<typename T>
	inline constexpr Vector<1, T>::Vector()
		: x(0)
	{}

	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>::Vector(K scalar)
		: x(static_cast<T>(scalar))
	{}

	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>::Vector(const Vector<1, K>& vec)
		: x(static_cast<T>(vec.x))
	{}



	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//

	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template<typename T>
	inline constexpr bool Vector<1, T>::operator==(const Vector<1, T>& rhs) {
		return this->x == rhs.x;
	}

	template<typename T>
	inline constexpr bool Vector<1, T>::operator!=(const Vector<1, T>& rhs) {
		return !(*this == rhs);
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template<typename T>
	inline constexpr Vector<1, T> Vector<1, T>::operator+() {
		return *this;
	}

	// operator -I
	template<typename T>
	inline constexpr Vector<1, T> Vector<1, T>::operator-() {
		return Vector<1, T>(-this->x);
	}

	// operator ++I
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator++() {
		++this->x;
		++this->y;
		return *this;
	}

	// operator --I
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator--() {
		--this->x;
		--this->y;
		return *this;
	}

	// operator I++
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T> Vector<1, T>::operator++(int) {
		Vector<1, T> res(*this);
		++*this;
		return res;
	}

	// operator I--
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T> Vector<1, T>::operator--(int) {
		Vector<1, T> res(*this);
		--*this;
		return res;
	}

	// operator =
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator=(const K scalar) {
		this->x = static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator=(const Vector<1, K>& vec) {
		this->x = static_cast<T>(vec.x);
		return *this;
	}

	// operator +=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator+=(const K scalar) {
		this->x += static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator+=(const Vector<1, K>& vec) {
		this->x += static_cast<T>(vec.x);
		return *this;
	}

	// operator -=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator-=(const K scalar) {
		this->x -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator-=(const Vector<1, K>& vec) {
		this->x -= static_cast<T>(vec.x);
		return *this;
	}

	// operator *=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator*=(const K scalar) {
		this->x *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator*=(const Vector<1, K>& vec) {
		this->x *= static_cast<T>(vec.x);
		return *this;
	}

	// operator /=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator/=(const K scalar) {
		this->x /= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator/=(const Vector<1, K>& vec) {
		this->x /= static_cast<T>(vec.x);
		return *this;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//
	
	// binary condition
	template<typename T>
	inline constexpr Vector<1, T> Vector<1, T>::operator&&(const Vector<1, T>& rhs) {
		return Vector<1, T>(this->x && rhs.x);
	}

	template<typename T>
	inline constexpr Vector<1, T> Vector<1, T>::operator||(const Vector<1, T>& rhs) {
		return Vector<1, T>(this->x || rhs.x);
	}

	// operator ~I
	template<typename T>
	inline constexpr Vector<1, T> Vector<1, T>::operator~() {
		return Vector<1, T>(~this->x, ~this->y);
	}

	// operator %=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator%=(const K scalar) {
		this->x %= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator%=(const Vector<1, K>& vec) {
		this->x %= static_cast<T>(vec.x);
		return *this;
	}

	// operator &=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator&=(const K scalar) {
		this->x &= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator&=(const Vector<1, K>& vec) {
		this->x &= static_cast<T>(vec.x);
		return *this;
	}

	// operator |=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator|=(const K scalar) {
		this->x |= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator|=(const Vector<1, K>& vec) {
		this->x |= static_cast<T>(vec.x);
		return *this;
	}

	// operator ^=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator^=(const K scalar) {
		this->x ^= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator^=(const Vector<1, K>& vec) {
		this->x ^= static_cast<T>(vec.x);
		return *this;
	}

	// operator <<=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator<<=(const K scalar) {
		this->x <<= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator<<=(const Vector<1, K>& vec) {
		this->x <<= static_cast<T>(vec.x);
		return *this;
	}

	// operator >>=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator>>=(const K scalar) {
		this->x >>= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T>& Vector<1, T>::operator>>=(const Vector<1, K>& vec) {
		this->x >>= static_cast<T>(vec.x);
		return *this;
	}

	








	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator+(const Vector<1, T>& lhs, const K rhs) {
		return Vector<1, T>(lhs.x + rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator+(const K lhs, const Vector<1, T>& rhs) {
		return Vector<1, T>(lhs + rhs.x);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator+(const Vector<1, T>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T>(lhs.x + rhs.x);
	}

	// operator -
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator-(const Vector<1, T>& lhs, const K rhs) {
		return Vector<1, T>(lhs.x - rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator-(const K lhs, const Vector<1, T>& rhs) {
		return Vector<1, T>(lhs - rhs.x);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator-(const Vector<1, T>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T>(lhs.x - rhs.x);
	}

	// operator *
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator*(const Vector<1, T>& lhs, const K rhs) {
		return Vector<1, T>(lhs.x * rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator*(const K lhs, const Vector<1, T>& rhs) {
		return Vector<1, T>(lhs * rhs.x);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator*(const Vector<1, T>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T>(lhs.x * rhs.x);
	}

	// operator /
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator/(const Vector<1, T>& lhs, const K rhs) {
		return Vector<1, T>(lhs.x / rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator/(const K lhs, const Vector<1, T>& rhs) {
		return Vector<1, T>(lhs / rhs.x);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator/(const Vector<1, T>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T>(lhs.x / rhs.x);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator%(const Vector<1, T>& lhs, const K rhs) {
		return Vector<1, T>(lhs.x % rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator%(const K lhs, const Vector<1, T>& rhs) {
		return Vector<1, T>(lhs % rhs.x);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator%(const Vector<1, T>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T>(lhs.x % rhs.x);
	}

	// operator &
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator&(const Vector<1, T>& lhs, const K rhs) {
		return Vector<1, T>(lhs.x & rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator&(const K lhs, const Vector<1, T>& rhs) {
		return Vector<1, T>(lhs & rhs.x);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator&(const Vector<1, T>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T>(lhs.x & rhs.x);
	}

	// operator |
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator|(const Vector<1, T>& lhs, const K rhs) {
		return Vector<1, T>(lhs.x | rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator|(const K lhs, const Vector<1, T>& rhs) {
		return Vector<1, T>(lhs | rhs.x);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T> operator|(const Vector<1, T>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T>(lhs.x | rhs.x);
	}

	// operator ^
	template<typename T, typename K> 
	inline constexpr Vector<1, T> operator^(const Vector<1, T>& lhs, const K rhs) {
		return Vector<1, T>(lhs.x ^ rhs);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<1, T> operator^(const K lhs, const Vector<1, T>& rhs) {
		return Vector<1, T>(lhs ^ rhs.x);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<1, T> operator^(const Vector<1, T>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T>(lhs.x ^ rhs.x);
	}

	// operator <<
	template<typename T, typename K> 
	inline constexpr Vector<1, T> operator<<(const Vector<1, T>& lhs, const K rhs) {
		return Vector<1, T>(lhs.x << rhs);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<1, T> operator<<(const K lhs, const Vector<1, T>& rhs) {
		return Vector<1, T>(lhs << rhs.x);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<1, T> operator<<(const Vector<1, T>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T>(lhs.x << rhs.x);
	}

	// operator >>
	template<typename T, typename K> 
	inline constexpr Vector<1, T> operator>>(const Vector<1, T>& lhs, const K rhs) {
		return Vector<1, T>(lhs.x >> rhs);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<1, T> operator>>(const K lhs, const Vector<1, T>& rhs) {
		return Vector<1, T>(lhs >> rhs.x);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<1, T> operator>>(const Vector<1, T>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T>(lhs.x >> rhs.x);
	}
}























