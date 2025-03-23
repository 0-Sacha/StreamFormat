#include "stream/flog.h"
#include "stream/fmt/context/formatter_executor/utility_functions.h"

#include "stream/default_logger.h"

#include <thread>

int main()
{
    stream::flog::DefaultLogger::core().info("HelloWorld !");

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100ms);

    stream::flog::DefaultLogger::core().warn("after 100ms !");
}
