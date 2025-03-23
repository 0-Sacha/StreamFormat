#pragma once

#include "stream/flog.hxx"
#include "stream/fmt.hxx"
#include "stream/profiler.hxx"

#include "stream/fmt/serializers/compilation_data.hxx"

#include <concepts>
#include <string>
#include <unordered_map>

namespace stream::tester {
    class TestFailure {};

    enum class TestStatus : int {
        ok,
        fail,
        Crash
    };
}  // namespace stream::tester

namespace stream::tester::detail {
    class TestSuite;
    class Test {
    public:
        Test(std::string_view name_, TestSuite& link, const fmt::detail::FileLocation& location) : name(name_), link(link), location(location), last_status(TestStatus::ok) {}

        virtual ~Test() = default;

    protected:
        virtual TestStatus run_impl() = 0;

    public:
        TestStatus run() {
            try {
                return last_status = run_impl();
            } catch (const TestFailure&) {
                return last_status = TestStatus::fail;
            } catch (...) {
                return last_status = TestStatus::Crash;
            }
        }

    public:
        std::string               name;
        TestSuite&                link;
        fmt::detail::FileLocation location;
        TestStatus                last_status;
    };

    struct TestStatusBank {
        void reset() {
            tests_done   = 0;
            tests_ok     = 0;
            tests_failed = 0;
            tests_crash  = 0;
        }

        void add_test_status(TestStatus status) {
            tests_done++;
            switch (status) {
                case TestStatus::ok:
                    tests_ok++;
                    break;
                case TestStatus::fail:
                    tests_failed++;
                    break;
                case TestStatus::Crash:
                    tests_crash++;
                    break;
            }
        }

        void add(TestStatusBank status) {
            tests_done += status.tests_done;
            tests_ok += status.tests_ok;
            tests_failed += status.tests_failed;
            tests_crash += status.tests_crash;
        }

        bool is_all_ok() {
            return tests_done == tests_ok && tests_crash == 0 && tests_failed == 0;
        }

        std::uint32_t error_status() {
            return tests_done - tests_ok;
        }

        std::uint32_t tests_done   = 0;
        std::uint32_t tests_ok     = 0;
        std::uint32_t tests_failed = 0;
        std::uint32_t tests_crash  = 0;
    };

    class TestSuite;
}  // namespace stream::tester::detail
namespace stream::tester {
    struct performance_testData {
        bool          enable     = false;
        std::uint32_t nb_samples = 10;
    };

    struct ConcurrencySpecificationData {
        bool enable = false;
    };

    class TestSuitesManager {
    public:
        static bool                                                            exec_all_test_suites();
        static inline std::unordered_map<std::string_view, detail::TestSuite*> test_suites;

    public:
        static inline bool                         verbose                   = false;
        static inline bool                         print_time                = false;
        static inline performance_testData         performance_test          = performance_testData{};
        static inline ConcurrencySpecificationData concurrency_specification = ConcurrencySpecificationData{};
    };
}  // namespace stream::tester
namespace stream::tester::detail {
    struct TestSuiteData {
        bool redirect_stdout = false;
        bool redirect_stdin  = false;
        bool redirect_stderr = false;
    };

    class TestSuite {
    public:
        TestSuite(std::string_view name_, TestSuiteData extra_ = TestSuiteData{}, TestSuite* parent_ = nullptr)
            : name(name_), tests(), extra(extra_), logger(), test_logger(), profiler(nullptr), parent(parent_) {
            if (parent == nullptr)
                TestSuitesManager::test_suites.insert({name, this});
            else
                parent->test_suites_linked.insert({name, this});
        }

        std::string                                 name;
        std::unordered_map<std::string, Test*>      tests;
        std::unordered_map<std::string, TestSuite*> test_suites_linked;

        TestSuiteData       extra;
        flog::BasicLogger   logger;
        flog::BasicLogger   test_logger;
        profiler::Profiler* profiler;

        TestSuite* parent;

    public:
        void init_logger();

    private:
        std::string         get_full_name() const;
        std::string         get_corrected_size_name();
        profiler::Profiler& get_profiler() const;

    public:
        TestStatusBank exec_all_tests();
    };
}  // namespace stream::tester::detail

namespace stream::fmt {
    template <typename FormatterExecutor>
    struct FormatterType<stream::tester::detail::TestSuite, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(const stream::tester::detail::TestSuite& t, FormatterExecutor& executor) {
            return executor.ostream.fast_write_string(t.name);
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<stream::tester::detail::Test, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(const stream::tester::detail::Test& t, FormatterExecutor& executor) {
            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string(t.link.name));
            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string_literal("::"));
            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string(t.name));
            return {};
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<stream::tester::TestStatus, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(const stream::tester::TestStatus& status, FormatterExecutor& executor) {
            switch (status) {
                case stream::tester::TestStatus::ok:
                    return executor.run("[  {C:green}OK{C}  ]");
                case stream::tester::TestStatus::fail:
                    return executor.run("[ {C:red}FAIL{C} ]");
                case stream::tester::TestStatus::Crash:
                    return executor.run("[{C:magenta}Crash{C} ]");
            }
            return {};
        }
    };

    template <typename FormatterExecutor>
    struct FormatterType<stream::tester::detail::TestStatusBank, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(const stream::tester::detail::TestStatusBank& status_bank, FormatterExecutor& executor) {
            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string_literal("tests_done "));
            SF_TRY(executor.run("{:C:white}", status_bank.tests_done));

            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string_literal(" | testsOK "));
            if (status_bank.tests_ok == status_bank.tests_done) {
                SF_TRY(executor.run("{:C:green}", status_bank.tests_ok));
            } else {
                SF_TRY(executor.run("{:C:yellow}", status_bank.tests_ok));
            }

            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string_literal(" | testsFAIL "));
            if (status_bank.tests_failed == 0) {
                SF_TRY(executor.run("{:C:green}", status_bank.tests_failed));
            } else {
                SF_TRY(executor.run("{:C:red}", status_bank.tests_failed));
            }

            SF_TRY(buf::WriteManip(executor.ostream).fast_write_string_literal(" | TestCrash "));
            if (status_bank.tests_crash == 0) {
                SF_TRY(executor.run("{:C:green}", status_bank.tests_crash));
            } else {
                SF_TRY(executor.run("{:C:magenta}", status_bank.tests_crash));
            }

            return {};
        }
    };
}  // namespace stream::fmt

//-------------------- Base --------------------//
#define STREAMFORMAT_TESTINTERNAL_SUITE_NAME(TestSuiteName) TestSuite_##TestSuiteName
#define STREAMFORMAT_TESTINTERNAL_FUNC_NAME(TestSuiteName, TestName) TestSuite_##TestSuiteName##TestName
#define STREAMFORMAT_TESTINTERNAL_FUNC_EXEC_NAME(TestSuiteName, TestName) TestSuite_##TestSuiteName##TestName##_ExecMethod
#define STREAMFORMAT_TESTINTERNAL_SUITE_EXTRA(...) \
    stream::tester::detail::TestSuiteData {        \
        __VA_ARGS__                                \
    }

//-------------------- TestSuite --------------------//
#define SFT_TEST_SUITE(TestSuiteName, ...) \
    stream::tester::detail::TestSuite STREAMFORMAT_TESTINTERNAL_SUITE_NAME(TestSuiteName)(#TestSuiteName, STREAMFORMAT_TESTINTERNAL_SUITE_EXTRA(__VA_ARGS__))
#define SFT_TEST_GROUP(TestSuiteName, GroupName, ...)                                                                                                 \
    stream::tester::detail::TestSuite STREAMFORMAT_TESTINTERNAL_SUITE_NAME(GroupName)(#GroupName, STREAMFORMAT_TESTINTERNAL_SUITE_EXTRA(__VA_ARGS__), \
                                                                                      &STREAMFORMAT_TESTINTERNAL_SUITE_NAME(TestSuiteName))

#define SFT_TEST_SUITE_DECLARATION(TestSuiteName, ...) stream::tester::detail::TestSuite STREAMFORMAT_TESTINTERNAL_SUITE_NAME(TestSuiteName)
#define SFT_TEST_GROUP_DECLARATION(TestSuiteName, GroupName, ...) stream::tester::detail::TestSuite STREAMFORMAT_TESTINTERNAL_SUITE_NAME(GroupName)
