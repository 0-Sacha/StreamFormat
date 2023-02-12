#pragma once

#include "BasicParserContext.h"
#include "BasicParserContextCoreImpl.h"
#include "BasicParserContextParseImpl.h"

namespace EngineCore::FMT {

	template<typename Format = std::string_view, typename BufferStr = Format, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsFmtConvertible<BufferStr>::Value
	void Parse(const BufferStr& buffer, const Format& formatData, Args&& ...args) {
		using ContextType = Context::BasicParserContext<typename Detail::GetFmtBaseType<Format>::Type, typename Detail::GetFmtBaseType<BufferStr>::Type>;
		auto childContextArgsInterface = Detail::ParserContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		Detail::FMTFormatBuffer<typename Detail::GetFmtBaseType<Format>::Type> format(formatData);
		ContextType context(buffer);
		return context.Run(format, &childContextArgsInterface);
	}
	
}

