#pragma once

#include "BasicVector1.h"
#include "BasicVector1.inl"

namespace EngineCore {

	template <typename Type>
	using BasicVector1 = BasicVector<1, Type>;

	using BasicVector1f = BasicVector1<float>;
	using BasicVector1d = BasicVector1<double>;
	using BasicVector1i = BasicVector1<int>;
	using BasicVector1u = BasicVector1<unsigned int>;

	using BasicVector1i8	= BasicVector1<int8_t>;
	using BasicVector1u8	= BasicVector1<uint8_t>;
	using BasicVector1i16	= BasicVector1<int16_t>;
	using BasicVector1u16	= BasicVector1<uint16_t>;
	using BasicVector1i32	= BasicVector1<int32_t>;
	using BasicVector1u32	= BasicVector1<uint32_t>;
	using BasicVector1i64	= BasicVector1<int64_t>;
	using BasicVector1u64	= BasicVector1<uint64_t>;



    template <typename Type, typename ComputeAlgorithm = EngineCompute::EngineComputeDefault>
    using Vector1 = Vector<1, Type, ComputeAlgorithm>;

    using Vector1f = Vector1<float>;
	using Vector1d = Vector1<double>;
	using Vector1i = Vector1<int>;
	using Vector1u = Vector1<unsigned int>;

	using Vector1i8	    = Vector1<int8_t>;
	using Vector1u8	    = Vector1<uint8_t>;
	using Vector1i16	= Vector1<int16_t>;
	using Vector1u16	= Vector1<uint16_t>;
	using Vector1i32	= Vector1<int32_t>;
	using Vector1u32	= Vector1<uint32_t>;
	using Vector1i64	= Vector1<int64_t>;
	using Vector1u64	= Vector1<uint64_t>;

}
