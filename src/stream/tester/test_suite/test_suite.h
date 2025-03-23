#pragma once

#include "stream/flog.h"
#include "stream/fmt.h"
#include "stream/profiler.h"

#include "stream/fmt/serializers/compilation_data.h"

#include <concepts>
#include <string>
#include <unordered_map>

namespace stream::tester
{
    class TestFailure
    {
    };

    enum class TestStatus : int
    {
        Ok,
        Fail,
        Crash
    };
}

namespace stream::tester::detail
{
    class TestSuite;
    class Test
    {
    public:
        Test(std::string&& name, TestSuite& link, const fmt::detail::FileLocation& location)
            : name(std::move(name))
            , Link(link)
            , location(location)
            , LastStatus(TestStatus::Ok)
        {}

        virtual ~Test() = default;

    protected:
        virtual TestStatus RunImpl() = 0;

    public:
        TestStatus run()
        {
            try
            {
                return LastStatus = RunImpl();
            }
            catch (const TestFailure&)
            {
                return LastStatus = TestStatus::Fail;
            }
            catch (...)
            {
                return LastStatus = TestStatus::Crash;
            }
        }

    public:
        std::string               name;
        TestSuite&                Link;
        fmt::detail::FileLocation location;
        TestStatus                LastStatus;
    };

    struct TestStatusBank
    {
        void Reset()
        {
            tests_done  = 0;
            tests_ok    = 0;
            tests_failed  = 0;
            testsCrash = 0;
        }

        void AddTestStatus(TestStatus status)
        {
            tests_done++;
            switch (status)
            {
                case TestStatus::Ok:
                    tests_ok++;
                    break;
                case TestStatus::Fail:
                    tests_failed++;
                    break;
                case TestStatus::Crash:
                    testsCrash++;
                    break;
            }
        }

        void add(TestStatusBank status)
        {
            tests_done += status.tests_done;
            tests_ok += status.tests_ok;
            tests_failed += status.tests_failed;
            testsCrash += status.testsCrash;
        }

        bool is_all_ok() { return tests_done == tests_ok && testsCrash == 0 && tests_failed == 0; }

        std::uint32_t ErrorStatus() { return tests_done - tests_ok; }

        std::uint32_t tests_done  = 0;
        std::uint32_t tests_ok    = 0;
        std::uint32_t tests_failed  = 0;
        std::uint32_t testsCrash = 0;
    };

    class TestSuite;
}
namespace stream::tester
{
    struct performance_testData
    {
        bool          enable    = false;
        std::uint32_t nb_samples = 10;
    };

    struct ConcurrencySpecificationData
    {
        bool enable = false;
    };

    class TestSuitesManager
    {
    public:
        static bool                                                            exec_all_test_suites();
        static inline std::unordered_map<std::string_view, detail::TestSuite*> test_suites;

    public:
        static inline bool                         verbose                 = false;
        static inline bool                         print_time               = false;
        static inline performance_testData         performance_test         = performance_testData{};
        static inline ConcurrencySpecificationData concurrency_specification = ConcurrencySpecificationData{};
    };
}
namespace stream::tester::detail
{
    struct TestSuiteData
    {
        bool redirect_stdout = false;
        bool redirect_stdin  = false;
        bool redirect_stderr = false;
    };

    class TestSuite
    {
    public:
        TestSuite(std::string&& name, TestSuiteData extra = TestSuiteData{}, TestSuite* parent = nullptr)
            : name(std::move(name))
            , tests()
            , extra(extra)
            , logger()
            , test_logger()
            , profiler(nullptr)
            , parent(parent)
        {
            if (parent == nullptr)
                TestSuitesManager::test_suites.insert({name, this});
            else
                parent->test_suites_linked.insert({name, this});
        }

        std::string                                      name;
        std::unordered_map<std::string_view, Test*>      tests;
        std::unordered_map<std::string_view, TestSuite*> test_suites_linked;

        TestSuiteData              extra;
        flog::BasicLogger          logger;
        flog::BasicLogger          test_logger;
        profiler::Profiler*        profiler;

        TestSuite* parent;

    public:
        void init_logger();

    private:
        std::string         get_full_name();
        std::string         get_corrected_size_name();
        profiler::Profiler& get_profiler();

    public:
        TestStatusBank exec_all_tests();
    };
}

namespace stream::fmt
{
    template <typename FormatterExecutor>
    struct FormatterType<stream::tester::detail::TestSuite, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const stream::tester::detail::TestSuite& t, FormatterExecutor& executor)
            { return executor.ostream.fast_write_string(t.name); }
    };

    template <typename FormatterExecutor>
    struct FormatterType<stream::tester::detail::Test, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const stream::tester::detail::Test& t, FormatterExecutor& executor)
        {
            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string(t.Link.name));
            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string_literal("::"));
            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string(t.name));
            return {};
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<stream::tester::TestStatus, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const stream::tester::TestStatus& status, FormatterExecutor& executor)
        {
            switch (status)
            {
                case stream::tester::TestStatus::Ok:
                    return executor.run("[  {C:green}OK{C}  ]");
                case stream::tester::TestStatus::Fail:
                    return executor.run("[ {C:red}FAIL{C} ]");
                case stream::tester::TestStatus::Crash:
                    return executor.run("[{C:magenta}Crash{C} ]");
            }
            return {};
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<stream::tester::detail::TestStatusBank, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(const stream::tester::detail::TestStatusBank& status_bank, FormatterExecutor& executor)
        {
            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string_literal("tests_done "));
            SF_TRY(executor.run("{:C:white}", status_bank.tests_done));

            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string_literal(" | testsOK "));
            if (status_bank.tests_ok == status_bank.tests_done)
                { SF_TRY(executor.run("{:C:green}", status_bank.tests_ok)); }
            else
                { SF_TRY(executor.run("{:C:yellow}", status_bank.tests_ok)); }

            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string_literal(" | testsFAIL "));
            if (status_bank.tests_failed == 0)
                { SF_TRY(executor.run("{:C:green}", status_bank.tests_failed)); }
            else
                { SF_TRY(executor.run("{:C:red}", status_bank.tests_failed)); }

            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string_literal(" | TestCrash "));
            if (status_bank.testsCrash == 0)
                { SF_TRY(executor.run("{:C:green}", status_bank.testsCrash)); }
            else
                { SF_TRY(executor.run("{:C:magenta}", status_bank.testsCrash)); }

            return {};
        }
    };
}

//-------------------- Base --------------------//
#define STREAMFORMAT_TESTINTERNAL_SUITE_NAME(TestSuiteName)               TestSuite_##TestSuiteName
#define STREAMFORMAT_TESTINTERNAL_FUNC_NAME(TestSuiteName, TestName)      TestSuite_##TestSuiteName##TestName
#define STREAMFORMAT_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName) TestSuite_##TestSuiteName##TestName##_ExecMethod
#define STREAMFORMAT_TESTINTERNAL_SUITE_EXTRA(...) \
    stream::tester::detail::TestSuiteData    \
    {                                             \
        __VA_ARGS__                               \
    }

//-------------------- TestSuite --------------------//
#define SFT_TEST_SUITE(TestSuiteName, ...) \
    stream::tester::detail::TestSuite STREAMFORMAT_TESTINTERNAL_SUITE_NAME(TestSuiteName)(#TestSuiteName, STREAMFORMAT_TESTINTERNAL_SUITE_EXTRA(__VA_ARGS__))
#define SFT_TEST_GROUP(TestSuiteName, GroupName, ...)                                                                                                    \
    stream::tester::detail::TestSuite STREAMFORMAT_TESTINTERNAL_SUITE_NAME(GroupName)(#GroupName, STREAMFORMAT_TESTINTERNAL_SUITE_EXTRA(__VA_ARGS__), \
                                                                                          &STREAMFORMAT_TESTINTERNAL_SUITE_NAME(TestSuiteName))

#define SFT_TEST_SUITE_DECLARATION(TestSuiteName, ...)            stream::tester::detail::TestSuite STREAMFORMAT_TESTINTERNAL_SUITE_NAME(TestSuiteName)
#define SFT_TEST_GROUP_DECLARATION(TestSuiteName, GroupName, ...) stream::tester::detail::TestSuite STREAMFORMAT_TESTINTERNAL_SUITE_NAME(GroupName)
