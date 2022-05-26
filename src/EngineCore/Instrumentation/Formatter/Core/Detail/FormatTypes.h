#pragma once

#include "Base.h"

namespace EngineCore::Instrumentation::FMT::Detail {
	
	template<typename T> struct ForwardAsInt;
	template<typename T> struct ForwardAsUInt;
	template<typename T> struct ForwardAsFloat;
	template<typename CharType> struct ForwardAsChar {};
	template<typename CharType, std::size_t SIZE> struct ForwardAsCharArray {};
	template<typename CharType> struct ForwardAsCharPt {};

	enum class ValueIntPrint : DataType {
		Int,
		Bin,
		Hex,
		Oct,
		Default = Int
	};

	enum class ShiftType : DataType {
		Nothing,
		Right,
		Left,
		Center,
		Default = Nothing
	};

	enum class ShiftPrint : DataType {
		Space,
		Zeros,
		Default = Space
	};

	enum class PrintStyle : DataType {
		UpperCase,
		LowerCase,
		Nothing,
		Default = UpperCase
	};

}

namespace EngineCore::Instrumentation::FMT::Detail {

	template <typename CharFormat>
	struct FormatSpecifier {
		FormatSpecifier()
			: Name(nullptr, 0)
			, ValueAsText(nullptr, 0)
			, ValueAsNumber(0)
			, ValueIsText(true) {}

		FormatSpecifier(const std::basic_string_view<CharFormat>& name, const std::basic_string_view<CharFormat>& value)
			: Name(name)
			, ValueAsText(value)
			, ValueAsNumber(0)
			, ValueIsText(true) {}

		FormatSpecifier(const std::basic_string_view<CharFormat>& name, const Detail::DataType value)
			: Name(name)
			, ValueAsText(nullptr, 0)
			, ValueAsNumber(value)
			, ValueIsText(false) {}

		static inline constexpr Detail::DataType SpecifierAsNumberNotSpecified()				{ return Detail::FORMAT_DATA_NOT_SPECIFIED; }
		static inline constexpr std::basic_string_view<CharFormat> SpecifierAsTextNotSpecified()	{ return std::basic_string_view<CharFormat>(""); }

		std::basic_string_view<CharFormat>	Name;
		std::basic_string_view<CharFormat>	ValueAsText;
		Detail::DataType				ValueAsNumber;
		bool ValueIsText;
	};

	template <typename CharFormat>
	struct FormatData {
	public:
		explicit FormatData()
			: IsInit(false)
			, HasSpec(false)

			, TrueValue(false)
			, Safe(false)

			, IntPrint(::EngineCore::Instrumentation::FMT::Detail::ValueIntPrint::Default)
			, DigitSize(Detail::DIGIT_SIZE_NOT_SPECIFIED)
			, FloatPrecision(Detail::FLOAT_PRECISION_NOT_SPECIFIED)

			, PrintStyle(Detail::PrintStyle::Default)

			, ShiftPrint(::EngineCore::Instrumentation::FMT::Detail::ShiftPrint::Default)
			, ShiftType(::EngineCore::Instrumentation::FMT::Detail::ShiftType::Default)
			, ShiftValue(Detail::SHIFT_NOT_SPECIFIED)

			, SpecifierCount(0)

			, AnsiTextColorChange()
			, AnsiStyleChange()
			, AnsiFrontChange()
		{}

		template <typename CharFormatOther>
		explicit FormatData(const FormatData<CharFormatOther>& other)
			: IsInit(other.IsInit)
			, HasSpec(other.HasSpec)

			, TrueValue(other.TrueValue)
			, Safe(other.Safe)

			, IntPrint(other.IntPrint)
			, DigitSize(other.DigitSize)
			, FloatPrecision(other.FloatPrecision)

			, PrintStyle(other.PrintStyle)

			, ShiftPrint(other.ShiftPrint)
			, ShiftType(other.ShiftType)
			, ShiftValue(other.ShiftValue)

			, SpecifierCount(other.SpecifierCount)
			, Specifier(other.Specifier)

			, AnsiTextColorChange()
			, AnsiStyleChange()
			, AnsiFrontChange()
		{}

		explicit FormatData(bool hasSpec

			, bool baseValue = false
			, bool safe = false

			, Detail::ValueIntPrint intPrint		= Detail::ValueIntPrint::Default
			, Detail::DataType digitSize		= Detail::DIGIT_SIZE_NOT_SPECIFIED
			, Detail::DataType floatPrecision = Detail::FLOAT_PRECISION_NOT_SPECIFIED

			, Detail::PrintStyle printStyle			= Detail::PrintStyle::Default 

			, Detail::ShiftPrint shiftPrint		= Detail::ShiftPrint::Default
			, Detail::ShiftType shiftType		= Detail::ShiftType::Default
			, Detail::DataType shiftValue = Detail::SHIFT_NOT_SPECIFIED)

			: IsInit(true)
			, HasSpec(hasSpec)

			, TrueValue(baseValue)
			, Safe(safe)

			, IntPrint(intPrint)
			, DigitSize(digitSize)
			, FloatPrecision(floatPrecision)

			, PrintStyle(printStyle)

			, ShiftPrint(shiftPrint)
			, ShiftType(shiftType)
			, ShiftValue(shiftValue)

			, SpecifierCount(0)

			, AnsiTextColorChange()
			, AnsiStyleChange()
			, AnsiFrontChange()
		{}


		FormatData& operator=(const FormatData& other) {
			std::memcpy(this, &other, sizeof(FormatData));
			AnsiTextColorChange = Detail::AnsiTextColorChange();
			AnsiStyleChange = Detail::AnsiStyleChange();
			AnsiFrontChange = Detail::AnsiFrontChange();
			return *this;
		}

	public:
		inline void Clone(const FormatData& other) 	{ std::memcpy(this, &other, sizeof(FormatData)); }

	public:
		bool IsInit;
		bool HasSpec;

		bool TrueValue;							// = 
		bool Safe;								// Safe 

		Detail::ValueIntPrint IntPrint; 		// B  - X  - O  - D
		Detail::DataType DigitSize;		// B? - X? - O? - D?
		Detail::DataType FloatPrecision;	// .

		Detail::PrintStyle PrintStyle;			// U  - L

		Detail::ShiftPrint ShiftPrint;			// <  - >  - ^
		Detail::DataType ShiftValue;		// <? - >? - ^?
		Detail::ShiftType ShiftType; 			// 0

		std::uint8_t SpecifierCount;
		std::array<FormatSpecifier<CharFormat>, 10> Specifier;

		Detail::AnsiTextColorChange AnsiTextColorChange;
		Detail::AnsiStyleChange AnsiStyleChange;
		Detail::AnsiFrontChange AnsiFrontChange;

	public:
		static inline constexpr std::uint8_t NotFound() { return (std::numeric_limits<std::uint8_t>::max)(); }

		std::basic_string_view<CharFormat> GetSpecifierAsText(const std::basic_string_view<CharFormat>& str, const std::basic_string_view<CharFormat>& defaultValue = FormatSpecifier<CharFormat>::SpecifierAsTextNotSpecified()) const {
			for (auto i = 0; i < SpecifierCount; ++i)
				if (Specifier[i].ValueIsText == true && Specifier[i].Name == str)
					return Specifier[i].ValueAsText;
			return defaultValue;
		}

		Detail::DataType GetSpecifierAsNumber(const std::basic_string_view<CharFormat>& str, const Detail::DataType defaultValue = FormatSpecifier<CharFormat>::SpecifierAsNumberNotSpecified()) const {
			for (std::uint8_t i = 0; i < SpecifierCount; ++i)
				if (Specifier[i].ValueIsText == false && Specifier[i].Name == str)
					return Specifier[i].ValueAsNumber;
			return defaultValue;
		}

		void AddSpecifier(const FormatSpecifier<CharFormat>& specifier)														{ if (SpecifierCount < Specifier.size()) Specifier[SpecifierCount++] = specifier; }
		void AddSpecifier(const std::basic_string_view<CharFormat>& name, const std::basic_string_view<CharFormat>& value)	{ AddSpecifier(FormatSpecifier<CharFormat>(name, value)); }
		void AddSpecifier(const std::basic_string_view<CharFormat>& name, const Detail::DataType value)				{ AddSpecifier(FormatSpecifier<CharFormat>(name, value)); }

	};
}