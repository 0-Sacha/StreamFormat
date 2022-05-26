#pragma once

#include "Base.h"

namespace EngineCore::Instrumentation::FMT::Detail {

	class FormatError {};

	class FormatBufferError	: public FormatError {};
	class FormatBufferFull	: public FormatBufferError {};
	class FormatBufferLock	: public FormatBufferError {};
	class FormatBufferEnd	: public FormatBufferError {};
	
	class FormatIndexError				: public FormatError {};
	class FormatBufferWrongIndex 		: public FormatIndexError {};
	class FormatBufferIndexOutOfRange 	: public FormatIndexError {};

	class FormatParseError		: public FormatError {};
	class FormatGivenTypeError	: public FormatParseError {};

}
