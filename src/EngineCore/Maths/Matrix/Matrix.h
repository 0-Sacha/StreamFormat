#pragma once

#include "EngineCore/Maths/Core/Core.h"
#include "EngineCore/Maths/Vector/Vector.h"

namespace EngineCore {

	// Column major order

	template <std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename Type, typename ComputeAlgorithm = EngineCompute::EngineComputeDefault>
	struct Matrix;

}




template<std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename Type, typename FormatContext>
struct CPPTools::Fmt::FormatType<EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>, FormatContext>
{
	static void Write(const EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>& mat, FormatContext& context) {
		context.BufferPushBack('{');

		std::size_t stride = context.GetStride();

		bool first = true;
		for (auto i = 0; i < ROWS_COUNT; ++i) {
			if (first)  first = false;
			else		{ context.BufferPushBack('\n'); context.BufferAddSpaces(stride); }
			context.WriteType(mat.GetVectorOfRow(i));
		}

		context.BufferPushBack('}');
	}
};

template<std::size_t COLUMNS_COUNT, std::size_t ROWS_COUNT, typename Type, typename UnFormatContext>
struct CPPTools::Fmt::UnFormatType<EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>, UnFormatContext>
{
	static bool Read(const EngineCore::Matrix<COLUMNS_COUNT, ROWS_COUNT, Type, EngineCore::EngineCompute::EngineComputeBasic>& vec, UnFormatContext& context) {
		if (!context.BufferIsEqualForward('{')) return false;
		bool first = true;
		for (auto i = 0; i < ROWS_COUNT; ++i) {
			if (first)	first = false;
			else		{ context.BufferPushBack(','); context.BufferPushBack(' '); }
			context.ReadType(mat.GetVectorOfRow(i));
		}
		if (!context.BufferIsEqualForward('}')) return false;
	}
};










