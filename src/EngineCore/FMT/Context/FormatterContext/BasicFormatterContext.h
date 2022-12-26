#pragma once

#include "FMT/Context/BasicContext/BasicContextInclude.h"

#include "Utils/FormatterType.h"
#include "Utils/NamedArgs.h"
#include "Utils/IndexArgs.h"
#include "Utils/STDEnumerable.h"

#include "AnsiFormatParser.h"

#include "FormatterContextArgsTuple.h"

#include "FMT/Detail/Buffer/BasicBufferOut.h"

namespace EngineCore::FMT::Context {
   
    template<typename CharFormat, typename CharBuffer>
    class BasicFormatterContext : public BasicContext<CharFormat, Detail::AnsiTextData>
    {
    public:
        using Base = BasicContext<CharFormat, Detail::AnsiTextData>;
        using M_Type = BasicFormatterContext<CharFormat, CharBuffer>;

        friend Base;

        using typename Base::CharFormatType;
        using typename Base::FormatDataType;
        using typename Base::StringViewFormat;
        using typename Base::FormatBufferType;
        using typename Base::ContextArgsInterface;
        
        using CharBufferType 	    = CharBuffer;
        using StringViewBuffer 	    = std::basic_string_view<CharBuffer>;
        using BufferOutType 	    = Detail::BasicFormatterMemoryBufferOut<CharBuffer>;
        using AnsiParserType 	    = Detail::AnsiFormatParser<M_Type, FormatBufferType>;

    public:
	    template<typename ...ContextArgs>
        BasicFormatterContext(const std::basic_string_view<CharFormat>& format, CharBuffer* const buffer, const std::size_t bufferSize, [[maybe_unused]] bool k, ContextArgs&&...args);
        BasicFormatterContext(const std::basic_string_view<CharFormat>& format, CharBuffer* const buffer, const std::size_t bufferSize, Detail::BasicContextArgsTupleInterface<M_Type>* argsInterface);
	    template<typename ParentCharFormat>
        BasicFormatterContext(const std::basic_string_view<CharFormat>& format, BasicFormatterContext<ParentCharFormat, CharBuffer>& parentContext, Detail::BasicContextArgsTupleInterface<M_Type>* argsInterface);

	    ~BasicFormatterContext();

    protected:
        using Base::m_Format;
        using Base::m_ValuesIndex;
        using Base::m_FormatData;
        using Base::m_ContextArgsInterface;
        using Base::m_OwnArgsInterface;

        BufferOutType 		    m_BufferOut;
        AnsiParserType 		    m_AnsiManager;

    public:
        using Base::Format;
        using Base::GetFormatData;
        using Base::ForwardFormatData;
        using Base::SetFormatData;
        using Base::GetContextArgsInterface;
        using Base::SetContextArgsInterface;

        inline BufferOutType&			    BufferOut()			    { return m_BufferOut; }
        inline const BufferOutType&		    BufferOut() const	    { return m_BufferOut; }

        inline AnsiParserType&				GetAnsiManager()		{ return m_AnsiManager; }
        inline const AnsiParserType&		GetAnsiManager() const	{ return m_AnsiManager; }

    public:
        using Base::SafeRun;
        void Run() override;

    public:
        template<typename CharType, std::size_t SIZE, typename ...NewContextArgs>
		inline void SubContext(const CharType (&format)[SIZE], NewContextArgs&& ...args)
		{ SubContext(std::basic_string_view<CharType>(format), std::forward<NewContextArgs>(args)...); }

        template<typename NewCharFormat, typename ...NewContextArgs>
        void SubContext(const std::basic_string_view<NewCharFormat>& format, NewContextArgs&& ...args);

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

        void ParseFormatDataColor() override { m_AnsiManager.ParseColor(); }
        void ParseFormatDataStyle() override { m_AnsiManager.ParseStyle(); }
        void ParseFormatDataFront() override { m_AnsiManager.ParseFront(); }

        Detail::AnsiTextData ContextStyleSave() override { return m_AnsiManager.Save(); }
        void ContextStyleRestore(const Detail::AnsiTextData& data) override { m_AnsiManager.Reload(data); }

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

        void ParseColor() override          { m_AnsiManager.ParseColor(); }
        void ParseStyle() override          { m_AnsiManager.ParseStyle(); }
        void ParseFront() override          { m_AnsiManager.ParseFront(); }
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
		inline void BasicRunType(Type&& type, Rest&& ...rest) 			{ BasicRunType(type); BasicRunType(std::forward<Rest>(rest)...); };
		template<typename Type> inline void BasicRunType(Type&& type)	{ FormatterType<typename Detail::FormatTypeForwardAs<Detail::GetBaseType<Type>>::Type, M_Type>::Write(type, *this); }

		template<typename Type, typename ...Rest>
		inline void BasicRunSubType(Type&& type, Rest&& ...rest) 		 	{ m_BufferOut.BasicWriteType(type); };

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
        inline void BasicSubWriteType(Type&& type, Rest&& ...rest)	{ BasicSubRunType(type, std::forward<Rest>(rest)...); }

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
        inline void CopyFormatToBuffer() { m_BufferOut.PushBackIndent(m_Format.GetAndForward()); }

        template<typename ...CharToTest> inline void WriteUntilNextParameterOr(const CharToTest ...ele)	{ while (m_Format.IsNotEqualTo('{', ele...) && m_Format.CanMoveForward())	CopyFormatToBuffer(); }
        template<typename ...CharToTest> inline void WriteUntilEndOfParameterOr(const CharToTest ...ele)	{ while (m_Format.IsNotEqualTo('}', ele...) && m_Format.CanMoveForward())	CopyFormatToBuffer(); }
    };
}

#include "BaseFormat\BaseAnsiTextColor.h"
#include "BaseFormat\BaseAnsiTextFront.h"
#include "BaseFormat\BaseAnsiTextStyle.h"
#include "BaseFormat\BaseFormat.h"
#include "BaseFormat\BaseSTDLib.h"
#include "BaseFormat\Chrono.h"
