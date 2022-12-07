#pragma once

#include "EngineCore/Core/Core.h"

namespace EngineCore::FMT::Detail {

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
		void ModifyThrow(const AnsiFront& given) { *this = given; }

	public:
		bool operator==(const AnsiFront& other) const { return FrontId == other.FrontId; }
	};

	struct AnsiTextCurrentFront {
	public:
		AnsiFront Front;
	};

	const static inline AnsiFront			RESET_ANSI_FRONT(AnsiFront::DefaultFront);
}

