#include "ProjectCore/Tester/TestSuite/AllTestSuite.h"
#include "ProjectCore/FMT.h"

#include "BaseFMTTests.h"

PCT_TEST_GROUP(FMT, TEXT_PROPERTIES);

#define TEST_FMT(fmt_test, expected)  PCT_EQ(Escaper(ProjectCore::FMT::FormatString(fmt_test, 0)), Escaper(expected))

static std::string Escaper(const std::string& str)
{
    std::string res;
    for (char c : str)
    {
        if (c != '\033')
        {
            res.push_back(c);
            continue;
        }

        res.push_back('\\');
        res.push_back('e');
    }
    return res;
}

PCT_TEST_GROUP(TEXT_PROPERTIES, ESCAPER_VALIDATING);
#define TEST_ESCAPER(str, str_res)  PCT_EQ(Escaper(str), str_res)
PCT_TEST_FUNC(ESCAPER_VALIDATING, BasicTest)
{
    TEST_ESCAPER("\033", "\\e");
    TEST_ESCAPER("\033k", "\\ek");
}

PCT_TEST_FUNC(TEXT_PROPERTIES, BasicColor)
{
    TEST_FMT("123", "123");

    TEST_FMT("{C:black} 123 "     , "\033[30m 123 \033[39m");
    TEST_FMT("{C:red} 123 "       , "\033[31m 123 \033[39m");
    TEST_FMT("{C:green} 123 "     , "\033[32m 123 \033[39m");
    TEST_FMT("{C:yellow} 123 "    , "\033[33m 123 \033[39m");
    TEST_FMT("{C:blue} 123 "      , "\033[34m 123 \033[39m");
    TEST_FMT("{C:magenta} 123 "   , "\033[35m 123 \033[39m");
    TEST_FMT("{C:cyan} 123 "      , "\033[36m 123 \033[39m");
    TEST_FMT("{C:white} 123 "     , "\033[37m 123 \033[39m");

    TEST_FMT("{C:+black} 123 "     , "\033[90m 123 \033[39m");
    TEST_FMT("{C:+red} 123 "       , "\033[91m 123 \033[39m");
    TEST_FMT("{C:+green} 123 "     , "\033[92m 123 \033[39m");
    TEST_FMT("{C:+yellow} 123 "    , "\033[93m 123 \033[39m");
    TEST_FMT("{C:+blue} 123 "      , "\033[94m 123 \033[39m");
    TEST_FMT("{C:+magenta} 123 "   , "\033[95m 123 \033[39m");
    TEST_FMT("{C:+cyan} 123 "      , "\033[96m 123 \033[39m");
    TEST_FMT("{C:+white} 123 "     , "\033[97m 123 \033[39m");
}

PCT_TEST_FUNC(TEXT_PROPERTIES, DoubleBasicColor)
{
    TEST_FMT("123", "123");

    TEST_FMT("{C:black} 1 {C:white} 23 "        , "\033[30m 1 \033[37m 23 \033[39m");
    TEST_FMT("{C:red} 1 {C:black} 23 "          , "\033[31m 1 \033[30m 23 \033[39m");
    TEST_FMT("{C:green} 1 {C:red} 23 "          , "\033[32m 1 \033[31m 23 \033[39m");
    TEST_FMT("{C:yellow} 1 {C:green} 23 "       , "\033[33m 1 \033[32m 23 \033[39m");
    TEST_FMT("{C:blue} 1 {C:yellow} 23 "        , "\033[34m 1 \033[33m 23 \033[39m");
    TEST_FMT("{C:magenta} 1 {C:blue} 23 "       , "\033[35m 1 \033[34m 23 \033[39m");
    TEST_FMT("{C:cyan} 1 {C:magenta} 23 "       , "\033[36m 1 \033[35m 23 \033[39m");
    TEST_FMT("{C:white} 1 {C:cyan} 23 "         , "\033[37m 1 \033[36m 23 \033[39m");

    TEST_FMT("{C:+black} 1 {C:+white} 23 "      , "\033[90m 1 \033[97m 23 \033[39m");
    TEST_FMT("{C:+red} 1 {C:+black} 23 "        , "\033[91m 1 \033[90m 23 \033[39m");
    TEST_FMT("{C:+green} 1 {C:+red} 23 "        , "\033[92m 1 \033[91m 23 \033[39m");
    TEST_FMT("{C:+yellow} 1 {C:+green} 23 "     , "\033[93m 1 \033[92m 23 \033[39m");
    TEST_FMT("{C:+blue} 1 {C:+yellow} 23 "      , "\033[94m 1 \033[93m 23 \033[39m");
    TEST_FMT("{C:+magenta} 1 {C:+blue} 23 "     , "\033[95m 1 \033[94m 23 \033[39m");
    TEST_FMT("{C:+cyan} 1 {C:+magenta} 23 "     , "\033[96m 1 \033[95m 23 \033[39m");
    TEST_FMT("{C:+white} 1 {C:+cyan} 23 "       , "\033[97m 1 \033[96m 23 \033[39m");
}


class TEST_FMT_ContextOut {};
PROJECTCORE_AUTO_FORMATTER_T(TEST_FMT_ContextOut, "{C:red} TEST_FMT_ContextOut {} ", 0);

#define TEST_FMT_CONTEXT(fmt_test, expected)  PCT_EQ(Escaper(ProjectCore::FMT::FormatString(fmt_test, TEST_FMT_ContextOut{})), Escaper(expected))

PCT_TEST_FUNC(TEXT_PROPERTIES, ContextOut)
{
    TEST_FMT_CONTEXT("{}", "\033[31m TEST_FMT_ContextOut 0 \033[39m");

    TEST_FMT_CONTEXT("{} 123 ", "\033[31m TEST_FMT_ContextOut 0 \033[39m 123 ");
    
    // TODO : check before doing a TextPropertiesExecution, should only have one \033[31m
    TEST_FMT_CONTEXT("{C:red}{} 123 ", "\033[31m TEST_FMT_ContextOut 0  123 \033[39m");
    
    TEST_FMT_CONTEXT("{C:+red}{} 123 ", "\033[91m\033[31m TEST_FMT_ContextOut 0 \033[91m 123 \033[39m");
}
