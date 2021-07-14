#pragma once

#include "../Matrix.h"

namespace EngineCore {

	//------------- Matrix2x2 -------------//
	template<typename T>
	struct Matrix<2, 2, T, EngineCompute::EngineComputeBasic>
	{
		//----------------------------------//
		//------------- Values -------------//
		//----------------------------------//

		using ValueType = T;
		using ColumnType = Vector<2, T>;
		using RowType = Vector<2, T>;

		union {
			ValueType	data[4];
			ColumnType	column[2];
		};

		static inline constexpr std::size_t GetNumberOfColumns()			{ return 2; }
		static inline constexpr std::size_t GetNumberOfRows()				{ return 2; }
		static inline constexpr std::size_t GetNumberOfElementsInAColumn()	{ return GetNumberOfRows(); }
		static inline constexpr std::size_t GetNumberOfElementsInARow()		{ return GetNumberOfColumns(); }

		inline constexpr ColumnType GetVectorOfColumn(std::size_t idx) const	{ return column[idx]; }
		inline constexpr RowType GetVectorOfRow(std::size_t idx) const			{ return RowType(data[idx], data[idx + 2]); }

		inline constexpr void SetVectorOfColumn(std::size_t idx, const ColumnType& col) { column[idx] = col; }
		inline constexpr void SetVectorOfRow(std::size_t idx, const RowType& row)		{ data[idx] = row.x; data[idx + 2] = row.y; }

		//--------------------------------------------//
		//------------- Base Constructor -------------//
		//--------------------------------------------//

		constexpr Matrix() : data{} {}
	};
}
