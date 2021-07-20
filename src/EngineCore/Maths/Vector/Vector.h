#pragma once

#include "EngineCore/Maths/Core/Core.h"
#include <concepts>
#include <array>

// A Vector must have the "constexpr Count()" function and the "using ValueType" define to the used Type
namespace EngineCore {
	template <std::size_t COUNT, typename Type, typename ComputeAlgorithm = EngineCompute::EngineComputeDefault>
	struct Vector;

	template <typename To, std::size_t COUNT, typename T>
	concept VectorConvertible = requires(To to) {
		requires To::Count() == COUNT;
		requires std::is_convertible_v<typename To::ValueType, T>;
	};
} // namespace EngineCore





template <std::size_t COUNT, typename Type, typename ComputeAlgorithm, typename FormatContext>
struct CPPTools::Fmt::FormatType<EngineCore::Vector<COUNT, Type, ComputeAlgorithm>, FormatContext>
{
	static void Write(const EngineCore::Vector<COUNT, Type, ComputeAlgorithm>& vec, FormatContext& context) {
		context.BufferPushBack('{');
		bool first = true;
		for (auto i = 0; i < COUNT; ++i) {
			if (first)  first = false;
			else		{ context.BufferPushBack(','); context.BufferPushBack(' '); }
			context.WriteType(vec.data[i]);
		}
		context.BufferPushBack('}');
	}
};

template <std::size_t COUNT, typename Type, typename ComputeAlgorithm, typename UnFormatContext>
struct CPPTools::Fmt::UnFormatType<EngineCore::Vector<COUNT, Type, ComputeAlgorithm>, UnFormatContext>
{
	static bool Read(const EngineCore::Vector<COUNT, Type, ComputeAlgorithm>& vec, UnFormatContext& context) {
		if(!context.BufferIsEqualForward('{')) return false;
		bool first = true;
		for (auto i = 0; i < COUNT; ++i) {
			if (first)	first = false;
			else		{ context.BufferPushBack(','); context.BufferPushBack(' '); } 
			context.ReadType(vec.data[i]);
		}
		if(!context.BufferIsEqualForward('}')) return false;
	}
};