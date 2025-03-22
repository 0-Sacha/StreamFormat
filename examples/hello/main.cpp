#include "stream/flog.h"
#include "stream/flog/DefaultLogger.h"
#include "stream/fmt/context/formatter_executor/utility_functions.h"

#include <thread>

int main()
{
    stream::flog::DefaultLogger::Core().info("HelloWorld !");

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100ms);

    stream::flog::DefaultLogger::Core().warn("After 100ms !");
}
