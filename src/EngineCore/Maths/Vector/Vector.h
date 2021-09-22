#pragma once

#include "EngineCore/Maths/Core/Core.h"

// A Vector must have the "constexpr Count()" function and the "using ValueType" define to the used Type
namespace EngineCore {
	template <std::size_t COUNT, typename Type, typename ComputeAlgorithm = EngineCompute::EngineComputeDefault>
	struct Vector;

	template <typename From, std::size_t COUNT, typename Type>
	concept VectorConvertibleTo = requires(From to) {
		requires From::Count() == COUNT;
		requires std::is_convertible_v<typename From::ValueType, Type>;
	};
	/*
	template <typename From, typename VecType>
	concept VectorConvertibleTo = requires(From to) {
		requires From::Count() == VecType::Count();
		requires std::is_convertible_v<typename From::ValueType, typename VecType::ValueType>;
	};*/
} // namespace EngineCore





template <std::size_t COUNT, typename Type, typename ComputeAlgorithm, typename FormatContext>
struct CPPTools::Fmt::FormatType<EngineCore::Vector<COUNT, Type, ComputeAlgorithm>, FormatContext>
{
	static void Write(const EngineCore::Vector<COUNT, Type, ComputeAlgorithm>& vec, FormatContext& context) {
		context.BufferOut().PushBack('{');
		bool first = true;
		for (auto i = 0; i < COUNT; ++i) {
			if (first)  first = false;
			else		{ context.BufferOut().PushBack(','); context.BufferOut().PushBack(' '); }
			context.WriteType(vec.data[i]);
		}
		context.BufferOut().PushBack('}');
	}
};

template <std::size_t COUNT, typename Type, typename ComputeAlgorithm, typename UnFormatContext>
struct CPPTools::Fmt::UnFormatType<EngineCore::Vector<COUNT, Type, ComputeAlgorithm>, UnFormatContext>
{
	static bool Read(const EngineCore::Vector<COUNT, Type, ComputeAlgorithm>& vec, UnFormatContext& context) {
		if(!context.BufferOut().IsEqualForward('{')) return false;
		bool first = true;
		for (auto i = 0; i < COUNT; ++i) {
			if (first)	first = false;
			else		{ context.BufferOut().PushBack(','); context.BufferOut().PushBack(' '); }
			context.ReadType(vec.data[i]);
		}
		if(!context.BufferOut().IsEqualForward('}')) return false;
	}
};