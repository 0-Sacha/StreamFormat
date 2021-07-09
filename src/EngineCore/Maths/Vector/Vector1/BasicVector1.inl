#pragma once

#include "BasicVector1.h"

namespace EngineCore {

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

    template <typename T>
    inline constexpr BasicVector<1, T>::BasicVector()
        : x(0) {}


    template <typename T>
    template <typename K>
    inline constexpr BasicVector<1, T>::BasicVector(const K scalar)
        : x(static_cast<T>(scalar)) {}

    template <typename T>
    template <typename K>
    inline constexpr BasicVector<1, T>::BasicVector(const BasicVector<1, K> &vec)
        : x(static_cast<T>(vec.x)) {}


	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//

	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator==(const BasicVector<1, K>& rhs) -> bool
	{
		return this->x == rhs.x;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator!=(const BasicVector<1, K>& rhs) -> bool {
		return !(*this == rhs);
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template<typename T>
	inline constexpr auto BasicVector<1, T>::operator+() -> BasicVector<1, T> {
		return *this;
	}

	// operator -I
	template<typename T>
	inline constexpr auto BasicVector<1, T>::operator-() -> BasicVector<1, T> {
		return BasicVector<1, T>(-this->x);
	}

	// operator ++I
	template<typename T>
	inline constexpr auto BasicVector<1, T>::operator++() -> BasicVector<1, T>& {
		++this->x;
		return *this;
	}

	// operator --I
	template<typename T>
	inline constexpr auto BasicVector<1, T>::operator--() -> BasicVector<1, T>& {
		--this->x;
		return *this;
	}

	// operator I++
	template<typename T>
	inline constexpr auto BasicVector<1, T>::operator++(int) -> BasicVector<1, T> {
		BasicVector<1, T> res(*this);
		++* this;
		return res;
	}

	// operator I--
	template<typename T>
	inline constexpr auto BasicVector<1, T>::operator--(int) -> BasicVector<1, T> {
		BasicVector<1, T> res(*this);
		--* this;
		return res;
	}

	// operator =
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator=(const K scalar) -> BasicVector<1, T>& {
		this->x = static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator=(const BasicVector<1, K>& vec) -> BasicVector<1, T>& {
		this->x = static_cast<T>(vec.x);
		return *this;
	}

	// operator +=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator+=(const K scalar) -> BasicVector<1, T>& {
		this->x += static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator+=(const BasicVector<1, K>& vec) -> BasicVector<1, T>& {
		this->x += static_cast<T>(vec.x);
		return *this;
	}

	// operator -=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator-=(const K scalar) -> BasicVector<1, T>& {
		this->x -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator-=(const BasicVector<1, K>& vec) -> BasicVector<1, T>& {
		this->x -= static_cast<T>(vec.x);
		return *this;
	}

	// operator *=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator*=(const K scalar) -> BasicVector<1, T>& {
		this->x *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator*=(const BasicVector<1, K>& vec) -> BasicVector<1, T>& {
		this->x *= static_cast<T>(vec.x);
		return *this;
	}

	// operator /=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator/=(const K scalar) -> BasicVector<1, T>& {
		this->x /= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator/=(const BasicVector<1, K>& vec) -> BasicVector<1, T>& {
		this->x /= static_cast<T>(vec.x);
		return *this;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// binary condition
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator&&(const BasicVector<1, K>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(this->x && rhs.x);
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator||(const BasicVector<1, K>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(this->x || rhs.x);
	}

	// operator ~I
	template<typename T>
	inline constexpr auto BasicVector<1, T>::operator~() -> BasicVector<1, T> {
		return BasicVector<1, T>(~this->x);
	}

	// operator %=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator%=(const K scalar) -> BasicVector<1, T>& {
		this->x %= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator%=(const BasicVector<1, K>& vec) -> BasicVector<1, T>& {
		this->x %= static_cast<T>(vec.x);
		return *this;
	}

	// operator &=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator&=(const K scalar) -> BasicVector<1, T>& {
		this->x &= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator&=(const BasicVector<1, K>& vec) -> BasicVector<1, T>& {
		this->x &= static_cast<T>(vec.x);
		return *this;
	}

	// operator |=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator|=(const K scalar) -> BasicVector<1, T>& {
		this->x |= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator|=(const BasicVector<1, K>& vec) -> BasicVector<1, T>& {
		this->x |= static_cast<T>(vec.x);
		return *this;
	}

	// operator ^=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator^=(const K scalar) -> BasicVector<1, T>& {
		this->x ^= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator^=(const BasicVector<1, K>& vec) -> BasicVector<1, T>& {
		this->x ^= static_cast<T>(vec.x);
		return *this;
	}

	// operator <<=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator<<=(const K scalar) -> BasicVector<1, T>& {
		this->x <<= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator<<=(const BasicVector<1, K>& vec) -> BasicVector<1, T>& {
		this->x <<= static_cast<T>(vec.x);
		return *this;
	}

	// operator >>=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator>>=(const K scalar) -> BasicVector<1, T>& {
		this->x >>= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<1, T>::operator>>=(const BasicVector<1, K>& vec) -> BasicVector<1, T>& {
		this->x >>= static_cast<T>(vec.x);
		return *this;
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K>
	inline constexpr auto operator+(const BasicVector<1, T>& lhs, const K rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x + rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator+(const K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs + rhs.x);
	}

	template<typename T, typename K>
	inline constexpr auto operator+(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x + rhs.x);
	}

	// operator -
	template<typename T, typename K>
	inline constexpr auto operator-(const BasicVector<1, T>& lhs, const K rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x - rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator-(const K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs - rhs.x);
	}

	template<typename T, typename K>
	inline constexpr auto operator-(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x - rhs.x);
	}

	// operator *
	template<typename T, typename K>
	inline constexpr auto operator*(const BasicVector<1, T>& lhs, const K rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x * rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator*(const K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs * rhs.x);
	}

	template<typename T, typename K>
	inline constexpr auto operator*(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x * rhs.x);
	}

	// operator /
	template<typename T, typename K>
	inline constexpr auto operator/(const BasicVector<1, T>& lhs, const K rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x / rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator/(const K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs / rhs.x);
	}

	template<typename T, typename K>
	inline constexpr auto operator/(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x / rhs.x);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>
	inline constexpr auto operator%(const BasicVector<1, T>& lhs, const K rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x % rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator%(const K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs % rhs.x);
	}

	template<typename T, typename K>
	inline constexpr auto operator%(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x % rhs.x);
	}

	// operator &
	template<typename T, typename K>
	inline constexpr auto operator&(const BasicVector<1, T>& lhs, const K rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x & rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator&(const K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs & rhs.x);
	}

	template<typename T, typename K>
	inline constexpr auto operator&(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x & rhs.x);
	}

	// operator |
	template<typename T, typename K>
	inline constexpr auto operator|(const BasicVector<1, T>& lhs, const K rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x | rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator|(const K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs | rhs.x);
	}

	template<typename T, typename K>
	inline constexpr auto operator|(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x | rhs.x);
	}

	// operator ^
	template<typename T, typename K>
	inline constexpr auto operator^(const BasicVector<1, T>& lhs, const K rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x ^ rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator^(const K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs ^ rhs.x);
	}

	template<typename T, typename K>
	inline constexpr auto operator^(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x ^ rhs.x);
	}

	// operator <<
	template<typename T, typename K>
	inline constexpr auto operator<<(const BasicVector<1, T>& lhs, const K rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x << rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator<<(const K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs << rhs.x);
	}

	template<typename T, typename K>
	inline constexpr auto operator<<(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x << rhs.x);
	}

	// operator >>
	template<typename T, typename K>
	inline constexpr auto operator>>(const BasicVector<1, T>& lhs, const K rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x >> rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator>>(const K lhs, const BasicVector<1, T>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs >> rhs.x);
	}

	template<typename T, typename K>
	inline constexpr auto operator>>(const BasicVector<1, T>& lhs, const BasicVector<1, K>& rhs) -> BasicVector<1, T> {
		return BasicVector<1, T>(lhs.x >> rhs.x);
	}
}