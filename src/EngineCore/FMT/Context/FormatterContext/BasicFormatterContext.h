#pragma once

#include "FMT/Context/BasicContext/BasicContextInclude.h"

#include "Utils/FormatterType.h"
#include "Utils/NamedArgs.h"
#include "Utils/IndexArgs.h"
#include "Utils/STDEnumerable.h"

#include "FMT/Context/BasicContext/TextPropertiesParser.h"

#include "FormatterContextArgsTuple.h"

namespace EngineCore::FMT::Context {
   
    template<typename CharFormat, typename CharBuffer>
    class BasicFormatterContext : public BasicContext<CharFormat, Detail::TextProperties::Properties>
    {
    public:
        using Base = BasicContext<CharFormat, Detail::TextProperties::Properties>;
        using M_Type = BasicFormatterContext<CharFormat, CharBuffer>;

        friend Base;

        using typename Base::CharFormatType;
        using typename Base::FormatDataType;
        using typename Base::StringViewFormat;
        using typename Base::FormatBufferType;
        using typename Base::ContextArgsInterface;
        
        using StringViewBuffer 	    = std::basic_string_view<CharBuffer>;
        using BufferOutType 	    = Detail::BasicFormatterMemoryBufferOut<CharBuffer>;
        using TextPropertiesParser  = Detail::TextPropertiesParser<M_Type>;

    public:
        BasicFormatterContext(Detail::BasicBufferManager<CharBuffer>& bufferManager);
	    BasicFormatterContext(Detail::BasicBufferManager<CharBuffer>& bufferManager, const Detail::TextProperties::Properties* parentContextProperties);
	    ~BasicFormatterContext();

    protected:
        using Base::m_Format;
        using Base::m_ValuesIndex;
        using Base::m_FormatData;
        using Base::m_ContextArgsInterface;

        BufferOutType 		                    m_BufferOut;
        TextPropertiesParser 	                m_TextPropertiesParser;

    public:
        using Base::Format;
        using Base::GetFormatData;
        using Base::ForwardFormatData;
        using Base::SetFormatData;
        using Base::GetContextArgsInterface;

        inline BufferOutType&			    BufferOut()			    { return m_BufferOut; }
        inline const BufferOutType&		    BufferOut() const	    { return m_BufferOut; }

        inline TextPropertiesParser&			GetTextPropertiesParser()		{ return m_TextPropertiesParser; }
        inline const TextPropertiesParser&		GetTextPropertiesParser() const	{ return m_TextPropertiesParser; }

    public:
        using Base::Run;
    
    protected:
        void FormatToParamsString(const CharFormat* buffer, std::size_t size) override  { Print(buffer, size); }
		void FormatExecParams() override                                                { if (!Parse()) m_BufferOut.PushBack('{'); }
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

        void ParseFormatDataColor() override { m_TextPropertiesParser.ParseColor(); }
        void ParseFormatDataStyle() override { m_TextPropertiesParser.ParseStyle(); }
        void ParseFormatDataFront() override { m_TextPropertiesParser.ParseFront(); }

        Detail::TextProperties::Properties ContextStyleSave() override { return m_TextPropertiesParser.Save(); }
        void ContextStyleRestore(const Detail::TextProperties::Properties& data) override { m_TextPropertiesParser.Reload(data); }

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

        void ParseColor() override          { m_TextPropertiesParser.ParseColor(); }
        void ParseStyle() override          { m_TextPropertiesParser.ParseStyle(); }
        void ParseFront() override          { m_TextPropertiesParser.ParseFront(); }
        void ContextStyleBegin() override   {}
        void ContextStyleEnd() override     {}

        void ParseSetter() override;

    public:
        using Base::FormatReadParameterThrow;
        using Base::FormatDataApplyNextOverride;

  	public:
		// Type formating from FormatterType<>
		template<typename Type, typename ...Rest>
		inline void RunType(Type&& type, const Rest&& ...rest) 			{ RunType(type); RunType(std::forward<Rest>(rest)...); }
		template<typename Type> inline void RunType(Type&& type) 		{ FormatterType<typename Detail::FormatTypeForwardAs<Detail::GetBaseType<Type>>::Type, M_Type>::Write(type, *this); }

		template<typename Type, typename ...Rest>
		inline void RunSubType(Type&& type, const Rest&& ...rest) 		{ RunSubType(type); RunSubType(std::forward<Rest>(rest)...); }
		template<typename Type> inline void RunSubType(Type&& type) 	{
			if (m_FormatData.NextOverride.size() == 0)
				return RunType(type);
			FormatDataType formatDataCopy = m_FormatData;
			FormatDataApplyNextOverride();
			RunType(type); 
			m_FormatData = formatDataCopy;
		}

		// Only support basic type that are considered as basic by Buffer class
		template<typename Type, typename ...Rest>
		inline void BasicRunType(Type&& type, Rest&& ...rest) 			    { BasicRunType(type); BasicRunType(std::forward<Rest>(rest)...); };
		template<typename Type> inline void BasicRunType(Type&& type)	    { m_BufferOut.BasicWriteType(type); }

        template<typename Type, typename ...Rest>
		inline void BasicRunSubType(Type&& type, const Rest&& ...rest)      { BasicRunSubType(type); BasicRunSubType(std::forward<Rest>(rest)...); }
		template<typename Type> inline void BasicRunSubType(Type&& type) 	{
			if (m_FormatData.NextOverride.size() == 0)
				return BasicRunType(type);
			FormatDataType formatDataCopy = m_FormatData;
			FormatDataApplyNextOverride();
			BasicRunType(type); 
			m_FormatData = formatDataCopy;
		}

        // Type formating from FormatterType<>
        template<typename Type, typename ...Rest>
        inline void WriteType(Type&& type, Rest&& ...rest)		{ RunType(type, std::forward<Rest>(rest)...); }
        template<typename Type, typename ...Rest>
        inline void WriteSubType(Type&& type, Rest&& ...rest)	{ RunSubType(type, std::forward<Rest>(rest)...); }

        // Only support basic type that are considered as basic by Buffer class
        template<typename Type, typename ...Rest>
        inline void BasicWriteType(Type&& type, Rest&& ...rest)	    { BasicRunType(type, std::forward<Rest>(rest)...); }
        template<typename Type, typename ...Rest>
        inline void BasicSubWriteType(Type&& type, Rest&& ...rest)	{ BasicRunSubType(type, std::forward<Rest>(rest)...); }

    public:
        using Base::GetStringViewParamUntil;
        using Base::GetStringViewUntil;
        using Base::ReadDataType;

    public:
        void CheckEndStr();

        template<typename CharStr>						inline void PrintCharPtr(const CharStr* str)					    	{ m_BufferOut.WriteCharPt(str); }
        template<typename CharStr>						inline void Print(const CharStr* str, std::size_t size)	        { m_BufferOut.WriteCharPt(str, size); }
        template<typename CharStr, std::size_t SIZE>	inline void Print(const CharStr(&str)[SIZE])					{ m_BufferOut.WriteCharPt(str, SIZE); }
        template<typename CharStr>						inline void Print(const std::basic_string_view<CharStr>& str)	{ m_BufferOut.WriteCharPt(str.data(), str.size()); }
        template<typename CharStr>						inline void Print(const std::basic_string<CharStr>& str)		{ Print(static_cast<std::basic_string_view<CharStr>>(str)); }

        template<typename CharStr>						inline void PrintCharPtrIndent(const CharStr* str)					        { m_BufferOut.WriteCharPtIndent(str); }
        template<typename CharStr>						inline void PrintIndent(const CharStr* str, std::size_t size)       { m_BufferOut.WriteCharPtIndent(str, size); }
        template<typename CharStr, std::size_t SIZE>	inline void PrintIndent(const CharStr(&str)[SIZE])					{ m_BufferOut.WriteCharPtIndent(str, SIZE); }
        template<typename CharStr>						inline void PrintIndent(const std::basic_string_view<CharStr>& str) { m_BufferOut.WriteCharPtIndent(str.data(), str.size()); }
    };
}

#include "BaseFormatter/FormatTextPropertiesColor.h"
#include "BaseFormatter/FormatTextPropertiesStyle.h"
#include "BaseFormatter/FormatTextPropertiesFront.h"

#include "BaseFormatter/BaseFormat.h"
#include "BaseFormatter/FormatSTDLib.h"
#include "BaseFormatter/FormatChrono.h"
