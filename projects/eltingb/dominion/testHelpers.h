/*
Brian Elting
7/12/2017
CS 362 Section 400

Test helpers
*/

#include "dominion.h"

#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#ifndef VERBOSE
#define VERBOSE 1
#endif // !VERBOSE

void assertFail(const char *msg, const char *file, int line);
void assertEqualsFail(int actual, int expected, const char *file, int line, int ignore);
void assertNotEqualsFail(int actual, const char *file, int line);
void assertPass();
void printResults();
void printRandomTestResult(struct gameState *actualState, struct gameState *expectedState, int player, int result, int iteration);

// Custom assert based on https://www.gnu.org/software/m68hc11/examples/assert_8h-source.html
#ifdef NDEBUG
# define assert(EX, ACTUAL, EXPECTED)
# define assertEquals(ACTUAL, EXPECTED)
# define assertNotEquals(ACTUAL, EXPECTED)
#else
# define assert(EX) (void)((EX) ? assertPass() : (assertFail(#EX, __FILE__, __LINE__), 0))
# define assertEquals(ACTUAL, EXPECTED) (void)((ACTUAL == EXPECTED) ? assertPass() : (assertEqualsFail(ACTUAL, EXPECTED, __FILE__, __LINE__, 0), 0))
# define assertNotEquals(ACTUAL, EXPECTED_NOT) (void)((ACTUAL != EXPECTED_NOT) ? assertPass() : (assertNotEqualsFail(ACTUAL, __FILE__, __LINE__), 0))
# define checkEquals(ACTUAL, EXPECTED) (ACTUAL == EXPECTED)
# define printEqualsFail(ACTUAL, EXPECTED) assertEqualsFail(ACTUAL, EXPECTED, __FILE__, __LINE__, 1)

#endif // !NDEBUG

// Custom print based on https://gcc.gnu.org/onlinedocs/gcc-4.6.3/gcc/Variadic-Macros.html
#if VERBOSE == 1
# define debug(...) printf(__VA_ARGS__)
#else
# define debug(...)
#endif

#endif // !TEST_HELPERS_H