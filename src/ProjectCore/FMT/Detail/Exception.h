#pragma once

#include "ProjectCore/Core/Core.h"

#include <exception>

namespace ProjectCore::FMT::Detail {

	class FMTException 			: public std::exception {};
	class FMTError				: public FMTException {};
	class FMTUtilityException	: public FMTException {};

	class FMTBufferError	: public FMTError {};
	class FMTBufferFull		: public FMTBufferError {};
	class FMTBufferLock		: public FMTBufferError {};
	class FMTBufferEnd		: public FMTBufferError {};
	
	class FMTIndexError				: public FMTError {};
	class FMTBufferWrongIndex 		: public FMTIndexError {};
	class FMTBufferIndexOutOfRange 	: public FMTIndexError {};

	class FMTParseError			: public FMTError {};
	class FMTGivenTypeError		: public FMTParseError {};

	class FMTImplError			: public FMTError {};
	class FMTShouldNotEndHere 	: public FMTImplError {};
	class FMTNotImplYet 		: public FMTImplError {};

}
