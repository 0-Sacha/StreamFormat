#pragma once

#include "test_suite.h"

#include "stream/core/prelude.h"

namespace stream::tester::detail
{
    struct TestFunction : public Test
    {
    public:
        using FuncType = std::function<void(TestFunction& link)>;

    public:
        TestFunction(std::string&& name, TestSuite& link, FuncType func, const fmt::detail::FileLocation& location)
            : Test(std::move(name), link, location)
            , Func(func)
        {
            Link.tests.insert({name, this});
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

        template <typename T, typename E>
        void TestEq(std::expected<T, E> result, std::convertible_to<T> auto expected, std::string_view testView, int line);
        template <typename T, typename E>
        void TestNotEq(std::expected<T, E> result, std::convertible_to<T> auto notExpected, std::string_view testView, int line);

        template <typename T, typename E>
        void AssertExpected(std::expected<T, E> result, std::string_view testView, int line);
        template <typename T>
        void AssertOptional(std::optional<T> result, std::string_view testView, int line);

    public:
        FuncType Func;
    };

    template <typename T>
    void TestFunction::TestEq(T result, std::convertible_to<T> auto expected, std::string_view testView, [[maybe_unused]] int line)
    {
        T expected_as_T = static_cast<T>(expected);
        if (result != expected_as_T)
        {
            Link.test_logger.error("{C:red}{} return {} instead of {}", testView, result, expected, FORMAT_SV("test_name", name)).value();
            throw TestFailure{};
        }
        Link.test_logger.trace("{C:green}{} return {}", testView, result, FORMAT_SV("test_name", name)).value();
    }
    template <typename T>
    void TestFunction::TestNotEq(T result, std::convertible_to<T> auto notExpected, std::string_view testView, [[maybe_unused]] int line)
    {
        if (result == static_cast<T>(notExpected))
        {
            Link.test_logger.error("{C:red}{} return {} but that result was prohibited", testView, result, FORMAT_SV("test_name", name)).value();
            throw TestFailure{};
        }
        Link.test_logger.trace("{C:green}{} return {}", testView, result, FORMAT_SV("test_name", name)).value();
    }
    inline void TestFunction::TestAssert(bool assert, std::string_view assertView, [[maybe_unused]] int line)
    {
        if (assert == false)
        {
            Link.test_logger.error("{C:red}ASSERT FAILED : {}", assertView, FORMAT_SV("test_name", name)).value();
            throw TestFailure{};
        }
        Link.test_logger.trace("{C:green}ASSERT SUCCED : {}", assertView, FORMAT_SV("test_name", name)).value();
    }


    template <typename T, typename E>
    void TestFunction::TestEq(std::expected<T, E> result, std::convertible_to<T> auto expected, std::string_view testView, [[maybe_unused]] int line)
    {
        if (result.has_value())
            TestEq(result.value(), expected, testView, line);
        else
            AssertExpected(result, testView, line);
    }
    template <typename T, typename E>
    void TestFunction::TestNotEq(std::expected<T, E> result, std::convertible_to<T> auto notExpected, std::string_view testView, [[maybe_unused]] int line)
    {
        if (result.has_value())
            TestEq(result.value(), notExpected, testView, line);
        else
            AssertExpected(result, testView, line);
    }


    template <typename T, typename E>
    void TestFunction::AssertExpected(std::expected<T, E> result, std::string_view testView, int line)
    {
        if (result.has_value() == false)
        {
            Link.test_logger.error("{C:red}{} return an error: {}", testView, result.error(), FORMAT_SV("test_name", name)).value();
            throw TestFailure{};
        }
    }
    template <typename T>
    void TestFunction::AssertOptional(std::optional<T> result, std::string_view testView, int line)
    {
        if (result.has_value() == false)
        {
            Link.test_logger.error("{C:red}{} didn't return any value", testView, FORMAT_SV("test_name", name)).value();
            throw TestFailure{};
        }
    }
}

#define STREAMFORMAT_TESTINTERNAL_FUNC_DECLARE_EXEC(TestSuiteName, TestName) \
    void STREAMFORMAT_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName)(stream::tester::detail::TestFunction & link);
#define STREAMFORMAT_TESTINTERNAL_FUNC_CREATE(TestSuiteName, TestName, ...)                                          \
    volatile stream::tester::detail::TestFunction STREAMFORMAT_TESTINTERNAL_FUNC_NAME(TestSuiteName, TestName)( \
        #TestName, STREAMFORMAT_TESTINTERNAL_SUITE_NAME(TestSuiteName), STREAMFORMAT_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName), STREAMFORMAT_FMT_FILE_LOCATION())

#define SFT_TEST_FUNC(TestSuiteName, TestName)                          \
    STREAMFORMAT_TESTINTERNAL_FUNC_DECLARE_EXEC(TestSuiteName, TestName) \
    STREAMFORMAT_TESTINTERNAL_FUNC_CREATE(TestSuiteName, TestName);      \
    void STREAMFORMAT_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName)(stream::tester::detail::TestFunction & link)

#define SFT_ASSERT(Test)           link.TestAssert(Test, #Test, __LINE__)
#define SFT_EQ(Test, Expected)     link.TestEq(Test, Expected, #Test, __LINE__)
#define SFT_NEQ(Test, NotExpected) link.TestNotEq(Test, NotExpected, #Test, __LINE__)

#define SFT_EXPECTED_VALUE(Test)   link.AssertExpected(Test, #Test, __LINE__)
