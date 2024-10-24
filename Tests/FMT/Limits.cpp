#include "StreamFormat/FMT.h"
#include "StreamFormat/Tester/TestSuite/AllTestSuite.h"

#include "BaseFMTTests.h"

PCT_TEST_GROUP(FMT, LIMITS);

#define PCT_TEST_FUNC_LowBufferSize(k)                                         \
  PCT_TEST_FUNC(LIMITS, LowBufferSize##k) {                                    \
    char buffer[k] = {0};                                                      \
    StreamFormat::FMT::FormatInChar(buffer, "0123456789");                     \
    for (int i = 0; i < k; ++i)                                                \
      PCT_EQ(buffer[i] - '0', i);                                              \
  }

PCT_TEST_FUNC_LowBufferSize(10);
PCT_TEST_FUNC_LowBufferSize(9);
PCT_TEST_FUNC_LowBufferSize(8);
PCT_TEST_FUNC_LowBufferSize(7);
PCT_TEST_FUNC_LowBufferSize(6);
PCT_TEST_FUNC_LowBufferSize(5);
PCT_TEST_FUNC_LowBufferSize(4);
PCT_TEST_FUNC_LowBufferSize(3);
PCT_TEST_FUNC_LowBufferSize(2);
PCT_TEST_FUNC_LowBufferSize(1);

PCT_TEST_FUNC(LIMITS, PlainLowBufferSize10) {
  char buffer[10] = {0};
  StreamFormat::FMT::FormatInChar(buffer, "0123456789");
  for (int i = 0; i < 10; ++i)
    PCT_EQ(buffer[i] - '0', i);
}

PCT_TEST_FUNC(LIMITS, PlainLowBufferSize1) {
  char buffer[1] = {0};
  StreamFormat::FMT::FormatInChar(buffer, "0");
  for (int i = 0; i < 1; ++i)
    PCT_EQ(buffer[i] - '0', i);
}

#define PCT_TEST_FUNC_LowBufferSizeArray(k)                                    \
  PCT_TEST_FUNC(LIMITS, LowBufferSizeArray##k) {                               \
    char buffer[k] = {0};                                                      \
    const char fmtBuffer[] = {                                                 \
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};                     \
    StreamFormat::FMT::Detail::BufferInfoView<char> format(fmtBuffer, k);      \
    StreamFormat::FMT::Detail::GivenBufferOutManager<char> manager(buffer, k); \
    StreamFormat::FMT::Detail::FormatInManager(manager, false, format);        \
    for (int i = 0; i < k; ++i)                                                \
      PCT_EQ(buffer[i] - '0', i);                                              \
  }

PCT_TEST_FUNC_LowBufferSizeArray(10);
PCT_TEST_FUNC_LowBufferSizeArray(9);
PCT_TEST_FUNC_LowBufferSizeArray(8);
PCT_TEST_FUNC_LowBufferSizeArray(7);
PCT_TEST_FUNC_LowBufferSizeArray(6);
PCT_TEST_FUNC_LowBufferSizeArray(5);
PCT_TEST_FUNC_LowBufferSizeArray(4);
PCT_TEST_FUNC_LowBufferSizeArray(3);
PCT_TEST_FUNC_LowBufferSizeArray(2);
PCT_TEST_FUNC_LowBufferSizeArray(1);

PCT_TEST_FUNC(LIMITS, PlainLowBufferSizeArray10) {
  char buffer[10] = {0};
  const char fmtBuffer[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  StreamFormat::FMT::Detail::BufferInfoView<char> fmt(fmtBuffer, 10);
  StreamFormat::FMT::Detail::GivenBufferOutManager<char> manager(buffer, 10);
  StreamFormat::FMT::Detail::FormatInManager(manager, false, fmt);
  for (int i = 0; i < 10; ++i)
    PCT_EQ(buffer[i] - '0', i);
}

PCT_TEST_FUNC(LIMITS, PlainLowBufferSizeArray1) {
  char buffer[1] = {0};
  const char fmtBuffer[] = {'0'};
  StreamFormat::FMT::Detail::BufferInfoView fmt(fmtBuffer, 1);
  StreamFormat::FMT::Detail::GivenBufferOutManager<char> manager(buffer, 1);
  StreamFormat::FMT::Detail::FormatInManager(manager, false, fmt);
  for (int i = 0; i < 1; ++i)
    PCT_EQ(buffer[i] - '0', i);
}

PCT_TEST_FUNC(LIMITS, LowBufferSizeArray10FMT30) {
  char buffer[10] = {0};
  const char fmtBuffer[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  StreamFormat::FMT::Detail::BufferInfoView fmt(fmtBuffer, 30);
  StreamFormat::FMT::Detail::GivenBufferOutManager<char> manager(buffer, 10);
  StreamFormat::FMT::Detail::FormatInManager(manager, false, fmt);
  for (int k = 0; k < 10; ++k)
    PCT_EQ(buffer[k] - '0', k);
}

PCT_TEST_FUNC(LIMITS, LowBufferSizeArray5Number9) {
  char buffer[10] = {0};
  StreamFormat::FMT::Detail::BufferInfoView<char> fmt("{}");
  StreamFormat::FMT::Detail::GivenBufferOutManager<char> manager(buffer, 10);
  std::uint64_t i = 9'876'543'210;
  StreamFormat::FMT::Detail::FormatInManager(manager, false, fmt, i);
  for (int k = 0; k < 10; ++k)
    PCT_EQ(buffer[k] - '0', 9 - k);
}
