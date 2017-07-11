#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#ifndef VERBOSE
#define VERBOSE 1
#endif // !VERBOSE

// Custom assert based on https://www.gnu.org/software/m68hc11/examples/assert_8h-source.html
void assertFail(const char *msg, const char *file, int line);
void assertEqualsFail(int actual, int expected, const char *file, int line);
void assertNotEqualsFail(int actual, const char *file, int line);
void assertPass();
void printResults();

#ifdef NDEBUG
# define assert(EX, ACTUAL, EXPECTED)
# define assertEquals(ACTUAL, EXPECTED)
# define assertNotEquals(ACTUAL, EXPECTED)
#else
# define assert(EX) (void)((EX) ? assertPass() : (assertFail(#EX, __FILE__, __LINE__), 0))
# define assertEquals(ACTUAL, EXPECTED) (void)((ACTUAL == EXPECTED) ? assertPass() : (assertEqualsFail(ACTUAL, EXPECTED, __FILE__, __LINE__), 0))
# define assertNotEquals(ACTUAL, EXPECTED_NOT) (void)((ACTUAL != EXPECTED_NOT) ? assertPass() : (assertNotEqualsFail(ACTUAL, __FILE__, __LINE__), 0))


#endif // !NDEBUG

// Custom print based on https://gcc.gnu.org/onlinedocs/gcc-4.6.3/gcc/Variadic-Macros.html
#if VERBOSE == 1
# define debug(...) printf(__VA_ARGS__)
#else
# define debug(...)
#endif


#endif // !TEST_HELPERS_H