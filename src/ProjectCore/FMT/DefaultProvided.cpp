#include "DefaultProvided.h"

namespace ProjectCore::FMT
{
    template class Detail::DynamicBufferOutManager<char>;
    template class Detail::ShrinkDynamicBufferOutManager<char>;
    template class Detail::GivenBufferOutManager<char>;

    template class Context::BasicFormatterContext<char, char>;
    template class Context::BasicParserContext<char, char>;
}
