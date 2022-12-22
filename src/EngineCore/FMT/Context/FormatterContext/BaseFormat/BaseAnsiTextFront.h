#pragma once

#include "FMT/Context/FormatterContext/BasicFormatterContext.h"

// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

namespace EngineCore::FMT {

	template<typename FormatterContext>
	struct FormatterType<Detail::AnsiFront, FormatterContext>
	{
		static void Write(const Detail::AnsiFront t, FormatterContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicWriteType('\033', '[', t.FrontId, 'm');
			context.GetAnsiManager().FrontModif(t);
		}
	};

}


