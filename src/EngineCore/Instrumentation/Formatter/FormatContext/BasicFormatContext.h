#pragma once

#include "EngineCore/Instrumentation/Formatter/Core/Detail/Detail.h"
#include "EngineCore/Instrumentation/Formatter/Core/Buffer/Buffer.h"

#include "BaseFormat/FormatType.h"
#include "BaseFormat/NamedArgs.h"
#include "BaseFormat/FormatArgs.h"
#include "BaseFormat/STDEnumerable.h"

#include "FormatContextArgsTuple.h"

#include "../Core/FormatterHandler/FormatterHandler.h"

namespace EngineCore::Instrumentation::FMT {
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	class BasicFormatContext {
	public:
		using CharFormatType = CharFormat;
		using CharBufferType = CharBuffer;

		using FormatDataType		= FormatData<CharFormat>;
		using FormatSpecifierType	= FormatSpecifier<CharFormat>;

		using StringViewFormat = std::basic_string_view<CharFormat>;
		using StringViewBuffer = std::basic_string_view<CharBuffer>;

		using M_Type = BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>;

	public:
		BasicFormatContext(const std::basic_string_view<CharFormat>& format, CharBuffer* const buffer, const std::size_t bufferSize, ContextArgs &&...args);
		BasicFormatContext(const bool bufferIsAutoResize, const std::basic_string_view<CharFormat>& format, ContextArgs &&...args);

		template<typename ParentCharFormat, typename ...ParentContextArgs>
		BasicFormatContext(const std::basic_string_view<CharFormat>& format, BasicFormatContext<ParentCharFormat, CharBuffer, ParentContextArgs...> &parentContext, ContextArgs &&...args);

		template<typename ChildCharFormat, typename ...ChildContextArgs>
		inline void UpdateContextFromChild(BasicFormatContext<ChildCharFormat, CharBuffer, ChildContextArgs...>& childContext);

	private:
		Detail::BasicFormatterMemoryBufferOut<CharBuffer>	m_BufferOut;
		Detail::FormatterMemoryFormat<CharFormat>			m_FormatStr;

		Detail::FormatContextArgsTuple<ContextArgs...> 		m_ContextArgs;

		std::size_t 			m_Indent;

		// For handling color / format data and idx (for not specified parameter)
		FormatIdx						m_ValuesIdx;
		FormatDataType					m_FormatData;
		Detail::AnsiTextCurrentColor	m_AnsiTextCurrentColor;
		Detail::AnsiTextCurrentStyle	m_AnsiTextCurrentStyle;
		Detail::AnsiTextCurrentFront	m_AnsiTextCurrentFront;
		Detail::AnsiFormatterChange		m_AnsiFormatterChange;

	public:
		inline Detail::BasicFormatterMemoryBufferOut<CharBuffer>&			BufferOut()			{ return m_BufferOut; }
		inline const Detail::BasicFormatterMemoryBufferOut<CharBuffer>&		BufferOut() const	{ return m_BufferOut; }
		inline Detail::FormatterMemoryFormat<CharFormat>&				FormatStr()			{ return m_FormatStr; }
		inline const Detail::FormatterMemoryFormat<CharFormat>&			FormatStr() const	{ return m_FormatStr; }

		inline Detail::AnsiTextCurrentColor&		GetAnsiTextCurrentColor()		{ return m_AnsiTextCurrentColor; }
		inline const Detail::AnsiTextCurrentColor&	GetAnsiTextCurrentColor() const	{ return m_AnsiTextCurrentColor; }
		inline Detail::AnsiTextCurrentStyle&		GetAnsiTextCurrentStyle()		{ return m_AnsiTextCurrentStyle; }
		inline const Detail::AnsiTextCurrentStyle&	GetAnsiTextCurrentStyle() const	{ return m_AnsiTextCurrentStyle; }
		inline Detail::AnsiTextCurrentFront&		GetAnsiTextCurrentFront()		{ return m_AnsiTextCurrentFront; }
		inline const Detail::AnsiTextCurrentFront&	GetAnsiTextCurrentFront() const { return m_AnsiTextCurrentFront; }

		inline Detail::AnsiFormatterChange&			GetAnsiFormatterChange()		{ return m_AnsiFormatterChange; }
		inline const Detail::AnsiFormatterChange&	GetAnsiFormatterChange() const	{ return m_AnsiFormatterChange; }

		inline FormatData<CharFormat>&			GetFormatData()				{ return m_FormatData; }
		inline const FormatData<CharFormat>&	GetFormatData() const		{ return m_FormatData; }
		inline FormatData<CharFormat>			ForwardFormatData() const	{ return m_FormatData; }

		inline std::size_t GetIndent() const					{ return m_Indent; }
		inline void SetIndent(const std::size_t indent) 		{ m_Indent = indent; }
		inline void AddIndent(const std::size_t indent) 		{ m_Indent += indent; }
		void SetIndent() 										{ m_Indent = m_BufferOut.GetBufferCurrentSize() - m_BufferOut.GetNoStride(); }

	public:
		inline static FormatterHandler& GetAPI()				{ return FormatterHandler::GetInstance(); }

	private:
		void ParameterParseDataStyle();
		void ParameterParseDataSpecial();
		void ParameterParseDataCustom();
		void ParameterParseData();
		bool GetFormatIdx(FormatIdx& idx);

		void ParameterParseSpecial();
		void ParameterParseVariable(FormatIdx formatIdx);
		bool ParameterParse();

	public:
		void Run();
		void SafeRun();

		template<typename NewCharFormat, typename ...NewContextArgs>
		void LittleFormat(const std::basic_string_view<NewCharFormat>& format, NewContextArgs&& ...args);
		template<typename CharType, std::size_t SIZE, typename ...NewContextArgs>
		inline void LittleFormat(const CharType (&format)[SIZE], NewContextArgs&& ...args)				{ LittleFormat(std::basic_string_view<CharType>(format), std::forward<NewContextArgs>(args)...); }

	private:
		template<typename CharList, std::size_t SIZE>
		std::uint8_t GetWordFromList(const std::basic_string_view<CharList> (&formatTypes)[SIZE]);

		/////---------- ReadTimerParameter ----------/////
		void ReadTimerParameter();

		/////---------- ReadDateParameter ----------/////
		void ReadDateParameter();

		/////---------- ReadAnsiTextColorParameter ----------/////
		void ReadAnsiTextColorParameter();
		std::uint8_t GetColorCode();
		std::uint8_t GetColorFG();
		std::uint8_t GetColorBG();
		void ReloadColor(const Detail::AnsiTextCurrentColor& targetColor, const Detail::AnsiTextColorChange& changeColor);

		/////---------- ReadTextFormatStyleParameter ----------/////
		void ReadAnsiTextStyleParameter();
		void WriteStyleParameter();
		void ReloadStyle(const Detail::AnsiTextCurrentStyle& targetStyle, const Detail::AnsiTextStyleChange& changeStyle);

		/////---------- ReadAnsiTextFrontParameter ----------/////
		void ReadAnsiTextFrontParameter();
		std::uint8_t GetFrontCode();
		void ReloadFront(const Detail::AnsiTextCurrentFront& targetFront, const Detail::AnsiTextFrontChange& changeFront);

		/////---------- ReadSetterParameter ----------/////
		void ReadSetterParameter();

	public:
		void CheckEndStr();

	public:
		// Unsigned-Integer Only
		template<typename T> bool FormatReadParameter(T& i);

	public:
		// Type formating from FormatType<>
		template<typename Type>
		inline void WriteType(Type&& type)							{ FormatType<Detail::GetBaseType<Type>, BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>>::Write(type, *this); }
		template<typename Type, typename ...Rest>
		inline void WriteType(Type&& type, const Rest&& ...rest)	{ WriteType(type); WriteType(std::forward<Rest>(rest)...); }

		// only support basic type that are considered as basic by the BufferOut class
		template<typename Type>
		inline void BasicWriteType(Type&& type)						{ m_BufferOut.BasicWriteType(type); }
		template<typename Type, typename ...Rest>
		inline void BasicWriteType(Type&& type, Rest&& ...rest)		{ m_BufferOut.BasicWriteType(type); BasicWriteType(std::forward<Rest>(rest)...); }


		template<typename CharStr>						inline void PrintCharPt(const CharStr* str)						{ m_BufferOut.WriteCharPt(str); }
		template<typename CharStr>						inline void PrintCharPt(const CharStr* str, std::size_t size)	{ m_BufferOut.WriteCharPt(str, size); }
		template<typename CharStr, std::size_t SIZE>	inline void Print(const CharStr(&str)[SIZE])					{ m_BufferOut.WriteCharPt(str, SIZE); }
		template<typename CharStr>						inline void Print(const std::basic_string_view<CharStr>& str)	{ m_BufferOut.WriteCharPt(str.data(), str.size()); }
		template<typename CharStr>						inline void Print(const std::basic_string<CharStr>& str)		{ Print(static_cast<std::basic_string_view<CharStr>>(str)); }

		template<typename CharStr>						inline void PrintCharPtIndent(const CharStr* str)					{ m_BufferOut.WriteCharPtIndent(str, m_Indent); }
		template<typename CharStr>						inline void PrintCharPtIndent(const CharStr* str, std::size_t size) { m_BufferOut.WriteCharPtIndent(str, size, m_Indent); }
		template<typename CharStr, std::size_t SIZE>	inline void PrintIndent(const CharStr(&str)[SIZE])					{ m_BufferOut.WriteCharPtIndent(str, SIZE, m_Indent); }
		template<typename CharStr>						inline void PrintIndent(const std::basic_string_view<CharStr>& str) { m_BufferOut.WriteCharPtIndent(str.data(), str.size(), m_Indent); }

	public:
		inline void CopyFormatToBuffer() { m_BufferOut.PushBackIndent(m_FormatStr.GetAndForward(), m_Indent); }

		template<typename ...CharToTest> inline void WriteUntilNextParameter(const CharToTest ...ele)	{ while (m_FormatStr.IsNotEqualTo('{', ele...) && m_FormatStr.CanMoveForward())	CopyFormatToBuffer(); }
		template<typename ...CharToTest> inline void WriteUntilEndOfParameter(const CharToTest ...ele)	{ while (m_FormatStr.IsNotEqualTo('}', ele...) && m_FormatStr.CanMoveForward())	CopyFormatToBuffer(); }

	public:

		void NewLineIndent()
		{
			m_BufferOut.PushBack('\n');
			m_BufferOut.PushBack(' ', m_Indent);
		}
	};
}