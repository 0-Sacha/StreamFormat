#pragma once

#include "EngineCore/FMT/Context/ParserContext/BasicParserContext.h"

namespace EngineCore::FMT {

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextFront::Front, ParserContext>
	{
		static void Read(const Detail::TextProperties::TextFront::Front t, ParserContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicReadType('\033', '[', t.FrontId, 'm');
		}
	};

}


