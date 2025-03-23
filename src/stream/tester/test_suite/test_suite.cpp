#include "test_suite.h"

#include "stream/profiler.h"

namespace stream::tester
{
    bool TestSuitesManager::exec_all_test_suites()
    {
        detail::TestStatusBank status;

        for (auto& [name, test_suite] : test_suites)
            status.add(test_suite->exec_all_tests());

        flog::BasicLogger logger("TestSuite");
        if (status.is_all_ok())
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
        if (parent == nullptr)
            profiler = new profiler::Profiler("TestSuite_" + name);
        else
            profiler = &get_profiler();
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
            profiler::DurationEvent current_test_duration(test->name, "Profile");
            TestStatus              test_status = TestStatus::Fail;
            current_test_duration.start();
            if (TestSuitesManager::performance_test.enable == false)
                test_status = test->run();
            else
            {
                for (std::uint32_t i = 0; i < TestSuitesManager::performance_test.nb_samples; ++i)
                {
                    test_status = test->run();
                    if (test_status != TestStatus::Ok) break;
                }
            }
            current_test_duration.stop();
            if (test_status != TestStatus::Ok)
            {}
            test_suite_status.AddTestStatus(test_status);
            logger.debug("{} -> {}", test_status, name);
            profiler->add_event(current_test_duration);
        }
        tests_duration.stop();

        profiler::DurationEvent groupsDuration("Groups", "Profile");
        groupsDuration.start();
        for (auto& [name, test_suite] : test_suites_linked)
        {
            if (first_test_suite)
                first_test_suite = false;
            else
                std::cout << std::endl;
            test_suite_status.add(test_suite->exec_all_tests());
        }
        groupsDuration.stop();
        test_suite_duration.stop();
        profiler->add_event(tests_duration);
        profiler->add_event(groupsDuration);
        profiler->add_event(test_suite_duration);

        if (test_suite_status.is_all_ok())
            logger.info("{C:+black}{}", test_suite_status);
        else
            logger.error("{C:+black}{}", test_suite_status);

        if (parent == nullptr)
        {
            profiler::ProfilerFactory::to_json(*profiler);
            delete profiler;
        }

        return test_suite_status;
    }

    void TestSuite::init_logger()
    {
        if (TestSuitesManager::verbose == false)
        {
            logger.set_severity(flog::LogSeverity::Debug);
            test_logger.set_severity(flog::LogSeverity::Debug);
        }
        else
        {
            logger.set_severity(flog::LogSeverity::Trace);
            test_logger.set_severity(flog::LogSeverity::Trace);
        }

        std::string time_pattern = "";
        if (TestSuitesManager::print_time) time_pattern = "[{T:pattern='%h:%m:%s:%ms'}] ";

        if (parent == nullptr)
        {
            logger.set_name(name);
            logger.SetRealPattern("{C:+black}" + time_pattern + "{name} >> {color}{data}");
            test_logger.set_name(name + ".{test_name}");
            test_logger.SetRealPattern("{C:+black}" + time_pattern + "{name} >> {color}{data}");
        }
        else
        {
            std::string correctedName = get_corrected_size_name();
            logger.set_name(correctedName);
            logger.set_real_pattern_strmv("{C:+black}" + time_pattern + "{name} >> {color}{data}");
            test_logger.set_name(correctedName + ".{test_name}");
            test_logger.set_real_pattern_strmv("{C:+black}" + time_pattern + "{name} >> {color}{data}");
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
        std::size_t biggest_name = 0;
        for (auto& [name, test_suite] : parent->test_suites_linked)
        {
            std::size_t tmp = test_suite->name.size();
            if (tmp > biggest_name) biggest_name = tmp;
        }
        std::string res = get_full_name();
        biggest_name -= name.size();
        res.reserve(res.size() + biggest_name);
        for (std::uint32_t i = 0; i < biggest_name; ++i)
            res.push_back(' ');
        return res;
    }

    profiler::Profiler& TestSuite::get_profiler()
    {
        if (parent == nullptr)
            return *profiler;
        return parent->get_profiler();
    }
}
