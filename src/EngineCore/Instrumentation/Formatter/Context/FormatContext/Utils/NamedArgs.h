#pragma once

#include "FormatType.h"

namespace EngineCore::Instrumentation::FMT {
	/////---------- string_view NamedArgs Do not allocate memory (Best) ----------/////
	template<typename T, typename CharName = char>
	struct StringViewNamedArgs
	{
		template<std::size_t SIZE>
		StringViewNamedArgs(const CharName(&name)[SIZE], T&& t)
			: m_Name(name), value(t) {}

		StringViewNamedArgs(const std::basic_string_view<CharName>& name, T&& t)
			: m_Name(name), value(t) {}

		template<std::size_t SIZE>
		StringViewNamedArgs(const CharName(&name)[SIZE], T& t)
			: m_Name(name), value(t) {}

		StringViewNamedArgs(const std::basic_string_view<CharName>& name, T& t)
			: m_Name(name), value(t) {}

	public:
		T& GetValue()											{ return value; }
		const T& GetValue() const								{ return value; }
		std::basic_string_view<CharName> GetName() const		{ return m_Name; }

	protected:
		std::basic_string_view<CharName> m_Name;
		T& value;
	};

	template<typename T, typename CharName, typename FormatContext>
	struct FormatType<StringViewNamedArgs<T, CharName>, FormatContext>
	{
		inline static void Write(const StringViewNamedArgs<T, CharName>& t, FormatContext& context) {
			context.RunType(t.GetValue());
		}
	};


	/////---------- stringNamedArgs Allocate memory (Only if necessary) ----------/////
	template<typename T, typename CharName = char>
	struct StringNamedArgs
	{

		StringNamedArgs(const std::string& str, T&& t)
			: m_Name(str), value(t) {}

		StringNamedArgs(std::string&& str, T&& t)
			: m_Name(std::move(str)), value(t) {}


		StringNamedArgs(const std::string& str, T& t)
			: m_Name(str), value(t) {}

		StringNamedArgs(std::string&& str, T& t)
			: m_Name(std::move(str)), value(t) {}

	public:
		T& GetValue()											{ return value; }
		const T& GetValue() const								{ return value; }
		std::basic_string_view<CharName> GetName() const		{ return m_Name; }

	protected:
		std::basic_string<CharName> m_Name;
		T& value;
	};

	template<typename T, typename CharName, typename FormatContext>
	struct FormatType<StringNamedArgs<T, CharName>, FormatContext>
	{
		inline static void Write(const StringNamedArgs<T, CharName>& t, FormatContext& context) {
			context.RunType(t.GetValue());
		}
	};


	namespace Detail {
		template <typename T>
		struct IsANamedArgs {
		public:
			[[maybe_unused]] inline constexpr static bool value = false;
		};

		template <typename T, typename CharName>
		struct IsANamedArgs<StringViewNamedArgs<T, CharName>> {
			[[maybe_unused]] inline constexpr static bool value = true;
		};

		template <typename T, typename CharName>
		struct IsANamedArgs<StringNamedArgs<T, CharName>> {
			[[maybe_unused]] inline constexpr static bool value = true;
		};

		template <typename T>
		inline constexpr bool IsANamedArgsValue = false;

		template <typename T, typename CharName>
		inline constexpr bool IsANamedArgsValue<StringViewNamedArgs<T, CharName>> = true;

		template <typename T, typename CharName>
		inline constexpr bool IsANamedArgsValue<StringNamedArgs<T, CharName>> = true;
	}
}


#define FORMAT(value)				EngineCore::Instrumentation::FMT::StringViewNamedArgs(#value, value)
#define FORMAT_SV(name, value)		EngineCore::Instrumentation::FMT::StringViewNamedArgs(name, value)

#define FORMAT_STR(name, value)		EngineCore::Instrumentation::FMT::StringNamedArgs(name, value)