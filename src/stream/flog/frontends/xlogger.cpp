#include "XLogger.h"

namespace stream::flog
{
    template class detail::XLogger<detail::BasicLoggerImpl<LogSeverity>>;
    template class detail::XLogger<detail::BasicLoggerMultiSinkFastImpl<LogSeverity, char>>;
    template class detail::XLogger<detail::BasicLoggerMultiSinkSafeImpl<LogSeverity, char>>;
}

namespace stream::flog::Sinks
{
    template class BasicConsoleSink<LogSeverity, char>;
    template class BasicFileSink<LogSeverity, char>;
}
