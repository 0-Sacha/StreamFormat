#pragma once

#include "ProjectCore/FLog.h"
#include "ProjectCore/FMT.h"
#include "ProjectCore/ProfilerManager.h"

#include "ProjectCore/FMT/Serializers/CompilationData.h"

#include <concepts>
#include <string>
#include <unordered_map>

namespace ProjectCore::Tester
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

namespace ProjectCore::Tester::Detail
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
namespace ProjectCore::Tester
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
namespace ProjectCore::Tester::Detail
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

namespace ProjectCore::FMT
{
    template <typename FormatContext>
    struct FormatterType<ProjectCore::Tester::Detail::TestSuite, FormatContext>
    {
        static void Format(const ProjectCore::Tester::Detail::TestSuite& t, FormatContext& context) { context.BufferOut().FastWriteString(t.Name); }
    };

    template <typename FormatContext>
    struct FormatterType<ProjectCore::Tester::Detail::Test, FormatContext>
    {
        static void Format(const ProjectCore::Tester::Detail::Test& t, FormatContext& context)
        {
            context.BufferOut().FastWriteString(t.Link.Name);
            context.BufferOut().FastWriteCharArray("::");
            context.BufferOut().FastWriteString(t.Name);
        }
    };

    template <typename FormatContext>
    struct FormatterType<ProjectCore::Tester::TestStatus, FormatContext>
    {
        static void Format(const ProjectCore::Tester::TestStatus& status, FormatContext& context)
        {
            switch (status)
            {
                case ProjectCore::Tester::TestStatus::Ok:
                    context.SubContextArrayFMT("[  {C:green}OK{C}  ]");
                    break;
                case ProjectCore::Tester::TestStatus::Fail:
                    context.SubContextArrayFMT("[ {C:red}FAIL{C} ]");
                    break;
                case ProjectCore::Tester::TestStatus::Crash:
                    context.SubContextArrayFMT("[{C:magenta}Crash{C} ]");
                    break;
            }
        }
    };

    template <typename FormatContext>
    struct FormatterType<ProjectCore::Tester::Detail::TestStatusBank, FormatContext>
    {
        static void Format(const ProjectCore::Tester::Detail::TestStatusBank& statusBank, FormatContext& context)
        {
            context.BufferOut().FastWriteCharArray("TestsDone ");
            context.SubContextArrayFMT("{:C:white}", statusBank.TestsDone);

            context.BufferOut().FastWriteCharArray(" | TestsOK ");
            if (statusBank.TestsOk == statusBank.TestsDone)
                context.SubContextArrayFMT("{:C:green}", statusBank.TestsOk);
            else
                context.SubContextArrayFMT("{:C:yellow}", statusBank.TestsOk);

            context.BufferOut().FastWriteCharArray(" | TestsFAIL ");
            if (statusBank.TestsFail == 0)
                context.SubContextArrayFMT("{:C:green}", statusBank.TestsFail);
            else
                context.SubContextArrayFMT("{:C:red}", statusBank.TestsFail);

            context.BufferOut().FastWriteCharArray(" | TestCrash ");
            if (statusBank.TestsCrash == 0)
                context.SubContextArrayFMT("{:C:green}", statusBank.TestsCrash);
            else
                context.SubContextArrayFMT("{:C:magenta}", statusBank.TestsCrash);
        }
    };
}

//-------------------- Base --------------------//
#define PROJECTCORE_TESTINTERNAL_SUITE_NAME(TestSuiteName)               TestSuite_##TestSuiteName
#define PROJECTCORE_TESTINTERNAL_FUNC_NAME(TestSuiteName, TestName)      TestSuite_##TestSuiteName##TestName
#define PROJECTCORE_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName) TestSuite_##TestSuiteName##TestName##_ExecMethod
#define PROJECTCORE_TESTINTERNAL_SUITE_EXTRA(...) \
    ProjectCore::Tester::Detail::TestSuiteData    \
    {                                             \
        __VA_ARGS__                               \
    }

//-------------------- TestSuite --------------------//
#define PCT_TEST_SUITE(TestSuiteName, ...) \
    ProjectCore::Tester::Detail::TestSuite PROJECTCORE_TESTINTERNAL_SUITE_NAME(TestSuiteName)(#TestSuiteName, PROJECTCORE_TESTINTERNAL_SUITE_EXTRA(__VA_ARGS__))
#define PCT_TEST_GROUP(TestSuiteName, GroupName, ...)                                                                                                    \
    ProjectCore::Tester::Detail::TestSuite PROJECTCORE_TESTINTERNAL_SUITE_NAME(GroupName)(#GroupName, PROJECTCORE_TESTINTERNAL_SUITE_EXTRA(__VA_ARGS__), \
                                                                                          &PROJECTCORE_TESTINTERNAL_SUITE_NAME(TestSuiteName))

#define PCT_TEST_SUITE_DECLARATION(TestSuiteName, ...)            ProjectCore::Tester::Detail::TestSuite PROJECTCORE_TESTINTERNAL_SUITE_NAME(TestSuiteName)
#define PCT_TEST_GROUP_DECLARATION(TestSuiteName, GroupName, ...) ProjectCore::Tester::Detail::TestSuite PROJECTCORE_TESTINTERNAL_SUITE_NAME(GroupName)
