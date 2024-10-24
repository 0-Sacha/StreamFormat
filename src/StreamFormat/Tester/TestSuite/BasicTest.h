#pragma once

#include "TestSuite.h"

namespace StreamFormat::Tester::Detail
{
    struct TestFunction : public Test
    {
    public:
        using FuncType = std::function<void(TestFunction& link)>;

    public:
        TestFunction(std::string&& name, TestSuite& link, FuncType func, const FMT::Detail::FileLocation& location)
            : Test(std::move(name), link, location)
            , Func(func)
        {
            Link.Tests.insert({Name, this});
        }

        ~TestFunction() override = default;

    protected:
        TestStatus RunImpl() override
        {
            Func(*this);
            return TestStatus::Ok;
        }

    public:
        void TestAssert(bool assert, const std::string_view assertView, int line);
        template <typename T>
        void TestEq(T result, std::convertible_to<T> auto expected, std::string_view testView, int line);
        template <typename T>
        void TestNotEq(T result, std::convertible_to<T> auto notExpected, std::string_view testView, int line);

    public:
        FuncType Func;
    };

    template <typename T>
    void TestFunction::TestEq(T result, std::convertible_to<T> auto expected, std::string_view testView, [[maybe_unused]] int line)
    {
        T expected_as_T = static_cast<T>(expected);
        if (result != expected_as_T)
        {
            Link.TestLogger.Error("{C:red}{} return {} instead of {}", testView, result, expected, FORMAT_SV("test_name", Name));
            throw TestFailure{};
        }

        Link.TestLogger.Trace("{C:green}{} return {}", testView, result, FORMAT_SV("test_name", Name));
    }

    template <typename T>
    void TestFunction::TestNotEq(T result, std::convertible_to<T> auto notExpected, std::string_view testView, [[maybe_unused]] int line)
    {
        if (result == static_cast<T>(notExpected))
        {
            Link.TestLogger.Error("{C:red}{} return {} but this result was prohibited", testView, result, FORMAT_SV("test_name", Name));
            throw TestFailure{};
        }

        Link.TestLogger.Trace("{C:green}{} return {}", testView, result, FORMAT_SV("test_name", Name));
    }

    inline void TestFunction::TestAssert(bool assert, std::string_view assertView, [[maybe_unused]] int line)
    {
        if (assert == false)
        {
            Link.TestLogger.Error("{C:red}ASSERT FAILED : {}", assertView, FORMAT_SV("test_name", Name));
            throw TestFailure{};
        }

        Link.TestLogger.Trace("{C:green}ASSERT SUCCED : {}", assertView, FORMAT_SV("test_name", Name));
    }
}

#define STREAMFORMAT_TESTINTERNAL_FUNC_DECLARE_EXEC(TestSuiteName, TestName) \
    void STREAMFORMAT_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName)(StreamFormat::Tester::Detail::TestFunction & link);
#define STREAMFORMAT_TESTINTERNAL_FUNC_CREATE(TestSuiteName, TestName, ...)                                          \
    volatile StreamFormat::Tester::Detail::TestFunction STREAMFORMAT_TESTINTERNAL_FUNC_NAME(TestSuiteName, TestName)( \
        #TestName, STREAMFORMAT_TESTINTERNAL_SUITE_NAME(TestSuiteName), STREAMFORMAT_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName), STREAMFORMAT_FMT_FILE_LOCATION())

#define PCT_TEST_FUNC(TestSuiteName, TestName)                          \
    STREAMFORMAT_TESTINTERNAL_FUNC_DECLARE_EXEC(TestSuiteName, TestName) \
    STREAMFORMAT_TESTINTERNAL_FUNC_CREATE(TestSuiteName, TestName);      \
    void STREAMFORMAT_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName)(StreamFormat::Tester::Detail::TestFunction & link)

#define PCT_ASSERT(Test)           link.TestAssert(Test, #Test, __LINE__)
#define PCT_EQ(Test, Expected)     link.TestEq(Test, Expected, #Test, __LINE__)
#define PCT_NEQ(Test, NotExpected) link.TestNotEq(Test, NotExpected, #Test, __LINE__)
