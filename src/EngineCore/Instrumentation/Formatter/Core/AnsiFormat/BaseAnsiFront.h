#pragma once

#include "EngineCore/Core.h"

namespace EngineCore::Instrumentation::FMT::Detail {

	// According to : https://en.wikipedia.org/wiki/ANSI_escape_code

	struct AnsiFront {
	public:
		static inline constexpr std::uint8_t DefaultFront	= 0;
		static inline constexpr std::uint8_t MinFront		= 0;
		static inline constexpr std::uint8_t MaxFront		= 9;

		static inline constexpr std::uint8_t FrontAnsiIdx	= 10;

	public:
		AnsiFront(const std::uint8_t frontId = DefaultFront)
			: FrontId((frontId > MaxFront ? DefaultFront : frontId) + FrontAnsiIdx) {}
		
	public:
		std::uint8_t FrontId;

	public:
		template <typename T> void ModifyThrow(const T&) { throw Detail::FormatGivenTypeError{}; }

		template <> void ModifyThrow(const AnsiFront& given) { *this = given; }
	};

	struct AnsiTextCurrentFront {
	public:
		AnsiFront Front;
	};

	const static inline AnsiFront			RESET_ANSI_FRONT(AnsiFront::DefaultFront);
}

