#include <stdio.h>
#include "CuTest.h"

CuSuite* StrUtilGetSuite();
CuSuite* MatrixUtilGetSuite();

void RunAllTests(void) {
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

    CuSuiteAddSuite(suite, StrUtilGetSuite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

//********************************************************
    CuString *output2 = CuStringNew();
    CuSuite* suite2 = CuSuiteNew();

    CuSuiteAddSuite(suite2, MatrixUtilGetSuite());

    CuSuiteRun(suite2);
    CuSuiteSummary(suite2, output2);
    CuSuiteDetails(suite2, output2);
    printf("%s\n", output2->buffer);
//********************************************************

}

int main(void) {
    RunAllTests();
}
