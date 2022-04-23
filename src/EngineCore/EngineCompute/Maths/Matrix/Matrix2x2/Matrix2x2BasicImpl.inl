#pragma once

#include "Matrix2x2BasicImpl.h"

namespace EngineCore::EngineCompute {

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Matrix()
		: data{ 1, 0
			  , 0, 1 } {}
	
	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Matrix(const MatrixConvertibleTo<2, 2, ValueType> auto& mat)
		: data{ static_cast<ValueType>(mat[0]), static_cast<ValueType>(mat[1])
			  , static_cast<ValueType>(mat[2]), static_cast<ValueType>(mat[3]) } {}

	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Matrix(const std::convertible_to<ValueType> auto scalar)
		: data{ static_cast<ValueType>(scalar), 0
			  , 0, static_cast<ValueType>(scalar) } {}
	
	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Matrix(const std::convertible_to<ValueType> auto x0, const std::convertible_to<ValueType> auto y0,
																						const std::convertible_to<ValueType> auto x1, const std::convertible_to<ValueType> auto y1)
		: data{ static_cast<ValueType>(x0), static_cast<ValueType>(y0)
			  , static_cast<ValueType>(x1), static_cast<ValueType>(y1) } {}

	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Matrix(const ValuesArrayType&& allValuesArr)
		: data{ allValuesArr } {}

	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Matrix(const VectorConvertibleTo<2, ValueType> auto&& row0, const VectorConvertibleTo<2, ValueType> auto&& row1)
		: rows{ static_cast<RowType>(row0), static_cast<RowType>(row1) } {}

	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Matrix(const RowType&& rowsArr)
		: rows{ rowsArr } {}

	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//



	//------------------------------------------------//
	//------------- Main Matrix Function -------------//
	//------------------------------------------------//

	// Not sure for the name
	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::ComputeMultAsAddInPlace(const MatrixConvertibleTo<2, 2, ValueType> auto& mat) {
		rows[0] *= mat.rows[0];
		rows[1] *= mat.rows[1];
		return *this;
	}
	
	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>  Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::ComputeMultAsAdd(const MatrixConvertibleTo<2, 2, ValueType> auto& mat) {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> (rows[0] * mat.rows[0], rows[1] * mat.rows[1]);
	}

	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Transpose() {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>{ rows[0][0], rows[1][0]
																		 , rows[0][1], rows[1][1] };
	}

	template <typename ValueType>
	inline constexpr ValueType Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Determinant() {
		return rows[0][0] * rows[1][1] - rows[1][0] * rows[0][1];
	}

	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Inverse() {
		ValueType oneOverDeterminant = static_cast<ValueType>(1) / Determinant();

		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>{
			 rows[1][1] * oneOverDeterminant,
			-rows[0][1] * oneOverDeterminant,
			-rows[1][0] * oneOverDeterminant,
			 rows[0][0] * oneOverDeterminant };
	}

	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::FromOuterProduct(const VectorConvertibleTo<2, ValueType> auto&& row0, const VectorConvertibleTo<2, ValueType> auto&& row1) {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(row0 * row1.data[0], row0 * row1.data[1]);
	}


	//-----------------------------------------------//
	//------------- Conversion Operator -------------//
	//-----------------------------------------------//

	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template <typename ValueType>
	inline constexpr bool Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator==(const MatrixConvertibleTo<2, 2, ValueType> auto& rhs) {
		return rows[0] == rhs.rows[0] && rows[1] == rhs.rows[1];
	}

	template <typename ValueType>
	inline constexpr bool Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator!=(const MatrixConvertibleTo<2, 2, ValueType> auto& rhs) {
		return rows[0] != rhs.rows[0] || rows[1] != rhs.rows[1];
	}

	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>  Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator+() {
		return *this;
	}

	// operator -I
	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>  Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator-() {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(-rows[0], -rows[1]);
	}


	// operator ++I
	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator++() {
		++this->rows[0];
		++this->rows[1];
		return *this;
	}

	// operator --I
	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator--() {
		--this->rows[0];
		--this->rows[1];
		return *this;
	}

	// operator I++
	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>  Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator++(int) {
		Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> res(*this);
		++*this;
		return res;
	}

	// operator I--
	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>  Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator--(int) {
		Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> res(*this);
		--*this;
		return res;
	}


	// operator =
	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator=(const std::convertible_to<ValueType> auto scalar) {
		rows[0] = { static_cast<ValueType>(scalar), 0 };
		rows[1] = { 0, static_cast<ValueType>(scalar) };
		return *this;
	}

	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator=(const MatrixConvertibleTo<2, 2, ValueType> auto& mat) {
		rows[0] = mat.rows[0];
		rows[1] = mat.rows[1];
		return *this;
	}


	// operator +=
	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator+=(const std::convertible_to<ValueType> auto scalar) {
		rows[0] += scalar;
		rows[1] += scalar;
		return *this;
	}

	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator+=(const MatrixConvertibleTo<2, 2, ValueType> auto& mat) {
		rows[0] += mat.rows[0];
		rows[1] += mat.rows[1];
		return *this;
	}


	// operator -=
	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator-=(const std::convertible_to<ValueType> auto scalar) {
		rows[0] -= scalar;
		rows[1] -= scalar;
		return *this;
	}

	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator-=(const MatrixConvertibleTo<2, 2, ValueType> auto& mat) {
		rows[0] -= mat.rows[0];
		rows[1] -= mat.rows[1];
		return *this;
	}


	// operator *=
	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator*=(const std::convertible_to<ValueType> auto scalar) {
		rows[0] *= scalar;
		rows[1] *= scalar;
		return *this;
	}

	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator*=(const MatrixConvertibleTo<2, 2, ValueType> auto& mat) {
		return M_Type{	rows[0][0] * mat[0][0] + rows[1][0] * mat[0][1],
						rows[0][1] * mat[0][0] + rows[1][1] * mat[0][1],
						rows[0][0] * mat[1][0] + rows[1][0] * mat[1][1],
						rows[0][1] * mat[1][0] + rows[1][1] * mat[1][1] };
	}


	// operator /=
	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator/=(const std::convertible_to<ValueType> auto scalar) {
		rows[0] /= scalar;
		rows[1] /= scalar;
		return *this;
	}

	template <typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::operator/=(const MatrixConvertibleTo<2, 2, ValueType> auto& mat) {
		return *this *= mat.Inverse();
	}


	// -----------------------------------//
	//------------- Operator -------------//
	//------------------------------------//
	// operator +
	template<typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator+(const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.rows[0] + rhs, lhs.rows[1] + rhs);
	}

	template<typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator+(const std::convertible_to<ValueType> auto lhs, const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs + rhs.rows[0], lhs + rhs.rows[1]);
	}

	template<typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator+(const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const MatrixConvertibleTo<2, 2, ValueType> auto& rhs) {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.rows[0] + rhs.rows[0], lhs.rows[1] + rhs.rows[1]);
	}


	// operator -
	template<typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator-(const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.rows[0] - rhs, lhs.rows[1] - rhs);
	}

	template<typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator-(const std::convertible_to<ValueType> auto lhs, const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs - rhs.rows[0], lhs - rhs.rows[1]);
	}

	template<typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator-(const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const MatrixConvertibleTo<2, 2, ValueType> auto& rhs) {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.rows[0] - rhs.rows[0], lhs.rows[1] - rhs.rows[1]);
	}


	// operator *
	// scalar
	template<typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.rows[0] * rhs, lhs.rows[1] * rhs);
	}

	template<typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const std::convertible_to<ValueType> auto lhs, const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs * rhs.rows[0], lhs * rhs.rows[1]);
	}


	// vec
	template<typename ValueType>
	inline constexpr typename Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::ColumnType operator*(const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::ColumnType(	lhs[0][0] * rhs[0] + lhs[0][1] * rhs[1],
																						lhs[1][0] * rhs[0] + lhs[1][1] * rhs[1]);
	}
	
	template<typename ValueType>
	inline constexpr typename Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::RowType operator*(const VectorConvertibleTo<2, ValueType> auto& lhs, const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::RowType(	lhs[0] * rhs[0][0] + lhs[1] * rhs[1][0],
																					lhs[0] * rhs[0][1] + lhs[1] * rhs[1][1]);
	}
	
	// same
	template<typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const MatrixConvertibleTo<2, 2, ValueType> auto& rhs) {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>{	lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1],
																			lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1],
																			lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1],
																			lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1]};
	}

	// others
	template<typename ValueType>
	inline constexpr Matrix<3, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const MatrixConvertibleTo<3, 2, ValueType> auto& rhs) {
		return Matrix<3, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(	lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1],
																			lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1],
																			lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1],
																			lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1],
																			lhs[0][0] * rhs[2][0] + lhs[1][0] * rhs[2][1],
																			lhs[0][1] * rhs[2][0] + lhs[1][1] * rhs[2][1]);
	}
	
	template<typename ValueType>
	inline constexpr Matrix<4, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator*(const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const MatrixConvertibleTo<4, 2, ValueType> auto& rhs) {
		return Matrix<4, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(	lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1],
																			lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1],
																			lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1],
																			lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1],
																			lhs[0][0] * rhs[2][0] + lhs[1][0] * rhs[2][1],
																			lhs[0][1] * rhs[2][0] + lhs[1][1] * rhs[2][1],
																			lhs[0][0] * rhs[3][0] + lhs[1][0] * rhs[3][1],
																			lhs[0][1] * rhs[3][0] + lhs[1][1] * rhs[3][1]);
	}




	// operator /
	// scalar
	template<typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator/(const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs.rows[0] / rhs, lhs.rows[1] / rhs);
	}

	template<typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator/(const std::convertible_to<ValueType> auto lhs, const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		return Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>(lhs / rhs.rows[0], lhs / rhs.rows[1]);
	}
	// vec
	template<typename ValueType>
	inline constexpr typename Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::ColumnType operator/(const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return lhs.Inverse() * rhs;
	}
	
	template<typename ValueType>
	inline constexpr typename Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>::RowType operator/(const VectorConvertibleTo<2, ValueType> auto& lhs, const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& rhs) {
		return lhs * rhs.Inverse();
	}
	// same
	template<typename ValueType>
	inline constexpr Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic> operator/(const Matrix<2, 2, ValueType, Detail::EngineComputeType::EngineComputeBasic>& lhs, const MatrixConvertibleTo<2, 2, ValueType> auto& rhs) {
		return lhs * rhs.Inverse();
	}
}