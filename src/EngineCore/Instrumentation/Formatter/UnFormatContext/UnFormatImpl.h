#pragma once

#include "BasicUnFormatContextParseImpl.h"

namespace EngineCore::Instrumentation::Fmt {
	template<typename FormatStr = std::string_view, typename BufferStr = FormatStr, typename ...Args>
	requires Detail::IsFmtConvertible<FormatStr>::Value&& Detail::IsFmtConvertible<BufferStr>::Value
	UnFormatContextError UnFormat(const BufferStr& buffer, const FormatStr& format, Args&& ...args) {
		Fmt::BasicUnFormatContext<typename Detail::GetFmtBaseType<FormatStr>::Type, typename Detail::GetFmtBaseType<BufferStr>::Type, Args...> context(format, buffer, std::forward<Args>(args)...);
		return context.SafeRun();
	}
}

