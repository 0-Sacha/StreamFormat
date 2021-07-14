#pragma once

#include "VectorDefaultBasicImpl.h"

namespace EngineCore {

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

	template <std::size_t COUNT, typename T>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>::Vector()
		: data{} {}

	template <std::size_t COUNT, typename T>
	template <typename ...K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>::Vector(const K ...values)
		: data{static_cast<T>(values)...} {}

	template <std::size_t COUNT, typename T>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>::Vector(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& vec) = default;

	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//

	template <std::size_t COUNT, typename T>
	template <typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>::Vector(const K scalar) {
		std::fill(data.begin(), data.end(), static_cast<T>(scalar));
	}

	template <std::size_t COUNT, typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>::Vector(const Vector<COUNT, K, ComputeAlgoritmClient>& vec) {
		data = vec.data;
	}


	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template<std::size_t COUNT, typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr bool Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator==(const Vector<COUNT, K, ComputeAlgoritmClient>& rhs) {
		return data == rhs.data;
	}

	template<std::size_t COUNT, typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr bool Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator!=(const Vector<COUNT, K, ComputeAlgoritmClient>& rhs) {
		return !(*this == rhs);
	}

	template<std::size_t COUNT, typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator&&(const Vector<COUNT, K, ComputeAlgoritmClient>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> newVec;
		std::generate(newVec.data.begin(), newVec.data.end(), [i = 0, this, &rhs]() { auto res = this->data[i] && rhs.data[i]; ++i; return res; });
		return newVec;
	}

	template<std::size_t COUNT, typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator||(const Vector<COUNT, K, ComputeAlgoritmClient>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> newVec;
		std::generate(newVec.data.begin(), newVec.data.end(), [i = 0, this, &rhs]() { auto res = this->data[i] || rhs.data[i]; ++i; return res; });
		return newVec;
	}

	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template<std::size_t COUNT, typename T>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator+() {
		return *this;
	}

	// operator -I
	template<std::size_t COUNT, typename T>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator-() {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> newVec;
		std::generate(newVec.data.begin(), newVec.data.end(), [i = 0, this]() mutable { auto res = -this->data[i]; ++i; return res; });
		return newVec;
	}

	// operator ~I
	template<std::size_t COUNT, typename T>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator~() {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> newVec;
		std::generate(newVec.data.begin(), newVec.data.end(), [i = 0, this]() mutable { auto res = ~this->data[i]; ++i; return res; });
		return newVec;
	}


	// operator ++I
	template<std::size_t COUNT, typename T>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator++() {
		for (ValueType& value : data)
			++value;
		return *this;
	}

	// operator --I
	template<std::size_t COUNT, typename T>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator--() {
		for (ValueType& value : data)
			--value;
		return *this;
	}

	// operator I++
	template<std::size_t COUNT, typename T>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator++(int) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> res(*this);
		++* this;
		return res;
	}

	// operator I--
	template<std::size_t COUNT, typename T>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator--(int) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> res(*this);
		--* this;
		return res;
	}


	// operator =
	template<std::size_t COUNT, typename T>
	template<typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator=(const K scalar) {
		std::fill(data.begin(), data.end(), static_cast<T>(scalar));
		return *this;
	}

	template<std::size_t COUNT, typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator=(const Vector<COUNT, K, ComputeAlgoritmClient>& vec) {
		data = vec.data;
		return *this;
	}

	// operator +=
	template<std::size_t COUNT, typename T>
	template<typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator+=(const K scalar) {
		for (ValueType& value : data)
			value += scalar;
		return *this;
	}

	template<std::size_t COUNT, typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator+=(const Vector<COUNT, K, ComputeAlgoritmClient>& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](T value) mutable { auto res = value + vec.data[i]; i++; return res; });
		return *this;
	}

	// operator -=
	template<std::size_t COUNT, typename T>
	template<typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator-=(const K scalar) {
		for (ValueType& value : data)
			value -= scalar;
		return *this;
	}

	template<std::size_t COUNT, typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator-=(const Vector<COUNT, K, ComputeAlgoritmClient>& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](T value) mutable { auto res = value - vec.data[i]; i++; return res; });
		return *this;
	}

	// operator *=
	template<std::size_t COUNT, typename T>
	template<typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator*=(const K scalar) {
		for (ValueType& value : data)
			value *= scalar;
		return *this;
	}

	template<std::size_t COUNT, typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator*=(const Vector<COUNT, K, ComputeAlgoritmClient>& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](T value) mutable { auto res = value * vec.data[i]; i++; return res; });
		return *this;
	}

	// operator /=
	template<std::size_t COUNT, typename T>
	template<typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator/=(const K scalar) {
		for (ValueType& value : data)
			value /= scalar;
		return *this;
	}

	template<std::size_t COUNT, typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator/=(const Vector<COUNT, K, ComputeAlgoritmClient>& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](T value) mutable { auto res = value / vec.data[i]; i++; return res; });
		return *this;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %=
	template<std::size_t COUNT, typename T>
	template<typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator%=(const K scalar) {
		for (ValueType& value : data)
			value %= scalar;
		return *this;
	}

	template<std::size_t COUNT, typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator%=(const Vector<COUNT, K, ComputeAlgoritmClient>& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](T value) mutable { auto res = value % vec.data[i]; i++; return res; });
		return *this;
	}

	// operator &=
	template<std::size_t COUNT, typename T>
	template<typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator&=(const K scalar) {
		for (ValueType& value : data)
			value &= scalar;
		return *this;
	}

	template<std::size_t COUNT, typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator&=(const Vector<COUNT, K, ComputeAlgoritmClient>& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](T value) mutable { auto res = value & vec.data[i]; i++; return res; });
		return *this;
	}

	// operator |=
	template<std::size_t COUNT, typename T>
	template<typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator|=(const K scalar) {
		for (ValueType& value : data)
			value |= scalar;
		return *this;
	}

	template<std::size_t COUNT, typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator|=(const Vector<COUNT, K, ComputeAlgoritmClient>& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](T value) mutable { auto res = value | vec.data[i]; i++; return res; });
		return *this;
	}

	// operator ^=
	template<std::size_t COUNT, typename T>
	template<typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator^=(const K scalar) {
		for (ValueType& value : data)
			value ^= scalar;
		return *this;
	}

	template<std::size_t COUNT, typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator^=(const Vector<COUNT, K, ComputeAlgoritmClient>& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](T value) mutable { auto res = value ^ vec.data[i]; i++; return res; });
		return *this;
	}

	// operator <<=
	template<std::size_t COUNT, typename T>
	template<typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator<<=(const K scalar) {
		for (ValueType& value : data)
			value <<= scalar;
		return *this;
	}

	template<std::size_t COUNT, typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator<<=(const Vector<COUNT, K, ComputeAlgoritmClient>& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](T value) mutable { auto res = value << vec.data[i]; i++; return res; });
		return *this;
	}

	// operator >>=
	template<std::size_t COUNT, typename T>
	template<typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator>>=(const K scalar) {
		for (ValueType& value : data)
			value >>= scalar;
		return *this;
	}

	template<std::size_t COUNT, typename T>
	template<typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic>& Vector<COUNT, T, EngineCompute::EngineComputeBasic>::operator>>=(const Vector<COUNT, K, ComputeAlgoritmClient>& vec) {
		std::transform(data.cbegin(), data.cend(), data.begin(), [i = 0, &vec](T value) mutable { auto res = value >> vec.data[i]; i++; return res; });
		return *this;
	}



	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator+(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] + rhs; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator+(const K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs + rhs.data[i]; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator+(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgoritmClient>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] + rhs.data[i]; ++i; return res; });
		return vec;
	}

	// operator -
	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator-(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] - rhs; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator-(const K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs - rhs.data[i]; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator-(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgoritmClient>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] - rhs.data[i]; ++i; return res; });
		return vec;
	}

	// operator *
	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator*(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] * rhs; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator*(const K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs * rhs.data[i]; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator*(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgoritmClient>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] * rhs.data[i]; ++i; return res; });
		return vec;
	}

	// operator /
	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator/(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] / rhs; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator/(const K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs / rhs.data[i]; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator/(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgoritmClient>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] / rhs.data[i]; ++i; return res; });
		return vec;
	}



	//-------------------------------------------//
	//------------- binary operator -------------//
	//-------------------------------------------//

	// operator %
	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator%(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] % rhs; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator%(const K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs % rhs.data[i]; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator%(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgoritmClient>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] % rhs.data[i]; ++i; return res; });
		return vec;
	}

	// operator &
	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator&(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] & rhs; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator&(const K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs & rhs.data[i]; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator&(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgoritmClient>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] & rhs.data[i]; ++i; return res; });
		return vec;
	}

	// operator |
	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator|(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] | rhs; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator|(const K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs | rhs.data[i]; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator|(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgoritmClient>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] | rhs.data[i]; ++i; return res; });
		return vec;
	}

	// operator ^
	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator^(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] ^ rhs; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator^(const K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs ^ rhs.data[i]; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator^(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgoritmClient>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] ^ rhs.data[i]; ++i; return res; });
		return vec;
	}

	// operator <<
	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator<<(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] << rhs; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator<<(const K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs << rhs.data[i]; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator<<(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgoritmClient>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] << rhs.data[i]; ++i; return res; });
		return vec;
	}

	// operator >>
	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator>>(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, rhs]() mutable { auto res = lhs.data[i] >> rhs; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator>>(const K lhs, const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, lhs, &rhs]() mutable { auto res = lhs >> rhs.data[i]; ++i; return res; });
		return vec;
	}

	template<std::size_t COUNT, typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Vector<COUNT, T, EngineCompute::EngineComputeBasic> operator>>(const Vector<COUNT, T, EngineCompute::EngineComputeBasic>& lhs, const Vector<COUNT, K, ComputeAlgoritmClient>& rhs) {
		Vector<COUNT, T, EngineCompute::EngineComputeBasic> vec;
		std::generate(vec.begin(), vec.end(), [i = 0, &lhs, &rhs]() mutable { auto res = lhs.data[i] >> rhs.data[i]; ++i; return res; });
		return vec;
	}
}

