#include "base_fmt_tests.hxx"

#include "stream/fmt/context/parser_executor/utility_functions.hxx"

#include "stream/fmt/buf/utils/buffer_globber_manip.hxx"

// NOLINTBEGIN(misc-const-correctness)
// NOLINTBEGIN(readability-magic-numbers)
SFT_TEST_GROUP(FMT, GLOBBER);
#define TEST_GLOBBER(data, glob)                                                           \
    {                                                                                      \
        stream::fmt::buf::StreamView<char> p_buffer(data);                                 \
        stream::fmt::buf::StreamView<char> p_glob(glob);                                   \
        stream::fmt::buf::Globber<const char>::buffer_exec_glob(p_buffer, p_glob).value(); \
        SFT_ASSERT(stream::fmt::buf::Access(p_buffer).is_end_of_string());                 \
    }

SFT_TEST_FUNC(GLOBBER, BASIC_WILDCARD){TEST_GLOBBER("qwerty", "qwerty") TEST_GLOBBER("qwerty", "q?erty") TEST_GLOBBER("qwerty", "q?????") TEST_GLOBBER("qwerty", "qwer?y")
                                           TEST_GLOBBER("qwerty", "qwert?") TEST_GLOBBER("qwerty", "??????") TEST_GLOBBER("qwerty", "*") TEST_GLOBBER("qwerty", "******")
                                               TEST_GLOBBER("qwerty", "*?**?*")}

SFT_TEST_GROUP(FMT, PARSE_GLOBBER);
SFT_TEST_FUNC(PARSE_GLOBBER, PG_BASIC_WILDCARD) {
    int k = 0;
    stream::fmt::parse("|123|", "|{}|", k).value();
    SFT_EQ(k, 123);

    {
        // char test[5];
        // stream::fmt::parse("|test|", "|{}|", test).value();
        // SFT_EQ(std::string(test), std::string("test"));
    }

    {
        // char test[4];
        // stream::fmt::parse("|test|", "|{:no-zero-end}|", test).value();
        // SFT_EQ(std::string(test, 4), std::string("test"));
    }

    {
        // char test[4];
        // stream::fmt::parse("|test|", "|{}t|", test).value();
        // SFT_EQ(std::string(test), std::string("tes"));
    }

    {
        // char test[11];
        // stream::fmt::parse("|test123456|", "|{}|", test).value();
        // SFT_EQ(std::string(test), std::string("test123456"));
    }

    {
        // char test[11];
        // stream::fmt::parse("|test123456|", "|{:glob='*1'}23456|", test).value();
        // SFT_EQ(std::string(test), std::string("test1"));
    }

    {
        // char test[11];
        // just glob = '????' but compiler are anrgy about trigraph on '??'
        // stream::fmt::parse("|test123456|",
        //                          "|{:glob='?"
        //                          "?"
        //                          "?"
        //                          "?'}123456|",
        //                          test).value();
        // SFT_EQ(std::string(test), std::string("test"));
    }
}
// NOLINTEND(readability-magic-numbers)
// NOLINTEND(misc-const-correctness)
