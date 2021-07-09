#pragma once

#include "BasicVector2.h"
#include "BasicVector2.inl"

namespace EngineCore {

	template <typename Type>
	using BasicVector2 = BasicVector<2, Type>;

	using BasicVector2f = BasicVector2<float>;
	using BasicVector2d = BasicVector2<double>;
	using BasicVector2i = BasicVector2<int>;
	using BasicVector2u = BasicVector2<unsigned int>;

	using BasicVector2i8	= BasicVector2<int8_t>;
	using BasicVector2u8	= BasicVector2<uint8_t>;
	using BasicVector2i16	= BasicVector2<int16_t>;
	using BasicVector2u16	= BasicVector2<uint16_t>;
	using BasicVector2i32	= BasicVector2<int32_t>;
	using BasicVector2u32	= BasicVector2<uint32_t>;
	using BasicVector2i64	= BasicVector2<int64_t>;
	using BasicVector2u64	= BasicVector2<uint64_t>;


    template <typename Type, typename ComputeAlgorithm = EngineCompute::EngineComputeDefault>
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
