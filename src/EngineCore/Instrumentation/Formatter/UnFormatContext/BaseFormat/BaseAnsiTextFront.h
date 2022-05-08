#pragma once

#include "../BasicUnFormatContext.h"

// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

namespace EngineCore::Fmt {

	template<typename UnFormatContext>
	struct UnFormatType<Detail::AnsiTextFront, UnFormatContext>
	{
		static void Read(const Detail::AnsiTextFront t, UnFormatContext& context) {
			Detail::NoStrideFunction nostride(context);

			context.BasicReadType('\033', '[', t.FrontId, 'm');
		}
	};

}


