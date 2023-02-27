#include "EngineCore/Tester/TestSuite/AllTestSuite.h"
#include "EngineCore/FMT/FMT.h"

#include "BaseFMTTests.h"

ECT_TEST_GROUP(FMT, SHIFT);

#define TEST_FMT_SHIFT_OneNumberTests(fmt_test, test_data, expected)  ECT_EQ(EngineCore::FMT::FormatString(fmt_test, test_data), expected);

ECT_TEST_FUNC(SHIFT, OneNumberTest_OneDigit)
{
	TEST_FMT_SHIFT_OneNumberTests("|{:>9  }|", 7, "|        7|");
	TEST_FMT_SHIFT_OneNumberTests("|{:>9: }|", 7, "|        7|");
	TEST_FMT_SHIFT_OneNumberTests("|{:>9:0}|", 7, "|000000007|");
	TEST_FMT_SHIFT_OneNumberTests("|{:>9:*}|", 7, "|********7|");
	TEST_FMT_SHIFT_OneNumberTests("|{:<9  }|", 7, "|7        |");
	TEST_FMT_SHIFT_OneNumberTests("|{:<9: }|", 7, "|7        |");
	TEST_FMT_SHIFT_OneNumberTests("|{:<9:0}|", 7, "|7        |");
	TEST_FMT_SHIFT_OneNumberTests("|{:<9:*}|", 7, "|7********|");

	TEST_FMT_SHIFT_OneNumberTests("|{:^10    }|", 7, "|     7    |");
	TEST_FMT_SHIFT_OneNumberTests("|{:^10:-|-}|", 7, "|-----7----|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^10:*|*}|", 7, "|*****7****|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^10:<|>}|", 7, "|<<<<<7>>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^10:>|<}|", 7, "|>>>>>7<<<<|");

	TEST_FMT_SHIFT_OneNumberTests("|{:^>10:-|-}|", 7, "|-----7----|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>10:*|*}|", 7, "|*****7****|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>10:<|>}|", 7, "|<<<<<7>>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>10:>|<}|", 7, "|>>>>>7<<<<|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<10:-|-}|", 7, "|----7-----|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<10:*|*}|", 7, "|****7*****|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<10:<|>}|", 7, "|<<<<7>>>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<10:>|<}|", 7, "|>>>>7<<<<<|");

	TEST_FMT_SHIFT_OneNumberTests("|{:^11:-|-}|", 7, "|-----7-----|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^11:*|*}|", 7, "|*****7*****|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^11:<|>}|", 7, "|<<<<<7>>>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^11:>|<}|", 7, "|>>>>>7<<<<<|");

	TEST_FMT_SHIFT_OneNumberTests("|{:^>11:-|-}|", 7, "|-----7-----|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>11:*|*}|", 7, "|*****7*****|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>11:<|>}|", 7, "|<<<<<7>>>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>11:>|<}|", 7, "|>>>>>7<<<<<|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<11:-|-}|", 7, "|-----7-----|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<11:*|*}|", 7, "|*****7*****|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<11:<|>}|", 7, "|<<<<<7>>>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<11:>|<}|", 7, "|>>>>>7<<<<<|");
}

ECT_TEST_FUNC(SHIFT, OneNumberTest_TwoDigit)
{
	TEST_FMT_SHIFT_OneNumberTests("|{:>10  }|", 14, "|        14|");
	TEST_FMT_SHIFT_OneNumberTests("|{:>10: }|", 14, "|        14|");
	TEST_FMT_SHIFT_OneNumberTests("|{:>10:0}|", 14, "|0000000014|");
	TEST_FMT_SHIFT_OneNumberTests("|{:>10:*}|", 14, "|********14|");
	TEST_FMT_SHIFT_OneNumberTests("|{:<10  }|", 14, "|14        |");
	TEST_FMT_SHIFT_OneNumberTests("|{:<10: }|", 14, "|14        |");
	TEST_FMT_SHIFT_OneNumberTests("|{:<10:0}|", 14, "|14        |");
	TEST_FMT_SHIFT_OneNumberTests("|{:<10:*}|", 14, "|14********|");

	TEST_FMT_SHIFT_OneNumberTests("|{:^10    }|", 14, "|    14    |");
	TEST_FMT_SHIFT_OneNumberTests("|{:^10:-|-}|", 14, "|----14----|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^10:*|*}|", 14, "|****14****|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^10:<|>}|", 14, "|<<<<14>>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^10:>|<}|", 14, "|>>>>14<<<<|");

	TEST_FMT_SHIFT_OneNumberTests("|{:^>10:-|-}|", 14, "|----14----|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>10:*|*}|", 14, "|****14****|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>10:<|>}|", 14, "|<<<<14>>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>10:>|<}|", 14, "|>>>>14<<<<|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<10:-|-}|", 14, "|----14----|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<10:*|*}|", 14, "|****14****|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<10:<|>}|", 14, "|<<<<14>>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<10:>|<}|", 14, "|>>>>14<<<<|");

	TEST_FMT_SHIFT_OneNumberTests("|{:^11:-|-}|", 14, "|-----14----|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^11:*|*}|", 14, "|*****14****|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^11:<|>}|", 14, "|<<<<<14>>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^11:>|<}|", 14, "|>>>>>14<<<<|");

	TEST_FMT_SHIFT_OneNumberTests("|{:^>11:-|-}|", 14, "|-----14----|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>11:*|*}|", 14, "|*****14****|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>11:<|>}|", 14, "|<<<<<14>>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>11:>|<}|", 14, "|>>>>>14<<<<|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<11:-|-}|", 14, "|----14-----|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<11:*|*}|", 14, "|****14*****|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<11:<|>}|", 14, "|<<<<14>>>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<11:>|<}|", 14, "|>>>>14<<<<<|");
}

ECT_TEST_FUNC(SHIFT, OneNumberTest_ThreeDigit)
{
	TEST_FMT_SHIFT_OneNumberTests("|{:>11  }|", 105, "|        105|");
	TEST_FMT_SHIFT_OneNumberTests("|{:>11: }|", 105, "|        105|");
	TEST_FMT_SHIFT_OneNumberTests("|{:>11:0}|", 105, "|00000000105|");
	TEST_FMT_SHIFT_OneNumberTests("|{:>11:*}|", 105, "|********105|");
	TEST_FMT_SHIFT_OneNumberTests("|{:<11  }|", 105, "|105        |");
	TEST_FMT_SHIFT_OneNumberTests("|{:<11: }|", 105, "|105        |");
	TEST_FMT_SHIFT_OneNumberTests("|{:<11:0}|", 105, "|105        |");
	TEST_FMT_SHIFT_OneNumberTests("|{:<11:*}|", 105, "|105********|");

	TEST_FMT_SHIFT_OneNumberTests("|{:^10    }|", 105, "|    105   |");
	TEST_FMT_SHIFT_OneNumberTests("|{:^10:-|-}|", 105, "|----105---|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^10:*|*}|", 105, "|****105***|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^10:<|>}|", 105, "|<<<<105>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^10:>|<}|", 105, "|>>>>105<<<|");

	TEST_FMT_SHIFT_OneNumberTests("|{:^>10:-|-}|", 105, "|----105---|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>10:*|*}|", 105, "|****105***|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>10:<|>}|", 105, "|<<<<105>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>10:>|<}|", 105, "|>>>>105<<<|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<10:-|-}|", 105, "|---105----|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<10:*|*}|", 105, "|***105****|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<10:<|>}|", 105, "|<<<105>>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<10:>|<}|", 105, "|>>>105<<<<|");

	TEST_FMT_SHIFT_OneNumberTests("|{:^11:-|-}|", 105, "|----105----|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^11:*|*}|", 105, "|****105****|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^11:<|>}|", 105, "|<<<<105>>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^11:>|<}|", 105, "|>>>>105<<<<|");

	TEST_FMT_SHIFT_OneNumberTests("|{:^>11:-|-}|", 105, "|----105----|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>11:*|*}|", 105, "|****105****|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>11:<|>}|", 105, "|<<<<105>>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^>11:>|<}|", 105, "|>>>>105<<<<|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<11:-|-}|", 105, "|----105----|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<11:*|*}|", 105, "|****105****|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<11:<|>}|", 105, "|<<<<105>>>>|");
	TEST_FMT_SHIFT_OneNumberTests("|{:^<11:>|<}|", 105, "|>>>>105<<<<|");
}
