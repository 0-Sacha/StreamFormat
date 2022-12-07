#pragma once

#include "FMT/Context/BasicContext/BasicContextInclude.h"

#include "Utils/FormatType.h"
#include "Utils/NamedArgs.h"
#include "Utils/IndexArgs.h"
#include "Utils/STDEnumerable.h"
#include "Utils/FormatContextTemplate.h"

#include "AnsiFormatParser.h"

#include "FormatContextArgsTuple.h"

#include "Formatter/Detail/Buffer/BasicBufferOut.h"

namespace EngineCore::FMT::Context {

    template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
    class BasicFormatContext : public BasicContext<CharFormat, Detail::AnsiTextData, BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>>
    {
    public:
        using Base = BasicContext<CharFormat, Detail::AnsiTextData, BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>>;
        using M_Type = BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>;

        friend Base;

        using typename Base::CharFormatType;
        using typename Base::FormatDataType;
        using typename Base::StringViewFormat;
        using typename Base::FormatBufferType;
        
        using CharBufferType 	= CharBuffer;
        using StringViewBuffer 	= std::basic_string_view<CharBuffer>;
        using BufferOutType 	= Detail::BasicFormatterMemoryBufferOut<CharBuffer>;
        using ContextArgsType 	= Detail::FormatContextArgsTuple<ContextArgs...>;
        using AnsiParserType 	= Detail::AnsiFormatParser<M_Type, FormatBufferType>;

    public:
        BasicFormatContext(const std::basic_string_view<CharFormat>& format, CharBuffer* const buffer, const std::size_t bufferSize, ContextArgs &&...args);
        BasicFormatContext(const bool bufferIsAutoResize, const std::basic_string_view<CharFormat>& format, ContextArgs &&...args);

        // Used for LittleFormat
        template<typename ParentCharFormat, typename ...ParentContextArgs>
        BasicFormatContext(const std::basic_string_view<CharFormat>& format, BasicFormatContext<ParentCharFormat, CharBuffer, ParentContextArgs...> &parentContext, ContextArgs &&...args);

	    ~BasicFormatContext();

    protected:
        using Base::m_Format;
        using Base::m_ValuesIndex;
        using Base::m_FormatData;

        BufferOutType 		m_BufferOut;
        AnsiParserType 		m_AnsiManager;
        ContextArgsType 	m_ContextArgs;

    public:
        using Base::Format;
        using Base::GetFormatData;
        using Base::ForwardFormatData;
        using Base::SetFormatData;
        using Base::GetAPI;

        inline BufferOutType&			    BufferOut()			    { return m_BufferOut; }
        inline const BufferOutType&		    BufferOut() const	    { return m_BufferOut; }

        inline AnsiParserType&				GetAnsiManager()		{ return m_AnsiManager; }
        inline const AnsiParserType&		GetAnsiManager() const	{ return m_AnsiManager; }

    public:
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
        using Base::GetTypeAtIndexConvertThrow;
        using Base::GetIndexOfCurrentNameArg;
        using Base::RunTypeAtIndex;
        
        void RunTypeAtIndex(const Detail::FormatIndex& index)                                   { m_ContextArgs.RunTypeAtIndex(*this, index); }
        Detail::FormatIndex GetIndexOfCurrentNameArg()                                          { return m_ContextArgs.GetIndexOfCurrentNameArg(*this, Detail::FormatIndex(0, m_ValuesIndex.MaxValue)); }

        template <typename T>
        const Detail::GetBaseType<T>* GetTypeAtIndex(const Detail::FormatIndex& index)          { return m_ContextArgs.template GetTypeAtIndexThrow<T>(*this, index); }

        template <typename T>
        T GetTypeAtIndexConvertThrow(const Detail::FormatIndex& index) {
            return m_ContextArgs.template GetTypeAtIndexConvertThrow<T>(*this, index);
        }

        template <typename T>
		bool RunFuncFromTypeAtIndex(const Detail::FormatIndex& index, std::function<void (const T&)> func)
        {
            const T* value = m_ContextArgs.template GetTypeAtIndexThrow<T>(*this, index);
            if (value != nullptr)
            {
                func(*value);
                return true;
            }
            return false;
        }
        
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


        void ParseFormatDataColor()     { m_AnsiManager.ParseColor(); }
        void ParseFormatDataStyle()     { m_AnsiManager.ParseStyle(); }
        void ParseFormatDataFront()     { m_AnsiManager.ParseFront(); }

        Detail::AnsiTextData ContextStyleSave()                         { return m_AnsiManager.Save(); }
        void ContextStyleRestore(const Detail::AnsiTextData& data)      { m_AnsiManager.Reload(data); }

    protected:
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

        void ParseColor()           { m_AnsiManager.ParseColor(); }
        void ParseStyle()           { m_AnsiManager.ParseStyle(); }
        void ParseFront()           { m_AnsiManager.ParseFront(); }

        void ContextStyleBegin()    {}
        void ContextStyleEnd()      {}

        void ParseSetter();

    public:
        using Base::FormatReadParameterThrow;

    public:
        using Base::RunType;
        using Base::RunSubType;
        using Base::BasicRunType;
        using Base::BasicRunSubType;


        // Type formating from FormatType<>
        template<typename Type>
        inline void RunType(Type&& type)                        { FormatType<typename FormatTypeForwardAs<Detail::GetBaseType<Type>>::Type, M_Type>::Write(type, *this); }
        template<typename Type, typename ...Rest>
        inline void WriteType(Type&& type, Rest&& ...rest)		{ RunType(type, std::forward<Rest>(rest)...); }
        template<typename Type, typename ...Rest>
        inline void WriteSubType(Type&& type, Rest&& ...rest)	{ RunSubType(type, std::forward<Rest>(rest)...); }

        // Only support basic type that are considered as basic by Buffer class
        template<typename Type>
        inline void BasicRunType(Type&& type)                       { m_BufferOut.BasicWriteType(type); }
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
