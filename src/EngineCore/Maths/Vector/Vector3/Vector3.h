#pragma once

#include "Vector3BasicImpl.h"
#include "Vector3BasicImpl.inl"

namespace EngineCore {

    template <typename Type, typename ComputeAlgorithm = EngineCompute::EngineComputeDefault>
    using Vector3 = Vector<3, Type, ComputeAlgorithm>;

    using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;
	using Vector3i = Vector3<int>;
	using Vector3u = Vector3<unsigned int>;

	using Vector3i8	    = Vector3<int8_t>;
	using Vector3u8	    = Vector3<uint8_t>;
	using Vector3i16	= Vector3<int16_t>;
	using Vector3u16	= Vector3<uint16_t>;
	using Vector3i32	= Vector3<int32_t>;
	using Vector3u32	= Vector3<uint32_t>;
	using Vector3i64	= Vector3<int64_t>;
	using Vector3u64	= Vector3<uint64_t>;

}
