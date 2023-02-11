#pragma once

#include "BaseTextProperties.h"

namespace EngineCore::FMT::Detail {

	struct TextProperties::TextFront
	{
		struct Reset {};

		struct Front;
	};

	struct TextProperties::TextFront::Front
	{
	public:
		static inline constexpr std::uint8_t DefaultFront	= 0;
		static inline constexpr std::uint8_t MinFront		= 0;
		static inline constexpr std::uint8_t MaxFront		= 9;

		static inline constexpr std::uint8_t FrontAnsiIdx	= 10;

	public:
		Front(const std::uint8_t frontId = DefaultFront)
			: FrontId((frontId > MaxFront ? DefaultFront : frontId) + FrontAnsiIdx) {}
		
	public:
		std::uint8_t FrontId;

	public:
		template <typename T> void ModifyThrow(const T&) { throw Detail::FMTGivenTypeError{}; }
		void ModifyThrow(const Front& given) { *this = given; }

	public:
		bool operator==(const Front& other) const { return FrontId == other.FrontId; }
	};
}
