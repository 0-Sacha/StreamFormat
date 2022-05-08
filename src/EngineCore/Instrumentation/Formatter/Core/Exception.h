#pragma once

#include <stdexcept>

namespace EngineCore::Fmt::Detail {

	class FormatError : std::runtime_error {
	public:
		FormatError()
			: std::runtime_error("FormatError")
		{
		}

		FormatError(const char *const errorMessage)
			: std::runtime_error(errorMessage)
		{
		}
	};

	class FormatBufferFull	: public FormatError {
	public:
		FormatBufferFull() : FormatError("FormatBufferFull") {}
	};
	
	class FormatBufferIndex : public FormatError {
	public:
		FormatBufferIndex() : FormatError("FormatBufferIndex") {}
	};

	class FormatBufferLock	: public FormatError {
	public:
		FormatBufferLock() : FormatError("FormatBufferLock") {}
	};
	
	class FormatBufferEnd	: public FormatError {
	public:
		FormatBufferEnd() : FormatError("FormatBufferEnd") {}
	};

	class FormatParseError	: public FormatError {
	public:
		FormatParseError() : FormatError("FormatParseError") {}
	};

}


