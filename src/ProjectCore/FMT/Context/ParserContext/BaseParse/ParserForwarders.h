#pragma once

#include "ProjectCore/FMT/Context/ParserContext/BasicParserContext.h"
#include "ProjectCore/FMT/Detail/Forwarders.h"

namespace ProjectCore::FMT
{
    // Int
	template<typename T, typename ParserContext>
	struct ParserType<Detail::ForwardAsInt<T>, ParserContext> {
		static inline void Read(T& t, ParserContext& context) {
			context.BufferIn().ReadIntFormatData(t, context.GetFormatData());
		}
	};

	// UInt
	template<typename T, typename ParserContext>
	struct ParserType<Detail::ForwardAsUInt<T>, ParserContext> {
		static inline void Read(T& t, ParserContext& context) {
			context.BufferIn().ReadUIntFormatData(t, context.GetFormatData());
		}
	};

	// Float
	template<typename T, typename ParserContext>
	struct ParserType<Detail::ForwardAsFloat<T>, ParserContext> {
		static inline void Read(T& t, ParserContext& context) {
			context.BufferIn().ReadFloatFormatData(t, context.GetFormatData());
		}
	};

	// Char type
	template<typename T, typename ParserContext>
	struct ParserType<Detail::ForwardAsChar<T>, ParserContext> {
		static inline void Read(T& t, ParserContext& context) {
			context.BufferIn().GetAndForward(t);
		}
	};
	template<std::size_t SIZE, typename T, typename ParserContext>
	struct ParserType<Detail::ForwardAsCharArray<T, SIZE>, ParserContext> {
		static inline void Read(T(&t)[SIZE], ParserContext& context) {
			const auto& data = context.GetFormatData();

			auto begin = context.GetFormatData().GetSpecifierAsNumber("begin", 0);
			auto size = context.GetFormatData().GetSpecifierAsNumber("size", (t[SIZE - 1] == 0 ? SIZE - 1 : SIZE) - begin);

			// if (data.HasSpecifier("indent"))
			// 	return context.BufferIn().ReadIndentCharPtr(t + begin, size);

			if (data.TrueValue)	context.BufferIn().Skip('\"');
			
			if (data.HasSpec == false)
				context.BufferIn().FastReadCharPtrThrow(t + begin, size);
			else
				context.BufferIn().FastReadCharPtrThrow(t + begin, size);
				// context.BufferIn().ReadCharPtr(t + begin, size, 0, data.ShiftType, data.ShiftSize, data.ShiftPrint);

			if (data.TrueValue)	context.BufferIn().Skip('\"');
		}
	};
	template<typename T, typename ParserContext>
	struct ParserType<Detail::ForwardAsCharPointer<T>, ParserContext> {
		static inline void Read(T* const t, ParserContext& context) {
			// FIXME
		}
	};
}
