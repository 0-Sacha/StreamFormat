#pragma once

#include "BasicParserContext.h"
#include "BasicParserContextCoreImpl.h"
#include "BasicParserContextParseImpl.h"

namespace EngineCore::FMT {
	template<typename Format = std::string_view, typename BufferStr = Format, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsFmtConvertible<BufferStr>::Value
	void Parser(const BufferStr& buffer, const Format& format, Args&& ...args) {
		Context::BasicParserContext<typename Detail::GetFmtBaseType<Format>::Type, typename Detail::GetFmtBaseType<BufferStr>::Type, Args...> context(format, buffer, std::forward<Args>(args)...);
		return context.SafeRun();
	}
}

