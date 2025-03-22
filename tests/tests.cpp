
#include "stream/Tester/TestSuite/AllTestSuite.h"
#include "stream/flog/DefaultLogger.h"

int main()
{
    stream::Tester::TestSuitesManager::Verbose = false;
    return stream::Tester::TestSuitesManager::ExecAllTestSuites();
}
