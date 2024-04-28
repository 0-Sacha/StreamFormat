#pragma once

#include "BasicFormatterContext.h"
#include "BasicFormatterContextCoreImpl.h"

namespace ProjectCore::FMT::Context
{
    template<typename CharFormat, typename CharBuffer>
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
