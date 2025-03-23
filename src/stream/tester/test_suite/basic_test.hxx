#pragma once

#include "test_suite.h"

#include "stream/core/prelude.h"

namespace stream::tester::detail {
    struct TestFunction : public Test {
    public:
        using FuncType = std::function<void(TestFunction& link)>;

    public:
        TestFunction(std::string_view name, TestSuite& link, FuncType func_, const fmt::detail::FileLocation& location) : Test(name, link, location), func(func_) {
            link.tests.insert({std::string{name}, this});
        }

        ~TestFunction() override = default;

    protected:
        TestStatus run_impl() override {
            func(*this);
            return TestStatus::ok;
        }

    public:
        void test_assert(bool assert, const std::string_view assertView, int line);
        template <typename T>
        void test_eq(T result, std::convertible_to<T> auto expected, std::string_view testView, int line);
        template <typename T>
        void test_not_eq(T result, std::convertible_to<T> auto notExpected, std::string_view testView, int line);

        template <typename T, typename E>
        void test_eq(std::expected<T, E> result, std::convertible_to<T> auto expected, std::string_view testView, int line);
        template <typename T, typename E>
        void test_not_eq(std::expected<T, E> result, std::convertible_to<T> auto notExpected, std::string_view testView, int line);

        template <typename T, typename E>
        void assert_expected(std::expected<T, E> result, std::string_view testView, int line);
        template <typename T>
        void assert_optional(std::optional<T> result, std::string_view testView, int line);

    public:
        FuncType func;
    };

    template <typename T>
    void TestFunction::test_eq(T result, std::convertible_to<T> auto expected, std::string_view testView, [[maybe_unused]] int line) {
        T expected_as_T = static_cast<T>(expected);
        if (result != expected_as_T) {
            link.test_logger.error("{C:red}{} return {} instead of {}", testView, result, expected, FORMAT_SV("test_name", name)).value();
            throw TestFailure{};
        }
        link.test_logger.trace("{C:green}{} return {}", testView, result, FORMAT_SV("test_name", name)).value();
    }
    template <typename T>
    void TestFunction::test_not_eq(T result, std::convertible_to<T> auto notExpected, std::string_view testView, [[maybe_unused]] int line) {
        if (result == static_cast<T>(notExpected)) {
            link.test_logger.error("{C:red}{} return {} but that result was prohibited", testView, result, FORMAT_SV("test_name", name)).value();
            throw TestFailure{};
        }
        link.test_logger.trace("{C:green}{} return {}", testView, result, FORMAT_SV("test_name", name)).value();
    }
    inline void TestFunction::test_assert(bool assert, std::string_view assertView, [[maybe_unused]] int line) {
        if (assert == false) {
            link.test_logger.error("{C:red}ASSERT FAILED : {}", assertView, FORMAT_SV("test_name", name)).value();
            throw TestFailure{};
        }
        link.test_logger.trace("{C:green}ASSERT SUCCED : {}", assertView, FORMAT_SV("test_name", name)).value();
    }


    template <typename T, typename E>
    void TestFunction::test_eq(std::expected<T, E> result, std::convertible_to<T> auto expected, std::string_view testView, [[maybe_unused]] int line) {
        if (result.has_value())
            test_eq(result.value(), expected, testView, line);
        else
            assert_expected(result, testView, line);
    }
    template <typename T, typename E>
    void TestFunction::test_not_eq(std::expected<T, E> result, std::convertible_to<T> auto notExpected, std::string_view testView, [[maybe_unused]] int line) {
        if (result.has_value())
            test_eq(result.value(), notExpected, testView, line);
        else
            assert_expected(result, testView, line);
    }


    template <typename T, typename E>
    void TestFunction::assert_expected(std::expected<T, E> result, std::string_view testView, int line) {
        if (result.has_value() == false) {
            link.test_logger.error("{C:red}{} return an error: {}", testView, result.error(), FORMAT_SV("test_name", name)).value();
            throw TestFailure{};
        }
    }
    template <typename T>
    void TestFunction::assert_optional(std::optional<T> result, std::string_view testView, int line) {
        if (result.has_value() == false) {
            link.test_logger.error("{C:red}{} didn't return any value", testView, FORMAT_SV("test_name", name)).value();
            throw TestFailure{};
        }
    }
}  // namespace stream::tester::detail

#define STREAMFORMAT_TESTINTERNAL_FUNC_DECLARE_EXEC(TestSuiteName, TestName) \
    void STREAMFORMAT_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName)(stream::tester::detail::TestFunction & link);
#define STREAMFORMAT_TESTINTERNAL_FUNC_CREATE(TestSuiteName, TestName, ...)                                     \
    volatile stream::tester::detail::TestFunction STREAMFORMAT_TESTINTERNAL_FUNC_NAME(TestSuiteName, TestName)( \
        #TestName, STREAMFORMAT_TESTINTERNAL_SUITE_NAME(TestSuiteName), STREAMFORMAT_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName), STREAMFORMAT_FMT_FILE_LOCATION())

#define SFT_TEST_FUNC(TestSuiteName, TestName)                           \
    STREAMFORMAT_TESTINTERNAL_FUNC_DECLARE_EXEC(TestSuiteName, TestName) \
    STREAMFORMAT_TESTINTERNAL_FUNC_CREATE(TestSuiteName, TestName);      \
    void STREAMFORMAT_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName)(stream::tester::detail::TestFunction & link)

#define SFT_ASSERT(Test) link.test_assert(Test, #Test, __LINE__)
#define SFT_EQ(Test, Expected) link.test_eq(Test, Expected, #Test, __LINE__)
#define SFT_NEQ(Test, NotExpected) link.test_not_eq(Test, NotExpected, #Test, __LINE__)

#define SFT_EXPECTED_VALUE(Test) link.assert_expected(Test, #Test, __LINE__)
