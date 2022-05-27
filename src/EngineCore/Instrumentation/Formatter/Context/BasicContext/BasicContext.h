#pragma once

#include "EngineCore/Instrumentation/Formatter/Core/Detail/Detail.h"
#include "EngineCore/Instrumentation/Formatter/Core/Buffer/Buffer.h"
#include "EngineCore/Instrumentation/Formatter/Core/FormatterHandler/FormatterHandler.h"

namespace EngineCore::Instrumentation::FMT::Context {
	template<typename CharFormat, typename ContextPackageSaving>
	class BasicContext {
	public:
		using CharFormatType 		= CharFormat;

		using FormatDataType		= Detail::FormatData<CharFormat>;
		using FormatSpecifierType	= Detail::FormatSpecifier<CharFormat>;

		using FormatBufferType		= Detail::FormatterMemoryFormat<CharFormat>;

		using StringViewFormat 		= std::basic_string_view<CharFormat>;

	public:
		explicit BasicContext(const std::basic_string_view<CharFormat>& format, const std::size_t maxIndex);

		template<typename NewCharFormat>
		explicit BasicContext(const std::basic_string_view<CharFormat>& format, BasicContext<NewCharFormat, ContextPackageSaving>& parent, const std::size_t maxIndex);

	protected:
		FormatBufferType		m_Format;
		Detail::FormatIndex		m_ValuesIndex;
		FormatDataType			m_FormatData;

	public:
		inline FormatBufferType&		Format()					{ return m_Format; }
		inline const FormatBufferType&	Format() const				{ return m_Format; }

		inline FormatDataType&			GetFormatData()				{ return m_FormatData; }
		inline const FormatDataType&	GetFormatData() const		{ return m_FormatData; }
		inline FormatDataType			ForwardFormatData() const	{ return m_FormatData; }

	public:
		inline static FormatterHandler& GetAPI()					{ return FormatterHandler::GetInstance(); }

	public:
		void Run() 		{ throw Detail::FormatShouldNotEndHere(); }
		void SafeRun();

		template<typename NewCharFormat, typename ...NewContextArgs>
		void LittleFormat(const std::basic_string_view<NewCharFormat>& format, NewContextArgs&& ...args) { throw Detail::FormatShouldNotEndHere(); }
		template<typename CharType, std::size_t SIZE, typename ...NewContextArgs>
		inline void LittleFormat(const CharType (&format)[SIZE], NewContextArgs&& ...args)
		{ LittleFormat(std::basic_string_view<CharType>(format), std::forward<NewContextArgs>(args)...); }

	public:
		Detail::FormatIndex GetFormatIndexThrow();

	public:
		// TupleInterface
		template <typename T>
		const T& GetTypeAtIndexThrow(const Detail::FormatIndex& index) 		{ throw Detail::FormatShouldNotEndHere(); }
		Detail::FormatIndex GetIndexOfCurrentNameArg() 						{ throw Detail::FormatShouldNotEndHere(); }
		void RunTypeAtIndex(const Detail::FormatIndex& index) 				{ throw Detail::FormatShouldNotEndHere(); }
		
		template <typename T>
		bool RunFuncFromTypeAtIndex(const Detail::FormatIndex& index, std::function<void (const T&)> func) { throw Detail::FormatShouldNotEndHere(); }

	protected:
		void ParseFormatDataBase();
		void ParseFormatDataSpecial();
		void ParseFormatDataCustom();
		void ParseFormatData();

		void ParseFormatDataColor() 	{ throw Detail::FormatShouldNotEndHere(); }
		void ParseFormatDataStyle() 	{ throw Detail::FormatShouldNotEndHere(); }
		void ParseFormatDataFront() 	{ throw Detail::FormatShouldNotEndHere(); }
		ContextPackageSaving ContextStyleSave() 					{ throw Detail::FormatShouldNotEndHere(); }
		void ContextStyleRestore(const ContextPackageSaving&) 		{ throw Detail::FormatShouldNotEndHere(); }

		void ParseSpecial();
		void ParseVariable(Detail::FormatIndex formatIdx);
		bool Parse();

	protected:
		void ParseTimer() 			{ throw Detail::FormatShouldNotEndHere(); }
		void ParseDate() 			{ throw Detail::FormatShouldNotEndHere(); }

		void ParseColor() 			{ throw Detail::FormatShouldNotEndHere(); }
		void ParseStyle() 			{ throw Detail::FormatShouldNotEndHere(); }
		void ParseFront() 			{ throw Detail::FormatShouldNotEndHere(); }
		void ContextStyleBegin() 	{ throw Detail::FormatShouldNotEndHere(); }
		void ContextStyleEnd() 		{ throw Detail::FormatShouldNotEndHere(); }

		void ParseSetter() 			{ throw Detail::FormatShouldNotEndHere(); }

	public:
		template<typename T> void FormatReadParameterThrow(T& i);

	public:
		// Type formating from FormatType<>
		template<typename Type>
		inline void RunType(Type&& type) 						{ throw Detail::FormatShouldNotEndHere(); }
		template<typename Type, typename ...Rest>
		inline void RunType(Type&& type, const Rest&& ...rest) 	{ RunType(type); RunType(std::forward<Rest>(rest)...); }

		// Only support basic type that are considered as basic by Buffer class
		template<typename Type>
		inline void BasicRunType(Type&& type) 					{ throw Detail::FormatShouldNotEndHere(); }
		template<typename Type, typename ...Rest>
		inline void BasicRunType(Type&& type, Rest&& ...rest) 	{ BasicRunType(type); BasicRunType(std::forward<Rest>(rest)...); };

	public:
		template <typename ...CharToTest>
		inline StringViewFormat GetStringViewParamUntil(CharToTest ...c) {
			const char* namePos = m_Format.GetBufferCurrentPos();
			m_Format.ParamGoTo(c...);
			return StringViewFormat(namePos, m_Format.GetBufferCurrentPos() - namePos);
		}

		template <typename ...CharToTest>
		inline StringViewFormat GetStringViewUntil(CharToTest ...c) {
			const char* namePos = m_Format.GetBufferCurrentPos();
			m_Format.GoTo(c...);
			return StringViewFormat(namePos, m_Format.GetBufferCurrentPos() - namePos);
		}

		inline Detail::DataType ReadDataType()
		{
			Detail::DataType res;
			m_Format.ReadInt(res);
			return res;
		}
	};
}