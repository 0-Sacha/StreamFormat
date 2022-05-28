#pragma once

#include "../BasicFormatContext.h"

// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

namespace EngineCore::Instrumentation::FMT {

	template<typename FormatContext>
	struct FormatType<Detail::AnsiFront, FormatContext>
	{
		static void Write(const Detail::AnsiFront t, FormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', t.FrontId, 'm');
			context.GetAnsiManager().FrontModif(t);
		}
	};

}


