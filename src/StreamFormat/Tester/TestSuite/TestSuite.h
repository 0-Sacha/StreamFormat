#pragma once

#include "StreamFormat/FLog.h"
#include "StreamFormat/FMT.h"
#include "StreamFormat/ProfilerManager.h"

#include "StreamFormat/FMT/Serializers/CompilationData.h"

#include <concepts>
#include <string>
#include <unordered_map>

namespace StreamFormat::Tester
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

namespace StreamFormat::Tester::Detail
{
    class TestSuite;
    class Test
    {
    public:
        Test(std::string&& name, TestSuite& link, const FMT::Detail::FileLocation& location)
            : Name(std::move(name))
            , Link(link)
            , Location(location)
            , LastStatus(TestStatus::Ok)
        {}

        virtual ~Test() = default;

    protected:
        virtual TestStatus RunImpl() = 0;

    public:
        TestStatus Run()
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
        std::string               Name;
        TestSuite&                Link;
        FMT::Detail::FileLocation Location;
        TestStatus                LastStatus;
    };

    struct TestStatusBank
    {
        void Reset()
        {
            TestsDone  = 0;
            TestsOk    = 0;
            TestsFail  = 0;
            TestsCrash = 0;
        }

        void AddTestStatus(TestStatus status)
        {
            TestsDone++;
            switch (status)
            {
                case TestStatus::Ok:
                    TestsOk++;
                    break;
                case TestStatus::Fail:
                    TestsFail++;
                    break;
                case TestStatus::Crash:
                    TestsCrash++;
                    break;
            }
        }

        void Add(TestStatusBank status)
        {
            TestsDone += status.TestsDone;
            TestsOk += status.TestsOk;
            TestsFail += status.TestsFail;
            TestsCrash += status.TestsCrash;
        }

        bool IsAllOk() { return TestsDone == TestsOk && TestsCrash == 0 && TestsFail == 0; }

        std::uint32_t ErrorStatus() { return TestsDone - TestsOk; }

        std::uint32_t TestsDone  = 0;
        std::uint32_t TestsOk    = 0;
        std::uint32_t TestsFail  = 0;
        std::uint32_t TestsCrash = 0;
    };

    class TestSuite;
}
namespace StreamFormat::Tester
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
        static bool                                                            ExecAllTestSuites();
        static inline std::unordered_map<std::string_view, Detail::TestSuite*> TestSuites;

    public:
        static inline bool                        Verbose                 = false;
        static inline bool                        PrintTime               = false;
        static inline PerformanceTestData         PerformanceTest         = PerformanceTestData{};
        static inline ConcurenceSpecificationData ConcurenceSpecification = ConcurenceSpecificationData{};
    };
}
namespace StreamFormat::Tester::Detail
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
            : Name(std::move(name))
            , Tests()
            , Extra(extra)
            , Logger()
            , TestLogger()
            , Profiler(nullptr)
            , Parent(parent)
        {
            if (parent == nullptr)
                TestSuitesManager::TestSuites.insert({Name, this});
            else
                Parent->TestSuitesLinked.insert({Name, this});
        }

        std::string                                      Name;
        std::unordered_map<std::string_view, Test*>      Tests;
        std::unordered_map<std::string_view, TestSuite*> TestSuitesLinked;

        TestSuiteData              Extra;
        FLog::BasicLogger          Logger;
        FLog::BasicLogger          TestLogger;
        ProfilerManager::Profiler* Profiler;

        TestSuite* Parent;

    public:
        void InitLogger();

    private:
        std::string                GetFullName();
        std::string                GetCorrectedSizeName();
        ProfilerManager::Profiler& GetProfiler();

    public:
        TestStatusBank ExecAllTests();
    };
}

namespace StreamFormat::FMT
{
    template <typename FormatterExecutor>
    struct FormatterType<StreamFormat::Tester::Detail::TestSuite, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> Format(const StreamFormat::Tester::Detail::TestSuite& t, FormatterExecutor& executor)
            { return executor.BufferOut.FastWriteString(t.Name); }
    };

    template <typename FormatterExecutor>
    struct FormatterType<StreamFormat::Tester::Detail::Test, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> Format(const StreamFormat::Tester::Detail::Test& t, FormatterExecutor& executor)
        {
            SF_TRY(Detail::BufferWriteManip(executor.BufferOut).FastWriteString(t.Link.Name));
            SF_TRY(Detail::BufferWriteManip(executor.BufferOut).FastWriteStringLitteral("::"));
            SF_TRY(Detail::BufferWriteManip(executor.BufferOut).FastWriteString(t.Name));
            return {};
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<StreamFormat::Tester::TestStatus, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> Format(const StreamFormat::Tester::TestStatus& status, FormatterExecutor& executor)
        {
            switch (status)
            {
                case StreamFormat::Tester::TestStatus::Ok:
                    return executor.Run("[  {C:green}OK{C}  ]");
                case StreamFormat::Tester::TestStatus::Fail:
                    return executor.Run("[ {C:red}FAIL{C} ]");
                case StreamFormat::Tester::TestStatus::Crash:
                    return executor.Run("[{C:magenta}Crash{C} ]");
            }
            return {};
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<StreamFormat::Tester::Detail::TestStatusBank, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> Format(const StreamFormat::Tester::Detail::TestStatusBank& statusBank, FormatterExecutor& executor)
        {
            SF_TRY(Detail::BufferWriteManip(executor.BufferOut).FastWriteStringLitteral("TestsDone "));
            SF_TRY(executor.Run("{:C:white}", statusBank.TestsDone));

            SF_TRY(Detail::BufferWriteManip(executor.BufferOut).FastWriteStringLitteral(" | TestsOK "));
            if (statusBank.TestsOk == statusBank.TestsDone)
                { SF_TRY(executor.Run("{:C:green}", statusBank.TestsOk)); }
            else
                { SF_TRY(executor.Run("{:C:yellow}", statusBank.TestsOk)); }

            SF_TRY(Detail::BufferWriteManip(executor.BufferOut).FastWriteStringLitteral(" | TestsFAIL "));
            if (statusBank.TestsFail == 0)
                { SF_TRY(executor.Run("{:C:green}", statusBank.TestsFail)); }
            else
                { SF_TRY(executor.Run("{:C:red}", statusBank.TestsFail)); }

            SF_TRY(Detail::BufferWriteManip(executor.BufferOut).FastWriteStringLitteral(" | TestCrash "));
            if (statusBank.TestsCrash == 0)
                { SF_TRY(executor.Run("{:C:green}", statusBank.TestsCrash)); }
            else
                { SF_TRY(executor.Run("{:C:magenta}", statusBank.TestsCrash)); }

            return {};
        }
    };
}

//-------------------- Base --------------------//
#define STREAMFORMAT_TESTINTERNAL_SUITE_NAME(TestSuiteName)               TestSuite_##TestSuiteName
#define STREAMFORMAT_TESTINTERNAL_FUNC_NAME(TestSuiteName, TestName)      TestSuite_##TestSuiteName##TestName
#define STREAMFORMAT_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName) TestSuite_##TestSuiteName##TestName##_ExecMethod
#define STREAMFORMAT_TESTINTERNAL_SUITE_EXTRA(...) \
    StreamFormat::Tester::Detail::TestSuiteData    \
    {                                             \
        __VA_ARGS__                               \
    }

//-------------------- TestSuite --------------------//
#define PCT_TEST_SUITE(TestSuiteName, ...) \
    StreamFormat::Tester::Detail::TestSuite STREAMFORMAT_TESTINTERNAL_SUITE_NAME(TestSuiteName)(#TestSuiteName, STREAMFORMAT_TESTINTERNAL_SUITE_EXTRA(__VA_ARGS__))
#define PCT_TEST_GROUP(TestSuiteName, GroupName, ...)                                                                                                    \
    StreamFormat::Tester::Detail::TestSuite STREAMFORMAT_TESTINTERNAL_SUITE_NAME(GroupName)(#GroupName, STREAMFORMAT_TESTINTERNAL_SUITE_EXTRA(__VA_ARGS__), \
                                                                                          &STREAMFORMAT_TESTINTERNAL_SUITE_NAME(TestSuiteName))

#define PCT_TEST_SUITE_DECLARATION(TestSuiteName, ...)            StreamFormat::Tester::Detail::TestSuite STREAMFORMAT_TESTINTERNAL_SUITE_NAME(TestSuiteName)
#define PCT_TEST_GROUP_DECLARATION(TestSuiteName, GroupName, ...) StreamFormat::Tester::Detail::TestSuite STREAMFORMAT_TESTINTERNAL_SUITE_NAME(GroupName)
