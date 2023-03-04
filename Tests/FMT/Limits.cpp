#include "EngineCore/Tester/TestSuite/AllTestSuite.h"

#include "BaseFMTTests.h"

ECT_TEST_GROUP(FMT, LIMITS);

#define ECT_TEST_FUNC_LowBufferSize(k)      \
                                            ECT_TEST_FUNC(LIMITS, LowBufferSize ## k)\
                                            {\
                                                char buffer[k] = { 0 };\
                                                EngineCore::FMT::FormatInChar(buffer, "0123456789");\
                                                for (int i = 0; i < k; ++i)\
                                                    ECT_EQ(buffer[i] - '0', i);\
                                            }

ECT_TEST_FUNC_LowBufferSize(10);
ECT_TEST_FUNC_LowBufferSize(9);
ECT_TEST_FUNC_LowBufferSize(8);
ECT_TEST_FUNC_LowBufferSize(7);
ECT_TEST_FUNC_LowBufferSize(6);
ECT_TEST_FUNC_LowBufferSize(5);
ECT_TEST_FUNC_LowBufferSize(4);
ECT_TEST_FUNC_LowBufferSize(3);
ECT_TEST_FUNC_LowBufferSize(2);
ECT_TEST_FUNC_LowBufferSize(1);

ECT_TEST_FUNC(LIMITS, PlainLowBufferSize10)
{
    char buffer[10] = { 0 };
    EngineCore::FMT::FormatInChar(buffer, "0123456789");
    for (int i = 0; i < 10; ++i)
        ECT_EQ(buffer[i] - '0', i);
}

ECT_TEST_FUNC(LIMITS, PlainLowBufferSize1)
{
    char buffer[1] = { 0 };
    EngineCore::FMT::FormatInChar(buffer, "0");
    for (int i = 0; i < 1; ++i)
        ECT_EQ(buffer[i] - '0', i);
}

#define ECT_TEST_FUNC_LowBufferSizeArray(k)      \
                                            ECT_TEST_FUNC(LIMITS, LowBufferSizeArray ## k)\
                                            {\
                                                char buffer[k] = { 0 };\
                                                const char fmtBuffer[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };\
	                                            EngineCore::FMT::Detail::BufferInProperties<char> properties(fmtBuffer, k);\
                                                EngineCore::FMT::Detail::GivenBufferOutManager<char> manager(buffer, k);\
                                                EngineCore::FMT::Detail::FormatInBufferOutManager(manager, properties, false);\
                                                for (int i = 0; i < k; ++i)\
                                                    ECT_EQ(buffer[i] - '0', i);\
                                            }

ECT_TEST_FUNC_LowBufferSizeArray(10);
ECT_TEST_FUNC_LowBufferSizeArray(9);
ECT_TEST_FUNC_LowBufferSizeArray(8);
ECT_TEST_FUNC_LowBufferSizeArray(7);
ECT_TEST_FUNC_LowBufferSizeArray(6);
ECT_TEST_FUNC_LowBufferSizeArray(5);
ECT_TEST_FUNC_LowBufferSizeArray(4);
ECT_TEST_FUNC_LowBufferSizeArray(3);
ECT_TEST_FUNC_LowBufferSizeArray(2);
ECT_TEST_FUNC_LowBufferSizeArray(1);

ECT_TEST_FUNC(LIMITS, PlainLowBufferSizeArray10)
{
    char buffer[10] = { 0 };
    const char fmtBuffer[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	EngineCore::FMT::Detail::BufferInProperties<char> properties(fmtBuffer, 10);
	EngineCore::FMT::Detail::GivenBufferOutManager<char> manager(buffer, 10);
    EngineCore::FMT::Detail::FormatInBufferOutManager(manager, properties, false);
    for (int i = 0; i < 10; ++i)
        ECT_EQ(buffer[i] - '0', i);
}

ECT_TEST_FUNC(LIMITS, PlainLowBufferSizeArray1)
{
    char buffer[1] = { 0 };
    const char fmtBuffer[] = { '0' };
	EngineCore::FMT::Detail::BufferInProperties<char> properties(fmtBuffer, 1);
	EngineCore::FMT::Detail::GivenBufferOutManager<char> manager(buffer, 1);
	EngineCore::FMT::Detail::FormatInBufferOutManager(manager, properties, false);
    for (int i = 0; i < 1; ++i)
        ECT_EQ(buffer[i] - '0', i);
}



ECT_TEST_FUNC(LIMITS, LowBufferSizeArray10FMT30)
{
	char buffer[10] = { 0 };
	const char fmtBuffer[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
    };
	EngineCore::FMT::Detail::BufferInProperties<char> properties(fmtBuffer, 30);
	EngineCore::FMT::Detail::GivenBufferOutManager<char> manager(buffer, 10);
	EngineCore::FMT::Detail::FormatInBufferOutManager(manager, properties, false);
	for (int i = 0; i < 10; ++i)
		ECT_EQ(buffer[i] - '0', i);
}


ECT_TEST_FUNC(LIMITS, LowBufferSizeArray5Number9)
{
	char buffer[10] = { 0 };
	EngineCore::FMT::Detail::BufferInProperties<char> properties("{}");
	EngineCore::FMT::Detail::GivenBufferOutManager<char> manager(buffer, 10);
	std::uint64_t i = 9'876'543'210;
	EngineCore::FMT::Detail::FormatInBufferOutManager(manager, properties, false, i);
	for (int i = 0; i < 10; ++i)
		ECT_EQ(buffer[i] - '0', 9 - i);
}
