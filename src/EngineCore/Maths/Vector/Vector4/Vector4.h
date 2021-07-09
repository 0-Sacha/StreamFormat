#pragma once

#include "BasicVector4.h"
#include "BasicVector4.inl"

namespace EngineCore {

	template <typename Type>
	using BasicVector4 = BasicVector<4, Type>;

	using BasicVector4f = BasicVector4<float>;
	using BasicVector4d = BasicVector4<double>;
	using BasicVector4i = BasicVector4<int>;
	using BasicVector4u = BasicVector4<unsigned int>;

	using BasicVector4i8	= BasicVector4<int8_t>;
	using BasicVector4u8	= BasicVector4<uint8_t>;
	using BasicVector4i16	= BasicVector4<int16_t>;
	using BasicVector4u16	= BasicVector4<uint16_t>;
	using BasicVector4i32	= BasicVector4<int32_t>;
	using BasicVector4u32	= BasicVector4<uint32_t>;
	using BasicVector4i64	= BasicVector4<int64_t>;
	using BasicVector4u64	= BasicVector4<uint64_t>;


    template <typename Type, typename ComputeAlgorithm = EngineCompute::EngineComputeDefault>
    using Vector4 = Vector<4, Type, ComputeAlgorithm>;

    using Vector4f = Vector4<float>;
	using Vector4d = Vector4<double>;
	using Vector4i = Vector4<int>;
	using Vector4u = Vector4<unsigned int>;

	using Vector4i8	    = Vector4<int8_t>;
	using Vector4u8	    = Vector4<uint8_t>;
	using Vector4i16	= Vector4<int16_t>;
	using Vector4u16	= Vector4<uint16_t>;
	using Vector4i32	= Vector4<int32_t>;
	using Vector4u32	= Vector4<uint32_t>;
	using Vector4i64	= Vector4<int64_t>;
	using Vector4u64	= Vector4<uint64_t>;

}
