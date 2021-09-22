#pragma once

#include "Matrix2x2BasicImpl.h"
#include "Matrix2x2BasicImpl.inl"

namespace EngineCore {

    template <typename Type, typename ComputeAlgorithm = EngineCompute::EngineComputeDefault>
    using Matrix2x2 = Matrix<2, 2, Type, ComputeAlgorithm>;

    using Matrix2x2f = Matrix2x2<float>;
	using Matrix2x2d = Matrix2x2<double>;
	using Matrix2x2i = Matrix2x2<int>;
	using Matrix2x2u = Matrix2x2<unsigned int>;

	using Matrix2x2i8	= Matrix2x2<int8_t>;
	using Matrix2x2u8	= Matrix2x2<uint8_t>;
	using Matrix2x2i16	= Matrix2x2<int16_t>;
	using Matrix2x2u16	= Matrix2x2<uint16_t>;
	using Matrix2x2i32	= Matrix2x2<int32_t>;
	using Matrix2x2u32	= Matrix2x2<uint32_t>;
	using Matrix2x2i64	= Matrix2x2<int64_t>;
	using Matrix2x2u64	= Matrix2x2<uint64_t>;

}
