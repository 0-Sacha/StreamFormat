#pragma once

#include "Matrix3x3BasicImpl.h"

namespace EngineCore::TNX {

	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>::Matrix()
		: data{ 1, 0, 0
			  , 0, 1, 0
			  , 0, 0, 1 } {}
	
	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>::Matrix(const MatrixConvertibleTo<3, 3, ValueType> auto& mat)
		: data{ static_cast<ValueType>(mat[0]), static_cast<ValueType>(mat[1]), static_cast<ValueType>(mat[2])
			  , static_cast<ValueType>(mat[3]), static_cast<ValueType>(mat[4]), static_cast<ValueType>(mat[5])
			  , static_cast<ValueType>(mat[6]), static_cast<ValueType>(mat[7]), static_cast<ValueType>(mat[8]) } {}

	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>::Matrix(const std::convertible_to<ValueType> auto scalar)
		: data{ static_cast<ValueType>(scalar), 0, 0
			  , 0, static_cast<ValueType>(scalar), 0
			  , 0, 0, static_cast<ValueType>(scalar) } {}
	
	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>::Matrix(const std::convertible_to<ValueType> auto x0, const std::convertible_to<ValueType> auto y0, const std::convertible_to<ValueType> auto z0,
																						const std::convertible_to<ValueType> auto x1, const std::convertible_to<ValueType> auto y1, const std::convertible_to<ValueType> auto z1,
																						const std::convertible_to<ValueType> auto x2, const std::convertible_to<ValueType> auto y2, const std::convertible_to<ValueType> auto z2)

		: data{ static_cast<ValueType>(x0), static_cast<ValueType>(y0), static_cast<ValueType>(z0)
			  , static_cast<ValueType>(x1), static_cast<ValueType>(y1), static_cast<ValueType>(z1)
			  , static_cast<ValueType>(x2), static_cast<ValueType>(y2), static_cast<ValueType>(z2) } {}

	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>::Matrix(const ValuesArrayType&& allValuesArr)
		: data{ allValuesArr } {}

	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>::Matrix(const VectorConvertibleTo<3, ValueType> auto&& row0, const VectorConvertibleTo<3, ValueType> auto&& row1)
		: rows{ static_cast<RowType>(row0), static_cast<RowType>(row1) } {}

	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>::Matrix(const RowType&& rowsArr)
		: rows{ rowsArr } {} 

	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//



	//------------------------------------------------//
	//------------- Main Matrix Function -------------//
	//------------------------------------------------//

	// Not sure for the name
	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& Matrix<3, 3, ValueType, TNXType::TNXBasic>::ComputeMultAsAddInPlace(const MatrixConvertibleTo<3, 3, ValueType> auto& mat) {
		rows[0] *= mat.rows[0];
		rows[1] *= mat.rows[1];
		rows[2] *= mat.rows[2];
		return *this;
	}
	
	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>  Matrix<3, 3, ValueType, TNXType::TNXBasic>::ComputeMultAsAdd(const MatrixConvertibleTo<3, 3, ValueType> auto& mat) {
		return Matrix<3, 3, ValueType, TNXType::TNXBasic> (rows[0] * mat.rows[0], rows[1] * mat.rows[1], rows[2] * mat.rows[2]);
	}

	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> Matrix<3, 3, ValueType, TNXType::TNXBasic>::Transpose() {
		return Matrix<3, 3, ValueType, TNXType::TNXBasic>{ rows[0][0], rows[1][0], rows[2][0]
																		 , rows[0][1], rows[1][1], rows[2][1]
																		 , rows[0][2], rows[1][2], rows[2][2]};
	}

	template <typename ValueType>
	inline constexpr ValueType Matrix<3, 3, ValueType, TNXType::TNXBasic>::Determinant() {
		return	+ rows[0][0] * (rows[1][1] * rows[2][2] - rows[2][1] * rows[1][2])
				- rows[1][0] * (rows[0][1] * rows[2][2] - rows[2][1] * rows[0][2])
				+ rows[2][0] * (rows[0][1] * rows[1][2] - rows[1][1] * rows[0][2]);;
	}

	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> Matrix<3, 3, ValueType, TNXType::TNXBasic>::Inverse() {
		ValueType oneOverDeterminant = static_cast<ValueType>(1) / Determinant();

		return Matrix<3, 3, ValueType, TNXType::TNXBasic>{
			+ (rows[1][1] * rows[2][2] - rows[2][1] * rows[1][2]) * oneOverDeterminant,
			- (rows[0][1] * rows[2][2] - rows[2][1] * rows[0][2]) * oneOverDeterminant,
			+ (rows[0][1] * rows[1][2] - rows[1][1] * rows[0][2]) * oneOverDeterminant,
			+ (rows[0][0] * rows[2][2] - rows[2][0] * rows[0][2]) * oneOverDeterminant,
			- (rows[1][0] * rows[2][2] - rows[2][0] * rows[1][2]) * oneOverDeterminant,
			- (rows[0][0] * rows[1][2] - rows[1][0] * rows[0][2]) * oneOverDeterminant,
			+ (rows[1][0] * rows[2][1] - rows[2][0] * rows[1][1]) * oneOverDeterminant,
			- (rows[0][0] * rows[2][1] - rows[2][0] * rows[0][1]) * oneOverDeterminant,
			+ (rows[0][0] * rows[1][1] - rows[1][0] * rows[0][1]) * oneOverDeterminant };
	}

	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> Matrix<3, 3, ValueType, TNXType::TNXBasic>::FromOuterProduct(const VectorConvertibleTo<3, ValueType> auto&& row0, const VectorConvertibleTo<3, ValueType> auto&& row1) {
		return Matrix<3, 3, ValueType, TNXType::TNXBasic>(row0 * row1.data[0], row0 * row1.data[1], row0 * row1.data[2]);
	}


	//-----------------------------------------------//
	//------------- Conversion Operator -------------//
	//-----------------------------------------------//

	//----------------------------------------------//
	//------------- Condition Operator -------------//
	//----------------------------------------------//

	template <typename ValueType>
	inline constexpr bool Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator==(const MatrixConvertibleTo<3, 3, ValueType> auto& rhs) {
		return rows[0] == rhs.rows[0] && rows[1] == rhs.rows[1] && rows[2] == rhs.rows[2];
	}

	template <typename ValueType>
	inline constexpr bool Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator!=(const MatrixConvertibleTo<3, 3, ValueType> auto& rhs) {
		return rows[0] != rhs.rows[0] || rows[1] != rhs.rows[1] || rows[2] != rhs.rows[2];
	}

	//------------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +I
	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>  Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator+() {
		return *this;
	}

	// operator -I
	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>  Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator-() {
		return Matrix<3, 3, ValueType, TNXType::TNXBasic>(-rows[0], -rows[1], -rows[2]);
	}


	// operator ++I
	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator++() {
		++this->rows[0];
		++this->rows[1];
		++this->rows[2];
		return *this;
	}

	// operator --I
	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator--() {
		--this->rows[0];
		--this->rows[1];
		--this->rows[2];
		return *this;
	}

	// operator I++
	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>  Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator++(int) {
		Matrix<3, 3, ValueType, TNXType::TNXBasic> res(*this);
		++*this;
		return res;
	}

	// operator I--
	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>  Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator--(int) {
		Matrix<3, 3, ValueType, TNXType::TNXBasic> res(*this);
		--*this;
		return res;
	}


	// operator =
	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator=(const std::convertible_to<ValueType> auto scalar) {
		ValueType value = static_cast<ValueType>(scalar);
		rows[0] = { value, 0, 0 };
		rows[1] = { 0, value, 0 };
		rows[2] = { 0, 0, value };
		return *this;
	}

	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator=(const MatrixConvertibleTo<3, 3, ValueType> auto& mat) {
		rows[0] = mat.rows[0];
		rows[1] = mat.rows[1];
		rows[2] = mat.rows[2];
		return *this;
	}


	// operator +=
	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator+=(const std::convertible_to<ValueType> auto scalar) {
		rows[0] += scalar;
		rows[1] += scalar;
		rows[2] += scalar;
		return *this;
	}

	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator+=(const MatrixConvertibleTo<3, 3, ValueType> auto& mat) {
		rows[0] += mat.rows[0];
		rows[1] += mat.rows[1];
		rows[2] += mat.rows[2];
		return *this;
	}


	// operator -=
	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator-=(const std::convertible_to<ValueType> auto scalar) {
		rows[0] -= scalar;
		rows[1] -= scalar;
		rows[2] -= scalar;
		return *this;
	}

	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator-=(const MatrixConvertibleTo<3, 3, ValueType> auto& mat) {
		rows[0] -= mat.rows[0];
		rows[1] -= mat.rows[1];
		rows[2] -= mat.rows[2];
		return *this;
	}


	// operator *=
	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator*=(const std::convertible_to<ValueType> auto scalar) {
		rows[0] *= scalar;
		rows[1] *= scalar;
		rows[2] *= scalar;
		return *this;
	}

	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator*=(const MatrixConvertibleTo<3, 3, ValueType> auto& mat) {

		return *this;
	}


	// operator /=
	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator/=(const std::convertible_to<ValueType> auto scalar) {
		rows[0] /= scalar;
		rows[1] /= scalar;
		rows[2] /= scalar;
		return *this;
	}

	template <typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& Matrix<3, 3, ValueType, TNXType::TNXBasic>::operator/=(const MatrixConvertibleTo<3, 3, ValueType> auto& mat) {
		return *this *= mat.Inverse();
	}


	// -----------------------------------//
	//------------- Operator -------------//
	//------------------------------------//
	// operator +
	template<typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator+(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Matrix<3, 3, ValueType, TNXType::TNXBasic>(lhs.rows[0] + rhs, lhs.rows[1] + rhs, lhs.rows[2] + rhs);
	}

	template<typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator+(const std::convertible_to<ValueType> auto lhs, const Matrix<3, 3, ValueType, TNXType::TNXBasic>& rhs) {
		return Matrix<3, 3, ValueType, TNXType::TNXBasic>(lhs + rhs.rows[0], lhs + rhs.rows[1], lhs + rhs.rows[2]);
	}

	template<typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator+(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const MatrixConvertibleTo<3, 3, ValueType> auto& rhs) {
		return Matrix<3, 3, ValueType, TNXType::TNXBasic>(lhs.rows[0] + rhs.rows[0], lhs.rows[1] + rhs.rows[1], lhs.rows[2] + rhs.rows[2]);
	}


	// operator -
	template<typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator-(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Matrix<3, 3, ValueType, TNXType::TNXBasic>(lhs.rows[0] - rhs, lhs.rows[1] - rhs, lhs.rows[2] - rhs);
	}

	template<typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator-(const std::convertible_to<ValueType> auto lhs, const Matrix<3, 3, ValueType, TNXType::TNXBasic>& rhs) {
		return Matrix<3, 3, ValueType, TNXType::TNXBasic>(lhs - rhs.rows[0], lhs - rhs.rows[1], lhs - rhs.rows[2]);
	}

	template<typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator-(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const MatrixConvertibleTo<3, 3, ValueType> auto& rhs) {
		return Matrix<3, 3, ValueType, TNXType::TNXBasic>(lhs.rows[0] - rhs.rows[0], lhs.rows[1] - rhs.rows[1], lhs.rows[2] - rhs.rows[2]);
	}


	// operator *
	// scalar
	template<typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator*(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Matrix<3, 3, ValueType, TNXType::TNXBasic>(lhs.rows[0] * rhs, lhs.rows[1] * rhs, lhs.rows[2] * rhs);
	}

	template<typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator*(const std::convertible_to<ValueType> auto lhs, const Matrix<3, 3, ValueType, TNXType::TNXBasic>& rhs) {
		return Matrix<3, 3, ValueType, TNXType::TNXBasic>(lhs * rhs.rows[0], lhs * rhs.rows[1], lhs * rhs.rows[2]);
	}


	// vec
	template<typename ValueType>
	inline constexpr typename Matrix<3, 3, ValueType, TNXType::TNXBasic>::ColumnType operator*(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return Matrix<3, 3, ValueType, TNXType::TNXBasic>::ColumnType(	lhs[0][0] * rhs.x + lhs[0][1] * rhs.y + lhs[0][2] * rhs.z,
																						lhs[1][0] * rhs.x + lhs[1][1] * rhs.y + lhs[1][2] * rhs.z,
																						lhs[2][0] * rhs.x + lhs[2][1] * rhs.y + lhs[2][2] * rhs.z);
	}
	
	template<typename ValueType>
	inline constexpr typename Matrix<3, 3, ValueType, TNXType::TNXBasic>::RowType operator*(const VectorConvertibleTo<2, ValueType> auto& lhs, const Matrix<3, 3, ValueType, TNXType::TNXBasic>& rhs) {
		return Matrix<3, 3, ValueType, TNXType::TNXBasic>::RowType(	rhs[0][0] * lhs.x + rhs[0][1] * lhs.y + rhs[0][2] * lhs.z,
																					rhs[1][0] * lhs.x + rhs[1][1] * lhs.y + rhs[1][2] * lhs.z,
																					rhs[2][0] * lhs.x + rhs[2][1] * lhs.y + rhs[2][2] * lhs.z);
	}
	
	// same
	template<typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator*(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const MatrixConvertibleTo<3, 3, ValueType> auto& rhs) {
		// accessing 3 times each -> cache

		const ValueType lhs00 = lhs[0][0];
		const ValueType lhs01 = lhs[0][1];
		const ValueType lhs02 = lhs[0][2];
		const ValueType lhs10 = lhs[1][0];
		const ValueType lhs11 = lhs[1][1];
		const ValueType lhs12 = lhs[1][2];
		const ValueType lhs20 = lhs[2][0];
		const ValueType lhs21 = lhs[2][1];
		const ValueType lhs22 = lhs[2][2];

		const ValueType rhs00 = rhs[0][0];
		const ValueType rhs01 = rhs[0][1];
		const ValueType rhs02 = rhs[0][2];
		const ValueType rhs10 = rhs[1][0];
		const ValueType rhs11 = rhs[1][1];
		const ValueType rhs12 = rhs[1][2];
		const ValueType rhs20 = rhs[2][0];
		const ValueType rhs21 = rhs[2][1];
		const ValueType rhs22 = rhs[2][2];

		return Matrix<3, 3, ValueType, TNXType::TNXBasic>{	lhs00 * rhs00 + lhs10 * rhs01 + lhs20 * rhs02,
																			lhs01 * rhs00 + lhs11 * rhs01 + lhs21 * rhs02,
																			lhs02 * rhs00 + lhs12 * rhs01 + lhs22 * rhs02,
																			lhs00 * rhs10 + lhs10 * rhs11 + lhs20 * rhs12,
																			lhs01 * rhs10 + lhs11 * rhs11 + lhs21 * rhs12,
																			lhs02 * rhs10 + lhs12 * rhs11 + lhs22 * rhs12,
																			lhs00 * rhs20 + lhs10 * rhs21 + lhs20 * rhs22,
																			lhs01 * rhs20 + lhs11 * rhs21 + lhs21 * rhs22,
																			lhs02 * rhs20 + lhs12 * rhs21 + lhs22 * rhs22 };
	}

	// others
	template<typename ValueType>
	inline constexpr Matrix<2, 3, ValueType, TNXType::TNXBasic> operator*(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const MatrixConvertibleTo<2, 3, ValueType> auto& rhs) {
		return Matrix<2, 3, ValueType, TNXType::TNXBasic>(	lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1] + lhs[2][0] * rhs[0][2],
																			lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1] + lhs[2][1] * rhs[0][2],
																			lhs[0][2] * rhs[0][0] + lhs[1][2] * rhs[0][1] + lhs[2][2] * rhs[0][2],
																			lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1] + lhs[2][0] * rhs[1][2],
																			lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1] + lhs[2][1] * rhs[1][2],
																			lhs[0][2] * rhs[1][0] + lhs[1][2] * rhs[1][1] + lhs[2][2] * rhs[1][2]);
	}
	
	template<typename ValueType>
	inline constexpr Matrix<4, 3, ValueType, TNXType::TNXBasic> operator*(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const MatrixConvertibleTo<4, 3, ValueType> auto& rhs) {
		// accessing more than 3 times each -> cache

		const ValueType lhs00 = lhs[0][0];
		const ValueType lhs01 = lhs[0][1];
		const ValueType lhs02 = lhs[0][2];
		const ValueType lhs10 = lhs[1][0];
		const ValueType lhs11 = lhs[1][1];
		const ValueType lhs12 = lhs[1][2];
		const ValueType lhs20 = lhs[2][0];
		const ValueType lhs21 = lhs[2][1];
		const ValueType lhs22 = lhs[2][2];

		const ValueType rhs00 = rhs[0][0];
		const ValueType rhs01 = rhs[0][1];
		const ValueType rhs02 = rhs[0][2];
		const ValueType rhs10 = rhs[1][0];
		const ValueType rhs11 = rhs[1][1];
		const ValueType rhs12 = rhs[1][2];
		const ValueType rhs20 = rhs[2][0];
		const ValueType rhs21 = rhs[2][1];
		const ValueType rhs22 = rhs[2][2];
		const ValueType rhs30 = rhs[3][0];
		const ValueType rhs31 = rhs[3][1];
		const ValueType rhs32 = rhs[3][2];

		return Matrix<4, 3, ValueType, TNXType::TNXBasic>(	lhs00 * rhs00 + lhs10 * rhs01 + lhs20 * rhs02,
																			lhs01 * rhs00 + lhs11 * rhs01 + lhs21 * rhs02,
																			lhs02 * rhs00 + lhs12 * rhs01 + lhs22 * rhs02,
																			lhs00 * rhs10 + lhs10 * rhs11 + lhs20 * rhs12,
																			lhs01 * rhs10 + lhs11 * rhs11 + lhs21 * rhs12,
																			lhs02 * rhs10 + lhs12 * rhs11 + lhs22 * rhs12,
																			lhs00 * rhs20 + lhs10 * rhs21 + lhs20 * rhs22,
																			lhs01 * rhs20 + lhs11 * rhs21 + lhs21 * rhs22,
																			lhs02 * rhs20 + lhs12 * rhs21 + lhs22 * rhs22,
																			lhs00 * rhs30 + lhs10 * rhs31 + lhs20 * rhs32,
																			lhs01 * rhs30 + lhs11 * rhs31 + lhs21 * rhs32,
																			lhs02 * rhs30 + lhs12 * rhs31 + lhs22 * rhs32);
	}




	// operator /
	// scalar
	template<typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator/(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs) {
		return Matrix<3, 3, ValueType, TNXType::TNXBasic>(lhs.rows[0] / rhs, lhs.rows[1] / rhs, lhs.rows[2] / rhs);
	}

	template<typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator/(const std::convertible_to<ValueType> auto lhs, const Matrix<3, 3, ValueType, TNXType::TNXBasic>& rhs) {
		return Matrix<3, 3, ValueType, TNXType::TNXBasic>(lhs / rhs.rows[0], lhs / rhs.rows[1], lhs / rhs.rows[2]);
	}

	// vec
	template<typename ValueType>
	inline constexpr typename Matrix<3, 3, ValueType, TNXType::TNXBasic>::ColumnType operator/(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs) {
		return lhs.Inverse() * rhs;
	}
	
	template<typename ValueType>
	inline constexpr typename Matrix<3, 3, ValueType, TNXType::TNXBasic>::RowType operator/(const VectorConvertibleTo<2, ValueType> auto& lhs, const Matrix<3, 3, ValueType, TNXType::TNXBasic>& rhs) {
		return lhs * rhs.Inverse();
	}

	// same
	template<typename ValueType>
	inline constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator/(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const MatrixConvertibleTo<3, 3, ValueType> auto& rhs) {
		return lhs * rhs.Inverse();
	}
}