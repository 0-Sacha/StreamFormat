#pragma once

#include "EngineCore/Instrumentation/Formatter/Core/Detail/Detail.h"
#include "EngineCore/Instrumentation/Formatter/Core/Buffer/Buffer.h"

#include "BaseFormat/FormatType.h"
#include "BaseFormat/NamedArgs.h"
#include "BaseFormat/FormatArgs.h"
#include "BaseFormat/STDEnumerable.h"

#include "FormatContextArgsTuple.h"

#include "../Core/FormatterHandler/FormatterHandler.h"

namespace EngineCore::Instrumentation::FMT::Context {

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	class BasicFormatContext : BasicContext<CharFormat>
	{
	public:
		using Base = BasicContext<CharFormat>;

		using Base::CharFormatType;
		using CharBufferType = CharBuffer;
		using Base::FormatDataType;
		using Base::StringViewFormat;
		using StringViewBuffer = std::basic_string_view<CharBuffer>;

		using M_Type = BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>;

	public:
		BasicFormatContext(const std::basic_string_view<CharFormat>& format, CharBuffer* const buffer, const std::size_t bufferSize, ContextArgs &&...args);
		BasicFormatContext(const bool bufferIsAutoResize, const std::basic_string_view<CharFormat>& format, ContextArgs &&...args);

		// Used for LittleFormat
		template<typename ParentCharFormat, typename ...ParentContextArgs>
		BasicFormatContext(const std::basic_string_view<CharFormat>& format, BasicFormatContext<ParentCharFormat, CharBuffer, ParentContextArgs...> &parentContext, ContextArgs &&...args);

	private:
		using Base::m_Format;
		using Base::m_ValuesIndex;
		using Base::m_FormatData;

		Detail::BasicFormatterMemoryBufferOut<CharBuffer>	m_BufferOut;
		Detail::AnsiManger<M_Type>							m_AnsiManager;
		Detail::FormatContextArgsTuple<ContextArgs...> 		m_ContextArgs;

	public:
		using Base::Format;
		using Base::GetFormatData;
		using Base::ForwardFormatData;
		using Base::GetAPI;

		inline Detail::BasicFormatterMemoryBufferOut<CharBuffer>&			BufferOut()			{ return m_BufferOut; }
		inline const Detail::BasicFormatterMemoryBufferOut<CharBuffer>&		BufferOut() const	{ return m_BufferOut; }

		inline Detail::AnsiManger<M_Type>&									GetAnsiManager()		{ return m_AnsiTextCurrentColor; }
		inline const Detail::AnsiManger<M_Type>&							GetAnsiManager() const	{ return m_AnsiTextCurrentColor; }

	public:
		using Base::Run;
		using Base::SafeRun;
		using Base::LittleFormat;

		void Run();

		template<typename NewCharFormat, typename ...NewContextArgs>
		void LittleFormat(const std::basic_string_view<NewCharFormat>& format, NewContextArgs&& ...args);

	public:
		using Base::GetFormatIndexThrow;

	public:
		// TupleInterface
		using Base::GetTypeAtIndexThrow;
		using Base::GetTypeAtIndexAuto;
		using Base::GetIndexOfCurrentNameArg;
		using Base::RunTypeAtIndex;
		
		template <typename T>
		const T& GetTypeAtIndexThrow(const Detail::FormatIndex& index);
		const auto& GetTypeAtIndexAuto(const Detail::FormatIndex& index);

		Detail::FormatIndex GetIndexOfCurrentNameArg();

		void RunTypeAtIndex(const Detail::FormatIndex& index);
		
	private:
		using Base::ParseFormatDataStyle;
		using Base::ParseFormatDataSpecial;
		using Base::ParseFormatDataCustom;
		using Base::ParseFormatData;

		using Base::ParseFormatDataColor;
		using Base::ParseFormatDataStyle;
		using Base::ParseFormatDataFront;
		using Base::ContextStyleSave;
		using Base::ContextStyleRestore;

		using Base::ParseSpecial;
		using Base::ParseVariable;
		using Base::Parse;


		void ParseFormatDataColor();
		void ParseFormatDataStyle();
		void ParseFormatDataFront();
		void ContextStyleSave();
		void ContextStyleRestore();

	private:
		using Base::ParseTimer;
		using Base::ParseDate;

		using Base::ParseColor;
		using Base::ParseStyle;
		using Base::ParseFront;
		using Base::ContextStyleBegin;
		using Base::ContextStyleEnd;

		using Base::ParseSetter;

		void ParseTimer();
		void ParseDate();

		void ParseColor();
		void ParseStyle();
		void ParseFront();
		void ContextStyleBegin();
		void ContextStyleEnd() ;

		void ParseSetter();

	public:
		using Base::FormatReadParameter;

	public:
		using Base::RunType;
		using Base::BasicRunType;

		// Type formating from FormatType<>
		template<typename Type>
		inline void RunType(Type&& type);
		template<typename Type, typename ...Rest>
		inline void WriteType(Type&& type, const Rest&& ...rest)		{ RunType(type, std::forward<Rest>(rest)...); }

		// Only support basic type that are considered as basic by Buffer class
		template<typename Type>
		inline void BasicRunType(Type&& type);
		template<typename Type, typename ...Rest>
		inline void BasicWriteType(Type&& type, const Rest&& ...rest)	{ BasicRunType(type, std::forward<Rest>(rest)...); }

	public:
		using Base::GetStringViewParamUntil;
		using Base::GetStringViewUntil;
		using Base::ReadDataType;

	public:
		void CheckEndStr();

		template<typename CharStr>						inline void PrintCharPt(const CharStr* str)						{ m_BufferOut.WriteCharPt(str); }
		template<typename CharStr>						inline void PrintCharPt(const CharStr* str, std::size_t size)	{ m_BufferOut.WriteCharPt(str, size); }
		template<typename CharStr, std::size_t SIZE>	inline void Print(const CharStr(&str)[SIZE])					{ m_BufferOut.WriteCharPt(str, SIZE); }
		template<typename CharStr>						inline void Print(const std::basic_string_view<CharStr>& str)	{ m_BufferOut.WriteCharPt(str.data(), str.size()); }
		template<typename CharStr>						inline void Print(const std::basic_string<CharStr>& str)		{ Print(static_cast<std::basic_string_view<CharStr>>(str)); }

		template<typename CharStr>						inline void PrintCharPtIndent(const CharStr* str)					{ m_BufferOut.WriteCharPtIndent(str); }
		template<typename CharStr>						inline void PrintCharPtIndent(const CharStr* str, std::size_t size) { m_BufferOut.WriteCharPtIndent(str, size); }
		template<typename CharStr, std::size_t SIZE>	inline void PrintIndent(const CharStr(&str)[SIZE])					{ m_BufferOut.WriteCharPtIndent(str, SIZE); }
		template<typename CharStr>						inline void PrintIndent(const std::basic_string_view<CharStr>& str) { m_BufferOut.WriteCharPtIndent(str.data(), str.size()); }

	public:
		inline void CopyFormatToBuffer() { m_BufferOut.PushBackIndent(m_Format.GetAndForward(), m_Indent); }

		template<typename ...CharToTest> inline void WriteUntilNextParameter(const CharToTest ...ele)	{ while (m_Format.IsNotEqualTo('{', ele...) && m_Format.CanMoveForward())	CopyFormatToBuffer(); }
		template<typename ...CharToTest> inline void WriteUntilEndOfParameter(const CharToTest ...ele)	{ while (m_Format.IsNotEqualTo('}', ele...) && m_Format.CanMoveForward())	CopyFormatToBuffer(); }
	};
}