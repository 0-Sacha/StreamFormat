#pragma once

#include "Vector1BasicImpl.h"

namespace EngineCore {

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

    template <typename T>
    inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>::Vector()
		: x{} {}

    template <typename T>
    inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>::Vector(const T scalar)
		: x{scalar} {}

    template <typename T>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>::Vector(const Vector<1, T, EngineCompute::EngineComputeBasic>& vec) = default;


	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//

	template <typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>::Vector(const K scalar)
		: x{static_cast<T>(scalar)} {}

	template <typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>::Vector(const Vector<1, K, ComputeAlgoritmClient>& vec)
		: x{static_cast<T>(vec.x) } {}

	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template<typename T>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr bool Vector<1, T, EngineCompute::EngineComputeBasic>::operator==(const Vector<1, K, ComputeAlgorithmClient>& rhs) {
		return this->x == rhs.x;
	}

	template<typename T>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr bool Vector<1, T, EngineCompute::EngineComputeBasic>::operator!=(const Vector<1, K, ComputeAlgorithmClient>& rhs) {
		return !(*this == rhs);
	}

	template<typename T>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> Vector<1, T, EngineCompute::EngineComputeBasic>::operator&&(const Vector<1, K, ComputeAlgorithmClient>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(this->x && rhs.x);
	}

	template<typename T>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> Vector<1, T, EngineCompute::EngineComputeBasic>::operator||(const Vector<1, K, ComputeAlgorithmClient>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(this->x || rhs.x);
	}

	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template<typename T>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> Vector<1, T, EngineCompute::EngineComputeBasic>::operator+() {
		return *this;
	}

	// operator -I
	template<typename T>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> Vector<1, T, EngineCompute::EngineComputeBasic>::operator-() {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(-this->x);
	}

	// operator ~I
	template<typename T>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> Vector<1, T, EngineCompute::EngineComputeBasic>::operator~() {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(~this->x);
	}


	// operator ++I
	template<typename T>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator++() {
		++this->x;
		return *this;
	}

	// operator --I
	template<typename T>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator--() {
		--this->x;
		return *this;
	}

	// operator I++
	template<typename T>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> Vector<1, T, EngineCompute::EngineComputeBasic>::operator++(int) {
		Vector<1, T, EngineCompute::EngineComputeBasic> res(*this);
		++* this;
		return res;
	}

	// operator I--
	template<typename T>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> Vector<1, T, EngineCompute::EngineComputeBasic>::operator--(int) {
		Vector<1, T, EngineCompute::EngineComputeBasic> res(*this);
		--* this;
		return res;
	}



	// operator =
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator=(const K scalar) {
		this->x = static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator=(const Vector<1, K, ComputeAlgorithmClient>& vec) {
		this->x = static_cast<T>(vec.x);
		return *this;
	}

	// operator +=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator+=(const K scalar) {
		this->x += static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator+=(const Vector<1, K, ComputeAlgorithmClient>& vec) {
		this->x += static_cast<T>(vec.x);
		return *this;
	}

	// operator -=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator-=(const K scalar) {
		this->x -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator-=(const Vector<1, K, ComputeAlgorithmClient>& vec) {
		this->x -= static_cast<T>(vec.x);
		return *this;
	}

	// operator *=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator*=(const K scalar) {
		this->x *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator*=(const Vector<1, K, ComputeAlgorithmClient>& vec) {
		this->x *= static_cast<T>(vec.x);
		return *this;
	}

	// operator /=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator/=(const K scalar) {
		this->x /= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator/=(const Vector<1, K, ComputeAlgorithmClient>& vec) {
		this->x /= static_cast<T>(vec.x);
		return *this;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//
	// 
	// operator %=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator%=(const K scalar) {
		this->x %= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator%=(const Vector<1, K, ComputeAlgorithmClient>& vec) {
		this->x %= static_cast<T>(vec.x);
		return *this;
	}

	// operator &=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator&=(const K scalar) {
		this->x &= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator&=(const Vector<1, K, ComputeAlgorithmClient>& vec) {
		this->x &= static_cast<T>(vec.x);
		return *this;
	}

	// operator |=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator|=(const K scalar) {
		this->x |= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator|=(const Vector<1, K, ComputeAlgorithmClient>& vec) {
		this->x |= static_cast<T>(vec.x);
		return *this;
	}

	// operator ^=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator^=(const K scalar) {
		this->x ^= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator^=(const Vector<1, K, ComputeAlgorithmClient>& vec) {
		this->x ^= static_cast<T>(vec.x);
		return *this;
	}

	// operator <<=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator<<=(const K scalar) {
		this->x <<= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator<<=(const Vector<1, K, ComputeAlgorithmClient>& vec) {
		this->x <<= static_cast<T>(vec.x);
		return *this;
	}

	// operator >>=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator>>=(const K scalar) {
		this->x >>= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic>& Vector<1, T, EngineCompute::EngineComputeBasic>::operator>>=(const Vector<1, K, ComputeAlgorithmClient>& vec) {
		this->x >>= static_cast<T>(vec.x);
		return *this;
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator+(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x + rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator+(const K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs + rhs.x);
	}

	template<typename T, typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator+(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x + rhs.x);
	}

	// operator -
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator-(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x - rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator-(const K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs - rhs.x);
	}

	template<typename T, typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator-(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x - rhs.x);
	}

	// operator *
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator*(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x * rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator*(const K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs * rhs.x);
	}

	template<typename T, typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator*(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x * rhs.x);
	}

	// operator /
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator/(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x / rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator/(const K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs / rhs.x);
	}

	template<typename T, typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator/(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x / rhs.x);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator%(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x % rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator%(const K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs % rhs.x);
	}

	template<typename T, typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator%(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x % rhs.x);
	}

	// operator &
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator&(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x & rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator&(const K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs & rhs.x);
	}

	template<typename T, typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator&(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x & rhs.x);
	}

	// operator |
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator|(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x | rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator|(const K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs | rhs.x);
	}

	template<typename T, typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator|(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x | rhs.x);
	}

	// operator ^
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator^(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x ^ rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator^(const K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs ^ rhs.x);
	}

	template<typename T, typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator^(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x ^ rhs.x);
	}

	// operator <<
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator<<(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x << rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator<<(const K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs << rhs.x);
	}

	template<typename T, typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator<<(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x << rhs.x);
	}

	// operator >>
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator>>(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x >> rhs);
	}

	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator>>(const K lhs, const Vector<1, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs >> rhs.x);
	}

	template<typename T, typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeBasic> operator>>(const Vector<1, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<1, K, ComputeAlgorithmClient>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeBasic>(lhs.x >> rhs.x);
	}
}