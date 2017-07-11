#include <stdio.h>
#include <stdarg.h>
#include "testHelpers.h"

int testCount = 0;
int passCount = 0;

void assertFail(const char *msg, const char *file, int line) {
    debug("FAIL at `%s` (%s:%d)\n", msg, file, line);
    testCount++;
}

void assertEqualsFail(int actual, int expected, const char *file, int line) {
    debug("FAIL (Actual: %d, Expected: %d) (%s:%d)\n", actual, expected, file, line);
    testCount++;
}

void assertNotEqualsFail(int actual, const char *file, int line) {
    debug("FAIL (Expected Not: %d) (%s:%d)\n", actual, file, line);
    testCount++;
}

void assertPass() {
    debug("PASS\n");
    testCount++;
    passCount++;
}

void printResults() {
    if (passCount == testCount) {
        printf("ALL ");
    }

    printf("%d/%d TESTS PASSED\n", passCount, testCount);
}