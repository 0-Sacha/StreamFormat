#include "stream/fmt.h"
#include "stream/tester/test_suite/all_test_suite.h"

#include "base_fmt_tests.h"

SFT_TEST_GROUP(FMT, LIMITS);

#define SFT_TEST_FUNC_LowBufferSize(k)                                    \
  SFT_TEST_FUNC(LIMITS, LowBufferSize##k) {                               \
    char buffer[k] = {0};                                                 \
    auto res = stream::fmt::format_in_char(buffer, "0123456789");     \
    SFT_EXPECTED_VALUE(res);                                        \
    for (int i = 0; i < k; ++i)                                           \
      SFT_EQ(buffer[i] - '0', i);                                         \
  }

SFT_TEST_FUNC_LowBufferSize(10);
SFT_TEST_FUNC_LowBufferSize(9);
SFT_TEST_FUNC_LowBufferSize(8);
SFT_TEST_FUNC_LowBufferSize(7);
SFT_TEST_FUNC_LowBufferSize(6);
SFT_TEST_FUNC_LowBufferSize(5);
SFT_TEST_FUNC_LowBufferSize(4);
SFT_TEST_FUNC_LowBufferSize(3);
SFT_TEST_FUNC_LowBufferSize(2);
SFT_TEST_FUNC_LowBufferSize(1);

SFT_TEST_FUNC(LIMITS, PlainLowBufferSize10) {
  char buffer[10] = {0};
  auto res = stream::fmt::format_in_char(buffer, "0123456789");
  SFT_EXPECTED_VALUE(res);
  for (int i = 0; i < 10; ++i)
    SFT_EQ(buffer[i] - '0', i);
}

SFT_TEST_FUNC(LIMITS, PlainLowBufferSize1) {
  char buffer[1] = {0};
  auto res = stream::fmt::format_in_char(buffer, "0");
  SFT_EXPECTED_VALUE(res);
  for (int i = 0; i < 1; ++i)
    SFT_EQ(buffer[i] - '0', i);
}

#define SFT_TEST_FUNC_LowBufferSizeArray(k)                                                 \
  SFT_TEST_FUNC(LIMITS, LowBufferSizeArray##k) {                                            \
    char buffer[k] = {0};                                                                   \
    const char fmtBuffer[] = {                                                              \
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};                                  \
    stream::fmt::buf::StreamView<char> format(fmtBuffer, k);                   \
    stream::fmt::buf::GivenStreamIOManager<char> manager(buffer, k);              \
    auto res = stream::fmt::detail::format_in_manager(manager, false, format);          \
    SFT_EXPECTED_VALUE(res);                                                          \
    for (int i = 0; i < k; ++i)                                                             \
      SFT_EQ(buffer[i] - '0', i);                                                           \
  }

SFT_TEST_FUNC_LowBufferSizeArray(10);
SFT_TEST_FUNC_LowBufferSizeArray(9);
SFT_TEST_FUNC_LowBufferSizeArray(8);
SFT_TEST_FUNC_LowBufferSizeArray(7);
SFT_TEST_FUNC_LowBufferSizeArray(6);
SFT_TEST_FUNC_LowBufferSizeArray(5);
SFT_TEST_FUNC_LowBufferSizeArray(4);
SFT_TEST_FUNC_LowBufferSizeArray(3);
SFT_TEST_FUNC_LowBufferSizeArray(2);
SFT_TEST_FUNC_LowBufferSizeArray(1);

SFT_TEST_FUNC(LIMITS, PlainLowBufferSizeArray10) {
  char buffer[10] = {0};
  const char fmtBuffer[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  stream::fmt::buf::StreamView<char> fmt(fmtBuffer, 10);
  stream::fmt::buf::GivenStreamIOManager<char> manager(buffer, 10);
  auto res = stream::fmt::detail::format_in_manager(manager, false, fmt);
  SFT_EXPECTED_VALUE(res);
  for (int i = 0; i < 10; ++i)
    SFT_EQ(buffer[i] - '0', i);
}

SFT_TEST_FUNC(LIMITS, PlainLowBufferSizeArray1) {
  char buffer[1] = {0};
  const char fmtBuffer[] = {'0'};
  stream::fmt::buf::StreamView fmt(fmtBuffer, 1);
  stream::fmt::buf::GivenStreamIOManager<char> manager(buffer, 1);
  auto res = stream::fmt::detail::format_in_manager(manager, false, fmt);
  SFT_EXPECTED_VALUE(res);
  for (int i = 0; i < 1; ++i)
    SFT_EQ(buffer[i] - '0', i);
}

SFT_TEST_FUNC(LIMITS, LowBufferSizeArray10FMT30) {
  char buffer[10] = {0};
  const char fmtBuffer[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  stream::fmt::buf::StreamView fmt(fmtBuffer, 30);
  stream::fmt::buf::GivenStreamIOManager<char> manager(buffer, 10);
  auto res = stream::fmt::detail::format_in_manager(manager, false, fmt);
  SFT_EXPECTED_VALUE(res);
  for (int k = 0; k < 10; ++k)
    SFT_EQ(buffer[k] - '0', k);
}

SFT_TEST_FUNC(LIMITS, LowBufferSizeArray5Number9) {
  char buffer[10] = {0};
  stream::fmt::buf::StreamView<char> fmt("{}");
  stream::fmt::buf::GivenStreamIOManager<char> manager(buffer, 10);
  std::uint64_t i = 9'876'543'210;
  auto res = stream::fmt::detail::format_in_manager(manager, false, fmt, i);
  SFT_EXPECTED_VALUE(res);
  for (int k = 0; k < 10; ++k)
    SFT_EQ(buffer[k] - '0', 9 - k);
}
