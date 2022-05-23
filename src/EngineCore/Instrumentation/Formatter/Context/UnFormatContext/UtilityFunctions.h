#pragma once

#include "BasicUnFormatContextParseImpl.h"

namespace EngineCore::Instrumentation::FMT {
	template<typename Format = std::string_view, typename BufferStr = Format, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsFmtConvertible<BufferStr>::Value
	UnFormatContextError UnFormat(const BufferStr& buffer, const Format& format, Args&& ...args) {
		FMT::BasicUnFormatContext<typename Detail::GetFmtBaseType<Format>::Type, typename Detail::GetFmtBaseType<BufferStr>::Type, Args...> context(format, buffer, std::forward<Args>(args)...);
		return context.SafeRun();
	}
}

