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
            testsDone  = 0;
            testsOk    = 0;
            testsFail  = 0;
            testsCrash = 0;
        }

        void AddTestStatus(TestStatus status)
        {
            testsDone++;
            switch (status)
            {
                case TestStatus::Ok:
                    testsOk++;
                    break;
                case TestStatus::Fail:
                    testsFail++;
                    break;
                case TestStatus::Crash:
                    testsCrash++;
                    break;
            }
        }

        void Add(TestStatusBank status)
        {
            testsDone += status.testsDone;
            testsOk += status.testsOk;
            testsFail += status.testsFail;
            testsCrash += status.testsCrash;
        }

        bool IsAllOk() { return testsDone == testsOk && testsCrash == 0 && testsFail == 0; }

        std::uint32_t ErrorStatus() { return testsDone - testsOk; }

        std::uint32_t testsDone  = 0;
        std::uint32_t testsOk    = 0;
        std::uint32_t testsFail  = 0;
        std::uint32_t testsCrash = 0;
    };

    class TestSuite;
}
namespace stream::tester
{
    struct PerformanceTestData
    {
        bool          Enable    = false;
        std::uint32_t NbSamples = 10;
    };

    struct ConcurenceSpecificationData
    {
        bool Enable = false;
    };

    class TestSuitesManager
    {
    public:
        static bool                                                            exec_all_test_suites();
        static inline std::unordered_map<std::string_view, detail::TestSuite*> test_suites;

    public:
        static inline bool                        verbose                 = false;
        static inline bool                        PrintTime               = false;
        static inline PerformanceTestData         PerformanceTest         = PerformanceTestData{};
        static inline ConcurenceSpecificationData ConcurenceSpecification = ConcurenceSpecificationData{};
    };
}
namespace stream::tester::detail
{
    struct TestSuiteData
    {
        bool Redirect_stdout = false;
        bool Redirect_stdin  = false;
        bool Redirect_stderr = false;
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
        std::string                get_full_name();
        std::string                get_corrected_size_name();
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
        [[nodiscard]] static std::expected<void, FMTResult> format(const stream::tester::detail::TestStatusBank& statusBank, FormatterExecutor& executor)
        {
            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string_literal("testsDone "));
            SF_TRY(executor.run("{:C:white}", statusBank.testsDone));

            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string_literal(" | testsOK "));
            if (statusBank.testsOk == statusBank.testsDone)
                { SF_TRY(executor.run("{:C:green}", statusBank.testsOk)); }
            else
                { SF_TRY(executor.run("{:C:yellow}", statusBank.testsOk)); }

            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string_literal(" | testsFAIL "));
            if (statusBank.testsFail == 0)
                { SF_TRY(executor.run("{:C:green}", statusBank.testsFail)); }
            else
                { SF_TRY(executor.run("{:C:red}", statusBank.testsFail)); }

            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string_literal(" | TestCrash "));
            if (statusBank.testsCrash == 0)
                { SF_TRY(executor.run("{:C:green}", statusBank.testsCrash)); }
            else
                { SF_TRY(executor.run("{:C:magenta}", statusBank.testsCrash)); }

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
