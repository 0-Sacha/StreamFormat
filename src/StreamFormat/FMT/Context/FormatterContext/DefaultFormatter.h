#pragma once

#include "UtilityFunctions.h"

namespace StreamFormat::FMT
{
    extern template class Detail::DynamicBufferOutManager<char>;
    extern template class Detail::ShrinkDynamicBufferOutManager<char>;
    extern template class Detail::GivenBufferOutManager<char>;

    template class Detail::FormatData<char>;
    template class Detail::BasicArgsTupleInterface<char>;
    template class Detail::FMTBufferOut<char>;
    template class Detail::FMTFormatBuffer<char>;
    template class Detail::TextPropertiesManager<Context::BasicFormatterContext<char, char>>;

    extern template class Context::BasicFormatterContext<char, char>;
}
