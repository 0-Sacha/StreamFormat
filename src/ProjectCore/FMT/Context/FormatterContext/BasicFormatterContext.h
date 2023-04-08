#pragma once

#include "ProjectCore/FMT/Context/BasicContext/BasicContextInclude.h"
#include "ProjectCore/FMT/Detail/Buffer/FMTBufferOut/FMTBufferOut.h"

#include "FormatterType.h"
#include "Utils/NamedArgs.h"
#include "Utils/IndexArgs.h"
#include "Utils/STDEnumerable.h"

#include "FormatterTextPropertiesExecutor/IFormatterTextPropertiesExecutor.h"

#include "FormatterContextArgsTuple.h"

namespace ProjectCore::FMT::Context
{
    template<typename CharFormat, typename CharBuffer>
    class BasicFormatterContext : public BasicContext<CharFormat>
    {
    public:
        using Base = BasicContext<CharFormat>;
        using M_Type = BasicFormatterContext<CharFormat, CharBuffer>;

        friend Base;

        using typename Base::CharFormatType;
        using typename Base::FormatDataType;
        using typename Base::StringViewFormat;
        using typename Base::FormatBufferType;
        using typename Base::ContextArgsInterface;
        using typename Base::TextPropertiesParser;
        
        using StringViewBuffer         = std::basic_string_view<CharBuffer>;
        using BufferOutType         = Detail::FMTBufferOut<CharBuffer>;

    public:
        BasicFormatterContext(Detail::BasicBufferOutManager<CharBuffer>& BufferOutManager, Detail::IFormatterTextPropertiesExecutor<BufferOutType>& textPropertiesExecutor, const Detail::TextProperties::Properties* parentContextProperties = nullptr);
        ~BasicFormatterContext() override;

    protected:
        using Base::m_Format;
        using Base::m_ValuesIndex;
        using Base::m_FormatData;
        using Base::m_ContextArgsInterface;
        using Base::m_TextPropertiesParser;

        BufferOutType                             m_BufferOut;

    public:
        using Base::Format;
        using Base::GetFormatData;
        using Base::ForwardFormatData;
        using Base::SetFormatData;
        using Base::GetContextArgsInterface;

        inline BufferOutType&                BufferOut()                { return m_BufferOut; }
        inline const BufferOutType&            BufferOut() const        { return m_BufferOut; }

    public:
        using Base::Run;
    
    protected:
        void FormatToParamsString(const CharFormat* buffer, std::size_t size) override  { m_BufferOut.FastWriteCharPtr(buffer, size); }
        void FormatExecParams() override                                                { if (!Parse()) m_BufferOut.PushBack('{'); }
        void SetArgsInterfaceCurrentContex() override                                   { m_ContextArgsInterface->SetContext(this); }

    public:
        template<typename NewCharFormat, typename ...NewContextArgs>
        void SubContext(const Detail::BufferInProperties<NewCharFormat>& bufferInProperties, NewContextArgs&& ...args);

        template<typename NewCharFormat, std::size_t SIZE, typename ...NewContextArgs>
        inline void SubContext(const NewCharFormat (&format)[SIZE], NewContextArgs&& ...args)
        {
            Detail::BufferInProperties<NewCharFormat> properties(format);
            return SubContext(properties, std::forward<NewContextArgs>(args)...);
        }

        template<typename NewCharFormat, typename ...NewContextArgs>
        void SubContext(const NewCharFormat* buffer, std::size_t size, NewContextArgs&& ...args)
        {
            Detail::BufferInProperties<NewCharFormat> properties(buffer, size);
            return SubContext(properties, std::forward<NewContextArgs>(args)...);
        }

    public:
        using Base::GetFormatIndexThrow;
      
    protected:
        using Base::ParseFormatDataBase;
        using Base::ParseFormatDataSpecial;
        using Base::ParseFormatDataCustom;
        using Base::ParseFormatData;

        using Base::ParseSpecial;
        using Base::ParseVariable;
        using Base::Parse;

    protected:
        using Base::ParseTimer;
        using Base::ParseDate;
        using Base::ParseSetter;

        void ParseTimer() override;
        void ParseDate() override;
        void ParseSetter() override;

    public:
        using Base::FormatReadParameterThrow;
        using Base::FormatDataApplyNextOverride;

      public:
        // Type formating from FormatterType<>
        template<typename Type, typename ...Rest>
        inline void RunType(Type&& type, const Rest&& ...rest)      { RunType(type); RunType(std::forward<Rest>(rest)...); }
        template<typename Type> inline void RunType(Type&& type)    { FormatterType<typename Detail::FormatTypeForwardAs<Detail::GetBaseType<Type>>::Type, M_Type>::Format(type, *this); }

        template<typename Type, typename ...Rest>
        inline void RunSubType(Type&& type, const Rest&& ...rest)   { RunSubType(type); RunSubType(std::forward<Rest>(rest)...); }
        template<typename Type> inline void RunSubType(Type&& type) {
            if (m_FormatData.NextOverride.size() == 0)
                return RunType(type);
            FormatDataType formatDataCopy = m_FormatData;
            FormatDataApplyNextOverride();
            RunType(type); 
            m_FormatData = formatDataCopy;
        }

        // Only support basic type that are considered as basic by Buffer class
        template<typename Type, typename ...Rest>
        inline void BasicRunType(Type&& type, Rest&& ...rest)               { BasicRunType(type); BasicRunType(std::forward<Rest>(rest)...); }
        template<typename Type> inline void BasicRunType(Type&& type)       { m_BufferOut.BasicWriteType(type); }

        template<typename Type, typename ...Rest>
        inline void BasicRunSubType(Type&& type, const Rest&& ...rest)      { BasicRunSubType(type); BasicRunSubType(std::forward<Rest>(rest)...); }
        template<typename Type> inline void BasicRunSubType(Type&& type) {
            if (m_FormatData.NextOverride.size() == 0)
                return BasicRunType(type);
            FormatDataType formatDataCopy = m_FormatData;
            FormatDataApplyNextOverride();
            BasicRunType(type); 
            m_FormatData = formatDataCopy;
        }

        // Type formating from FormatterType<>
        template<typename Type, typename ...Rest>
        inline void WriteType(Type&& type, Rest&& ...rest)  { RunType(type, std::forward<Rest>(rest)...); }
        template<typename Type, typename ...Rest>
        inline void WriteSubType(Type&& type, Rest&& ...rest) { RunSubType(type, std::forward<Rest>(rest)...); }

        // Only support basic type that are considered as basic by Buffer class
        template<typename Type, typename ...Rest>
        inline void BasicWriteType(Type&& type, Rest&& ...rest) { BasicRunType(type, std::forward<Rest>(rest)...); }
        template<typename Type, typename ...Rest>
        inline void BasicSubWriteType(Type&& type, Rest&& ...rest) { BasicRunSubType(type, std::forward<Rest>(rest)...); }

    public:
        using Base::GetStringViewParamUntil;
        using Base::GetStringViewUntil;
        using Base::ReadDataType;

    public:
        void CheckEndStr();
    };
}

#include "BaseFormatter/FormatTextPropertiesColor.h"
#include "BaseFormatter/FormatTextPropertiesStyle.h"
#include "BaseFormatter/FormatTextPropertiesFront.h"
#include "BaseFormatter/BaseFormat.h"
#include "BaseFormatter/FormatSTDLib.h"
#include "BaseFormatter/FormatChrono.h"

#include "FormatterTextPropertiesExecutor/FormatterNOTextPropertiesExecutor.h"
#include "FormatterTextPropertiesExecutor/FormatterANSITextPropertiesExecutor.h"
