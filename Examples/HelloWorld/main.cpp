#include "StreamFormat/FLog.h"
#include "StreamFormat/FLog/DefaultLogger.h"

#include <thread>

int main()
{
    StreamFormat::FLog::DefaultLogger::Core().Info("HelloWorld !");

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100ms);

    StreamFormat::FLog::DefaultLogger::Core().Warn("After 100ms !");
}
