#include "BaseFMTTests.h"

#include "StreamFormat/FMT/Context/ParserContext/UtilityFunctions.h"

#include "StreamFormat/FMT/Buffer/Utils/PatternMatching/Glob.h"

PCT_TEST_GROUP(FMT, GLOBBER);
#define TEST_GLOBBER(data, glob)                                                           \
    {                                                                                      \
        StreamFormat::FMT::Detail::BasicBufferIn<char> p_buffer(data);                      \
        StreamFormat::FMT::Detail::BasicBufferIn<char> p_glob(glob);                        \
        StreamFormat::FMT::Detail::Globber<char, char>::BufferInExecGlob(p_buffer, p_glob); \
        PCT_ASSERT(p_buffer.IsEnd());                                                      \
    }

PCT_TEST_FUNC(GLOBBER, BASIC_WILDCARD){TEST_GLOBBER("qwerty", "qwerty") TEST_GLOBBER("qwerty", "q?erty") TEST_GLOBBER("qwerty", "q?????") TEST_GLOBBER("qwerty", "qwer?y")
                                           TEST_GLOBBER("qwerty", "qwert?") TEST_GLOBBER("qwerty", "??????") TEST_GLOBBER("qwerty", "*") TEST_GLOBBER("qwerty", "******")
                                               TEST_GLOBBER("qwerty", "*?**?*")}

PCT_TEST_GROUP(FMT, PARSE_GLOBBER);
PCT_TEST_FUNC(PARSE_GLOBBER, PG_BASIC_WILDCARD)
{
    int k = 0;
    StreamFormat::FMT::Parse("|123|", "|{}|", k);
    PCT_EQ(k, 123);

    {
        char test[5];
        StreamFormat::FMT::Parse("|test|", "|{}|", test);
        PCT_EQ(std::string(test), std::string("test"));
    }

    {
        char test[4];
        StreamFormat::FMT::Parse("|test|", "|{:no-zero-end}|", test);
        PCT_EQ(std::string(test, 4), std::string("test"));
    }

    {
        char test[4];
        StreamFormat::FMT::Parse("|test|", "|{}t|", test);
        PCT_EQ(std::string(test), std::string("tes"));
    }

    {
        char test[11];
        StreamFormat::FMT::Parse("|test123456|", "|{}|", test);
        PCT_EQ(std::string(test), std::string("test123456"));
    }

    {
        char test[11];
        StreamFormat::FMT::Parse("|test123456|", "|{:glob='*1'}23456|", test);
        PCT_EQ(std::string(test), std::string("test1"));
    }

    {
        char test[11];
        // just glob = '????' but compiler are anrgy about trigraph on '??'
        StreamFormat::FMT::Parse("|test123456|",
                                "|{:glob='?"
                                "?"
                                "?"
                                "?'}123456|",
                                test);
        PCT_EQ(std::string(test), std::string("test"));
    }
}
