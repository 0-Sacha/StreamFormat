
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

		using CharBufferType	= CharBuffer;
		using StringViewBuffer	= std::basic_string_view<CharBuffer>;
		using BufferInType		= Detail::BasicFormatterMemoryBufferIn<CharBuffer>;

	public:
		BasicParserContext(const std::basic_string_view<CharBuffer>& buffer);

		template<typename ParentCharFormat>
		BasicParserContext(BasicParserContext<ParentCharFormat, CharBuffer>& parentContext);

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
		using Base::SafeRun;
		void RunImpl();
		void SetArgsInterfaceCurrentContex() override { m_ContextArgsInterface->SetContext(this); }

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
		inline void BasicSubReadType(Type& type, Rest&... rest)	{ BasicSubRunType(type, std::forward<Rest>(rest)...); }

	public:
		using Base::GetStringViewParamUntil;
		using Base::GetStringViewUntil;
		using Base::ReadDataType;

	public:
		inline bool FormatIsEndOfParameter()	{ return m_Format.IsEqualTo('}'); }
		inline void FormatGoToEndOfParameter()	{ while (m_Format.IsNotEqualTo('}') && m_Format.CanMoveForward()) m_Format.ForwardNoCheck(); }
		inline void FormatGoOutOfParameter()	{ while (m_Format.IsNotEqualTo('}') && m_Format.CanMoveForward()) m_Format.ForwardNoCheck(); m_Format.Forward(); }

		inline bool Check()						{ return m_BufferIn.IsEqualTo(m_Format.Get()); }
		inline bool CheckAndNext()				{ if (m_BufferIn.IsEqualTo(m_Format.Get())) { m_BufferIn.Forward(); m_Format.Forward(); return true; } return false; }

		template<typename ...CharToTest>
		inline bool CheckUntilNextParameter(const CharToTest ...ele) {
			while (m_Format.IsNotEqualTo('{', ele...) && m_Format.CanMoveForward()) {
				if (!Check()) return false;
				m_Format.ForwardNoCheck(); m_BufferIn.Forward();
			}
			return true;
		}

		template<typename ...CharToTest>
		inline bool CheckUntilEndOfParameter(const CharToTest ...ele) {
			while (m_Format.IsNotEqualTo('}', ele...) && m_Format.CanMoveForward()) {
				if (!Check()) return false;
				m_Format.ForwardNoCheck(); m_BufferIn.Forward();
			}
			return true;
		}
	};
}

#include "BaseParse/ParseTextPropertiesColor.h"
#include "BaseParse/ParseTextPropertiesStyle.h"
#include "BaseParse/ParseTextPropertiesFront.h"

#include "BaseParse/BaseParser.h"
#include "BaseParse/ParseSTDLib.h"
#include "BaseParse/ParseChrono.h"
