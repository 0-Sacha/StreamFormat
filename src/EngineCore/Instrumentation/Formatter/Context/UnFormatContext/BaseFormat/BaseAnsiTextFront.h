#pragma once

#include "../BasicUnFormatContext.h"

// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

namespace EngineCore::Instrumentation::FMT {

	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiTextFront, UnFormatContext>
	{
		static void Read(const Detail::AnsiTextFront t, UnFormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicReadType('\033', '[', t.FrontId, 'm');
		}
	};

}


