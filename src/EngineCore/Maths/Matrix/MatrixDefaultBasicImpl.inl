#pragma once

#include "MatrixDefaultBasicImpl.h"

namespace EngineCore {

	//----------------------------------//
	//------------- Values -------------//
	//----------------------------------//

	template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename T>
	inline constexpr Matrix<COLUMNS_COUNT, ROWS_COUNT, T, EngineCompute::EngineComputeBasic>::Matrix() {

	}

	template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename T>
	inline constexpr Matrix<COLUMNS_COUNT, ROWS_COUNT, T, EngineCompute::EngineComputeBasic>::Matrix(const MatrixConvertibleTo<COLUMN_COUNT, ROW_COUNT, ValueType> auto& mat) {
		for
	}

	template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename T>
	inline constexpr Matrix<COLUMNS_COUNT, ROWS_COUNT, T, EngineCompute::EngineComputeBasic>::Matrix(const std::convertible_to<ValueType> auto scalar) {

	}

	template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename T>
	inline constexpr Matrix<COLUMNS_COUNT, ROWS_COUNT, T, EngineCompute::EngineComputeBasic>::Matrix(const AllValuesArrayType&& allValuesArr)
		: data{ allValuesArr } {}

	template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename T>
	inline constexpr Matrix<COLUMNS_COUNT, ROWS_COUNT, T, EngineCompute::EngineComputeBasic>::Matrix(const RowType&& rowsArr)
		: rows{ rowsArr } {}


	template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename T>
	inline constexpr typename Matrix<COLUMNS_COUNT, ROWS_COUNT, T, EngineCompute::EngineComputeBasic>::ColumnType Matrix<COLUMNS_COUNT, ROWS_COUNT, T, EngineCompute::EngineComputeBasic>::GetColumn(const std::size_t idx) const {
		typename Matrix<COLUMNS_COUNT, ROWS_COUNT, T, EngineCompute::EngineComputeBasic>::RowType res;
		std::generate(res.GetArray().begin(), res.GetArray().end(), [i = 0, idx, this]() mutable { auto res = this->data[idx + i * ROWS_COUNT]; ++i; return res; });
		return res;
	}

	template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename T>
	inline constexpr void Matrix<COLUMNS_COUNT, ROWS_COUNT, T, EngineCompute::EngineComputeBasic>::SetColumn(const std::size_t idx, const Matrix<COLUMNS_COUNT, ROWS_COUNT, T, EngineCompute::EngineComputeBasic>::ColumnType& col) {
		auto i = 0;
		for (T& i : col.GetArray()) {
			data[idx + i * ROWS_COUNT] = col.GetArray()[idx];
			++i;
		}
	}



	//--------------------------------------------//
	//------------- Base Constructor -------------//
	//--------------------------------------------//
	
	// Construct as identity
	template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename T>
	inline constexpr Matrix<COLUMNS_COUNT, ROWS_COUNT, T, EngineCompute::EngineComputeBasic>::Matrix() {
		std::generate(data.begin(), data.end(), [i = 0]() mutable {
			if (i % (COLUMNS_COUNT + 1) == 0)	{ ++i; return 1; }
			else								{ ++i; return 0; } });
	}

	template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename T>
	inline constexpr Matrix<COLUMNS_COUNT, ROWS_COUNT, T, EngineCompute::EngineComputeBasic>::Matrix(const Matrix<COLUMNS_COUNT, ROWS_COUNT, T, EngineCompute::EngineComputeBasic>& mat) = default;


	//--------------------------------------------------//
	//------------- Conversion Constructor -------------//
	//--------------------------------------------------//

	template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename T>
	template <typename K>
	inline constexpr Matrix<COLUMNS_COUNT, ROWS_COUNT, T, EngineCompute::EngineComputeBasic>::Matrix(const K scalar) {
		std::generate(data.begin(), data.end(), [i = 0, scalar = static_cast<T>(scalar)]() mutable {
			if (i % (COLUMNS_COUNT + 1) == 0)	{ ++i; return scalar; }
			else								{ ++i; return 0; } });
	}

}
