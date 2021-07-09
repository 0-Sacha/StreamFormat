#pragma once

#include "EngineCore/Core/Core.h"
#include "EngineCore/Maths/Core/Base.h"

namespace EngineCore {
	template<std::size_t COUNT, typename Type>
	struct BasicVector;

	template <std::size_t COUNT, typename Type, typename ComputeAlgorithm = EngineCompute::EngineComputeDefault>
	struct Vector;
} // namespace EngineCore





template<std::size_t COUNT, typename Type, typename FormatContext>
struct CPPTools::Fmt::FormatType<EngineCore::BasicVector<COUNT, Type>, FormatContext>
{
	static void Write(const EngineCore::BasicVector<COUNT, Type>& vec, FormatContext& context) {
		context.BufferPushBack('{');
		bool first = true;
		for (auto i = 0; i < COUNT; ++i) {
			if (first) {	first = false;
			} else		{ context.BufferPushBack(','); context.BufferPushBack(' '); } 
			context.WriteType(vec.data[i]); 
		}
		context.BufferPushBack('}');
	}
};

template<std::size_t COUNT, typename Type, typename UnFormatContext>
struct CPPTools::Fmt::UnFormatType<EngineCore::BasicVector<COUNT, Type>, UnFormatContext>
{
	static auto Read(const EngineCore::BasicVector<COUNT, Type>& vec, UnFormatContext& context) -> bool {
		if(!context.BufferIsEqualForward('{')) return false;
		bool first = true;
		for (auto i = 0; i < COUNT; ++i) {
			if (first)	first = false;
			else		{ context.BufferPushBack(','); context.BufferPushBack(' '); } 
			context.ReadType(vec.data[i], context);
		}
		if(!context.BufferIsEqualForward('}')) return false;
	}
};

template<std::size_t COUNT, typename Type, typename ComputeAlgorithm, typename FormatContext>
struct CPPTools::Fmt::FormatType<EngineCore::Vector<COUNT, Type, ComputeAlgorithm>, FormatContext>
{
	static void Write(const EngineCore::Vector<COUNT, Type, ComputeAlgorithm>& vec, FormatContext& context) {
		FormatType<EngineCore::BasicVector<COUNT, Type>, FormatContext>::Write(static_cast<const EngineCore::BasicVector<COUNT, Type>&>(vec), context);
	}
};

template<std::size_t COUNT, typename Type, typename ComputeAlgorithm, typename UnFormatContext>
struct CPPTools::Fmt::UnFormatType<EngineCore::Vector<COUNT, Type, ComputeAlgorithm>, UnFormatContext>
{
	static auto Read(const EngineCore::Vector<COUNT, Type, ComputeAlgorithm>& vec, UnFormatContext& context) -> bool {
		return UnFormatType<EngineCore::BasicVector<COUNT, Type>, UnFormatContext>::Read(static_cast<EngineCore::BasicVector<COUNT, Type>&>(vec), context);
	}
};
