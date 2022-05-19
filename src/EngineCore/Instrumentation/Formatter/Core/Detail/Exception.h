#pragma once

#include "Base.h"

namespace EngineCore::Instrumentation::FMT::Detail {

	class FormatError {};

	class FormatBufferFull	: public FormatError {};
	class FormatBufferLock	: public FormatError {};
	class FormatBufferEnd	: public FormatError {};
	
	class FormatBufferWrongIndex 		: public FormatError {};
	class FormatBufferIndexOutOfRange 	: public FormatError {};

	class FormatParseError	: public FormatError {};

}
