#include "TestSuite.h"
#include "ProjectCore/Instrumentation/ProfilerManger/ProfilerManger.h"

namespace ProjectCore::Tester
{
    bool TestSuitesManager::ExecAllTestSuites()
    {
        PROJECTCORE_FORMATTER_TIME_BEGIN();
        Detail::TestStatusBank status;

        for (auto& [name, testSuite] : TestSuites)
            status.Add(testSuite->ExecAllTests());

        LoggerManager::BasicLogger logger("TestSuite");
        if (status.IsAllOk())
            logger.Info("{C:white}RESULT => {C:+black}{}", status);
        else
            logger.Error("{C:white}RESULT => {C:+black}{}", status);

        return status.ErrorStatus();
    }
}

namespace ProjectCore::Tester::Detail
{
    TestStatusBank TestSuite::ExecAllTests()
    {
        if (Parent == nullptr)
            Profiler = new Instrumentation::Profiler("TestSuite_" + Name);
        InitLogger();

        Instrumentation::Profiler& profiler = GetProfiler();
        Logger.Info("{C:+black}BEGIN");
        Instrumentation::DurationEvent testSuiteDuration(GetFullName(), "Profile");
        testSuiteDuration.Start();
        bool firstTestSuite = true;
        TestStatusBank testSuiteStatus;
        Instrumentation::DurationEvent testsDuration("Tests", "Profile");
        testsDuration.Start();
        for (auto& [name, test] : Tests)
        {
            firstTestSuite = false;
            Instrumentation::DurationEvent currentTestDuration(test->Name, "Profile");
            TestStatus testStatus = TestStatus::Fail;
            currentTestDuration.Start();
            if (TestSuitesManager::PerformanceTest.Enable == false)
                testStatus = test->Run();
            else
            {
                for (std::uint32_t i = 0; i < TestSuitesManager::PerformanceTest.NbSamples; ++i)
                {
                    testStatus = test->Run();
                    if (testStatus != TestStatus::Ok)
                        break;
                }
            }
            currentTestDuration.Stop();
            if (testStatus != TestStatus::Ok)
            {
            }
            testSuiteStatus.AddTestStatus(testStatus);
            Logger.Debug("{} -> {}", testStatus, name);
            profiler.AddEvent(currentTestDuration);
        }
        testsDuration.Stop();

        Instrumentation::DurationEvent groupsDuration("Groups", "Profile");
        groupsDuration.Start();
        for (auto& [name, testSuite] : TestSuitesLinked)
        {
            if (firstTestSuite)
                firstTestSuite = false;
            else
                std::cout << std::endl;
            testSuiteStatus.Add(testSuite->ExecAllTests());
        }
        groupsDuration.Stop();
        testSuiteDuration.Stop();
        profiler.AddEvent(testsDuration);
        profiler.AddEvent(groupsDuration);
        profiler.AddEvent(testSuiteDuration);

        if (testSuiteStatus.IsAllOk())
            Logger.Info("{C:+black}{}", testSuiteStatus);
        else
            Logger.Error("{C:+black}{}", testSuiteStatus);

        if (Parent == nullptr)
        {
            Instrumentation::ProfilerFactory::ToJson(*Profiler);
            delete Profiler;
        }

        return testSuiteStatus;
    }

    void TestSuite::InitLogger()
    {
        if (TestSuitesManager::Verbose == false)
        {
            Logger.SetSeverity(LoggerManager::LogSeverity::Debug);
            TestLogger.SetSeverity(LoggerManager::LogSeverity::Debug);
        }
        else
        {
            Logger.SetSeverity(LoggerManager::LogSeverity::Trace);
            TestLogger.SetSeverity(LoggerManager::LogSeverity::Trace);
        }

        std::string timePattern = "";
        if (TestSuitesManager::PrintTime)
            timePattern = "[{T:pattern='%h:%m:%s:%ms'}] ";

        if (Parent == nullptr)
        {
            Logger.SetName(Name);
            Logger.SetRealPattern("{C:+black}" + timePattern + "{name} >> {color}{data}");
            TestLogger.SetName(Name + ".{test_name}");
            TestLogger.SetRealPattern("{C:+black}" + timePattern + "{name} >> {color}{data}");
        }
        else
        {
            std::string correctedName = GetCorrectedSizeName();
            Logger.SetName(correctedName);
            Logger.SetRealPatternStrmv("{C:+black}" + timePattern + "{name} >> {color}{data}");
            TestLogger.SetName(correctedName + ".{test_name}");
            TestLogger.SetRealPatternStrmv("{C:+black}" + timePattern + "{name} >> {color}{data}");
        }
    }

    std::string TestSuite::GetFullName()
    {
        if (Parent == nullptr)
            return Name;
        return Parent->GetFullName() + "::" + Name;
    }

    std::string TestSuite::GetCorrectedSizeName()
    {
        if (Parent == nullptr)
            return Name;
        std::size_t biggestName = 0;
        for (auto& [name, testSuite] : Parent->TestSuitesLinked)
        {
            std::size_t tmp = testSuite->Name.size();
            if (tmp > biggestName)
                biggestName = tmp;
        }
        std::string res = GetFullName();
        biggestName -= Name.size();
        res.reserve(res.size() + biggestName);
        for (std::uint32_t i = 0; i < biggestName; ++i)
            res.push_back(' ');
        return res;
    }

    Instrumentation::Profiler& TestSuite::GetProfiler()
    {
        if (Parent == nullptr)
            return *Profiler;
        return Parent->GetProfiler();
    }
}
