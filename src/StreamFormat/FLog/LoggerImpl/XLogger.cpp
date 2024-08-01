#include "XLogger.h"

namespace StreamFormat::FLog
{
    template class Detail::XLogger<Detail::BasicLoggerImpl<LogSeverity>>;
    template class Detail::XLogger<Detail::BasicLoggerMultiSinkFastImpl<LogSeverity, char>>;
    template class Detail::XLogger<Detail::BasicLoggerMultiSinkSafeImpl<LogSeverity, char>>;
}

namespace StreamFormat::FLog::Sinks
{
    template class BasicConsoleSink<LogSeverity, char>;
    template class BasicFileSink<LogSeverity, char>;
}
