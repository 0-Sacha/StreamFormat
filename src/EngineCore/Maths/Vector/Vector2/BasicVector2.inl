#pragma once

#include "BasicVector2.h"

namespace EngineCore {

	//----------------------------------//
	//------------- Values -------------//
	//----------------------------------//

	template<typename T>
	inline constexpr auto BasicVector<2, T>::Data(const uint8_t idx) -> T& {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
		case 0: return x;
		case 1: return y;
		}
	}

	template<typename T>
	inline constexpr auto BasicVector<2, T>::Data(const uint8_t idx) const -> const T& {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
		case 0: return x;
		case 1: return y;
		}
	}

	template<typename T>
	inline constexpr auto BasicVector<2, T>::operator[](const uint8_t idx) -> T& {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
		case 0: return x;
		case 1: return y;
		}
	}

	template<typename T>
	inline constexpr auto BasicVector<2, T>::operator[](const uint8_t idx) const -> const T& {
		ENGINE_CORE_ASSERT(idx < Count());

		switch (idx) {
		case 0: return x;
		case 1: return y;
		}
	}

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

    template <typename T>
    inline constexpr BasicVector<2, T>::BasicVector()
        : x(static_cast<T>(0)), y(static_cast<T>(0)) {}


    template <typename T>
    template <typename K>
    inline constexpr BasicVector<2, T>::BasicVector(const K scalar)
        : x(static_cast<T>(scalar)), y(static_cast<T>(scalar)) {}

	template <typename T>
	template <typename K1, typename K2>
	inline constexpr BasicVector<2, T>::BasicVector(const K1 valueX, const K2 valueY)
		: x(static_cast<T>(valueX)), y(static_cast<T>(valueY)) {}

    template <typename T>
    template <typename K>
    inline constexpr BasicVector<2, T>::BasicVector(const BasicVector<2, K> &vec)
        :  x(static_cast<T>(vec.x)), y(static_cast<T>(vec.y)) {}

	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//

	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator==(const BasicVector<2, K>& rhs) -> bool {
		return this->x == rhs.x && this->y == rhs.y;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator!=(const BasicVector<2, K>& rhs) -> bool {
		return !(*this == rhs);
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template<typename T>
	inline constexpr auto BasicVector<2, T>::operator+() -> BasicVector<2, T> {
		return *this;
	}

	// operator -I
	template<typename T>
	inline constexpr auto BasicVector<2, T>::operator-() -> BasicVector<2, T> {
		return BasicVector<2, T>(-this->x, -this->y);
	}

	// operator ++I
	template<typename T>
	inline constexpr auto BasicVector<2, T>::operator++() -> BasicVector<2, T>& {
		++this->x;
		++this->y;
		return *this;
	}
	
	// operator --I
	template<typename T>
	inline constexpr auto BasicVector<2, T>::operator--() -> BasicVector<2, T>& {
		--this->x;
		--this->y;
		return *this;
	}

	// operator I++
	template<typename T>
	inline constexpr auto BasicVector<2, T>::operator++(int) -> BasicVector<2, T> {
		BasicVector<2, T> res(*this);
		++* this;
		return res;
	}

	// operator I--
	template<typename T>
	inline constexpr auto BasicVector<2, T>::operator--(int) -> BasicVector<2, T> {
		BasicVector<2, T> res(*this);
		--* this;
		return res;
	}

	// operator =
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator=(const K scalar) -> BasicVector<2, T>& {
		this->x = static_cast<T>(scalar);
		this->y = static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator=(const BasicVector<2, K>& vec) -> BasicVector<2, T>& {
		this->x = static_cast<T>(vec.x);
		this->y = static_cast<T>(vec.y);
		return *this;
	}

	// operator +=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator+=(const K scalar) -> BasicVector<2, T>& {
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator+=(const BasicVector<2, K>& vec) -> BasicVector<2, T>& {
		this->x += static_cast<T>(vec.x);
		this->y += static_cast<T>(vec.y);
		return *this;
	}

	// operator -=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator-=(const K scalar) -> BasicVector<2, T>& {
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator-=(const BasicVector<2, K>& vec) -> BasicVector<2, T>& {
		this->x -= static_cast<T>(vec.x);
		this->y -= static_cast<T>(vec.y);
		return *this;
	}

	// operator *=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator*=(const K scalar) -> BasicVector<2, T>& {
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator*=(const BasicVector<2, K>& vec) -> BasicVector<2, T>& {
		this->x *= static_cast<T>(vec.x);
		this->y *= static_cast<T>(vec.y);
		return *this;
	}

	// operator /=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator/=(const K scalar) -> BasicVector<2, T>& {
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator/=(const BasicVector<2, K>& vec) -> BasicVector<2, T>& {
		this->x /= static_cast<T>(vec.x);
		this->y /= static_cast<T>(vec.y);
		return *this;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// binary condition
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator&&(const BasicVector<2, K>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(this->x && rhs.x, this->y && rhs.y);
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator||(const BasicVector<2, K>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(this->x || rhs.x, this->y || rhs.y);
	}

	// operator ~I
	template<typename T>
	inline constexpr auto BasicVector<2, T>::operator~() -> BasicVector<2, T> {
		return BasicVector<2, T>(~this->x, ~this->y);
	}

	// operator %=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator%=(const K scalar) -> BasicVector<2, T>& {
		this->x %= static_cast<T>(scalar);
		this->y %= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator%=(const BasicVector<2, K>& vec) -> BasicVector<2, T>& {
		this->x %= static_cast<T>(vec.x);
		this->y %= static_cast<T>(vec.y);
		return *this;
	}

	// operator &=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator&=(const K scalar) -> BasicVector<2, T>& {
		this->x &= static_cast<T>(scalar);
		this->y &= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator&=(const BasicVector<2, K>& vec) -> BasicVector<2, T>& {
		this->x &= static_cast<T>(vec.x);
		this->y &= static_cast<T>(vec.y);
		return *this;
	}

	// operator |=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator|=(const K scalar) -> BasicVector<2, T>& {
		this->x |= static_cast<T>(scalar);
		this->y |= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator|=(const BasicVector<2, K>& vec) -> BasicVector<2, T>& {
		this->x |= static_cast<T>(vec.x);
		this->y |= static_cast<T>(vec.y);
		return *this;
	}

	// operator ^=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator^=(const K scalar) -> BasicVector<2, T>& {
		this->x ^= static_cast<T>(scalar);
		this->y ^= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator^=(const BasicVector<2, K>& vec) -> BasicVector<2, T>& {
		this->x ^= static_cast<T>(vec.x);
		this->y ^= static_cast<T>(vec.y);
		return *this;
	}

	// operator <<=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator<<=(const K scalar) -> BasicVector<2, T>& {
		this->x <<= static_cast<T>(scalar);
		this->y <<= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator<<=(const BasicVector<2, K>& vec) -> BasicVector<2, T>& {
		this->x <<= static_cast<T>(vec.x);
		this->y <<= static_cast<T>(vec.y);
		return *this;
	}

	// operator >>=
	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator>>=(const K scalar) -> BasicVector<2, T>& {
		this->x >>= static_cast<T>(scalar);
		this->y >>= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr auto BasicVector<2, T>::operator>>=(const BasicVector<2, K>& vec) -> BasicVector<2, T>& {
		this->x >>= static_cast<T>(vec.x);
		this->y >>= static_cast<T>(vec.y);
		return *this;
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K>
	inline constexpr auto operator+(const BasicVector<2, T>& lhs, const K rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x + rhs, lhs.y + rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator+(const K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs + rhs.x, lhs + rhs.y);
	}

	template<typename T, typename K>
	inline constexpr auto operator+(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	// operator -
	template<typename T, typename K>
	inline constexpr auto operator-(const BasicVector<2, T>& lhs, const K rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x - rhs, lhs.y - rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator-(const K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs - rhs.x, lhs - rhs.y);
	}

	template<typename T, typename K>
	inline constexpr auto operator-(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	// operator *
	template<typename T, typename K>
	inline constexpr auto operator*(const BasicVector<2, T>& lhs, const K rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x * rhs, lhs.y * rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator*(const K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs * rhs.x, lhs * rhs.y);
	}

	template<typename T, typename K>
	inline constexpr auto operator*(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x * rhs.x, lhs.y * rhs.y);
	}

	// operator /
	template<typename T, typename K>
	inline constexpr auto operator/(const BasicVector<2, T>& lhs, const K rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x / rhs, lhs.y / rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator/(const K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs / rhs.x, lhs / rhs.y);
	}

	template<typename T, typename K>
	inline constexpr auto operator/(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x / rhs.x, lhs.y / rhs.y);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>
	inline constexpr auto operator%(const BasicVector<2, T>& lhs, const K rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x % rhs, lhs.y % rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator%(const K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs % rhs.x, lhs % rhs.y);
	}

	template<typename T, typename K>
	inline constexpr auto operator%(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x % rhs.x, lhs.y % rhs.y);
	}

	// operator &
	template<typename T, typename K>
	inline constexpr auto operator&(const BasicVector<2, T>& lhs, const K rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x & rhs, lhs.y & rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator&(const K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs & rhs.x, lhs & rhs.y);
	}

	template<typename T, typename K>
	inline constexpr auto operator&(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x & rhs.x, lhs.y & rhs.y);
	}

	// operator |
	template<typename T, typename K>
	inline constexpr auto operator|(const BasicVector<2, T>& lhs, const K rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x | rhs, lhs.y | rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator|(const K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs | rhs.x, lhs | rhs.y);
	}

	template<typename T, typename K>
	inline constexpr auto operator|(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x | rhs.x, lhs.y | rhs.y);
	}

	// operator ^
	template<typename T, typename K>
	inline constexpr auto operator^(const BasicVector<2, T>& lhs, const K rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x ^ rhs, lhs.y ^ rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator^(const K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs ^ rhs.x, lhs ^ rhs.y);
	}

	template<typename T, typename K>
	inline constexpr auto operator^(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x ^ rhs.x, lhs.y ^ rhs.y);
	}

	// operator <<
	template<typename T, typename K>
	inline constexpr auto operator<<(const BasicVector<2, T>& lhs, const K rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x << rhs, lhs.y << rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator<<(const K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs << rhs.x, rhs << rhs.y);
	}

	template<typename T, typename K>
	inline constexpr auto operator<<(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x << rhs.x, lhs.y << rhs.y);
	}

	// operator >>
	template<typename T, typename K>
	inline constexpr auto operator>>(const BasicVector<2, T>& lhs, const K rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x >> rhs, lhs.y >> rhs);
	}

	template<typename T, typename K>
	inline constexpr auto operator>>(const K lhs, const BasicVector<2, T>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs >> rhs.x, lhs >> rhs.y);
	}

	template<typename T, typename K>
	inline constexpr auto operator>>(const BasicVector<2, T>& lhs, const BasicVector<2, K>& rhs) -> BasicVector<2, T> {
		return BasicVector<2, T>(lhs.x >> rhs.x, lhs.y >> rhs.y);
	}
}