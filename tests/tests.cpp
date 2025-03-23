
#include "stream/tester/test_suite/all_test_suite.h"
#include "stream/default_logger.h"

int main()
{
    stream::tester::TestSuitesManager::verbose = false;
    return stream::tester::TestSuitesManager::exec_all_test_suites();
}
