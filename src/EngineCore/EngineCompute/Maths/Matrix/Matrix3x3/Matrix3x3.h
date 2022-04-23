#pragma once

#include "Matrix3x3BasicImpl.h"
#include "Matrix3x3BasicImpl.inl"

namespace EngineCore::EngineCompute {

    template <typename Type, typename ComputeAlgorithm = EngineCompute::EngineComputeDefault>
    using Matrix3x3 = Matrix<3, 3, Type, ComputeAlgorithm>;

    using Matrix3x3f = Matrix3x3<float>;
	using Matrix3x3d = Matrix3x3<double>;
	using Matrix3x3i = Matrix3x3<int>;
	using Matrix3x3u = Matrix3x3<unsigned int>;

	using Matrix3x3i8	= Matrix3x3<int8_t>;
	using Matrix3x3u8	= Matrix3x3<uint8_t>;
	using Matrix3x3i16	= Matrix3x3<int16_t>;
	using Matrix3x3u16	= Matrix3x3<uint16_t>;
	using Matrix3x3i32	= Matrix3x3<int32_t>;
	using Matrix3x3u32	= Matrix3x3<uint32_t>;
	using Matrix3x3i64	= Matrix3x3<int64_t>;
	using Matrix3x3u64	= Matrix3x3<uint64_t>;

}
