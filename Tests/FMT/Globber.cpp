#include "ProjectCore/Tester/TestSuite/AllTestSuite.h"
#include "ProjectCore/FMT/FMT.h"
#include "ProjectCore/FMT/Detail/Buffer/Utils/PatternMatching/Glob/Glob.h"

#include "BaseFMTTests.h"

PCT_TEST_GROUP(FMT, GLOBBER);
PCT_TEST_FUNC(GLOBBER, BASIC_WILDCARD)
{
    ProjectCore::FMT::Detail::BasicBufferIn<char> buffer("LAW");
    ProjectCore::FMT::Detail::BasicBufferIn<char> glob("LAW");

    ProjectCore::FMT::Detail::Globber<char, char>::BufferInExecGlob(buffer, glob);

    PCT_ASSERT(buffer.IsEnd());
}
