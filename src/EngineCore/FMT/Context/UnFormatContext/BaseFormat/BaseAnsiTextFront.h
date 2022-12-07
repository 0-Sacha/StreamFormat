#pragma once

#include "FMT/Context/UnFormatContext/BasicUnFormatContext.h"

// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

namespace EngineCore::FMT {

	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiFront, UnFormatContext>
	{
		static void Read(const Detail::AnsiFront t, UnFormatContext& context) {
			Detail::NoStrideFunction nostride(context.BufferOut());
			context.BasicReadType('\033', '[', t.FrontId, 'm');
		}
	};

}


