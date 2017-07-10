#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#ifndef VERBOSE
#define VERBOSE 1
#endif // !VERBOSE

// Custom assert based on https://www.gnu.org/software/m68hc11/examples/assert_8h-source.html
void assertFail(const char *msg, const char *file, int line);
void assertEqualsFail(int actual, int expected, const char *file, int line);
void assertPass();
void printResults();

#ifdef NDEBUG
# define assert(EX, ACTUAL, EXPECTED)
# define assertEquals(ACTUAL, EXPECTED)
#else
# define assert(EX) (void)((EX) ? assertPass() : (assertFail(#EX, __FILE__, __LINE__), 0))
# define assertEquals(ACTUAL, EXPECTED) (void)((ACTUAL == EXPECTED) ? assertPass() : (assertEqualsFail(ACTUAL, EXPECTED, __FILE__, __LINE__), 0))

#endif // !NDEBUG

#endif // !TEST_HELPERS_H