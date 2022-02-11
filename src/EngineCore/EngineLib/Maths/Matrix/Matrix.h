#pragma once

#include "EngineCore/EngineLib/Maths/Vector/Vector.h"

namespace EngineCore {

	// Matrix are row-major order
	template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename Type, typename ComputeAlgorithm = EngineCompute::EngineComputeDefault>
	struct Matrix;

	template <typename From, std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename T>
	concept MatrixConvertibleTo = requires(From to) {
		requires From::GetNumberOfColumns() == COLUMNS_COUNT;
		requires From::GetNumberOfRows()	== ROWS_COUNT;
		requires std::is_convertible_v<typename From::ValueType, T>;
	};

	template <typename From, typename MatType>
	concept MatrixConvertibleToM = requires(From to) {
		requires From::GetNumberOfColumns() == MatType::GetNumberOfColumns();
		requires From::GetNumberOfRows()	== MatType::GetNumberOfRows();
		requires std::is_convertible_v<typename From::ValueType, typename MatType::ValueType>;
	};
}



template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename Type, typename FormatContext>
struct EngineCore::Fmt::FormatType<EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>, FormatContext>
{
	static void Write(const EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>& mat, FormatContext& context) {
		context.BufferOut().PushBack('{');

		std::size_t stride = context.GetStride();

		bool first = true;
		for (auto i = 0; i < mat.GetNumberOfRows(); ++i) {
			if (first)  first = false;
			else		{ context.BufferOut().PushBack('\n'); context.BufferOut().AddSpaces(stride); }
			context.WriteType(mat.GetRow(i));
		}

		context.BufferOut().PushBack('}');
	}
};

template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename Type, typename UnFormatContext>
struct EngineCore::Fmt::UnFormatType<EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>, UnFormatContext>
{
	static bool Read(const EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>& mat, UnFormatContext& context) {
		if (!context.BufferOut().IsEqualForward('{')) return false;
		bool first = true;
		for (auto i = 0; i < mat.GetNumberOfRows(); ++i) {
			if (first)	first = false;
			else		{ context.BufferOut().PushBack(','); context.BufferOut().PushBack(' '); }

			typename EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>::RowType row;
			context.ReadType(row);
			mat.SetRow(row);
		}
		if (!context.BufferOut().IsEqualForward('}')) return false;
	}
};










