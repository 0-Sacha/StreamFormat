#pragma once

#include "MatrixDefaultBasicImpl.h"

namespace EngineCore::EngineCompute {

	//----------------------------------//
	//------------- Values -------------//
	//----------------------------------//

	template <std::size_t COLUMN_COUNT, std::size_t ROW_COUNT, typename Type>
	inline constexpr typename Matrix<COLUMN_COUNT, ROW_COUNT, Type, Detail::EngineComputeType::EngineComputeBasic>::ColumnType Matrix<COLUMN_COUNT, ROW_COUNT, Type, Detail::EngineComputeType::EngineComputeBasic>::GetColumn(const std::size_t idx) const {
		typename Matrix<COLUMN_COUNT, ROW_COUNT, Type, Detail::EngineComputeType::EngineComputeBasic>::RowType res;
		std::generate(res.GetArray().begin(), res.GetArray().end(), [i = 0, idx, this]() mutable { auto res = this->data[idx + i * ROW_COUNT]; ++i; return res; });
		return res;
	}

	template <std::size_t COLUMN_COUNT, std::size_t ROW_COUNT, typename Type>
	inline constexpr void Matrix<COLUMN_COUNT, ROW_COUNT, Type, Detail::EngineComputeType::EngineComputeBasic>::SetColumn(const std::size_t idx, const typename Matrix<COLUMN_COUNT, ROW_COUNT, Type, Detail::EngineComputeType::EngineComputeBasic>::ColumnType& col) {
		auto i = 0;
		for (Type& i : col.GetArray()) {
			data[idx + i * ROW_COUNT] = col.GetArray()[idx];
			++i;
		}
	}


	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//

	template <std::size_t COLUMN_COUNT, std::size_t ROW_COUNT, typename Type>
	inline constexpr Matrix<COLUMN_COUNT, ROW_COUNT, Type, Detail::EngineComputeType::EngineComputeBasic>::Matrix() {
		std::generate(data.begin(), data.end(), [i = 0]() mutable {
			if (i % (COLUMN_COUNT + 1) == 0)	{ ++i; return 1; }
			else								{ ++i; return 0; }
		});
	}
	
	template <std::size_t COLUMN_COUNT, std::size_t ROW_COUNT, typename Type>
	inline constexpr Matrix<COLUMN_COUNT, ROW_COUNT, Type, Detail::EngineComputeType::EngineComputeBasic>::Matrix(const std::convertible_to<ValueType> auto ... values)
		: data { static_cast<ValueType>(values)... } {}


	template <std::size_t COLUMN_COUNT, std::size_t ROW_COUNT, typename ValueType>
	inline constexpr Matrix<COLUMN_COUNT, ROW_COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Matrix(const MatrixConvertibleTo<COLUMN_COUNT, ROW_COUNT, ValueType> auto& mat) {
	}

	template <std::size_t COLUMN_COUNT, std::size_t ROW_COUNT, typename ValueType>
	inline constexpr Matrix<COLUMN_COUNT, ROW_COUNT, ValueType, Detail::EngineComputeType::EngineComputeBasic>::Matrix(const std::convertible_to<ValueType> auto scalar) {
		std::generate(data.begin(), data.end(), [i = 0, scalar = static_cast<ValueType>(scalar)]() mutable {
			if (i % (COLUMN_COUNT + 1) == 0) { ++i; return scalar; }
			else { ++i; return 0; } });
	}

	template <std::size_t COLUMN_COUNT, std::size_t ROW_COUNT, typename Type>
	inline constexpr Matrix<COLUMN_COUNT, ROW_COUNT, Type, Detail::EngineComputeType::EngineComputeBasic>::Matrix(const ValuesArrayType&& allValuesArr)
		: data{ allValuesArr } {}

	template <std::size_t COLUMN_COUNT, std::size_t ROW_COUNT, typename Type>
	inline constexpr Matrix<COLUMN_COUNT, ROW_COUNT, Type, Detail::EngineComputeType::EngineComputeBasic>::Matrix(const RowType&& rowsArr)
		: rows{ rowsArr } {}

}
