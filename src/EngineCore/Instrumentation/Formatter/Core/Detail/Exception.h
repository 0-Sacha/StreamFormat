#pragma once

#include "Base.h"

namespace EngineCore::FMT::Detail {

	class FormatExecption {};
	class FormatError				: public FormatExecption {};
	class FormatUtilityExecption	: public FormatExecption {};

	class FormatBufferError	: public FormatError {};
	class FormatBufferFull	: public FormatBufferError {};
	class FormatBufferLock	: public FormatBufferError {};
	class FormatBufferEnd	: public FormatBufferError {};
	
	class FormatIndexError				: public FormatError {};
	class FormatBufferWrongIndex 		: public FormatIndexError {};
	class FormatBufferIndexOutOfRange 	: public FormatIndexError {};

	class FormatParseError		: public FormatError {};
	class FormatGivenTypeError	: public FormatParseError {};

	class FormatImplError			: public FormatError {};
	class FormatShouldNotEndHere 	: public FormatImplError {};
	class FormatNotImplYet 			: public FormatImplError {};



	class FormatIndexNotFoundException 	: public FormatUtilityExecption{};
	class FormatGetTypeAtIndexTypeOK 	: public FormatUtilityExecption{};

}
