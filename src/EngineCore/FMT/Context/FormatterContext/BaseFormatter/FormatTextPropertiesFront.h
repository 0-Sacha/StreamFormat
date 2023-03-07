#pragma once

#include "EngineCore/FMT/Context/FormatterContext/BasicFormatterContext.h"

namespace EngineCore::FMT {

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextFront::ResetFront, FormatterContext>
	{
		static void Format(const Detail::TextProperties::TextFront::ResetFront t, FormatterContext& context) {
			context.GetTextPropertiesParser().FrontModifReset();
		}
	};

	template<typename FormatterContext>
	struct FormatterType<Detail::TextProperties::TextFront::FrontID, FormatterContext>
	{
		static void Format(const Detail::TextProperties::TextFront::FrontID t, FormatterContext& context) {
			context.GetTextPropertiesParser().FrontModif(t);
		}
	};
}
