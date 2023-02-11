
#pragma once

#include "FMT/Context/BasicContext/BasicContextInclude.h"

#include "Utils/ParserType.h"

#include "ParserContextArgsTuple.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename CharBuffer>
	class BasicParserContext : public BasicContext<CharFormat, int>
	{
	public:
		using Base = BasicContext<CharFormat, int>;
		using M_Type = BasicParserContext<CharFormat, CharBuffer>;

		friend Base;

		using typename Base::CharFormatType;
		using typename Base::FormatDataType;
		using typename Base::StringViewFormat;
		using typename Base::FormatBufferType;
		using typename Base::ContextArgsInterface;

		using StringViewBuffer	= std::basic_string_view<CharBuffer>;
		using BufferInType		= Detail::BasicFormatterMemoryBufferIn<CharBuffer>;

	public:
		template <std::size_t SIZE>
		explicit BasicParserContext(const CharBuffer (&buffer)[SIZE]);
		explicit BasicParserContext(const CharBuffer* const buffer, const std::size_t size);
		explicit BasicParserContext(const std::basic_string_view<CharBuffer>& buffer);

		~BasicParserContext();

	protected:
		using Base::m_Format;
		using Base::m_ValuesIndex;
		using Base::m_FormatData;
		using Base::m_ContextArgsInterface;

		BufferInType 		m_BufferIn;

	public:
		using Base::Format;
		using Base::GetFormatData;
		using Base::ForwardFormatData;
		using Base::SetFormatData;

		inline BufferInType& BufferIn()					{ return m_BufferIn; }
		inline const BufferInType& BufferIn() const		{ return m_BufferIn; }

	public:
        using Base::Run;

    protected:
        void FormatToParamsString(const CharFormat* buffer, std::size_t size) override {
			m_BufferIn.IsSameForwardThrow(buffer, size);
		}

		void FormatExecParams() override {
			if (Parse() == false)
				if (m_BufferIn.IsEqualToForward('{') == false)
					throw Detail::FMTParseError();
		}

		void SetArgsInterfaceCurrentContex() override                                   { m_ContextArgsInterface->SetContext(this); }

	public:
        template<typename CharType, std::size_t SIZE, typename ...NewContextArgs>
		inline void SubContext(const CharType (&format)[SIZE], NewContextArgs&& ...args)
		{ SubContextFormat(format, SIZE, std::forward<NewContextArgs>(args)...); }

        template<typename NewCharFormat, typename ...NewContextArgs>
        void SubContext(const std::basic_string_view<NewCharFormat>& format, NewContextArgs&& ...args)
		{ SubContextFormat(format.data(), format.size(), std::forward<NewContextArgs>(args)...); }

        template<typename NewCharFormat, typename ...NewContextArgs>
        void SubContext(const std::basic_string<NewCharFormat>& format, NewContextArgs&& ...args)
		{ SubContextFormat(format.data(), format.size(), std::forward<NewContextArgs>(args)...); }

        template<typename NewCharFormat, typename ...NewContextArgs>
        void SubContextFormat(const NewCharFormat* const formatStr, const std::size_t formatStrSize, NewContextArgs&& ...args);

	public:
		using Base::GetFormatIndexThrow;

	protected:
		using Base::ParseFormatDataBase;
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


		void ParseFormatDataColor() override {}
		void ParseFormatDataStyle() override {}
		void ParseFormatDataFront() override {}

		int ContextStyleSave()						{ return 0; }
		void ContextStyleRestore(const int& data)	{ }

	protected:
		using Base::ParseTimer;
		using Base::ParseDate;

		using Base::ParseColor;
		using Base::ParseStyle;
		using Base::ParseFront;
		using Base::ContextStyleBegin;
		using Base::ContextStyleEnd;

		using Base::ParseSetter;

		void ParseTimer() override;
		void ParseDate() override;

		void ParseColor() override			{}
		void ParseStyle() override			{}
		void ParseFront() override			{}
		void ContextStyleBegin() override	{}
		void ContextStyleEnd() override		{}

		void ParseSetter() override;

	public:
		using Base::FormatReadParameterThrow;
		using Base::FormatDataApplyNextOverride;

	public:
		// Type formating from FormatterType<>
		template<typename Type, typename ...Rest>
		inline void RunType(Type& type, Rest&... rest) 				{ RunType(type); RunType(std::forward<Rest>(rest)...); }
		template<typename Type> inline void RunType(Type& type) 	{ ParserType<typename Detail::FormatTypeForwardAs<Detail::GetBaseType<Type>>::Type, M_Type>::Read(type, *this); }

		template<typename Type, typename ...Rest>
		inline void RunSubType(Type& type, Rest& ...rest) 			{ RunSubType(type); RunSubType(std::forward<Rest>(rest)...); }
		template<typename Type> inline void RunSubType(Type& type) 	{
			if (m_FormatData.NextOverride.size() == 0)
				return RunType(type);
			FormatDataType formatDataCopy = m_FormatData;
			FormatDataApplyNextOverride();
			RunType(type); 
			m_FormatData = formatDataCopy;
		}

		// Only support basic type that are considered as basic by Buffer class
		template<typename Type, typename ...Rest>
		inline void BasicRunType(Type& type, Rest&... rest) 			{ BasicRunType(type); BasicRunType(std::forward<Rest>(rest)...); };
		template<typename Type> inline void BasicRunType(Type& type)	{ m_BufferIn.BasicReadType(type); }

		template<typename Type, typename ...Rest>
		inline void BasicRunSubType(Type& type, Rest&... rest) 		 	{ BasicRunSubType(type); BasicRunSubType(std::forward<Rest>(rest)...); };
		template<typename Type> inline void BasicRunSubType(Type& type) {
			if (m_FormatData.NextOverride.size() == 0)
				return BasicRunType(type);
			FormatDataType formatDataCopy = m_FormatData;
			FormatDataApplyNextOverride();
			BasicRunType(type); 
			m_FormatData = formatDataCopy;
		}

		// Type formating from ParserType<>
		template<typename Type, typename ...Rest>
		inline void ReadType(Type& type, Rest&... rest)		{ RunType(type, std::forward<Rest>(rest)...); }
		template<typename Type, typename ...Rest>
		inline void ReadSubType(Type& type, Rest&... rest)	{ RunSubType(type, std::forward<Rest>(rest)...); }

		// Only support basic type that are considered as basic by Buffer class
		template<typename Type, typename ...Rest>
		inline void BasicReadType(Type& type, Rest&... rest)	{ BasicRunType(type, std::forward<Rest>(rest)...); }
		template<typename Type, typename ...Rest>
		inline void BasicSubReadType(Type& type, Rest&... rest)	{ BasicRunSubType(type, std::forward<Rest>(rest)...); }

	public:
		using Base::GetStringViewParamUntil;
		using Base::GetStringViewUntil;
		using Base::ReadDataType;
	};
}

#include "BaseParse/ParseTextPropertiesColor.h"
#include "BaseParse/ParseTextPropertiesStyle.h"
#include "BaseParse/ParseTextPropertiesFront.h"

#include "BaseParse/BaseParser.h"
#include "BaseParse/ParseSTDLib.h"
#include "BaseParse/ParseChrono.h"
