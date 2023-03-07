#include "ProjectCore/Tester/TestSuite/AllTestSuite.h"
#include "ProjectCore/FMT/FMT.h"

#include "BaseFMTTests.h"

PCT_TEST_GROUP(FMT, LIMITS);

#define PCT_TEST_FUNC_LowBufferSize(k)      \
                                            PCT_TEST_FUNC(LIMITS, LowBufferSize ## k)\
                                            {\
                                                char buffer[k] = { 0 };\
                                                ProjectCore::FMT::FormatInChar(buffer, "0123456789");\
                                                for (int i = 0; i < k; ++i)\
                                                    PCT_EQ(buffer[i] - '0', i);\
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

PCT_TEST_FUNC(LIMITS, PlainLowBufferSize10)
{
    char buffer[10] = { 0 };
    ProjectCore::FMT::FormatInChar(buffer, "0123456789");
    for (int i = 0; i < 10; ++i)
        PCT_EQ(buffer[i] - '0', i);
}

PCT_TEST_FUNC(LIMITS, PlainLowBufferSize1)
{
    char buffer[1] = { 0 };
    ProjectCore::FMT::FormatInChar(buffer, "0");
    for (int i = 0; i < 1; ++i)
        PCT_EQ(buffer[i] - '0', i);
}

#define PCT_TEST_FUNC_LowBufferSizeArray(k)      \
                                            PCT_TEST_FUNC(LIMITS, LowBufferSizeArray ## k)\
                                            {\
                                                char buffer[k] = { 0 };\
                                                const char fmtBuffer[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };\
	                                            ProjectCore::FMT::Detail::BufferInProperties<char> properties(fmtBuffer, k);\
                                                ProjectCore::FMT::Detail::GivenBufferOutManager<char> manager(buffer, k);\
                                                ProjectCore::FMT::Detail::FormatInBufferOutManager(manager, properties, false);\
                                                for (int i = 0; i < k; ++i)\
                                                    PCT_EQ(buffer[i] - '0', i);\
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

PCT_TEST_FUNC(LIMITS, PlainLowBufferSizeArray10)
{
    char buffer[10] = { 0 };
    const char fmtBuffer[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	ProjectCore::FMT::Detail::BufferInProperties<char> properties(fmtBuffer, 10);
	ProjectCore::FMT::Detail::GivenBufferOutManager<char> manager(buffer, 10);
    ProjectCore::FMT::Detail::FormatInBufferOutManager(manager, properties, false);
    for (int i = 0; i < 10; ++i)
        PCT_EQ(buffer[i] - '0', i);
}

PCT_TEST_FUNC(LIMITS, PlainLowBufferSizeArray1)
{
    char buffer[1] = { 0 };
    const char fmtBuffer[] = { '0' };
	ProjectCore::FMT::Detail::BufferInProperties<char> properties(fmtBuffer, 1);
	ProjectCore::FMT::Detail::GivenBufferOutManager<char> manager(buffer, 1);
	ProjectCore::FMT::Detail::FormatInBufferOutManager(manager, properties, false);
    for (int i = 0; i < 1; ++i)
        PCT_EQ(buffer[i] - '0', i);
}



PCT_TEST_FUNC(LIMITS, LowBufferSizeArray10FMT30)
{
	char buffer[10] = { 0 };
	const char fmtBuffer[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
    };
	ProjectCore::FMT::Detail::BufferInProperties<char> properties(fmtBuffer, 30);
	ProjectCore::FMT::Detail::GivenBufferOutManager<char> manager(buffer, 10);
	ProjectCore::FMT::Detail::FormatInBufferOutManager(manager, properties, false);
	for (int i = 0; i < 10; ++i)
		PCT_EQ(buffer[i] - '0', i);
}


PCT_TEST_FUNC(LIMITS, LowBufferSizeArray5Number9)
{
	char buffer[10] = { 0 };
	ProjectCore::FMT::Detail::BufferInProperties<char> properties("{}");
	ProjectCore::FMT::Detail::GivenBufferOutManager<char> manager(buffer, 10);
	std::uint64_t i = 9'876'543'210;
	ProjectCore::FMT::Detail::FormatInBufferOutManager(manager, properties, false, i);
	for (int i = 0; i < 10; ++i)
		PCT_EQ(buffer[i] - '0', 9 - i);
}
