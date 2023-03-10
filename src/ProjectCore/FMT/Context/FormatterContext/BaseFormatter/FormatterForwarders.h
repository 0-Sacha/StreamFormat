#pragma once

#include "ProjectCore/FMT/Context/FormatterContext/BasicFormatterContext.h"
#include "ProjectCore/FMT/Detail/Forwarders.h"

namespace ProjectCore::FMT
{
    // Int Forwarders
    template<typename T, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsInt<T>, FormatterContext> {
		static inline void Format(const T t, FormatterContext& context) {
			context.BufferOut().WriteIntFormatData(t, context.GetFormatData());
		}
	};

	// UInt Forwarders
	template<typename T, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsUInt<T>, FormatterContext> {
		static inline void Format(const T t, FormatterContext& context) {
			context.BufferOut().WriteUIntFormatData(t, context.GetFormatData());
		}
	};

	// Float Forwarders
	template<typename T, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsFloat<T>, FormatterContext> {
		static void Format(const T t, FormatterContext& context) {
			context.BufferOut().WriteFloatFormatData(t, context.GetFormatData());
		}
	};

	// Char Forwarders
	template<typename T, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsChar<T>, FormatterContext> {
		inline static void Format(const T t, FormatterContext& context) {
			context.BufferOut().PushBack(t);
		}
	};

	// Char Array Forwarders
	template<typename T, std::size_t SIZE, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsCharArray<T, SIZE>, FormatterContext> {
		static void Format(const T(&t)[SIZE], FormatterContext& context) {
			const auto& data = context.GetFormatData();

			auto begin = context.GetFormatData().GetSpecifierAsNumber("begin", 0);
			auto size = context.GetFormatData().GetSpecifierAsNumber("size", (t[SIZE - 1] == 0 ? SIZE - 1 : SIZE) - begin);

			if (data.HasSpecifier("indent"))
				return context.BufferOut().WriteIndentCharPtr(t + begin, size);

			if (data.TrueValue)	context.BufferOut().PushBack('\"');
			
			if (data.HasSpec == false)
				context.BufferOut().FastWriteCharPtr(t + begin, size);
			else
				context.BufferOut().WriteCharPtr(t + begin, size, data.ShiftType, data.ShiftSize, data.ShiftPrint);

			if (data.TrueValue)	context.BufferOut().PushBack('\"');
		}
	};

	// Char Pointers Forwarders
	template<typename T, typename FormatterContext>
	struct FormatterType<Detail::ForwardAsCharPointer<T>, FormatterContext> {
		static void Format(const T* t, FormatterContext& context) {
			const auto& data = context.GetFormatData();

			if (t == nullptr)
				return context.BufferOut().FastWriteStringView(data.GetSpecifierAsText("null", "[nullptr string]"));

			auto begin = data.GetSpecifierAsNumber("begin", 0);
			auto size = data.GetSpecifierAsNumber("size", Detail::FORMAT_DATA_NOT_SPECIFIED);

			if (data.HasSpecifier("indent"))
			{
				if (size == Detail::FORMAT_DATA_NOT_SPECIFIED)
					return context.BufferOut().WriteIndentCharPtrNSize(t + begin);
				return context.BufferOut().WriteIndentCharPtr(t + begin, size);
			}

			if (data.TrueValue) context.BufferOut().PushBack('\"');

			if (data.HasSpec == false)
			{
				if (size != Detail::FORMAT_DATA_NOT_SPECIFIED)	context.BufferOut().FastWriteCharPtr(t + begin, size);
				else											context.BufferOut().FastWriteCharPtrNSize(t + begin);
			}
			else
			{
				if (size != Detail::FORMAT_DATA_NOT_SPECIFIED)	context.BufferOut().WriteCharPtr(t + begin, size, data.ShiftType, data.ShiftSize, data.ShiftPrint);
				else											context.BufferOut().WriteCharPtrNSize(t + begin, data.ShiftType, data.ShiftSize, data.ShiftPrint);
			}

			if (data.TrueValue) context.BufferOut().PushBack('\"');
		}
	};
}
