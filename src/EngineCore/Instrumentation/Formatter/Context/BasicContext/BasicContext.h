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
	template<typename CharFormat, typename ContextPackageSaving>
	class BasicContext {
	public:
		using CharFormatType = CharFormat;

		using FormatDataType		= FormatData<CharFormat>;
		using FormatSpecifierType	= FormatSpecifier<CharFormat>;

		using FormatBufferType	= Detail::FormatterMemoryFormat<CharFormat>;

		using StringViewFormat = std::basic_string_view<CharFormat>;

	public:
		explicit BasicContext(const std::basic_string_view<CharFormat>& format);

	private:
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
		void Run() 		= 0;
		void SafeRun();

		template<typename NewCharFormat, typename ...NewContextArgs>
		void LittleFormat(const std::basic_string_view<NewCharFormat>& format, NewContextArgs&& ...args) = 0;
		template<typename CharType, std::size_t SIZE, typename ...NewContextArgs>
		inline void LittleFormat(const CharType (&format)[SIZE], NewContextArgs&& ...args)
		{ LittleFormat(std::basic_string_view<CharType>(format), std::forward<NewContextArgs>(args)...); }

	public:
		Detail::FormatIndex GetFormatIndexThrow();

	public:
		// TupleInterface
		template <typename T>
		const T& GetTypeAtIndexThrow(const Detail::FormatIndex& index) 		= 0;
		const auto& GetTypeAtIndexAuto(const Detail::FormatIndex& index) 	= 0;

		Detail::FormatIndex GetIndexOfCurrentNameArg() 						= 0;

		void RunTypeAtIndex(const Detail::FormatIndex& index) 				= 0;
		
	private:
		void ParseFormatDataBase();
		void ParseFormatDataSpecial();
		void ParseFormatDataCustom();
		void ParseFormatData();

		void ParseFormatDataColor() 	= 0;
		void ParseFormatDataStyle() 	= 0;
		void ParseFormatDataFront() 	= 0;
		ContextPackageSaving ContextStyleSave() 					= 0;
		void ContextStyleRestore(const ContextPackageSaving&) 		= 0;

		void ParseSpecial();
		void ParseVariable(FormatIndex formatIdx);
		bool Parse();

	private:
		void ParseTimer() 			= 0;
		void ParseDate() 			= 0;

		void ParseColor() 			= 0;
		void ParseStyle() 			= 0;
		void ParseFront() 			= 0;
		void ContextStyleBegin() 	= 0;
		void ContextStyleEnd() 		= 0;

		void ParseSetter() 			= 0;

	public:
		template<typename T> void FormatReadParameterThrow(T& i);

	public:
		// Type formating from FormatType<>
		template<typename Type>
		inline void RunType(Type&& type) 						= 0;
		template<typename Type, typename ...Rest>
		inline void RunType(Type&& type, const Rest&& ...rest) 	{ RunType(type); RunType(std::forward<Rest>(rest)...); }

		// Only support basic type that are considered as basic by Buffer class
		template<typename Type>
		inline void BasicRunType(Type&& type) 					= 0;
		template<typename Type, typename ...Rest>
		inline void BasicRunType(Type&& type, Rest&& ...rest) 	{ BasicRunType(type); BasicRunType(std::forward<Rest>(rest)...); };

	public:
		inline StringViewFormat GetStringViewParamUntil(CharFormat... c) {
			const char* namePos = m_Format.GetBufferCurrentPos();
			m_Format.ParamGoTo(c);
			return StringViewFormat(namePos, m_Format.GetBufferCurrentPos() - namePos);
		}

		inline StringViewFormat GetStringViewUntil(CharFormat... c) {
			const char* namePos = m_Format.GetBufferCurrentPos();
			m_Format.GoTo(c);
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