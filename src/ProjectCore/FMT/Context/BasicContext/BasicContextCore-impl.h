#pragma once

#include "BasicContext.h"

namespace ProjectCore::FMT::Context
{
    template <typename CharFormat>
    BasicContext<CharFormat>::BasicContext(Detail::ITextPropertiesExecutor& textPropertiesExecutor, const Detail::TextProperties::Properties* parentContextProperties)
        : m_Format()
        , m_ValuesIndex(0, 0)
        , m_FormatData()
        , m_ContextArgsInterface(nullptr)
        , m_TextProperties(*this, textPropertiesExecutor, parentContextProperties)
    {}

    template <typename CharFormat>
    void BasicContext<CharFormat>::Terminate()
    {
        m_TextProperties.Terminate();
    }

    template <typename CharFormat>
    void BasicContext<CharFormat>::RunImpl()
    {
        while (!m_Format.IsEnd())
        {
            const CharFormat* beginContinousString = m_Format.GetBufferCurrentPos();
            std::size_t sizeContinousString = 0;
            while (m_Format.IsEnd() == false && m_Format.IsEqualTo('{') == false)
            {
                ++sizeContinousString;
                m_Format.Forward();
            }
            FormatToParamsString(beginContinousString, sizeContinousString);

            if (m_Format.IsEnd() == false && m_Format.IsEqualTo('{'))
                FormatExecParams();
        }
    }

    template <typename CharFormat>
    void BasicContext<CharFormat>::Run(FormatBufferType& format, ContextArgsInterface* argsInterface)
    {
        // Save old context
        FormatBufferType oldFormat = m_Format;
        ContextArgsInterface* oldArgsInterface = m_ContextArgsInterface;
        Detail::FormatIndex oldValuesIndex = m_ValuesIndex;
        Detail::TextProperties::Properties saveTextProperties = m_TextProperties.Save();
        // Set new context
        m_Format = format;
        m_ContextArgsInterface = argsInterface;
        m_ValuesIndex = Detail::FormatIndex(0, static_cast<typename Detail::FormatIndex::BaseType>(argsInterface->Size()));
        SetArgsInterfaceCurrentContex();
        // Run
        RunImpl();
        // Restore old context
        m_Format = oldFormat;
        m_ContextArgsInterface = oldArgsInterface;
        m_ValuesIndex = oldValuesIndex;
        m_TextProperties.Reload(saveTextProperties);
    }

    template <typename CharFormat>
    void BasicContext<CharFormat>::FormatDataApplyNextOverride()
    {
        if (m_FormatData.NextOverride.size() == 0)
            return;
    
        FormatBufferType overrideAsFormat(m_FormatData.NextOverride);
        FormatBufferType formatCopy = m_Format;
        m_Format = overrideAsFormat;
        ParseFormatData();
        m_Format = formatCopy;
    }
}
