#pragma once

#include "Vector1BasicImpl.h"
#include "Vector1BasicImpl.inl"

namespace EngineCore {

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
