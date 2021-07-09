#pragma once

#include "BasicVector3.h"
#include "BasicVector3.inl"

namespace EngineCore {

	template <typename Type>
	using BasicVector3 = BasicVector<3, Type>;

	using BasicVector3f = BasicVector3<float>;
	using BasicVector3d = BasicVector3<double>;
	using BasicVector3i = BasicVector3<int>;
	using BasicVector3u = BasicVector3<unsigned int>;

	using BasicVector3i8	= BasicVector3<int8_t>;
	using BasicVector3u8	= BasicVector3<uint8_t>;
	using BasicVector3i16	= BasicVector3<int16_t>;
	using BasicVector3u16	= BasicVector3<uint16_t>;
	using BasicVector3i32	= BasicVector3<int32_t>;
	using BasicVector3u32	= BasicVector3<uint32_t>;
	using BasicVector3i64	= BasicVector3<int64_t>;
	using BasicVector3u64	= BasicVector3<uint64_t>;


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
