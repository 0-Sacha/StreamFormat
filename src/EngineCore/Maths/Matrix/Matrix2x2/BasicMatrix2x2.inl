#pragma once

#include "BasicMatrix2x2.h"

namespace EngineCore {

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

	template <typename T>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::Matrix()
		: data{ 1, 0, 0, 1 } {}

	template <typename T>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::Matrix(const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& mat) = default;

/*
	template <typename T>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::Matrix(const T scalar)
		: data{ scalar, 0, 0, scalar } {}

	template <typename T>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::Matrix(const RowType&& row0, const RowType&& row1)
		: rows{ row0, row1 } {}

	template <typename T>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::Matrix(const T x0, const T y0,
		const T x1, const T y1)
		: data{ x0, y0, x1, y1 } {}


	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//

	template <typename T>
	template <typename K, typename ComputeAlgoritmClient>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::Matrix(const Matrix<2, 2, K, ComputeAlgoritmClient>& mat)
		: data{ static_cast<T>(mat.data[0]), static_cast<T>(mat.data[1]), static_cast<T>(mat.data[2]), static_cast<T>(mat.data[3]) } {}


	template <typename T>
	template <typename K>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::Matrix(const K scalar)
		: data{ static_cast<T>(scalar), 0, 0, static_cast<T>(scalar) } {}

	template <typename T>
	template <typename K1, typename ComputeAlgoritmClient1, typename K2, typename ComputeAlgoritmClient2>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::Matrix(const RowTypeLike<K1, ComputeAlgoritmClient1>&& row0, const ColumnTypeLike<K2, ComputeAlgoritmClient2>&& row1)
		: rows{ static_cast<RowType>(row0), static_cast<RowType>(row1) } {}

	template <typename T>
	template <typename X0, typename Y0, typename X1, typename Y1>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::Matrix(const X0 x0, const Y0 y0,
		const X1 x1, const Y1 y1)
		: rows{ static_cast<T>(x0), static_cast<T>(y0), static_cast<T>(x1), static_cast<T>(y1) } {}


	//------------------------------------------------//
	//------------- Main Matrix Function -------------//
	//------------------------------------------------//

	// Not sure for the name
	template <typename T>
	template <typename K, typename ComputeAlgoritmClient>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::ComputeMultAsAddInPlace(const Matrix <2, 2, K, ComputeAlgoritmClient>& mat) {
		rows[0] *= mat.rows[0];
		rows[1] *= mat.rows[1];
		return *this;
	}

	template <typename T>
	template <typename K, typename ComputeAlgoritmClient>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic> Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::ComputeMultAsAdd(const Matrix <2, 2, K, ComputeAlgoritmClient>& mat) {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic> (rows[0] * mat.rows[0], rows[1] * mat.rows[1]);
	}


	template <typename T>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic> Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::Transpose() {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>{ rows[0][0], rows[1][0], rows[0][1], rows[1][1] };
	}

	template <typename T>
	inline constexpr T Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::Determinant() {
		return rows[0][0] * rows[1][1] - rows[1][0] * rows[0][1];
	}

	template <typename T>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic> Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::Inverse() {
		T oneOverDeterminant = static_cast<T>(1) / Determinant();

		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>{
			 rows[1][1] * oneOverDeterminant,
			-rows[0][1] * oneOverDeterminant,
			-rows[1][0] * oneOverDeterminant,
			 rows[0][0] * oneOverDeterminant };
	}

	template <typename T>
	template <typename K1, typename ComputeAlgoritmClient1, typename K2, typename ComputeAlgoritmClient2>
	static inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic> Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::FromOuterProduct(const RowTypeLike<K1, ComputeAlgoritmClient1>&& row0, const ColumnTypeLike<K2, ComputeAlgoritmClient2>&& row1) {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>(row0 * row1.data[0], row0 * row1.data[1]);
	}



	//-----------------------------------------------//
	//------------- Conversion Operator -------------//
	//-----------------------------------------------//

	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template <typename T>
	template <typename K, typename ComputeAlgoritmClient>
	inline constexpr bool Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator==(const Matrix<2, 2, K, ComputeAlgoritmClient>& rhs) {
		return data == rhs.data;
	}

	template <typename T>
	template <typename K, typename ComputeAlgoritmClient>
	inline constexpr bool Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator!=(const Matrix<2, 2, K, ComputeAlgoritmClient>& rhs) {
		return !(*this == rhs);
	}


	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template <typename T>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>  Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator+() {
		return *this;
	}

	// operator -I
	template <typename T>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>  Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator-() {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>(-rows[0], -rows[1]);
	}


	// operator ++I
	template <typename T>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator++() {
		++this->rows[0];
		++this->rows[1];
		return *this;
	}

	// operator --I
	template <typename T>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator--() {
		--this->rows[0];
		--this->rows[1];
		return *this;
	}

	// operator I++
	template <typename T>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>  Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator++(int) {
		Matrix<2, 2, T, EngineCompute::EngineComputeBasic> res(*this);
		++*this;
		return res;
	}

	// operator I--
	template <typename T>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>  Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator--(int) {
		Matrix<2, 2, T, EngineCompute::EngineComputeBasic> res(*this);
		--*this;
		return res;
	}


	// operator =
	template <typename T>
	template <typename K>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator=(const K scalar) {
		rows[0] = { static_cast<T>(scalar), 0 };
		rows[1] = { 0, static_cast<T>(scalar) };
		return *this;
	}

	template <typename T>
	template <typename K, typename ComputeAlgoritmClient>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator=(const Matrix<2, 2, K, ComputeAlgoritmClient>& mat) {
		rows[0] = mat.rows[0];
		rows[1] = mat.rows[1];
		return *this;
	}


	// operator +=
	template <typename T>
	template <typename K>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator+=(const K scalar) {
		rows[0] += scalar;
		rows[1] += scalar;
		return *this;
	}

	template <typename T>
	template <typename K, typename ComputeAlgoritmClient>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator+=(const Matrix<2, 2, K, ComputeAlgoritmClient>& mat) {
		rows[0] += mat.rows[0];
		rows[1] += mat.rows[1];
		return *this;
	}


	// operator -=
	template <typename T>
	template <typename K>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator-=(const K scalar) {
		rows[0] -= scalar;
		rows[1] -= scalar;
		return *this;
	}

	template <typename T>
	template <typename K, typename ComputeAlgoritmClient>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator-=(const Matrix<2, 2, K, ComputeAlgoritmClient>& mat) {
		rows[0] -= mat.rows[0];
		rows[1] -= mat.rows[1];
		return *this;
	}


	// operator *=
	template <typename T>
	template <typename K>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator*=(const K scalar) {
		rows[0] *= scalar;
		rows[1] *= scalar;
		return *this;
	}

	template <typename T>
	template <typename K, typename ComputeAlgoritmClient>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator*=(const Matrix<2, 2, K, ComputeAlgoritmClient>& mat) {

		return *this;
	}


	// operator /=
	template <typename T>
	template <typename K>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator/=(const K scalar) {
		rows[0] /= scalar;
		rows[1] /= scalar;
		return *this;
	}

	template <typename T>
	template <typename K, typename ComputeAlgoritmClient>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::operator/=(const Matrix<2, 2, K, ComputeAlgoritmClient>& mat) {
		return *this *= mat.Inverse();
	}


	// -----------------------------------//
	//------------- Operator -------------//
	//------------------------------------//
	
	// operator +
	template <typename T, typename K>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic> operator+(const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>(lhs.rows[0] + rhs, lhs.rows[1] + rhs);
	}

	template <typename T, typename K>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic> operator+(const K lhs, const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>(lhs + rhs.rows[0], lhs + rhs.rows[1]);
	}

	template <typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic> operator+(const Matrix<2, 2, K, EngineCompute::EngineComputeBasic>& lhs, const Matrix<2, 2, K, ComputeAlgoritmClient>& rhs) {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>(lhs.rows[0] + rhs.rows[0], lhs.rows[1] + rhs.rows[1]);
	}


	// operator -
	template <typename T, typename K>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic> operator-(const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>(lhs.rows[0] - rhs, lhs.rows[1] - rhs);
	}

	template <typename T, typename K>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic> operator-(const K lhs, const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>(lhs - rhs.rows[0], lhs - rhs.rows[1]);
	}

	template <typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic> operator-(const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& lhs, const Matrix<2, 2, K, ComputeAlgoritmClient>& rhs) {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>(lhs.rows[0] - rhs.rows[0], lhs.rows[1] - rhs.rows[1]);
	}

	// operator *
	template <typename T, typename K>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic> operator*(	const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& lhs,
																					const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>::ValueTypeConvertible auto rhs) {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>(lhs.rows[0] * rhs, lhs.rows[1] * rhs);
	}

	template <typename T, typename K>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic> operator*(	const typename Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>::ValueTypeConvertible auto lhs,
																					const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>(lhs * rhs.rows[0], lhs * rhs.rows[1]);
	}


	template <typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr typename Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::ColumnType operator*(	const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& lhs,
																										const typename Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::RowTypeLike auto& rhs) {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::ColumnType(	lhs[0][0] * rhs[0] + lhs[1][0] * rhs[1],
																				lhs[0][1] * rhs[0] + lhs[1][1] * rhs[1]);
	}
	
	template <typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr typename Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::RowType operator*(const typename Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::ColumnTypeLike auto& lhs,
																									const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::RowType(	lhs[0] * rhs[0][0] + lhs[1] * rhs[0][1],
																			lhs[0] * rhs[1][0] + lhs[1] * rhs[1][1]);
	}
	
	template <typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic> operator*(const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& lhs, const Matrix<2, 2, K, ComputeAlgoritmClient>& rhs) {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>(	lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1],
																	lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1],
																	lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1],
																	lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1]);
	}

	template <typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Matrix<3, 2, T, EngineCompute::EngineComputeBasic> operator*(const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& lhs, const Matrix<3, 2, K, ComputeAlgoritmClient>& rhs) {
		return Matrix<3, 2, T, EngineCompute::EngineComputeBasic>(	lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1],
																	lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1],
																	lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1],
																	lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1],
																	lhs[0][0] * rhs[2][0] + lhs[1][0] * rhs[2][1],
																	lhs[0][1] * rhs[2][0] + lhs[1][1] * rhs[2][1]);
	}
	
	template <typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Matrix<4, 2, T, EngineCompute::EngineComputeBasic> operator*(const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& lhs, const Matrix<4, 2, K, ComputeAlgoritmClient>& rhs) {
		return Matrix<4, 2, T, EngineCompute::EngineComputeBasic>(	lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1],
																	lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1],
																	lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1],
																	lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1],
																	lhs[0][0] * rhs[2][0] + lhs[1][0] * rhs[2][1],
																	lhs[0][1] * rhs[2][0] + lhs[1][1] * rhs[2][1],
																	lhs[0][0] * rhs[3][0] + lhs[1][0] * rhs[3][1],
																	lhs[0][1] * rhs[3][0] + lhs[1][1] * rhs[3][1]);
	}




	// operator /
	template <typename T, typename K>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic> operator/(const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& lhs, const K rhs) {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>(lhs.rows[0] / rhs, lhs.rows[1] / rhs);
	}

	template <typename T, typename K>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic> operator/(const K lhs, const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& rhs) {
		return Matrix<2, 2, T, EngineCompute::EngineComputeBasic>(lhs / rhs.rows[0], lhs / rhs.rows[1]);
	}

	template <typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr typename Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::ColumnType operator/(const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& lhs, const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::RowTypeLike<T, ComputeAlgoritmClient>& rhs) {
		return lhs.Inverse() * rhs;
	}
	
	template <typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr typename Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::RowType operator/(const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>::ColumnTypeLike<T, ComputeAlgoritmClient>& lhs, const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& rhs) {
		return lhs * rhs.Inverse();
	}

	template <typename T, typename K, typename ComputeAlgoritmClient>
	inline constexpr Matrix<2, 2, T, EngineCompute::EngineComputeBasic> operator/(const Matrix<2, 2, T, EngineCompute::EngineComputeBasic>& lhs, const Matrix<2, 2, K, ComputeAlgoritmClient>& rhs) {
		return lhs * rhs.Inverse();
	}
	*/
}