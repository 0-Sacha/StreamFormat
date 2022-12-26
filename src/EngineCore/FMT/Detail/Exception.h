#pragma once

#include "EngineCore/Core/Core.h"

namespace EngineCore::FMT::Detail {

	class FormatException {};
	class FormatError				: public FormatException {};
	class FormatUtilityException	: public FormatException {};

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

}
