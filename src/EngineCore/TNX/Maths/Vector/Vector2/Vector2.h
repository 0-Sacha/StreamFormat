#pragma once

#include "Vector2BasicImpl.h"
#include "Vector2BasicImpl.inl"

namespace EngineCore::TNX {

    template <typename Type, typename ComputeAlgorithm = TNX::TNXDefault>
    using Vector2 = Vector<2, Type, ComputeAlgorithm>;

    using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
	using Vector2i = Vector2<int>;
	using Vector2u = Vector2<unsigned int>;

	using Vector2i8	    = Vector2<int8_t>;
	using Vector2u8	    = Vector2<uint8_t>;
	using Vector2i16	= Vector2<int16_t>;
	using Vector2u16	= Vector2<uint16_t>;
	using Vector2i32	= Vector2<int32_t>;
	using Vector2u32	= Vector2<uint32_t>;
	using Vector2i64	= Vector2<int64_t>;
	using Vector2u64	= Vector2<uint64_t>;

}
