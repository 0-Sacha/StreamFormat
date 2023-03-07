#pragma once

#include "ProjectCore/Core/Core.h"

#include <string>

namespace ProjectCore::FMT::Detail {

	/////---------- Const PT ----------/////

	template<typename T>
	struct RemoveConstPt
	{
		using type = T;
	};

	template<typename T>
	struct RemoveConstPt<T*>
	{
		using type = T*;
	};

	template<typename T>
	struct RemoveConstPt<const T*>
	{
		using type = T*;
	};

	template<typename T>
	using GetBaseType = typename RemoveConstPt<std::remove_cv_t<std::remove_reference_t<T>>>::type;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	template<typename T>
	struct IsCharType {
		using BaseType = GetBaseType<T>;
		static constexpr bool Value = std::is_same_v<BaseType, char>
								   || std::is_same_v<BaseType, wchar_t>
								   || std::is_same_v<BaseType, char8_t>
								   || std::is_same_v<BaseType, char16_t>
								   || std::is_same_v<BaseType, char32_t>;
	};

	template<typename T>
	struct IsFmtConvertible {
		static constexpr bool Value = std::is_convertible_v<T, std::basic_string_view<char>>
				  				   || std::is_convertible_v<T, std::basic_string_view<wchar_t>>
				  				   || std::is_convertible_v<T, std::basic_string_view<char8_t>>
				  				   || std::is_convertible_v<T, std::basic_string_view<char16_t>>
				  				   || std::is_convertible_v<T, std::basic_string_view<char32_t>>;
	};

	template<typename T>
	struct IsFmtConvertible<std::basic_string<T>> {
		static constexpr bool Value = true;
	};

	template<typename T>
	struct IsFmtConvertible<std::basic_string_view<T>> {
		static constexpr bool Value = true;
	};

	template<typename T, std::size_t SIZE>
	requires IsCharType<T>::Value
	struct IsFmtConvertible<T[SIZE]> {
		static constexpr bool Value = true;
	};

	template<typename T>
	requires IsCharType<T>::Value
		struct IsFmtConvertible<T*> {
		static constexpr bool Value = true;
	};


	template<typename T>
	struct GetFmtBaseType {
		using Type = void;
	};
	
	template<typename T>
	struct GetFmtBaseType<std::basic_string<T>> {
		using Type = GetBaseType<T>;
	};

	template<typename T>
	struct GetFmtBaseType<std::basic_string_view<T>> {
		using Type = GetBaseType<T>;
	};

	template<typename T, std::size_t SIZE>
	requires IsCharType<T>::Value
		struct GetFmtBaseType<T[SIZE]> {
		using Type = GetBaseType<T>;
	};

	template<typename T>
	requires IsCharType<T>::Value
		struct GetFmtBaseType<T*> {
		using Type = GetBaseType<T>;
	};
}
