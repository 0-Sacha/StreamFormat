#pragma once

#include "Matrix.h"

namespace EngineCore {

	template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename T>
	struct Matrix<COLUMNS_COUNT, ROWS_COUNT, T, EngineCompute::EngineComputeBasic> {

		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		using ValueType		= T;
		using ColumnType	= Vector<ROWS_COUNT, T>;
		using RowType		= Vector<COLUMNS_COUNT, T>;

		union {
			std::array<ValueType, COLUMNS_COUNT * ROWS_COUNT>	data;
			std::array<RowType, ROWS_COUNT>						rows;
		};

		static inline constexpr std::size_t GetNumberOfColumns()			{ return COLUMNS_COUNT; }
		static inline constexpr std::size_t GetNumberOfRows()				{ return ROWS_COUNT; }
		static inline constexpr std::size_t GetNumberOfElementsInAColumn()	{ return GetNumberOfRows(); }
		static inline constexpr std::size_t GetNumberOfElementsInARow()		{ return GetNumberOfColumns(); }

		inline constexpr std::array<ValueType, COLUMNS_COUNT* ROWS_COUNT>& GetArray()				{ return data; }
		inline constexpr const std::array<ValueType, COLUMNS_COUNT* ROWS_COUNT>& GetArray() const	{ return data; }
		inline constexpr std::array<RowType, ROWS_COUNT>& GetRowsArray()							{ return rows; }
		inline constexpr const std::array<RowType, ROWS_COUNT>& GetRowsArray() const				{ return rows; }

		constexpr RowType GetRow(const std::size_t idx) const							{ return rows[idx]; }
		constexpr void SetRow(const std::size_t idx, const RowType& row)			 	{ rows[idx] = row; }

		inline constexpr ColumnType GetColumn(const std::size_t idx) const;
		inline constexpr void SetColumn(const std::size_t idx, const ColumnType& col);


		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//

		// Construct as identity
		constexpr Matrix();
		constexpr Matrix(const Matrix<COLUMNS_COUNT, ROWS_COUNT, T, EngineCompute::EngineComputeBasic>& mat);


		//--------------------------------------------------//
		//------------- Conversion Constructor -------------//
		//--------------------------------------------------//

		template <typename K> constexpr Matrix(const K scalar);

	};

}