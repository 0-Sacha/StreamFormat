#pragma once

#include "FMT/Context/ParserContext/BasicParserContext.h"

// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

namespace EngineCore::FMT {

	template<typename ParserContext>
	struct ParserType<Detail::AnsiFront, ParserContext>
	{
		static void Read(const Detail::AnsiFront t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicReadType('\033', '[', t.FrontId, 'm');
		}
	};

}


