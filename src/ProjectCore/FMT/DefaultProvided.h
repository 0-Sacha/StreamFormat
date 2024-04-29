#pragma once

#include "Context/FormatterContext/UtilityFunctions.h"
#include "Context/ParserContext/UtilityFunctions.h"

namespace ProjectCore::FMT
{
    extern template class Detail::DynamicBufferOutManager<char>;
    extern template class Detail::ShrinkDynamicBufferOutManager<char>;
    extern template class Detail::GivenBufferOutManager<char>;

    extern template class Context::BasicFormatterContext<char, char>;
    extern template class Context::BasicParserContext<char, char>;
}
