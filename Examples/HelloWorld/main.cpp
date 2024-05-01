#include "ProjectCore/FLog.h"
#include "ProjectCore/FLog/DefaultLogger.h"

#include <thread>

int main()
{
    ProjectCore::FLog::DefaultLogger::Core().Info("HelloWorld !");

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100ms);

    ProjectCore::FLog::DefaultLogger::Core().Warn("After 100ms !");
}
