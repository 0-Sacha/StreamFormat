
#include "EngineCore/Tester/TestSuite/AllTestSuite.h"

int main()
{
	EngineCore::Tester::TestSuitesManager::Verbose = false;
	EngineCore::Tester::TestSuitesManager::ExecAllTestSuites();
}
