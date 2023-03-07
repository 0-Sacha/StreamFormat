#pragma once

#include "ProjectCore/Core/Core.h"
#include "Types/Types.h"

#include <array>
#include <string_view>

namespace ProjectCore::FMT::Detail {
	
	enum class ValueIntPrint : DataType
	{
		Dec,
		Bin,
		Hex,
		Oct,
		Default = Dec
	};

	enum class ShiftType : DataType
	{
		Nothing,
		Right,
		Left,
		CenterRight,
		CenterLeft,
		Default = Nothing
	};

	enum class PrintStyle : DataType
	{
		Nothing,
		UpperCase,
		LowerCase,
		Default = Nothing
	};

	struct ShiftPrint {
	public:
		constexpr ShiftPrint()
			: Before(' ')
			, After(' ')
		{}

		constexpr ShiftPrint(char c)
			: Before(c)
			, After(c == '0' ? ' ' : c)
		{}

		constexpr ShiftPrint(char before, char after)
			: Before(before)
			, After(after == '0' ? ' ' : after)
		{}

	public:
		char Before;
		char After;

	public:
		constexpr bool BeforeIsADigit() const 	{ return Before >= '0' && Before <= '9'; }

		constexpr void Validate()  				{ if (After >= '0' && After <= '9') After = ' '; }
	};

	static constexpr ShiftPrint ShiftPrint_Space = ShiftPrint(' ');
	static constexpr ShiftPrint ShiftPrint_Zeros = ShiftPrint('0', ' ');
	static constexpr ShiftPrint ShiftPrint_Chevron = ShiftPrint('>', '<');

	struct DigitSize : public BasicCustomDataType<DataType, -1, -2>
	{ 
	public:
		inline constexpr DigitSize(const DataType value = DEFAULT)
			: BasicCustomDataType<DataType, -1, -2>(value)
		{}

		// operator =
		template <typename K>
		requires std::is_convertible_v<DataType, K>
		inline constexpr DigitSize& operator=(const K i)	{ Value = static_cast<DataType>(i); return *this; }

		template <typename K, K KDEFAULT, K KNON_VALID>
		requires std::is_convertible_v<DataType, K>
		inline constexpr BasicCustomDataType& operator=(const BasicCustomDataType<K, KDEFAULT, KNON_VALID>& i)	{ Value = static_cast<DataType>(i.Value); return *this; }
	};

	struct ShiftSize : public BasicCustomDataType<DataType, 0, -1>
	{ 
	public:
		inline constexpr ShiftSize(const DataType value = DEFAULT)
			: BasicCustomDataType<DataType, 0, -1>(value)
		{}

		// operator =
		template <typename K>
		requires std::is_convertible_v<DataType, K>
		inline constexpr ShiftSize& operator=(const K i)	{ Value = static_cast<DataType>(i); return *this; }

		template <typename K, K KDEFAULT, K KNON_VALID>
		requires std::is_convertible_v<DataType, K>
		inline constexpr ShiftSize& operator=(const BasicCustomDataType<K, KDEFAULT, KNON_VALID>& i)	{ Value = static_cast<DataType>(i.Value); return *this; }
	};

	struct FloatPrecision : public BasicCustomDataType<DataType, -1, -2> { 
	public:
		static constexpr DataType BASIC_DECIMAL_SIZE = 2;

	public:
		inline constexpr FloatPrecision(const DataType value = DEFAULT)
			: BasicCustomDataType<DataType, -1, -2>(value)
		{}

		inline constexpr void SetToBasicSizeIfDefault() 	{ if (IsDefault()) Value = BASIC_DECIMAL_SIZE; };
		inline constexpr bool IsBasicSize() 				{ return Value == BASIC_DECIMAL_SIZE; };

		// operator =
		template <typename K>
		requires std::is_convertible_v<DataType, K>
		inline constexpr FloatPrecision& operator=(const K i)	{ Value = static_cast<DataType>(i); return *this; }

		template <typename K, K KDEFAULT, K KNON_VALID>
		requires std::is_convertible_v<DataType, K>
		inline constexpr FloatPrecision& operator=(const BasicCustomDataType<K, KDEFAULT, KNON_VALID>& i)	{ Value = static_cast<DataType>(i.Value); return *this; }
	};

}

namespace ProjectCore::FMT::Detail {

	template <typename CharFormat>
	struct FormatSpecifier {
		FormatSpecifier()
			: Name(nullptr, 0)
			, ValueAsText(nullptr, 0)
			, ValueAsNumber(0)
			, ValueHasText(false)
			, ValueHasNumber(false)
		{}

		FormatSpecifier(const std::basic_string_view<CharFormat>& name)
			: Name(name)
			, ValueAsText(nullptr, 0)
			, ValueAsNumber(0)
			, ValueHasText(false)
			, ValueHasNumber(false)
		{}

		FormatSpecifier(const std::basic_string_view<CharFormat>& name, const std::basic_string_view<CharFormat>& value)
			: Name(name)
			, ValueAsText(value)
			, ValueAsNumber(0)
			, ValueHasText(true)
			, ValueHasNumber(false)
		{}

		FormatSpecifier(const std::basic_string_view<CharFormat>& name, const Detail::DataType value)
			: Name(name)
			, ValueAsText(nullptr, 0)
			, ValueAsNumber(value)
			, ValueHasText(false)
			, ValueHasNumber(true)
		{}

		FormatSpecifier(const std::basic_string_view<CharFormat>& name, const Detail::DataType valueAsNumber, const std::basic_string_view<CharFormat>& valueAsText)
			: Name(name)
			, ValueAsText(valueAsText)
			, ValueAsNumber(valueAsNumber)
			, ValueHasText(true)
			, ValueHasNumber(true)
		{}

		FormatSpecifier(const std::basic_string_view<CharFormat>& name, const std::basic_string_view<CharFormat>& valueAsText, const Detail::DataType valueAsNumber)
			: Name(name)
			, ValueAsText(valueAsText)
			, ValueAsNumber(valueAsNumber)
			, ValueHasText(true)
			, ValueHasNumber(true)
		{}

		static inline constexpr Detail::DataType SpecifierAsNumberNotSpecified						= Detail::FORMAT_DATA_NOT_SPECIFIED;
		static inline constexpr std::basic_string_view<CharFormat> SpecifierAsTextNotSpecified		= std::basic_string_view<CharFormat>("");

		std::basic_string_view<CharFormat>	Name;
		std::basic_string_view<CharFormat>	ValueAsText;
		Detail::DataType					ValueAsNumber;
		bool								ValueHasText;
		bool								ValueHasNumber;
	};

	template <typename CharFormat>
	struct FormatData {
	public:
		using FormatSpecifierType = FormatSpecifier<CharFormat>;

	public:
		bool IsInit								= false;
		bool HasSpec							= false;

		bool KeepNewStyle						= false; 	// W

		bool TrueValue							= false;	// = 
		bool Safe								= false;	// Safe 

		Detail::ValueIntPrint IntPrint			= Detail::ValueIntPrint::Default; 	// B  - X  - O  - D
		Detail::DigitSize DigitSize				= Detail::DigitSize{};				// B? - X? - O? - D?
		Detail::FloatPrecision FloatPrecision	= Detail::FloatPrecision{};			// .

		Detail::PrintStyle PrintStyle			= Detail::PrintStyle::Default;		// U  - L

		Detail::ShiftPrint ShiftPrint			= Detail::ShiftPrint{};				// 0 - ' ' - * .....
		Detail::ShiftSize ShiftSize				= Detail::ShiftSize{};				// <? - >? - ^?
		Detail::ShiftType ShiftType				= Detail::ShiftType::Default;	 	// <  - >  - ^

		std::basic_string_view<CharFormat> NextOverride 		= std::basic_string_view<CharFormat>(nullptr, 0);

		std::uint8_t SpecifierCount								= 0;
		std::array<FormatSpecifier<CharFormat>, 10> Specifier	{};

	public:
		static inline constexpr std::uint8_t NotFound() { return (std::numeric_limits<std::uint8_t>::max)(); }

		FormatSpecifierType* GetSpecifier(const std::basic_string_view<CharFormat>& name) {
			for (std::uint8_t i{}; i < SpecifierCount; ++i)
				if (Specifier[i].Name == name)
					return &Specifier[i];
			return nullptr;
		}

		FormatSpecifierType* GetSpecifierOnlyText(const std::basic_string_view<CharFormat>& name) {
			for (std::uint8_t i{}; i < SpecifierCount; ++i)
				if (Specifier[i].ValueHasText && Specifier[i].Name == name)
					return &Specifier[i];
			return nullptr;
		}

		FormatSpecifierType* GetSpecifierOnlyNumber(const std::basic_string_view<CharFormat>& name) {
			for (std::uint8_t i{}; i < SpecifierCount; ++i)
				if (Specifier[i].ValueHasNumber && Specifier[i].Name == name)
					return &Specifier[i];
			return nullptr;
		}

		const FormatSpecifierType* GetSpecifier(const std::basic_string_view<CharFormat>& name) const {
			for (std::uint8_t i{}; i < SpecifierCount; ++i)
				if (Specifier[i].Name == name)
					return &Specifier[i];
			return nullptr;
		}

		const FormatSpecifierType* GetSpecifierOnlyText(const std::basic_string_view<CharFormat>& name) const {
			for (std::uint8_t i{}; i < SpecifierCount; ++i)
				if (Specifier[i].ValueHasText && Specifier[i].Name == name)
					return &Specifier[i];
			return nullptr;
		}

		const FormatSpecifierType* GetSpecifierOnlyNumber(const std::basic_string_view<CharFormat>& name) const {
			for (std::uint8_t i{}; i < SpecifierCount; ++i)
				if (Specifier[i].ValueHasNumber && Specifier[i].Name == name)
					return &Specifier[i];
			return nullptr;
		}

		std::basic_string_view<CharFormat> GetSpecifierAsText(const std::basic_string_view<CharFormat>& name, const std::basic_string_view<CharFormat>& defaultValue = FormatSpecifierType::SpecifierAsTextNotSpecified) const {
			const FormatSpecifierType* formatSpecifier = GetSpecifierOnlyText(name);
			if (formatSpecifier == nullptr)
				return defaultValue;
			return formatSpecifier->ValueAsText;
		}

		Detail::DataType GetSpecifierAsNumber(const std::basic_string_view<CharFormat>& name, const Detail::DataType defaultValue = FormatSpecifierType::SpecifierAsNumberNotSpecified) const {
			const FormatSpecifierType* formatSpecifier = GetSpecifierOnlyNumber(name);
			if (formatSpecifier == nullptr)
				return defaultValue;
			return formatSpecifier->ValueAsNumber;
		}

		void AddSpecifierForce(const FormatSpecifierType& specifier)
		{
			if (SpecifierCount < Specifier.size())
				Specifier[SpecifierCount++] = specifier;
		}

		void AddSpecifier(const FormatSpecifierType& specifier, bool dontOverride = false) {
			FormatSpecifierType* formatSpecifier = GetSpecifier(specifier.Name);
			if (formatSpecifier == nullptr)
				AddSpecifierForce(specifier);
			else if (dontOverride == false)
			{
				if (specifier.ValueHasText) {
					formatSpecifier->ValueHasText = true;
					formatSpecifier->ValueAsText = specifier.ValueAsText;
				}
				if (specifier.ValueHasNumber) {
					formatSpecifier->ValueHasNumber = true;
					formatSpecifier->ValueAsNumber = specifier.ValueAsNumber;
				}
			}
		}

		void AddSpecifier(const std::basic_string_view<CharFormat>& name, const std::basic_string_view<CharFormat>& value, bool dontOverride = false) {
			FormatSpecifierType* formatSpecifier = GetSpecifier(name);
			if (formatSpecifier == nullptr)
				AddSpecifierForce(FormatSpecifierType(name, value));
			else if (dontOverride == false)
			{
				formatSpecifier->ValueHasText = true;
				formatSpecifier->ValueAsText = value;
			}
		}
		
		void AddSpecifier(const std::basic_string_view<CharFormat>& name, const Detail::DataType value, bool dontOverride = false) {
			FormatSpecifierType* formatSpecifier = GetSpecifier(name);
			if (formatSpecifier == nullptr)
				AddSpecifierForce(FormatSpecifierType(name, value));
			else if (dontOverride == false)
			{
				formatSpecifier->ValueHasNumber = true;
				formatSpecifier->ValueAsNumber = value;
			}
		}

		void AddSpecifier(const std::basic_string_view<CharFormat>& name) {
			FormatSpecifierType* formatSpecifier = GetSpecifier(name);
			if (formatSpecifier == nullptr)
				AddSpecifierForce(FormatSpecifierType(name));
		}

	public:
		template <typename T> void ModifyThrow(const T&) { throw Detail::FMTGivenTypeError{}; }

		void ModifyThrow(const FormatData& given) 					{ *this = given; }

		void ModifyThrow(const Detail::ValueIntPrint& given) 		{ IntPrint = given; }
		void ModifyThrow(const Detail::PrintStyle& given) 			{ PrintStyle = given; }
		void ModifyThrow(const Detail::DigitSize& given) 			{ DigitSize = given; }
		void ModifyThrow(const Detail::ShiftSize& given) 			{ ShiftSize = given; }
		void ModifyThrow(const Detail::FloatPrecision& given) 		{ FloatPrecision = given; }
		void ModifyThrow(const Detail::ShiftPrint& given) 			{ ShiftPrint = given; }
		void ModifyThrow(const Detail::ShiftType& given) 			{ ShiftType = given; }
		void ModifyThrow(const FormatSpecifier<CharFormat>& given) 	{ AddSpecifier(given); }

		template <typename T> bool ModifyTestThrow(const T* given) {
			if (given == nullptr)
				return false;
			ModifyThrow(*given);
			return true;
		}
	};
}