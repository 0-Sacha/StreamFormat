#pragma once

#include "EngineCore/Core.h"
#include "EngineCore/TNX/Detail/TNXType.h"

// A Vector must have the "constexpr Count()" function and the "using ValueType" define to the used Type
namespace EngineCore::TNX {
	template <std::size_t COUNT, typename Type, typename ComputeAlgorithm = TNXType::TNXBasic>
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




#include "EngineCore/Instrumentation/Formatter/Formatter.h"
template <std::size_t COUNT, typename Type, typename ComputeAlgorithm, typename FormatContext>
struct EngineCore::Instrumentation::FMT::FormatType<EngineCore::TNX::Vector<COUNT, Type, ComputeAlgorithm>, FormatContext>
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
struct EngineCore::Instrumentation::FMT::UnFormatType<EngineCore::TNX::Vector<COUNT, Type, ComputeAlgorithm>, UnFormatContext>
{
	static void Read(const EngineCore::Vector<COUNT, Type, ComputeAlgorithm>& vec, UnFormatContext& context) {
		context.BufferOut().IsEqualForwardThrow('{');
		bool first = true;
		for (auto i = 0; i < COUNT; ++i) {
			if (first)	first = false;
			else		{ context.BufferOut().PushBack(','); context.BufferOut().PushBack(' '); }
			context.ReadType(vec.data[i]);
		}
		context.BufferOut().IsEqualForwardThrow('}');
	}
};