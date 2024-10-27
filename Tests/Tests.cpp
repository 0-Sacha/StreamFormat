
#include "StreamFormat/Tester/TestSuite/AllTestSuite.h"
#include "StreamFormat/FLog/DefaultLogger.h"

int main()
{
    StreamFormat::Tester::TestSuitesManager::Verbose = false;
    return StreamFormat::Tester::TestSuitesManager::ExecAllTestSuites();
}
