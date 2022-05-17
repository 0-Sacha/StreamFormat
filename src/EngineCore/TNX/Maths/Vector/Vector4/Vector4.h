#pragma once

#include "Vector4BasicImpl.h"
#include "Vector4BasicImpl.inl"

namespace EngineCore::TNX {

    template <typename Type, typename ComputeAlgorithm = TNX::TNXDefault>
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
