#include <string.h>
#include <ctype.h>
#include "CuTest.h"

char* StrToUpper(char* pStr) {

    while( *pStr != '\0' )
    {
        *pStr = toupper((unsigned char) *pStr);
        ++pStr;
    }
    return "HELLO WORLD";
}

void TestStrToUpper(CuTest *tc) {
    char* input = strdup("hello world");
    char* actual = StrToUpper(input);
    char* expected = "HELLO WORLD";
    CuAssertStrEquals(tc, expected, actual);
}

CuSuite* StrUtilGetSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestStrToUpper);
    return suite;
}
