#pragma once

#include "BaseTextProperties.h"

namespace ProjectCore::FMT::Detail {

	struct TextProperties::TextFront
	{
		struct ResetFront {};

		struct FrontID;
		struct Front;
	};

	struct TextProperties::TextFront::FrontID
	{
	public:
		static inline constexpr std::uint8_t DefaultFrontID	= 10;
		static inline constexpr std::uint8_t MinFrontID		= 10;
		static inline constexpr std::uint8_t MaxFrontID		= 19;

	public:
		std::uint8_t ID;

		constexpr FrontID() 				: ID(DefaultFrontID) {}
		constexpr FrontID(std::uint8_t id) 	: ID(id) {}
	
	public:
		constexpr bool operator==(const FrontID& other) const { return ID == other.ID; }
		constexpr bool IsValid() const { return ID > MinFrontID && ID < MaxFrontID; }
	};

	struct TextProperties::TextFront::Front
	{
	public:
		constexpr Front(const FrontID frontId = FrontID::DefaultFrontID)
			: CurrentID(frontId.IsValid() ? frontId : FrontID::DefaultFrontID)
		{}
		
	public:
		FrontID CurrentID;

	public:
		void ModifyReset() 									{ *this = Front{}; }
		
		template <typename T> void ModifyThrow(const T&) 	{ throw Detail::FMTGivenTypeError{}; }
		void ModifyThrow(const ResetFront& given)			{ ModifyReset(); }
		void ModifyThrow(const Front& given)				{ *this = given; }
		void ModifyThrow(const FrontID& given) 				{ CurrentID = given; }

	public:
		bool operator==(const Front& other) const { return CurrentID == other.CurrentID; }
	};
}
