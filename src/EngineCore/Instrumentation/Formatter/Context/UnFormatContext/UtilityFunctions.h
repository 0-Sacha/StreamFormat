#pragma once


#include "BasicUnFormatContext.h"
#include "BasicUnFormatContextCoreImpl.h"
#include "BasicUnFormatContextParseImpl.h"

namespace EngineCore::FMT {
	template<typename Format = std::string_view, typename BufferStr = Format, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsFmtConvertible<BufferStr>::Value
	void UnFormat(const BufferStr& buffer, const Format& format, Args&& ...args) {
		Context::BasicUnFormatContext<typename Detail::GetFmtBaseType<Format>::Type, typename Detail::GetFmtBaseType<BufferStr>::Type, Args...> context(format, buffer, std::forward<Args>(args)...);
		return context.SafeRun();
	}
}

