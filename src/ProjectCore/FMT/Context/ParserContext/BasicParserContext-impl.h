#pragma once

#include "BasicParserContext.h"

#include "ProjectCore/FMT/Context/BasicContext/BasicContext-impl.h"

namespace ProjectCore::FMT::Context
{
    template <typename CharFormat, typename CharBuffer>
    BasicParserContext<CharFormat, CharBuffer>::BasicParserContext(Detail::BufferInProperties<CharBuffer>               bufferProperties,
                                                                   Detail::IParserTextPropertiesExecutor<BufferInType>& textPropertiesExecutor,
                                                                   const Detail::TextProperties::Properties*            parentContextProperties)
        : Base(textPropertiesExecutor, parentContextProperties)
        , m_BufferIn(bufferProperties)
    {
        // TODO:
        // textPropertiesExecutor.SetBuffer(m_BufferIn);
    }

    template <typename CharFormat, typename CharBuffer>
    void BasicParserContext<CharFormat, CharBuffer>::ParseSetter()
    {
        // TODO:
    }
}
