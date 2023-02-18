#pragma once

#include "EngineCore/FMT/Context/ParserContext/BasicParserContext.h"
#include "EngineCore/FMT/Detail/Forwarders.h"

namespace EngineCore::FMT::Detail
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
			// FIXME
		}
	};
	template<typename T, typename ParserContext>
	struct ParserType<Detail::ForwardAsCharPointer<T>, ParserContext> {
		static inline void Read(T* const t, ParserContext& context) {
			// FIXME
		}
	};
}
