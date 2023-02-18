#pragma once

#include "EngineCore/FMT/Context/FormatterContext/BasicFormatterContext.h"
#include "EngineCore/FMT/Detail/Forwarders.h"

namespace EngineCore::FMT::Detail
{
    // Int Forwarders
    template<typename T, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsInt<T>, FormatterContext> {
		static inline void Write(const T t, FormatterContext& context) {
			context.BufferOut().WriteIntFormatData(t, context.GetFormatData());
		}
	};

	// UInt Forwarders
	template<typename T, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsUInt<T>, FormatterContext> {
		static inline void Write(const T t, FormatterContext& context) {
			context.BufferOut().WriteUIntFormatData(t, context.GetFormatData());
		}
	};

	// Float Forwarders
	template<typename T, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsFloat<T>, FormatterContext> {
		static void Write(const T t, FormatterContext& context) {
			context.BufferOut().WriteFloatFormatData(t, context.GetFormatData());
		}
	};

	// Char Forwarders
	template<typename T, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsChar<T>, FormatterContext> {
		inline static void Write(const T t, FormatterContext& context) {
			context.BufferOut().PushBack(t);
		}
	};

	// Char Array Forwarders
	template<typename T, std::size_t SIZE, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsCharArray<T, SIZE>, FormatterContext> {
		static void Write(const T(&t)[SIZE], FormatterContext& context) {
			const auto& data = context.GetFormatData();

			auto begin = context.GetFormatData().GetSpecifierAsNumber("begin", 0);
			auto size = context.GetFormatData().GetSpecifierAsNumber("size", SIZE - begin);

			if (data.TrueValue)	context.BufferOut().PushBack('\"');
			context.BufferOut().WriteCharPtr(t + begin, size);
			if (data.TrueValue)	context.BufferOut().PushBack('\"');
		}
	};

	// Char Pointers Forwarders
	template<typename T, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsCharPointer<T>, FormatterContext> {
		static void Write(const T* t, FormatterContext& context) {
			if (t == nullptr)
				return context.Print(context.GetFormatData().GetSpecifierAsText("null", "[nullptr string]"));

			const auto& data = context.GetFormatData();

			if (data.TrueValue)										context.BufferOut().PushBack('\"');

			auto begin = data.GetSpecifierAsNumber("begin", 0);
			auto size = data.GetSpecifierAsNumber("size", Detail::FORMAT_DATA_NOT_SPECIFIED);

			if (size != Detail::FORMAT_DATA_NOT_SPECIFIED)	context.Print(t + begin, size);
			else											context.PrintCharPtr(t + begin);

			if (data.TrueValue)										context.BufferOut().PushBack('\"');
		}
	};
}
