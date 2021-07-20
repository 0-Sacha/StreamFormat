#pragma once

#include "../Matrix.h"
#include <array>


namespace EngineCore {

	//------------- Matrix2x2 -------------//
	template <typename Type>
	struct Matrix<2, 2, Type, EngineCompute::EngineComputeBasic>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//
		
		using ValueType = Type;
		using ColumnType	= Vector<2, ValueType, EngineCompute::EngineComputeBasic>;
		using RowType		= Vector<2, ValueType, EngineCompute::EngineComputeBasic>;

		template <typename T, typename ComputeAlgorithm> using ColumnTypeLike	= Vector<2, T, ComputeAlgorithm>;
		template <typename T, typename ComputeAlgorithm> using RowTypeLike		= Vector<2, T, ComputeAlgorithm>;

		union {
			std::array<ValueType, 4>	data;
			std::array<RowType, 2>		rows;
		};

		static inline constexpr bool MatrixIsRowMajorOrder()				{ return true; }

		static inline constexpr std::size_t GetNumberOfColumns()			{ return 2; }
		static inline constexpr std::size_t GetNumberOfRows()				{ return 2; }
		static inline constexpr std::size_t GetNumberOfElementsInAColumn()	{ return GetNumberOfRows(); }
		static inline constexpr std::size_t GetNumberOfElementsInARow()		{ return GetNumberOfColumns(); }
		static inline constexpr std::size_t GetMaxNumberOfElements()		{ return GetNumberOfColumns() * GetNumberOfRows(); }

		inline constexpr std::array<ValueType, 4>& GetArray()					{ return data; }
		inline constexpr const std::array<ValueType, 4>&	GetArray() const	{ return data; }
		inline constexpr std::array<RowType, 2>&	GetRowsArray()				{ return rows; }
		inline constexpr const std::array<RowType, 2>& GetRowsArray() const		{ return rows; }

		inline constexpr RowType& operator[](const std::size_t idx)				{ ENGINE_CORE_ASSERT(idx < GetMaxNumberOfElements()); return data[idx]; }
		inline constexpr const RowType& operator[](const std::size_t idx) const { ENGINE_CORE_ASSERT(idx < GetMaxNumberOfElements()); return data[idx]; }

		inline constexpr RowType GetRow(const std::size_t idx) const			{ return rows[idx]; }
		inline constexpr void SetRow(const std::size_t idx, const RowType& row)	{ rows[idx] = row; }

		inline constexpr ColumnType GetColumn(const std::size_t idx) const				{ return ColumnType(data[idx], data[idx + 2]); }
		inline constexpr void SetColumn(const std::size_t idx, const ColumnType& col)	{ data[idx] = col.x; data[idx + 2] = col.y; }

		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//

		// Construct as identity
		constexpr Matrix();
		constexpr Matrix(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& mat);
/*
		// Construct as multiple of the identity matrix
		constexpr Matrix(const ValueType scalar);
		// Initialization with row-major order
		constexpr Matrix(	const ValueType x0, const ValueType y0,
							const ValueType x1, const ValueType y1);
		constexpr Matrix(const RowType&& row0, const RowType&& row1);



		//--------------------------------------------------//
		//------------- Conversion Constructor -------------//
		//--------------------------------------------------//

		template <typename K, typename ComputeAlgoritmClient> constexpr Matrix(const Matrix <2, 2, K, ComputeAlgoritmClient>& mat);

		template <typename K> constexpr Matrix(const K scalar);
		constexpr Matrix(const RowTypeLike auto&& row0, const ColumnTypeLike auto&& row1);
		template <typename X0, typename Y0, typename X1, typename Y1> constexpr Matrix(	const X0 x0, const Y0 y0,
																						const X1 x1, const Y1 y1);

		//------------------------------------------------//
		//------------- Main Matrix Function -------------//
		//------------------------------------------------//
	
		// Not sure for the name
		template <typename K, typename ComputeAlgoritmClient> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& ComputeMultAsAddInPlace(const Matrix<2, 2, K, ComputeAlgoritmClient>& mat);
		// Not sure for the name
		template <typename K, typename ComputeAlgoritmClient> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>  ComputeMultAsAdd(const Matrix<2, 2, K, ComputeAlgoritmClient>& mat);

		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> Transpose();

		constexpr T Determinant();

		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> Inverse();


		template <typename K1, typename ComputeAlgoritmClient1, typename K2, typename ComputeAlgoritmClient2>
		static constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> FromOuterProduct(const RowTypeLike<K1, ComputeAlgoritmClient1>&& row0, const ColumnTypeLike<K2, ComputeAlgoritmClient2>&& row1);
		
		//-----------------------------------------------//
		//------------- Conversion Operator -------------//
		//-----------------------------------------------//

		//----------------------------------------------//
		//------------- Condition Operator -------------//
		//----------------------------------------------//

		template <typename K, typename ComputeAlgoritmClient> constexpr bool operator==(const Matrix<2, 2, K, ComputeAlgoritmClient>& rhs);
		template <typename K, typename ComputeAlgoritmClient> constexpr bool operator!=(const Matrix<2, 2, K, ComputeAlgoritmClient>& rhs);


		//------------------------------------//
		//------------- Operator -------------//
		//------------------------------------//

		// operator +I
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>  operator+();
		// operator -I
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>  operator-();

		// operator ++I
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator++();
		// operator --I
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator--();
		// operator I++
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>  operator++(int);
		// operator I--
		constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>  operator--(int);


		// operator =
		template <typename K> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator=(const K scalar);
		template <typename K, typename ComputeAlgoritmClient> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator=(const Matrix<2, 2, K, ComputeAlgoritmClient>& mat);

		// operator +=
		template <typename K> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator+=(const K scalar);
		template <typename K, typename ComputeAlgoritmClient> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator+=(const Matrix<2, 2, K, ComputeAlgoritmClient>& mat);

		// operator -=
		template <typename K> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator-=(const K scalar);
		template <typename K, typename ComputeAlgoritmClient> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator-=(const Matrix<2, 2, K, ComputeAlgoritmClient>& mat);

		// operator *=
		template <typename K> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator*=(const K scalar);
		template <typename K, typename ComputeAlgoritmClient> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator*=(const Matrix<2, 2, K, ComputeAlgoritmClient>& mat);

		// operator /=
		template <typename K> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator/=(const K scalar);
		template <typename K, typename ComputeAlgoritmClient> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& operator/=(const Matrix<2, 2, K, ComputeAlgoritmClient>& mat);
		*/
	};

	// -----------------------------------//
	//------------- Operator -------------//
	//------------------------------------//
/*
	// operator +
	template <typename ValueType, typename K> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator+(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const K rhs);
	template <typename ValueType, typename K> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator+(const K lhs, const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType, typename K, typename ComputeAlgoritmClient> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator+(const Matrix<2, 2, K, EngineCompute::EngineComputeBasic>& lhs, const Matrix<2, 2, K, ComputeAlgoritmClient>& rhs);

	// operator -
	template <typename ValueType, typename K> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator-(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const K rhs);
	template <typename ValueType, typename K> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator-(const K lhs, const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& rhs);
	template <typename ValueType, typename K, typename ComputeAlgoritmClient> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator-(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const Matrix<2, 2, K, ComputeAlgoritmClient>& rhs);
	*/
	// operator *
	template <typename ValueType, typename K>
	constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator*(	const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs,
																					const K rhs) requires std::is_convertible_v<K, ValueType> {
		ENGINE_CORE_INFO("mat * cte");
		return Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>();
	}

	template <typename ValueType, typename K>
	constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator*(	const K lhs,
																					const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& rhs) requires std::is_convertible_v<K, ValueType> {
		ENGINE_CORE_INFO("cte * mat");
		return Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>();
	}

	template <typename ValueType, typename K, typename ComputeAlgoritmOther>
	constexpr typename Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>::ColumnType operator*(	const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs,
																								const Vector<2, K, ComputeAlgoritmOther>& rhs) requires std::is_convertible_v<K, ValueType> {
		ENGINE_CORE_INFO("mat * vec");
		return typename Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>::ColumnType();
	}

	template <typename ValueType, typename K, typename ComputeAlgoritmOther>
	constexpr typename Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>::RowType operator*(const Vector<2, K, ComputeAlgoritmOther>& lhs,
																							const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& rhs) requires std::is_convertible_v<K, ValueType> {
		ENGINE_CORE_INFO("vec * mat");
		return typename Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>::RowType();
	}

	template <typename ValueType, typename K, typename ComputeAlgoritmClient>
	constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator*(	const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs,
																					const Matrix<2, 2, K, ComputeAlgoritmClient>& rhs) requires std::is_convertible_v<K, ValueType> {
		ENGINE_CORE_INFO("mat * mat");
		return Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>();
	}

	/*
	template <typename ValueType, typename K, typename ComputeAlgoritmClient> constexpr Matrix<3, 2, T, EngineCompute::EngineComputeBasic> operator*(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const Matrix<3, 2, K, ComputeAlgoritmClient>& rhs);
	template <typename ValueType, typename K, typename ComputeAlgoritmClient> constexpr Matrix<4, 2, T, EngineCompute::EngineComputeBasic> operator*(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const Matrix<4, 2, K, ComputeAlgoritmClient>& rhs);


	// operator /
	template <typename ValueType, typename K> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator/(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const K rhs);
	template <typename ValueType, typename K> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator/(const K lhs, const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& rhs);

	template <typename ValueType, typename K, typename ComputeAlgoritmClient> constexpr typename Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>::ColumnType operator/(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>::RowTypeLike<T, ComputeAlgoritmClient>& rhs);
	template <typename ValueType, typename K, typename ComputeAlgoritmClient> constexpr typename Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>::RowType operator/(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>::ColumnTypeLike<T, ComputeAlgoritmClient>& lhs, const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& rhs);

	template <typename ValueType, typename K, typename ComputeAlgoritmClient> constexpr Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic> operator/(const Matrix<2, 2, ValueType, EngineCompute::EngineComputeBasic>& lhs, const Matrix<2, 2, K, ComputeAlgoritmClient>& rhs);
	*/
}