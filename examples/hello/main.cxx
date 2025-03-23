#include "stream/flog.hxx"
#include "stream/fmt/context/formatter_executor/utility_functions.hxx"

#include "stream/default_logger.hxx"

#include <thread>

int main()
{
    stream::flog::DefaultLogger::core().info("HelloWorld !");

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100ms);

    stream::flog::DefaultLogger::core().warn("after 100ms !");
}
