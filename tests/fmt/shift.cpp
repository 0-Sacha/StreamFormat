#include "stream/fmt.h"
#include "stream/Tester/TestSuite/AllTestSuite.h"

#include "BaseFMTTests.h"

SFT_TEST_GROUP(FMT, SHIFT);

#define TEST_FMT(fmt_test, expected, ...) SFT_EQ(stream::fmt::FormatString(fmt_test, __VA_ARGS__), expected)

SFT_TEST_GROUP(SHIFT, NUMBER_SHIFT);
SFT_TEST_GROUP(NUMBER_SHIFT, ONE_DIGIT);
SFT_TEST_FUNC(ONE_DIGIT, Right)
{
    TEST_FMT("|{:>9  }|", "|        7|", 7);
    TEST_FMT("|{:>9: }|", "|        7|", 7);
    TEST_FMT("|{:>9:0}|", "|000000007|", 7);
    TEST_FMT("|{:>9:*}|", "|********7|", 7);
}
SFT_TEST_FUNC(ONE_DIGIT, Left)
{
    TEST_FMT("|{:<9  }|", "|7        |", 7);
    TEST_FMT("|{:<9: }|", "|7        |", 7);
    TEST_FMT("|{:<9:0}|", "|7        |", 7);
    TEST_FMT("|{:<9:*}|", "|7********|", 7);
}
SFT_TEST_FUNC(ONE_DIGIT, Center)
{
    TEST_FMT("|{:^10    }|", "|     7    |", 7);
    TEST_FMT("|{:^10:-|-}|", "|-----7----|", 7);
    TEST_FMT("|{:^10:*|*}|", "|*****7****|", 7);
    TEST_FMT("|{:^10:<|>}|", "|<<<<<7>>>>|", 7);
    TEST_FMT("|{:^10:>|<}|", "|>>>>>7<<<<|", 7);

    TEST_FMT("|{:^11:-|-}|", "|-----7-----|", 7);
    TEST_FMT("|{:^11:*|*}|", "|*****7*****|", 7);
    TEST_FMT("|{:^11:<|>}|", "|<<<<<7>>>>>|", 7);
    TEST_FMT("|{:^11:>|<}|", "|>>>>>7<<<<<|", 7);
}
SFT_TEST_FUNC(ONE_DIGIT, CenterRight)
{
    TEST_FMT("|{:^>10:-|-}|", "|-----7----|", 7);
    TEST_FMT("|{:^>10:*|*}|", "|*****7****|", 7);
    TEST_FMT("|{:^>10:<|>}|", "|<<<<<7>>>>|", 7);
    TEST_FMT("|{:^>10:>|<}|", "|>>>>>7<<<<|", 7);

    TEST_FMT("|{:^>11:-|-}|", "|-----7-----|", 7);
    TEST_FMT("|{:^>11:*|*}|", "|*****7*****|", 7);
    TEST_FMT("|{:^>11:<|>}|", "|<<<<<7>>>>>|", 7);
    TEST_FMT("|{:^>11:>|<}|", "|>>>>>7<<<<<|", 7);
}
SFT_TEST_FUNC(ONE_DIGIT, CenterLeft)
{
    TEST_FMT("|{:^<10:-|-}|", "|----7-----|", 7);
    TEST_FMT("|{:^<10:*|*}|", "|****7*****|", 7);
    TEST_FMT("|{:^<10:<|>}|", "|<<<<7>>>>>|", 7);
    TEST_FMT("|{:^<10:>|<}|", "|>>>>7<<<<<|", 7);

    TEST_FMT("|{:^<11:-|-}|", "|-----7-----|", 7);
    TEST_FMT("|{:^<11:*|*}|", "|*****7*****|", 7);
    TEST_FMT("|{:^<11:<|>}|", "|<<<<<7>>>>>|", 7);
    TEST_FMT("|{:^<11:>|<}|", "|>>>>>7<<<<<|", 7);
}

SFT_TEST_GROUP(NUMBER_SHIFT, TWO_DIGIT);
SFT_TEST_FUNC(TWO_DIGIT, Right)
{
    TEST_FMT("|{:>10  }|", "|        14|", 14);
    TEST_FMT("|{:>10: }|", "|        14|", 14);
    TEST_FMT("|{:>10:0}|", "|0000000014|", 14);
    TEST_FMT("|{:>10:*}|", "|********14|", 14);
}
SFT_TEST_FUNC(TWO_DIGIT, Left)
{
    TEST_FMT("|{:<10  }|", "|14        |", 14);
    TEST_FMT("|{:<10: }|", "|14        |", 14);
    TEST_FMT("|{:<10:0}|", "|14        |", 14);
    TEST_FMT("|{:<10:*}|", "|14********|", 14);
}
SFT_TEST_FUNC(TWO_DIGIT, Center)
{
    TEST_FMT("|{:^10    }|", "|    14    |", 14);
    TEST_FMT("|{:^10:-|-}|", "|----14----|", 14);
    TEST_FMT("|{:^10:*|*}|", "|****14****|", 14);
    TEST_FMT("|{:^10:<|>}|", "|<<<<14>>>>|", 14);
    TEST_FMT("|{:^10:>|<}|", "|>>>>14<<<<|", 14);

    TEST_FMT("|{:^11:-|-}|", "|-----14----|", 14);
    TEST_FMT("|{:^11:*|*}|", "|*****14****|", 14);
    TEST_FMT("|{:^11:<|>}|", "|<<<<<14>>>>|", 14);
    TEST_FMT("|{:^11:>|<}|", "|>>>>>14<<<<|", 14);
}
SFT_TEST_FUNC(TWO_DIGIT, CenterRight)
{
    TEST_FMT("|{:^>10:-|-}|", "|----14----|", 14);
    TEST_FMT("|{:^>10:*|*}|", "|****14****|", 14);
    TEST_FMT("|{:^>10:<|>}|", "|<<<<14>>>>|", 14);
    TEST_FMT("|{:^>10:>|<}|", "|>>>>14<<<<|", 14);

    TEST_FMT("|{:^>11:-|-}|", "|-----14----|", 14);
    TEST_FMT("|{:^>11:*|*}|", "|*****14****|", 14);
    TEST_FMT("|{:^>11:<|>}|", "|<<<<<14>>>>|", 14);
    TEST_FMT("|{:^>11:>|<}|", "|>>>>>14<<<<|", 14);
}
SFT_TEST_FUNC(TWO_DIGIT, CenterLeft)
{
    TEST_FMT("|{:^<10:-|-}|", "|----14----|", 14);
    TEST_FMT("|{:^<10:*|*}|", "|****14****|", 14);
    TEST_FMT("|{:^<10:<|>}|", "|<<<<14>>>>|", 14);
    TEST_FMT("|{:^<10:>|<}|", "|>>>>14<<<<|", 14);

    TEST_FMT("|{:^<11:-|-}|", "|----14-----|", 14);
    TEST_FMT("|{:^<11:*|*}|", "|****14*****|", 14);
    TEST_FMT("|{:^<11:<|>}|", "|<<<<14>>>>>|", 14);
    TEST_FMT("|{:^<11:>|<}|", "|>>>>14<<<<<|", 14);
}

SFT_TEST_GROUP(NUMBER_SHIFT, THREE_DIGIT);
SFT_TEST_FUNC(THREE_DIGIT, Right)
{
    TEST_FMT("|{:>11  }|", "|        105|", 105);
    TEST_FMT("|{:>11: }|", "|        105|", 105);
    TEST_FMT("|{:>11:0}|", "|00000000105|", 105);
    TEST_FMT("|{:>11:*}|", "|********105|", 105);
}
SFT_TEST_FUNC(THREE_DIGIT, Left)
{
    TEST_FMT("|{:<11  }|", "|105        |", 105);
    TEST_FMT("|{:<11: }|", "|105        |", 105);
    TEST_FMT("|{:<11:0}|", "|105        |", 105);
    TEST_FMT("|{:<11:*}|", "|105********|", 105);
}
SFT_TEST_FUNC(THREE_DIGIT, Center)
{
    TEST_FMT("|{:^10    }|", "|    105   |", 105);
    TEST_FMT("|{:^10:-|-}|", "|----105---|", 105);
    TEST_FMT("|{:^10:*|*}|", "|****105***|", 105);
    TEST_FMT("|{:^10:<|>}|", "|<<<<105>>>|", 105);
    TEST_FMT("|{:^10:>|<}|", "|>>>>105<<<|", 105);

    TEST_FMT("|{:^11:-|-}|", "|----105----|", 105);
    TEST_FMT("|{:^11:*|*}|", "|****105****|", 105);
    TEST_FMT("|{:^11:<|>}|", "|<<<<105>>>>|", 105);
    TEST_FMT("|{:^11:>|<}|", "|>>>>105<<<<|", 105);
}
SFT_TEST_FUNC(THREE_DIGIT, CenterRight)
{
    TEST_FMT("|{:^>10:-|-}|", "|----105---|", 105);
    TEST_FMT("|{:^>10:*|*}|", "|****105***|", 105);
    TEST_FMT("|{:^>10:<|>}|", "|<<<<105>>>|", 105);
    TEST_FMT("|{:^>10:>|<}|", "|>>>>105<<<|", 105);

    TEST_FMT("|{:^>11:-|-}|", "|----105----|", 105);
    TEST_FMT("|{:^>11:*|*}|", "|****105****|", 105);
    TEST_FMT("|{:^>11:<|>}|", "|<<<<105>>>>|", 105);
    TEST_FMT("|{:^>11:>|<}|", "|>>>>105<<<<|", 105);
}
SFT_TEST_FUNC(THREE_DIGIT, CenterLeft)
{
    TEST_FMT("|{:^<10:-|-}|", "|---105----|", 105);
    TEST_FMT("|{:^<10:*|*}|", "|***105****|", 105);
    TEST_FMT("|{:^<10:<|>}|", "|<<<105>>>>|", 105);
    TEST_FMT("|{:^<10:>|<}|", "|>>>105<<<<|", 105);

    TEST_FMT("|{:^<11:-|-}|", "|----105----|", 105);
    TEST_FMT("|{:^<11:*|*}|", "|****105****|", 105);
    TEST_FMT("|{:^<11:<|>}|", "|<<<<105>>>>|", 105);
    TEST_FMT("|{:^<11:>|<}|", "|>>>>105<<<<|", 105);
}

SFT_TEST_GROUP(SHIFT, STRING_SHIFT);
SFT_TEST_GROUP(STRING_SHIFT, ARRAY);
SFT_TEST_FUNC(ARRAY, Right)
{
    TEST_FMT("|{:>10  }|", "|      test|", "test");
    TEST_FMT("|{:>10: }|", "|      test|", "test");
    TEST_FMT("|{:>10:0}|", "|000000test|", "test");
    TEST_FMT("|{:>10:*}|", "|******test|", "test");
}
SFT_TEST_FUNC(ARRAY, Left)
{
    TEST_FMT("|{:<10  }|", "|test      |", "test");
    TEST_FMT("|{:<10: }|", "|test      |", "test");
    TEST_FMT("|{:<10:0}|", "|test000000|", "test");
    TEST_FMT("|{:<10:*}|", "|test******|", "test");
}
SFT_TEST_FUNC(ARRAY, Center)
{
    TEST_FMT("|{:^10    }|", "|   test   |", "test");
    TEST_FMT("|{:^10:-|-}|", "|---test---|", "test");
    TEST_FMT("|{:^10:*|*}|", "|***test***|", "test");
    TEST_FMT("|{:^10:<|>}|", "|<<<test>>>|", "test");
    TEST_FMT("|{:^10:>|<}|", "|>>>test<<<|", "test");

    TEST_FMT("|{:^11:-|-}|", "|----test---|", "test");
    TEST_FMT("|{:^11:*|*}|", "|****test***|", "test");
    TEST_FMT("|{:^11:<|>}|", "|<<<<test>>>|", "test");
    TEST_FMT("|{:^11:>|<}|", "|>>>>test<<<|", "test");
}
SFT_TEST_FUNC(ARRAY, CenterRight)
{
    TEST_FMT("|{:^>10:-|-}|", "|---test---|", "test");
    TEST_FMT("|{:^>10:*|*}|", "|***test***|", "test");
    TEST_FMT("|{:^>10:<|>}|", "|<<<test>>>|", "test");
    TEST_FMT("|{:^>10:>|<}|", "|>>>test<<<|", "test");

    TEST_FMT("|{:^>11:-|-}|", "|----test---|", "test");
    TEST_FMT("|{:^>11:*|*}|", "|****test***|", "test");
    TEST_FMT("|{:^>11:<|>}|", "|<<<<test>>>|", "test");
    TEST_FMT("|{:^>11:>|<}|", "|>>>>test<<<|", "test");
}
SFT_TEST_FUNC(ARRAY, CenterLeft)
{
    TEST_FMT("|{:^<10:-|-}|", "|---test---|", "test");
    TEST_FMT("|{:^<10:*|*}|", "|***test***|", "test");
    TEST_FMT("|{:^<10:<|>}|", "|<<<test>>>|", "test");
    TEST_FMT("|{:^<10:>|<}|", "|>>>test<<<|", "test");

    TEST_FMT("|{:^<11:-|-}|", "|---test----|", "test");
    TEST_FMT("|{:^<11:*|*}|", "|***test****|", "test");
    TEST_FMT("|{:^<11:<|>}|", "|<<<test>>>>|", "test");
    TEST_FMT("|{:^<11:>|<}|", "|>>>test<<<<|", "test");
}

SFT_TEST_GROUP(STRING_SHIFT, POINTER);
SFT_TEST_FUNC(POINTER, Right)
{
    const char* test = "test";
    TEST_FMT("|{:>10  }|", "|      test|", test);
    TEST_FMT("|{:>10: }|", "|      test|", test);
    TEST_FMT("|{:>10:0}|", "|000000test|", test);
    TEST_FMT("|{:>10:*}|", "|******test|", test);

    const char* test_with_size = "test_with_size";
    TEST_FMT("|{:>10  , size=4}|", "|      test|", test_with_size);
    TEST_FMT("|{:>10: , size=4}|", "|      test|", test_with_size);
    TEST_FMT("|{:>10:0, size=4}|", "|000000test|", test_with_size);
    TEST_FMT("|{:>10:*, size=4}|", "|******test|", test_with_size);
}
SFT_TEST_FUNC(POINTER, Left)
{
    const char* test = "test";
    TEST_FMT("|{:<10  }|", "|test      |", test);
    TEST_FMT("|{:<10: }|", "|test      |", test);
    TEST_FMT("|{:<10:0}|", "|test000000|", test);
    TEST_FMT("|{:<10:*}|", "|test******|", test);

    const char* test_with_size = "test_with_size";
    TEST_FMT("|{:<10  , size=4}|", "|test      |", test_with_size);
    TEST_FMT("|{:<10: , size=4}|", "|test      |", test_with_size);
    TEST_FMT("|{:<10:0, size=4}|", "|test000000|", test_with_size);
    TEST_FMT("|{:<10:*, size=4}|", "|test******|", test_with_size);
}
SFT_TEST_FUNC(POINTER, Center)
{
    const char* test = "test";
    TEST_FMT("|{:^10    }|", "|   test   |", test);
    TEST_FMT("|{:^10:-|-}|", "|---test---|", test);
    TEST_FMT("|{:^10:*|*}|", "|***test***|", test);
    TEST_FMT("|{:^10:<|>}|", "|<<<test>>>|", test);
    TEST_FMT("|{:^10:>|<}|", "|>>>test<<<|", test);

    TEST_FMT("|{:^11:-|-}|", "|----test---|", test);
    TEST_FMT("|{:^11:*|*}|", "|****test***|", test);
    TEST_FMT("|{:^11:<|>}|", "|<<<<test>>>|", test);
    TEST_FMT("|{:^11:>|<}|", "|>>>>test<<<|", test);

    const char* test_with_size = "test_with_size";
    TEST_FMT("|{:^10    , size=4}|", "|   test   |", test_with_size);
    TEST_FMT("|{:^10:-|-, size=4}|", "|---test---|", test_with_size);
    TEST_FMT("|{:^10:*|*, size=4}|", "|***test***|", test_with_size);
    TEST_FMT("|{:^10:<|>, size=4}|", "|<<<test>>>|", test_with_size);
    TEST_FMT("|{:^10:>|<, size=4}|", "|>>>test<<<|", test_with_size);

    TEST_FMT("|{:^11:-|-, size=4}|", "|----test---|", test_with_size);
    TEST_FMT("|{:^11:*|*, size=4}|", "|****test***|", test_with_size);
    TEST_FMT("|{:^11:<|>, size=4}|", "|<<<<test>>>|", test_with_size);
    TEST_FMT("|{:^11:>|<, size=4}|", "|>>>>test<<<|", test_with_size);
}
SFT_TEST_FUNC(POINTER, CenterRight)
{
    const char* test = "test";
    TEST_FMT("|{:^>10:-|-}|", "|---test---|", test);
    TEST_FMT("|{:^>10:*|*}|", "|***test***|", test);
    TEST_FMT("|{:^>10:<|>}|", "|<<<test>>>|", test);
    TEST_FMT("|{:^>10:>|<}|", "|>>>test<<<|", test);

    TEST_FMT("|{:^>11:-|-}|", "|----test---|", test);
    TEST_FMT("|{:^>11:*|*}|", "|****test***|", test);
    TEST_FMT("|{:^>11:<|>}|", "|<<<<test>>>|", test);
    TEST_FMT("|{:^>11:>|<}|", "|>>>>test<<<|", test);

    const char* test_with_size = "test_with_size";
    TEST_FMT("|{:^>10:-|-, size=4}|", "|---test---|", test_with_size);
    TEST_FMT("|{:^>10:*|*, size=4}|", "|***test***|", test_with_size);
    TEST_FMT("|{:^>10:<|>, size=4}|", "|<<<test>>>|", test_with_size);
    TEST_FMT("|{:^>10:>|<, size=4}|", "|>>>test<<<|", test_with_size);

    TEST_FMT("|{:^>11:-|-, size=4}|", "|----test---|", test_with_size);
    TEST_FMT("|{:^>11:*|*, size=4}|", "|****test***|", test_with_size);
    TEST_FMT("|{:^>11:<|>, size=4}|", "|<<<<test>>>|", test_with_size);
    TEST_FMT("|{:^>11:>|<, size=4}|", "|>>>>test<<<|", test_with_size);
}
SFT_TEST_FUNC(POINTER, CenterLeft)
{
    const char* test = "test";
    TEST_FMT("|{:^<10:-|-}|", "|---test---|", test);
    TEST_FMT("|{:^<10:*|*}|", "|***test***|", test);
    TEST_FMT("|{:^<10:<|>}|", "|<<<test>>>|", test);
    TEST_FMT("|{:^<10:>|<}|", "|>>>test<<<|", test);

    TEST_FMT("|{:^<11:-|-}|", "|---test----|", test);
    TEST_FMT("|{:^<11:*|*}|", "|***test****|", test);
    TEST_FMT("|{:^<11:<|>}|", "|<<<test>>>>|", test);
    TEST_FMT("|{:^<11:>|<}|", "|>>>test<<<<|", test);

    const char* test_with_size = "test_with_size";
    TEST_FMT("|{:^<10:-|-, size=4}|", "|---test---|", test_with_size);
    TEST_FMT("|{:^<10:*|*, size=4}|", "|***test***|", test_with_size);
    TEST_FMT("|{:^<10:<|>, size=4}|", "|<<<test>>>|", test_with_size);
    TEST_FMT("|{:^<10:>|<, size=4}|", "|>>>test<<<|", test_with_size);

    TEST_FMT("|{:^<11:-|-, size=4}|", "|---test----|", test_with_size);
    TEST_FMT("|{:^<11:*|*, size=4}|", "|***test****|", test_with_size);
    TEST_FMT("|{:^<11:<|>, size=4}|", "|<<<test>>>>|", test_with_size);
    TEST_FMT("|{:^<11:>|<, size=4}|", "|>>>test<<<<|", test_with_size);
}
