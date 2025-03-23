#include "test_suite.h"

#include "stream/profiler.h"

namespace stream::tester
{
    bool TestSuitesManager::exec_all_test_suites()
    {
        detail::TestStatusBank status;

        for (auto& [name, test_suite] : test_suites)
            status.Add(test_suite->exec_all_tests());

        flog::BasicLogger logger("TestSuite");
        if (status.IsAllOk())
            logger.info("{C:white}RESULT => {C:+black}{}", status);
        else
            logger.error("{C:white}RESULT => {C:+black}{}", status);

        return status.ErrorStatus();
    }
}

namespace stream::tester::detail
{
    TestStatusBank TestSuite::exec_all_tests()
    {
        if (parent == nullptr) profiler = new profiler::Profiler("TestSuite_" + name);
        init_logger();

        logger.info("{C:+black}{}", "BEGIN");
        profiler::DurationEvent test_suite_duration(get_full_name(), "Profile");
        test_suite_duration.start();
        bool                           first_test_suite = true;
        TestStatusBank                 test_suite_status;
        profiler::DurationEvent tests_duration("tests", "Profile");
        tests_duration.start();
        for (auto& [name, test] : tests)
        {
            first_test_suite = false;
            profiler::DurationEvent currentTestDuration(test->name, "Profile");
            TestStatus                     testStatus = TestStatus::Fail;
            currentTestDuration.start();
            if (TestSuitesManager::PerformanceTest.Enable == false)
                testStatus = test->run();
            else
            {
                for (std::uint32_t i = 0; i < TestSuitesManager::PerformanceTest.NbSamples; ++i)
                {
                    testStatus = test->run();
                    if (testStatus != TestStatus::Ok) break;
                }
            }
            currentTestDuration.Stop();
            if (testStatus != TestStatus::Ok)
            {}
            test_suite_status.AddTestStatus(testStatus);
            logger.debug("{} -> {}", testStatus, name);
            profiler->add_event(currentTestDuration);
        }
        tests_duration.Stop();

        profiler::DurationEvent groupsDuration("Groups", "Profile");
        groupsDuration.start();
        for (auto& [name, test_suite] : test_suites_linked)
        {
            if (first_test_suite)
                first_test_suite = false;
            else
                std::cout << std::endl;
            test_suite_status.Add(test_suite->exec_all_tests());
        }
        groupsDuration.Stop();
        test_suite_duration.Stop();
        profiler->add_event(tests_duration);
        profiler->add_event(groupsDuration);
        profiler->add_event(test_suite_duration);

        if (test_suite_status.IsAllOk())
            logger.info("{C:+black}{}", test_suite_status);
        else
            logger.error("{C:+black}{}", test_suite_status);

        if (parent == nullptr)
        {
            profiler::ProfilerFactory::ToJson(*profiler);
            delete profiler;
        }

        return test_suite_status;
    }

    void TestSuite::init_logger()
    {
        if (TestSuitesManager::verbose == false)
        {
            logger.SetSeverity(flog::LogSeverity::Debug);
            test_logger.SetSeverity(flog::LogSeverity::Debug);
        }
        else
        {
            logger.SetSeverity(flog::LogSeverity::Trace);
            test_logger.SetSeverity(flog::LogSeverity::Trace);
        }

        std::string timePattern = "";
        if (TestSuitesManager::PrintTime) timePattern = "[{T:pattern='%h:%m:%s:%ms'}] ";

        if (parent == nullptr)
        {
            logger.set_name(name);
            logger.SetRealPattern("{C:+black}" + timePattern + "{name} >> {color}{data}");
            test_logger.set_name(name + ".{test_name}");
            test_logger.SetRealPattern("{C:+black}" + timePattern + "{name} >> {color}{data}");
        }
        else
        {
            std::string correctedName = get_corrected_size_name();
            logger.set_name(correctedName);
            logger.SetRealPatternStrmv("{C:+black}" + timePattern + "{name} >> {color}{data}");
            test_logger.set_name(correctedName + ".{test_name}");
            test_logger.SetRealPatternStrmv("{C:+black}" + timePattern + "{name} >> {color}{data}");
        }
    }

    std::string TestSuite::get_full_name()
    {
        if (parent == nullptr) return name;
        return parent->get_full_name() + "::" + name;
    }

    std::string TestSuite::get_corrected_size_name()
    {
        if (parent == nullptr) return name;
        std::size_t biggestName = 0;
        for (auto& [name, test_suite] : parent->test_suites_linked)
        {
            std::size_t tmp = test_suite->name.size();
            if (tmp > biggestName) biggestName = tmp;
        }
        std::string res = get_full_name();
        biggestName -= name.size();
        res.reserve(res.size() + biggestName);
        for (std::uint32_t i = 0; i < biggestName; ++i)
            res.push_back(' ');
        return res;
    }

    profiler::Profiler& TestSuite::get_profiler()
    {
        if (parent == nullptr) return *profiler;
        return parent->get_profiler();
    }
}
