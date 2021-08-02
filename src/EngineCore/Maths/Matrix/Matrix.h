#pragma once

#include "EngineCore/Maths/Vector/Vector.h"

namespace EngineCore {

	// Matrix are row-major order
	template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename Type, typename ComputeAlgorithm = EngineCompute::EngineComputeDefault>
	struct Matrix;

	template <typename From, std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename T>
	concept MatrixConvertibleTo = requires(From to) {
		requires From::GetNumberOfColumns() == COLUMNS_COUNT;
		requires From::GetNumberOfRows() == ROWS_COUNT;
		requires std::is_convertible_v<typename From::ValueType, T>;
	};
}



template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename Type, typename FormatContext>
struct CPPTools::Fmt::FormatType<EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>, FormatContext>
{
	static void Write(const EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>& mat, FormatContext& context) {
		context.BufferPushBack('{');

		std::size_t stride = context.GetStride();

		bool first = true;
		for (auto i = 0; i < mat.GetNumberOfRows(); ++i) {
			if (first)  first = false;
			else		{ context.BufferPushBack('\n'); context.BufferAddSpaces(stride); }
			context.WriteType(mat.GetRow(i));
		}

		context.BufferPushBack('}');
	}
};

template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename Type, typename UnFormatContext>
struct CPPTools::Fmt::UnFormatType<EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>, UnFormatContext>
{
	static bool Read(const EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>& mat, UnFormatContext& context) {
		if (!context.BufferIsEqualForward('{')) return false;
		bool first = true;
		for (auto i = 0; i < mat.GetNumberOfRows(); ++i) {
			if (first)	first = false;
			else		{ context.BufferPushBack(','); context.BufferPushBack(' '); }

			typename EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>::RowType row;
			context.ReadType(row);
			mat.SetRow(row);
		}
		if (!context.BufferIsEqualForward('}')) return false;
	}
};










