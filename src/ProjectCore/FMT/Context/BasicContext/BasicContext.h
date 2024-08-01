#pragma once

#include "ProjectCore/FMT/Detail/ConvertTraits.h"
#include "ProjectCore/FMT/Detail/Detail.h"

#include "ProjectCore/FMT/Buffer/FMTFormatBuffer/FMTFormatBuffer.h"

#include "BasicArgsTupleInterface.h"

#include "TextPropertiesManager.h"

namespace ProjectCore::FMT::Context
{
    template <typename CharFormat>
    class BasicContext
    {
    private:
        using M_Type = BasicContext<CharFormat>;

    public:
        using CharFormatType = CharFormat;

        using FormatDataType      = Detail::FormatData<CharFormat>;
        using FormatSpecifierType = Detail::FormatSpecifier<CharFormat>;

        using FormatBufferType = Detail::FMTFormatBuffer<CharFormat>;

        using StringViewFormat = std::basic_string_view<CharFormat>;

        using ContextArgsInterface = Detail::BasicArgsTupleInterface<CharFormatType>;

        using TextProperties = Detail::TextPropertiesManager<M_Type>;

    public:
        BasicContext(Detail::ITextPropertiesExecutor& textPropertiesExecutor, const Detail::TextProperties::Properties* parentContextProperties = nullptr);
        virtual ~BasicContext() = default;
        void Terminate();

    protected:
        FormatBufferType      m_Format;
        Detail::FormatIndex   m_ValuesIndex;
        FormatDataType        m_FormatData;
        ContextArgsInterface* m_ContextArgsInterface;
        TextProperties        m_TextProperties;

    public:
        inline FormatBufferType&       Format() { return m_Format; }
        inline const FormatBufferType& Format() const { return m_Format; }

        inline FormatDataType&       GetFormatData() { return m_FormatData; }
        inline const FormatDataType& GetFormatData() const { return m_FormatData; }
        inline FormatDataType        ForwardFormatData() const { return m_FormatData; }
        inline void                  SetFormatData(const FormatDataType& formatData) { m_FormatData = formatData; }

        inline ContextArgsInterface&       GetContextArgsInterface() { return *m_ContextArgsInterface; }
        inline const ContextArgsInterface& GetContextArgsInterface() const { return *m_ContextArgsInterface; }

        inline TextProperties&       GetTextProperties() { return m_TextProperties; }
        inline const TextProperties& GetTextProperties() const { return m_TextProperties; }

    protected:
        virtual void SetArgsInterfaceCurrentContex()                                  = 0;
        virtual void FormatToParamsString(const CharFormat* buffer, std::size_t size) = 0;
        virtual void FormatExecParams()                                               = 0;

    protected:
        void RunImpl();

    public:
        void Run(FormatBufferType& format, ContextArgsInterface* argsInterface);
        void Run(Detail::BufferInProperties<CharFormat>& bufferInProperties, ContextArgsInterface* argsInterface)
        {
            return Run(static_cast<FormatBufferType>(bufferInProperties), argsInterface);
        }

    public:
        Detail::FormatIndex GetFormatIndexThrow();

    public:
        void FormatDataApplyNextOverride();

    protected:
        std::basic_string_view<CharFormat> ParseNextOverrideFormatData();

        void ParseFormatDataBase();
        void ParseFormatDataBase_ValueIntPrint(const typename Detail::ValueIntPrint type);
        void ParseFormatDataSpecial();
        void ParseFormatDataSpecial_ShiftType(const typename Detail::ShiftType type);
        void ParseFormatDataCustom();
        void ParseFormatData();

        void ParseSpecial();
        void ParseVariable(typename Detail::FormatIndex formatIdx);
        bool Parse();

    protected:
        virtual void ParseSetter() = 0;

    public:
        template <typename T>
        void FormatReadParameterThrow(T& i, const T& defaultValue);

    public:
        template <typename... CharToTest>
        inline StringViewFormat GetStringViewParamUntil(CharToTest... c)
        {
            const char* namePos = m_Format.GetBufferCurrentPos();
            m_Format.ParamGoTo(c...);
            return StringViewFormat(namePos, static_cast<std::size_t>(m_Format.GetBufferCurrentPos() - namePos));
        }

        template <typename... CharToTest>
        inline StringViewFormat GetStringViewUntil(CharToTest... c)
        {
            const char* namePos = m_Format.GetBufferCurrentPos();
            m_Format.GoTo(c...);
            return StringViewFormat(namePos, static_cast<std::size_t>(m_Format.GetBufferCurrentPos() - namePos));
        }

        inline typename Detail::DataType ReadDataType()
        {
            Detail::DataType res;
            m_Format.ReadInt(res);
            return res;
        }
    };
}

namespace ProjectCore::FMT::Context
{
    template <typename CharFormat>
    template <typename T>
    void BasicContext<CharFormat>::FormatReadParameterThrow(T& i, const T& defaultValue)
    {
        if (!m_Format.IsEqualTo('{'))
        {
            if (m_Format.FastReadUInt(i) == false) i = defaultValue;
            return;
        }

        // SubIndex
        Detail::FormatIndex formatIdx = GetFormatIndexThrow();
        m_Format.IsEqualToForwardThrow('}');
        if constexpr (std::is_convertible_v<T, int64_t>)
            i = static_cast<T>(m_ContextArgsInterface->GetIntAt(formatIdx));
        else if constexpr (std::is_convertible_v<T, StringViewFormat>)
            i = static_cast<T>(m_ContextArgsInterface->GetStringAt(formatIdx));

        // FIXME WTF
        // TRY         const CharFormat* const mainSubFormat = m_Format.GetBufferCurrentPos();
        // CATCH     m_Format.SetBufferCurrentPos(mainSubFormat);
    }
}
