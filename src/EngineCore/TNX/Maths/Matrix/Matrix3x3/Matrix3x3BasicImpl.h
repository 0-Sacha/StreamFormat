#pragma once

#include "../Matrix.h"


namespace EngineCore::TNX {

	//------------- Matrix2x2 -------------//
	template <typename Type>
	struct Matrix<3, 3, Type, TNXType::TNXBasic>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		static constexpr std::size_t COLUMN_COUNT	= 3;
		static constexpr std::size_t ROW_COUNT		= 3;
		using ValueType			= Type;
		using ComputeAlgorithm	= TNXType::TNXBasic;

		using M_Type			= Matrix<COLUMN_COUNT, ROW_COUNT, ValueType, ComputeAlgorithm>;

		using ColumnType		= Vector<ROW_COUNT, ValueType, ComputeAlgorithm>;
		using RowType			= Vector<COLUMN_COUNT, ValueType, ComputeAlgorithm>;

		using ValuesArrayType	= std::array<ValueType, ROW_COUNT* COLUMN_COUNT>;
		using RowArrayType		= std::array<RowType, COLUMN_COUNT>;

		union {
			ValuesArrayType	data;
			RowArrayType	rows;
		};

		static inline constexpr std::size_t GetNumberOfColumns()			{ return COLUMN_COUNT; }
		static inline constexpr std::size_t GetNumberOfRows()				{ return ROW_COUNT; }
		static inline constexpr std::size_t GetNumberOfElementsInAColumn()	{ return GetNumberOfRows(); }
		static inline constexpr std::size_t GetNumberOfElementsInARow()		{ return GetNumberOfColumns(); }
		static inline constexpr std::size_t GetMaxNumberOfElements()		{ return GetNumberOfColumns() * GetNumberOfRows(); }

		inline constexpr ValuesArrayType&			GetArray()				{ return data; }
		inline constexpr const ValuesArrayType&		GetArray() const		{ return data; }
		inline constexpr RowArrayType&				GetRowsArray()			{ return rows; }
		inline constexpr const RowArrayType&		GetRowsArray() const	{ return rows; }

		inline constexpr RowType& operator[](const std::size_t idx)				{ ENGINECORE_ASSERT(idx < GetMaxNumberOfElements()); return rows[idx]; }
		inline constexpr const RowType& operator[](const std::size_t idx) const	{ ENGINECORE_ASSERT(idx < GetMaxNumberOfElements()); return rows[idx]; }

		inline constexpr RowType GetRow(const std::size_t idx) const				{ return rows[idx]; }
		inline constexpr void SetRow(const std::size_t idx, const RowType& row)	{ rows[idx] = row; }

		inline constexpr ColumnType GetColumn(const std::size_t idx) const				{ return ColumnType(data[idx], data[idx + 2]); }
		inline constexpr void SetColumn(const std::size_t idx, const ColumnType& col)	{ data[idx] = col.x; data[idx + 2] = col.y; }

		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//

		// Construct as identity
		constexpr Matrix();

		// Copy Matrix
		constexpr Matrix(const MatrixConvertibleTo<3, 3, ValueType> auto& mat);
	
		// Construct as multiple of the identity matrix
		constexpr Matrix(const std::convertible_to<ValueType> auto scalar);
		
		// Initialization with row-major order
		constexpr Matrix(	const std::convertible_to<ValueType> auto x0, const std::convertible_to<ValueType> auto y0, const std::convertible_to<ValueType> auto z0,
							const std::convertible_to<ValueType> auto x1, const std::convertible_to<ValueType> auto y1, const std::convertible_to<ValueType> auto z1,
							const std::convertible_to<ValueType> auto x2, const std::convertible_to<ValueType> auto y2, const std::convertible_to<ValueType> auto z2);
		
		// Initialization with row-major order
		constexpr Matrix(const ValuesArrayType&& allValuesArr);

		// Initialize all rows
		constexpr Matrix(const VectorConvertibleTo<3, ValueType> auto&& row0, const VectorConvertibleTo<3, ValueType> auto&& row1);

		// Initialize all rows
		constexpr Matrix(const RowType&& rowsArr);

		//--------------------------------------------------//
		//------------- Conversion Constructor -------------//
		//--------------------------------------------------//


		//------------------------------------------------//
		//------------- Main Matrix Function -------------//
		//------------------------------------------------//
		// 
		// Not sure for the name
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& ComputeMultAsAddInPlace(const MatrixConvertibleTo<3, 3, ValueType> auto& mat);
		// Not sure for the name
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>  ComputeMultAsAdd(const MatrixConvertibleTo<3, 3, ValueType> auto& mat);

		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> Transpose();

		constexpr ValueType Determinant();

		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> Inverse();

		// Row, column
		static constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> FromOuterProduct(const VectorConvertibleTo<3, ValueType> auto&& row0, const VectorConvertibleTo<3, ValueType> auto&& row1);
		
		//-----------------------------------------------//
		//------------- Conversion Operator -------------//
		//-----------------------------------------------//

		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		constexpr bool operator==(const MatrixConvertibleTo<3, 3, ValueType> auto& rhs);
		constexpr bool operator!=(const MatrixConvertibleTo<3, 3, ValueType> auto& rhs);

		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>  operator+();
		// operator -I
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>  operator-();

		// operator ++I
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& operator++();
		// operator --I
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& operator--();
		// operator I++
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>  operator++(int);
		// operator I--
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>  operator--(int);


		// operator =
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& operator=(const std::convertible_to<ValueType> auto scalar);
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& operator=(const MatrixConvertibleTo<3, 3, ValueType> auto& mat);

		// operator +=
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& operator+=(const std::convertible_to<ValueType> auto scalar);
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& operator+=(const MatrixConvertibleTo<3, 3, ValueType> auto& mat);

		// operator -=
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& operator-=(const std::convertible_to<ValueType> auto scalar);
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& operator-=(const MatrixConvertibleTo<3, 3, ValueType> auto& mat);

		// operator *=
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& operator*=(const std::convertible_to<ValueType> auto scalar);
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& operator*=(const MatrixConvertibleTo<3, 3, ValueType> auto& mat);

		// operator /=
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& operator/=(const std::convertible_to<ValueType> auto scalar);
		constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic>& operator/=(const MatrixConvertibleTo<3, 3, ValueType> auto& mat);
	};

	// -----------------------------------//
	//------------- Operator -------------//
	//------------------------------------//

	// operator +
	template<typename ValueType> constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator+(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template<typename ValueType> constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator+(const std::convertible_to<ValueType> auto lhs, const Matrix<3, 3, ValueType, TNXType::TNXBasic>& rhs);
	template<typename ValueType> constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator+(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const MatrixConvertibleTo<2, 2, ValueType> auto& rhs);

	// operator -
	template<typename ValueType> constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator-(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template<typename ValueType> constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator-(const std::convertible_to<ValueType> auto lhs, const Matrix<3, 3, ValueType, TNXType::TNXBasic>& rhs);
	template<typename ValueType> constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator-(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const MatrixConvertibleTo<2, 2, ValueType> auto& rhs);
	
	// operator *
	template<typename ValueType> constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator*(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template<typename ValueType> constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator*(const std::convertible_to<ValueType> auto lhs, const Matrix<3, 3, ValueType, TNXType::TNXBasic>& rhs);
	// row in input
	template<typename ValueType> constexpr typename Matrix<3, 3, ValueType, TNXType::TNXBasic>::ColumnType operator*(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs);
	// column in input
	template<typename ValueType> constexpr typename Matrix<3, 3, ValueType, TNXType::TNXBasic>::RowType operator*(const VectorConvertibleTo<2, ValueType> auto& lhs, const Matrix<3, 3, ValueType, TNXType::TNXBasic>& rhs);
	// same
	template<typename ValueType> constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator*(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const MatrixConvertibleTo<3, 3, ValueType> auto& rhs);
	// other
	template<typename ValueType> constexpr Matrix<2, 3, ValueType, TNXType::TNXBasic> operator*(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const MatrixConvertibleTo<2, 3, ValueType> auto& rhs);
	template<typename ValueType> constexpr Matrix<4, 3, ValueType, TNXType::TNXBasic> operator*(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const MatrixConvertibleTo<4, 3, ValueType> auto& rhs);


	// operator /
	template<typename ValueType> constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator/(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const std::convertible_to<ValueType> auto rhs);
	template<typename ValueType> constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator/(const std::convertible_to<ValueType> auto lhs, const Matrix<3, 3, ValueType, TNXType::TNXBasic>& rhs);
	// row in input
	template<typename ValueType> constexpr typename Matrix<3, 3, ValueType, TNXType::TNXBasic>::ColumnType operator/(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const VectorConvertibleTo<2, ValueType> auto& rhs);
	// column in input
	template<typename ValueType> constexpr typename Matrix<3, 3, ValueType, TNXType::TNXBasic>::RowType operator/(const VectorConvertibleTo<2, ValueType> auto& lhs, const Matrix<3, 3, ValueType, TNXType::TNXBasic>& rhs);
	// same
	template<typename ValueType> constexpr Matrix<3, 3, ValueType, TNXType::TNXBasic> operator/(const Matrix<3, 3, ValueType, TNXType::TNXBasic>& lhs, const MatrixConvertibleTo<3, 3, ValueType> auto& rhs);
}