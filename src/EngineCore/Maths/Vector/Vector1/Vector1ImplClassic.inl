#pragma once

#include "Vector1.inl"

namespace EngineCore {
	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//
	/*
	template<typename T>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>::Vector()
		: x(0)
	{}

	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>::Vector(K scalar)
		: x(static_cast<T>(scalar))
	{}

	template<typename T>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>::Vector(const Vector<1, K, ComputeAlgorithmClient>& vec)
		: x(static_cast<T>(vec.x))
	{}


/*
	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//

	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template<typename T, typename ComputeAlgorithm>
	template<typename K, typename ComputeAlgorithmClient>
	inline constexpr bool Vector<1, T, EngineCompute::EngineComputeClassic>::operator==(const Vector<1, K, ComputeAlgorithmClient>& rhs)
	{
		return this->x == rhs.x;
	}

	template<typename T>
	inline constexpr bool Vector<1, T, EngineCompute::EngineComputeClassic>::operator!=(const Vector<1, T, EngineCompute::EngineComputeClassic>& rhs) {
		return !(*this == rhs);
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template<typename T>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> Vector<1, T, EngineCompute::EngineComputeClassic>::operator+() {
		return *this;
	}

	// operator -I
	template<typename T>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> Vector<1, T, EngineCompute::EngineComputeClassic>::operator-() {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(-this->x);
	}

	// operator ++I
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator++() {
		++this->x;
		++this->y;
		return *this;
	}

	// operator --I
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator--() {
		--this->x;
		--this->y;
		return *this;
	}

	// operator I++
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> Vector<1, T, EngineCompute::EngineComputeClassic>::operator++(int) {
		Vector<1, T, EngineCompute::EngineComputeClassic> res(*this);
		++*this;
		return res;
	}

	// operator I--
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> Vector<1, T, EngineCompute::EngineComputeClassic>::operator--(int) {
		Vector<1, T, EngineCompute::EngineComputeClassic> res(*this);
		--*this;
		return res;
	}

	// operator =
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator=(const K scalar) {
		this->x = static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator=(const Vector<1, K>& vec) {
		this->x = static_cast<T>(vec.x);
		return *this;
	}

	// operator +=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator+=(const K scalar) {
		this->x += static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator+=(const Vector<1, K>& vec) {
		this->x += static_cast<T>(vec.x);
		return *this;
	}

	// operator -=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator-=(const K scalar) {
		this->x -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator-=(const Vector<1, K>& vec) {
		this->x -= static_cast<T>(vec.x);
		return *this;
	}

	// operator *=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator*=(const K scalar) {
		this->x *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator*=(const Vector<1, K>& vec) {
		this->x *= static_cast<T>(vec.x);
		return *this;
	}

	// operator /=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator/=(const K scalar) {
		this->x /= static_cast<T>(scalar);
		return *this;
	}

	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator/=(const Vector<1, K>& vec) {
		this->x /= static_cast<T>(vec.x);
		return *this;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//
	
	// binary condition
	template<typename T>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> Vector<1, T, EngineCompute::EngineComputeClassic>::operator&&(const Vector<1, T, EngineCompute::EngineComputeClassic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(this->x && rhs.x);
	}

	template<typename T>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> Vector<1, T, EngineCompute::EngineComputeClassic>::operator||(const Vector<1, T, EngineCompute::EngineComputeClassic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(this->x || rhs.x);
	}

	// operator ~I
	template<typename T>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> Vector<1, T, EngineCompute::EngineComputeClassic>::operator~() {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(~this->x, ~this->y);
	}

	// operator %=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator%=(const K scalar) {
		this->x %= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator%=(const Vector<1, K>& vec) {
		this->x %= static_cast<T>(vec.x);
		return *this;
	}

	// operator &=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator&=(const K scalar) {
		this->x &= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator&=(const Vector<1, K>& vec) {
		this->x &= static_cast<T>(vec.x);
		return *this;
	}

	// operator |=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator|=(const K scalar) {
		this->x |= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator|=(const Vector<1, K>& vec) {
		this->x |= static_cast<T>(vec.x);
		return *this;
	}

	// operator ^=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator^=(const K scalar) {
		this->x ^= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator^=(const Vector<1, K>& vec) {
		this->x ^= static_cast<T>(vec.x);
		return *this;
	}

	// operator <<=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator<<=(const K scalar) {
		this->x <<= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator<<=(const Vector<1, K>& vec) {
		this->x <<= static_cast<T>(vec.x);
		return *this;
	}

	// operator >>=
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator>>=(const K scalar) {
		this->x >>= static_cast<T>(scalar);
		return *this;
	}
	
	template<typename T>
	template<typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic>& Vector<1, T, EngineCompute::EngineComputeClassic>::operator>>=(const Vector<1, K>& vec) {
		this->x >>= static_cast<T>(vec.x);
		return *this;
	}

	








	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator+(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x + rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator+(const K lhs, const Vector<1, T, EngineCompute::EngineComputeClassic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs + rhs.x);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator+(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x + rhs.x);
	}

	// operator -
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator-(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x - rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator-(const K lhs, const Vector<1, T, EngineCompute::EngineComputeClassic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs - rhs.x);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator-(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x - rhs.x);
	}

	// operator *
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator*(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x * rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator*(const K lhs, const Vector<1, T, EngineCompute::EngineComputeClassic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs * rhs.x);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator*(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x * rhs.x);
	}

	// operator /
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator/(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x / rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator/(const K lhs, const Vector<1, T, EngineCompute::EngineComputeClassic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs / rhs.x);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator/(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x / rhs.x);
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator%(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x % rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator%(const K lhs, const Vector<1, T, EngineCompute::EngineComputeClassic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs % rhs.x);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator%(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x % rhs.x);
	}

	// operator &
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator&(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x & rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator&(const K lhs, const Vector<1, T, EngineCompute::EngineComputeClassic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs & rhs.x);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator&(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x & rhs.x);
	}

	// operator |
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator|(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x | rhs);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator|(const K lhs, const Vector<1, T, EngineCompute::EngineComputeClassic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs | rhs.x);
	}
	
	template<typename T, typename K>
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator|(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x | rhs.x);
	}

	// operator ^
	template<typename T, typename K> 
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator^(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x ^ rhs);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator^(const K lhs, const Vector<1, T, EngineCompute::EngineComputeClassic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs ^ rhs.x);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator^(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x ^ rhs.x);
	}

	// operator <<
	template<typename T, typename K> 
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator<<(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x << rhs);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator<<(const K lhs, const Vector<1, T, EngineCompute::EngineComputeClassic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs << rhs.x);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator<<(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x << rhs.x);
	}

	// operator >>
	template<typename T, typename K> 
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator>>(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const K rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x >> rhs);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator>>(const K lhs, const Vector<1, T, EngineCompute::EngineComputeClassic>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs >> rhs.x);
	}
	
	template<typename T, typename K> 
	inline constexpr Vector<1, T, EngineCompute::EngineComputeClassic> operator>>(const Vector<1, T, EngineCompute::EngineComputeClassic>& lhs, const Vector<1, K>& rhs) {
		return Vector<1, T, EngineCompute::EngineComputeClassic>(lhs.x >> rhs.x);
	}
	*/
}























