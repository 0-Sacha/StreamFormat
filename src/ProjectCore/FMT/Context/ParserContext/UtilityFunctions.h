#pragma once

#include "BasicParserContext.h"
#include "BasicParserContextCoreImpl.h"
#include "BasicParserContextParseImpl.h"

namespace ProjectCore::FMT {

	template<typename Format = std::string_view, typename BufferStr = Format, typename ...Args>
	requires Detail::IsFmtConvertible<Format>::Value&& Detail::IsFmtConvertible<BufferStr>::Value
	void Parse(const BufferStr& buffer, const Format& formatData, Args&& ...args) {
		using ContextType = Context::BasicParserContext<typename Detail::GetFmtBaseType<Format>::Type, typename Detail::GetFmtBaseType<BufferStr>::Type>;
		auto contextArgsInterface = Detail::ParserContextArgsTupleInterface<ContextType, Args...>(std::forward<Args>(args)...);
		Detail::BufferInProperties<typename Detail::GetFmtBaseType<Format>::Type> formatManager(formatData);
		Detail::FMTFormatBuffer<typename Detail::GetFmtBaseType<Format>::Type> format(formatManager);
		Detail::ParserANSITextPropertiesExecutor<typename ContextType::BufferInType> textPropertiesExecutor;
		ContextType context(buffer, textPropertiesExecutor);
		context.Run(format, &contextArgsInterface);
		context.Terminate();
	}
	
}

