#include <stdio.h>
#include "testHelpers.h"

int testCount = 0;
int passCount = 0;

void assertFail(const char *msg, const char *file, int line) {
#if VERBOSE == 1
    printf("FAIL at `%s` (%s:%d)\n", msg, file, line);
#endif // VERBOSE == 1

    testCount++;
}

void assertEqualsFail(int actual, int expected, const char *file, int line) {
#if VERBOSE == 1
    printf("FAIL (Actual: %d, Expected: %d) (%s:%d)\n", actual, expected, file, line);
#endif // VERBOSE == 1

    testCount++;
}

void assertPass() {
#if VERBOSE == 1
    printf("PASS\n");
#endif // VERBOSE == 1

    testCount++;
    passCount++;
}

void printResults() {
    if (passCount == testCount) {
        printf("ALL ");
    }

    printf("%d/%d TESTS PASSED\n", passCount, testCount);
}