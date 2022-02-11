#pragma once

namespace EngineCore::Fmt::Detail {

	class FormatError {};

	class FormatBufferFull	: public FormatError {};
	class FormatBufferIndex : public FormatError {};
	class FormatBufferLock	: public FormatError {};
	class FormatBufferEnd	: public FormatError {};

	class FormatParseError	: public FormatError {};

}
