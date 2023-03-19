#include "ProjectCore/Tester/TestSuite/AllTestSuite.h"
#include "ProjectCore/FMT/FMT.h"
#include "ProjectCore/FMT/Detail/Buffer/Utils/PatternMatching/Glob/Glob.h"

#include "BaseFMTTests.h"

PCT_TEST_GROUP(FMT, GLOBBER);
#define TEST_GLOBBER(data, glob)  \
                                    { \
                                        ProjectCore::FMT::Detail::BasicBufferIn<char> p_buffer(data); \
                                        ProjectCore::FMT::Detail::BasicBufferIn<char> p_glob(glob); \
                                        ProjectCore::FMT::Detail::Globber<char, char>::BufferInExecGlob(p_buffer, p_glob); \
                                        PCT_ASSERT(p_buffer.IsEnd()); \
                                    }

PCT_TEST_FUNC(GLOBBER, BASIC_WILDCARD)
{
    TEST_GLOBBER("qwerty", "qwerty");
    TEST_GLOBBER("qwerty", "q?erty");
    TEST_GLOBBER("qwerty", "q?????");
    TEST_GLOBBER("qwerty", "qwer?y");
    TEST_GLOBBER("qwerty", "qwert?");
    TEST_GLOBBER("qwerty", "??????");
    TEST_GLOBBER("qwerty", "*");
    TEST_GLOBBER("qwerty", "******");
    TEST_GLOBBER("qwerty", "*?**?*");
}

PCT_TEST_GROUP(FMT, PARSE_GLOBBER);
PCT_TEST_FUNC(PARSE_GLOBBER, PG_BASIC_WILDCARD)
{
    int k = 0;
    ProjectCore::FMT::Parse("|123|", "|{}|", k);
    PCT_EQ(k, 123);

    {
        char test[5];
        ProjectCore::FMT::Parse("|test|", "|{}|", test);
        PCT_EQ(std::string(test), std::string("test"));
    }

    {
        char test[4];
        ProjectCore::FMT::Parse("|test|", "|{:no-zero-end}|", test);
        PCT_EQ(std::string(test), std::string("test"));
    }
    
    {
        char test[4];
        ProjectCore::FMT::Parse("|test|", "|{}t|", test);
        PCT_EQ(std::string(test), std::string("tes"));
    }

    {
        char test[11];
        ProjectCore::FMT::Parse("|test123456|", "|{}|", test);
        PCT_EQ(std::string(test), std::string("test123456"));
    }

    {
        char test[11];
        ProjectCore::FMT::Parse("|test123456|", "|{:glob='*1'}23456|", test);
        PCT_EQ(std::string(test), std::string("test1"));
    }

    {
        char test[11];
        // just glob = '????' but compiler are anrgy about trigraph on '??'
        ProjectCore::FMT::Parse("|test123456|", "|{:glob='?""?""?""?'}123456|", test);
        PCT_EQ(std::string(test), std::string("test"));
    }
}

