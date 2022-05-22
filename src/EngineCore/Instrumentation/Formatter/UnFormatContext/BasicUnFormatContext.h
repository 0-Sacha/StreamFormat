#pragma once

#include "../Core/Detail/Detail.h"
#include "BaseFormat/UnFormatType.h"
#include "../FormatContext/BasicFormatContext.h"

#include "UnFormatContextArgsTuple.h"

namespace EngineCore::Instrumentation::FMT {
	struct UnFormatContextError
	{
		bool Error					{false};
		std::int16_t FormatPosError	{0};
		std::int16_t BufferPosError	{0};
		UnFormatContextError()
			: Error(false), FormatPosError(0), BufferPosError(0) { }
		UnFormatContextError(std::int16_t formatPosError, std::int16_t bufferPosError)
			: Error(true), FormatPosError(formatPosError), BufferPosError(bufferPosError) { }
		inline operator bool() const { return Error; }
	};

}

namespace EngineCore::Instrumentation::FMT {

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	class BasicUnFormatContext
	{
	public:
		using CharFormatType = CharFormat;
		using CharBufferType = CharBuffer;

		using FormatDataType = FormatData<CharFormat>;
		using FormatSpecifierType = FormatSpecifier<CharFormat>;

		using StringViewFormat = std::basic_string_view<CharFormat>;
		using StringViewBuffer = std::basic_string_view<CharBuffer>;

		using M_Type = BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>;

	public:
		BasicUnFormatContext(const std::basic_string_view<CharFormat>& format, const std::basic_string_view<CharBuffer>& buffer, ContextArgs&& ...args);

		template<typename ParentCharFormat, typename ...ParentContextArgs>
		BasicUnFormatContext(const std::basic_string_view<CharFormat>& format, BasicUnFormatContext<ParentCharFormat, CharBuffer, ParentContextArgs...>& parentContext, ContextArgs&& ...args);

		template<typename ChildCharFormat, typename ...ChildContextArgs>
		inline void UpdateContextFromChild(BasicFormatContext<ChildCharFormat, CharBuffer, ChildContextArgs...>& childContext);

	private:
		Detail::BasicFormatterMemoryBufferIn<CharBuffer>	m_BufferIn;
		Detail::FormatterMemoryFormat<CharFormat>			m_FormatStr;

		Detail::UnFormatContextArgsTuple<ContextArgs...>	m_ContextArgs;

		std::size_t 			m_Indent;

		FormatIdx				m_ValuesIdx;
		FormatDataType			m_FormatData;
		Detail::AnsiTextCurrentColor	m_AnsiTextCurrentColor;
		Detail::AnsiStyle	m_AnsiStyle;
		Detail::AnsiTextCurrentFront	m_AnsiTextCurrentFront;
		Detail::AnsiFormatterChange		m_AnsiFormatterChange;

	public:
		inline Detail::BasicFormatterMemoryBufferIn<CharBuffer>&		BufferIn()			{ return m_BufferIn; }
		inline const Detail::BasicFormatterMemoryBufferIn<CharBuffer>&	BufferIn() const	{ return m_BufferIn; }
		inline Detail::FormatterMemoryFormat<CharFormat>&				FormatStr()			{ return m_FormatStr; }
		inline const Detail::FormatterMemoryFormat<CharFormat>&			FormatStr() const	{ return m_FormatStr; }

		inline Detail::AnsiTextCurrentColor&		GetAnsiTextCurrentColor()		{ return m_AnsiTextCurrentColor; }
		inline const Detail::AnsiTextCurrentColor&	GetAnsiTextCurrentColor() const { return m_AnsiTextCurrentColor; }
		inline Detail::AnsiStyle&		GetAnsiStyle()		{ return m_AnsiStyle; }
		inline const Detail::AnsiStyle&	GetAnsiStyle() const { return m_AnsiStyle; }
		inline Detail::AnsiTextCurrentFront&		GetAnsiTextCurrentFront()		{ return m_AnsiTextCurrentFront; }
		inline const Detail::AnsiTextCurrentFront&	GetAnsiTextCurrentFront() const { return m_AnsiTextCurrentFront; }

		inline Detail::AnsiFormatterChange&			GetAnsiFormatterChange()		{ return m_AnsiFormatterChange; }
		inline const Detail::AnsiFormatterChange&	GetAnsiFormatterChange() const	{ return m_AnsiFormatterChange; }

		inline FormatDataType&			GetFormatData()				{ return m_FormatData; }
		inline const FormatDataType&	GetFormatData() const		{ return m_FormatData; }
		inline FormatDataType			ForwardFormatData() const	{ return m_FormatData; }

		inline std::size_t	GetIndent() const						{ return m_Indent; }

		static inline std::int16_t NoError()						{ return -1; }

	private:
		/////---------- Impl ----------/////
		void ParameterParseDataStyle();
		void ParameterParseDataSpecial();
		void ParameterParseDataCustom();
		void ParameterParseData();
		bool GetFormatIdx(FormatIdx& idx);

		void ParameterParseSpecial();
		void ParameterParseVariable(FormatIdx formatIdx);
		bool ParameterParse();

	private:
		static void ReadAnsiTextColorParameter();
		static void ReadAnsiTextStyleParameter();
		static void ReadAnsiTextFrontParameter();
		static void ReadTimerParameter();
		static void ReadDateParameter();
		void IgnoreParameter();

	public:
		void Run();
		UnFormatContextError SafeRun();

		template<typename NewCharFormat, typename ...NewContextArgs>
		void LittleUnFormat(const std::basic_string_view<NewCharFormat>& format, NewContextArgs&& ...args);
		template<typename CharType, std::size_t SIZE, typename ...NewContextArgs>
		inline void LittleUnFormat(const CharType(&format)[SIZE], NewContextArgs&& ...args) { LittleUnFormat(std::basic_string_view<CharType>(format), std::forward<NewContextArgs>(args)...); }

	public:
		template<typename T> bool FormatReadParameter(T& i);

	public:
		// Other Type from UnFormatType
		template<typename Type>
		inline void ReadType(Type& type)						{ UnFormatType<Detail::GetBaseType<Type>, BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>>::Read(type, *this); }
		template<typename Type, typename ...Rest>
		inline void ReadType(Type& type, Rest&& ...rest)		{ ReadType(type); ReadType(std::forward<Rest>(rest)...); }

		template<typename Type>
		inline void BasicReadType(Type& type)					{ m_BufferIn.BasicReadType(type); }
		template<typename Type, typename ...Rest>
		inline void BasicReadType(Type& type, Rest& ...rest)	{ m_BufferIn.BasicReadType(type); BasicReadType(std::forward<Rest>(rest)...); }

	public:
		inline bool FormatIsEndOfParameter()	{ return m_FormatStr.IsEqualTo('}'); }
		inline void FormatGoToEndOfParameter()	{ while (m_FormatStr.IsNotEqualTo('}') && m_FormatStr.CanMoveForward()) m_FormatStr.ForwardNoCheck(); }
		inline void FormatGoOutOfParameter()	{ while (m_FormatStr.IsNotEqualTo('}') && m_FormatStr.CanMoveForward()) m_FormatStr.ForwardNoCheck(); m_FormatStr.Forward(); }

		inline bool Check() { return m_BufferIn.IsEqualTo(m_FormatStr.Get()); }
		inline bool CheckAndNext() { if (m_BufferIn.IsEqualTo(m_FormatStr.Get())) { m_BufferIn.Forward(); m_FormatStr.Forward(); return true; } return false; }

		template<typename ...CharToTest>
		inline bool CheckUntilNextParameter(const CharToTest ...ele) {
			while (m_FormatStr.IsNotEqualTo('{', ele...) && m_FormatStr.CanMoveForward()) {
				if (!Check()) return false;
				m_FormatStr.ForwardNoCheck(); m_BufferIn.Forward();
			}
			return true;
		}
		template<typename ...CharToTest>
		inline bool CheckUntilEndOfParameter(const CharToTest ...ele) {
			while (m_FormatStr.IsNotEqualTo('}', ele...) && m_FormatStr.CanMoveForward()) {
				if (!Check()) return false;
				m_FormatStr.ForwardNoCheck(); m_BufferIn.Forward();
			}
			return true;
		}
	};
}


