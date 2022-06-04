#pragma once

#include "EngineCore/TNX/Maths/Vector/Vector.h"

namespace EngineCore::TNX {

	// Matrix are row-major order
	template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename Type, typename ComputeAlgorithm = TNXType::TNXDefault>
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

namespace EngineCore::TNX {

template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename Type, typename FormatContext>
struct EngineCore::FMT::FormatType<EngineCore::TNX::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::TNX::TNXBasic>, FormatContext>
{
	static void Write(const EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::TNX::TNXBasic>& mat, FormatContext& context) {
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
struct EngineCore::FMT::UnFormatType<EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::TNX::TNXBasic>, UnFormatContext>
{
	static void Read(const EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::TNX::TNXBasic>& mat, UnFormatContext& context) {
		context.BufferOut().IsEqualForwardThrow('{');
		bool first = true;
		for (auto i = 0; i < mat.GetNumberOfRows(); ++i) {
			if (first)	first = false;
			else		{ context.BufferOut().PushBack(','); context.BufferOut().PushBack(' '); }

			typename EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::TNX::TNXBasic>::RowType row;
			context.ReadType(row);
			mat.SetRow(row);
		}
		context.BufferOut().IsEqualForwardThrow('}');
	}
};










