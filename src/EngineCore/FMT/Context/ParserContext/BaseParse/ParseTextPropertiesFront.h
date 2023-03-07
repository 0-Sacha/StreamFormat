#pragma once

#include "EngineCore/FMT/Context/ParserContext/BasicParserContext.h"

namespace EngineCore::FMT {

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextFront::ResetFront, ParserContext>
	{
		static void Format(const Detail::TextProperties::TextFront::ResetFront t, ParserContext& context) {
			context.GetTextPropertiesParser().FrontModifReset();
		}
	};

	template<typename ParserContext>
	struct ParserType<Detail::TextProperties::TextFront::FrontID, ParserContext>
	{
		static void Format(const Detail::TextProperties::TextFront::FrontID t, ParserContext& context) {
			context.GetTextPropertiesParser().FrontModif(t);
		}
	};
}
