#pragma once

#include "BasicFormatterContext.h"

#include "StreamFormat/FMT/Context/BasicContext/BasicContext-impl.h"

namespace StreamFormat::FMT::Context
{
    template <typename CharFormat, typename CharBuffer>
    BasicFormatterContext<CharFormat, CharBuffer>::BasicFormatterContext(Detail::BasicBufferOutManager<CharBuffer>&               BufferOutManager,
                                                                         Detail::IFormatterTextPropertiesExecutor<BufferOutType>& textPropertiesExecutor,
                                                                         const Detail::TextProperties::Properties*                parentContextProperties)
        : Base(textPropertiesExecutor, parentContextProperties)
        , m_BufferOut(BufferOutManager)
    {
        textPropertiesExecutor.SetBuffer(&m_BufferOut);
    }

    template <typename CharFormat, typename CharBuffer>
    BasicFormatterContext<CharFormat, CharBuffer>::~BasicFormatterContext()
    {
        m_BufferOut.EndContext();
        m_BufferOut.PushBackEndChar();
    }

    template <typename CharFormat, typename CharBuffer>
    void BasicFormatterContext<CharFormat, CharBuffer>::ParseSetter()
    {
        ParseFormatData();

        // Indent
        auto indent = m_FormatData.GetSpecifier("indent");
        if (indent != nullptr)
        {
            if (indent->ValueHasNumber == true)
                BufferOut().SetIndent(static_cast<std::size_t>(indent->ValueAsNumber));
            else
                BufferOut().SetIndent();
        }
    }
}
