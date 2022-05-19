#pragma once

#include "FormatType.h"


namespace EngineCore::Instrumentation::FMT {

	class STDEnumerableUtility {
	public:
		static constexpr std::string_view DefaultJoin	= ", ";
		static constexpr std::string_view DefaultBegin	= "{ ";
		static constexpr std::string_view DefaultEnd	= " }";
	};

	template <typename T, typename CharJoin = char, typename CharBegin = char, typename CharEnd = char>
	class STDEnumerable {
	public:

		explicit inline STDEnumerable(const T& value,
			const std::basic_string_view<CharJoin>& strJoin = ", ",
			const std::basic_string_view<CharBegin>& strBegin = "{ ",
			const std::basic_string_view<CharEnd>& strEnd = " }",
			const Detail::FormatDataType beginIdx = 0,
			const Detail::FormatDataType size = Detail::FORMAT_DATA_NOT_SPECIFIED)
			: m_Value(value)
			, m_StrJoin(strJoin)
			, m_StrBegin(strBegin)
			, m_StrEnd(strEnd)
			, m_BeginIdx(beginIdx)
			, m_Size(size == Detail::FORMAT_DATA_NOT_SPECIFIED ? (Detail::FormatDataType)value.size() - beginIdx : size)
		{
		}

		inline const T& GetValue() const { return m_Value; }

		inline std::basic_string_view<CharEnd>		GetStrJoin() const	{ return m_StrJoin; }
		inline std::basic_string_view<CharBegin>	GetStrBegin() const	{ return m_StrBegin; }
		inline std::basic_string_view<CharEnd>		GetStrEnd() const	{ return m_StrEnd; }

		inline Detail::FormatDataType GetBeginIdx() const	{ return m_BeginIdx; }
		inline Detail::FormatDataType GetSize() const		{ return m_Size; }

	private:
		const T& m_Value;

		std::basic_string_view<CharBegin> m_StrJoin;
		std::basic_string_view<CharBegin> m_StrBegin;
		std::basic_string_view<CharEnd>	m_StrEnd;

		Detail::FormatDataType m_BeginIdx;
		Detail::FormatDataType m_Size;
	};

	template <typename T, typename CharBegin, typename CharJoin, typename CharEnd, typename FormatContext>
	struct FormatType<STDEnumerable<T, CharBegin, CharJoin, CharEnd>, FormatContext> {
		static void Write(const STDEnumerable<T, CharBegin, CharJoin, CharEnd>& enumerable, FormatContext& context) {
			{
				Detail::RestoreIndentFunction restoreIndent(context, enumerable.GetStrEnd(), false);

				context.PrintIndent(enumerable.GetStrBegin());

				context.AddIndent(enumerable.GetStrBegin().size());

				bool first = true;
				std::size_t addindent = 0;
				std::for_each_n(enumerable.GetValue().cbegin() + enumerable.GetBeginIdx(), enumerable.GetSize(), [&](const auto& element) {
					if (first)	first = false;
					else 		context.PrintIndent(enumerable.GetStrJoin());
					{
						Detail::GetIndentFunction getindent(context);
						context.WriteType(element);
						addindent = getindent.GetIndent();
					}
				});

				Detail::GetIndentInfo info(enumerable.GetStrJoin());
				context.AddIndent(info.AddIndent);
				context.AddIndent(addindent);
			}

			context.PrintIndent(enumerable.GetStrEnd());
		}
	};


	template<typename T>
	struct ForwardAsSTDEnumerable {};

	template <typename T, typename FormatContext>
	struct FormatType<ForwardAsSTDEnumerable<T>, FormatContext> {
		static void Write(const T& container, FormatContext& context) {
			STDEnumerable<T> enumerable(container,
				context.GetFormatData().GetSpecifierAsText("join",		STDEnumerableUtility::DefaultJoin),
				context.GetFormatData().GetSpecifierAsText("begin",		STDEnumerableUtility::DefaultBegin),
				context.GetFormatData().GetSpecifierAsText("end",		STDEnumerableUtility::DefaultEnd),
				context.GetFormatData().GetSpecifierAsNumber("begin",	0),
				context.GetFormatData().GetSpecifierAsNumber("size",	Detail::FORMAT_DATA_NOT_SPECIFIED));

			context.WriteType(enumerable);
		}
	};

}