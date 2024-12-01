#include "BaseFMTTests.h"

#include "StreamFormat/FMT/Context/ParserExecutor/UtilityFunctions.h"

#include "StreamFormat/FMT/Buffer/Utils/BufferGlobberManip.h"

SFT_TEST_GROUP(FMT, GLOBBER);
#define TEST_GLOBBER(data, glob)                                                  \
  {                                                                               \
    StreamFormat::FMT::Detail::BufferInfoView<char> p_buffer(data);               \
    StreamFormat::FMT::Detail::BufferInfoView<char> p_glob(glob);                 \
    StreamFormat::FMT::Detail::Globber<const char>::BufferInExecGlob(p_buffer,    \
                                                               p_glob).value();   \
    SFT_ASSERT(                                                                   \
        StreamFormat::FMT::Detail::BufferAccess(p_buffer).IsEndOfString());       \
  }

SFT_TEST_FUNC(GLOBBER, BASIC_WILDCARD){
    TEST_GLOBBER("qwerty", "qwerty") TEST_GLOBBER("qwerty", "q?erty")
        TEST_GLOBBER("qwerty", "q?????") TEST_GLOBBER("qwerty", "qwer?y")
            TEST_GLOBBER("qwerty", "qwert?") TEST_GLOBBER("qwerty", "??????")
                TEST_GLOBBER("qwerty", "*") TEST_GLOBBER("qwerty", "******")
                    TEST_GLOBBER("qwerty", "*?**?*")}

SFT_TEST_GROUP(FMT, PARSE_GLOBBER);
SFT_TEST_FUNC(PARSE_GLOBBER, PG_BASIC_WILDCARD) {
  int k = 0;
  StreamFormat::FMT::Parse("|123|", "|{}|", k).value();
  SFT_EQ(k, 123);

  {
    // char test[5];
    // StreamFormat::FMT::Parse("|test|", "|{}|", test).value();
    // SFT_EQ(std::string(test), std::string("test"));
  }

  {
    // char test[4];
    // StreamFormat::FMT::Parse("|test|", "|{:no-zero-end}|", test).value();
    // SFT_EQ(std::string(test, 4), std::string("test"));
  }

  {
    // char test[4];
    // StreamFormat::FMT::Parse("|test|", "|{}t|", test).value();
    // SFT_EQ(std::string(test), std::string("tes"));
  }

  {
    // char test[11];
    // StreamFormat::FMT::Parse("|test123456|", "|{}|", test).value();
    // SFT_EQ(std::string(test), std::string("test123456"));
  }

  {
    // char test[11];
    // StreamFormat::FMT::Parse("|test123456|", "|{:glob='*1'}23456|", test).value();
    // SFT_EQ(std::string(test), std::string("test1"));
  }

  {
    // char test[11];
    // just glob = '????' but compiler are anrgy about trigraph on '??'
    // StreamFormat::FMT::Parse("|test123456|",
    //                          "|{:glob='?"
    //                          "?"
    //                          "?"
    //                          "?'}123456|",
    //                          test).value();
    // SFT_EQ(std::string(test), std::string("test"));
  }
}
