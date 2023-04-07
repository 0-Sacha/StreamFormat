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

			std::size_t begin = (std::size_t)context.GetFormatData().GetSpecifierAsNumber("begin", 0);
			bool isZeroEnded = context.GetFormatData().HasSpecifier("no-zero-end");
			std::size_t size = (std::size_t)context.GetFormatData().GetSpecifierAsNumber("size", static_cast<Detail::DataType>(SIZE - static_cast<std::size_t>(isZeroEnded ? 0 : 1) - begin));

			// if (data.HasSpecifier("indent"))
			// 	return context.BufferIn().ReadIndentCharPtr(t + begin, size);

			if (data.TrueValue)	context.BufferIn().Skip('\"');

			if (context.GetFormatData().HasSpecifier("glob"))
			{
				auto globberPattern = context.GetFormatData().GetSpecifierAsText("glob");
				context.BufferIn().FastReadCharPtrGlobber(globberPattern, t + begin, size, isZeroEnded);
			}
			else if (context.GetFormatData().HasSpecifier("regex"))
			{
				throw Detail::FMTImplError{};
			}
			else
			{
				if (data.HasSpec == false)
					context.BufferIn().FastReadCharPtrThrow(t + begin, size, isZeroEnded);
				else
					context.BufferIn().FastReadCharPtrThrow(t + begin, size, isZeroEnded);
					// context.BufferIn().ReadCharPtr(t + begin, size, 0, data.ShiftType, data.ShiftSize, data.ShiftPrint);
			}

			if (data.TrueValue)	context.BufferIn().Skip('\"');
		}
	};
	template<typename T, typename ParserContext>
	struct ParserType<Detail::ForwardAsCharPointer<T>, ParserContext> {
		static inline void Read(T* const, ParserContext&) {
			// FIXME
		}
	};
}
