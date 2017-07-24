/*
Brian Elting
7/12/2017
CS 362 Section 400

Test helpers
*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "testHelpers.h"

int testCount = 0;
int passCount = 0;

void assertFail(const char *msg, const char *file, int line) {
    debug("FAIL at `%s` (%s:%d)\n", msg, file, line);
    testCount++;
}

void assertEqualsFail(int actual, int expected, const char *file, int line, int ignore) {
    debug("FAIL (Actual: %d, Expected: %d) (%s:%d)\n", actual, expected, file, line);

    if (!ignore) {
        testCount++;
    }
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

    printf("%d/%d TESTS PASSED\n\n", passCount, testCount);
}

void printRandomTestResult(struct gameState *actualState, struct gameState *expectedState, int player, int result, int iteration) {
    int i;

    debug("TEST ITERATION %d ", iteration);
    assertEquals(memcmp(actualState, expectedState, sizeof(struct gameState)), 0);

    if (!checkEquals(result, 0)) {
        debug("- Function call result ");
        printEqualsFail(result, 0);
    }

    if (!checkEquals(actualState->deckCount[player], expectedState->deckCount[player])) {
        debug("- Deck count ");
        printEqualsFail(actualState->deckCount[player], expectedState->deckCount[player]);
    }

    if (!checkEquals(actualState->handCount[player], expectedState->handCount[player])) {
        debug("- Hand count ");
        printEqualsFail(actualState->handCount[player], expectedState->handCount[player]);
    }

    if (!checkEquals(actualState->discardCount[player], expectedState->discardCount[player])) {
        debug("- Discard count ");
        printEqualsFail(actualState->discardCount[player], expectedState->discardCount[player]);
    }

    if (!checkEquals(actualState->playedCardCount, expectedState->playedCardCount)) {
        debug("- Played count ");
        printEqualsFail(actualState->playedCardCount, expectedState->playedCardCount);
    }

    for (i = 0; i < MAX_DECK; i++) {
        if (!checkEquals(actualState->deck[player][i], expectedState->deck[player][i])) {
            debug("- Deck card %d ", i);
            printEqualsFail(actualState->deck[player][i], expectedState->deck[player][i]);
        }
    }

    for (i = 0; i < MAX_HAND; i++) {
        if (!checkEquals(actualState->hand[player][i], expectedState->hand[player][i])) {
            debug("- Hand card %d ", i);
            printEqualsFail(actualState->hand[player][i], expectedState->hand[player][i]);
        }
    }

    for (i = 0; i < MAX_DECK; i++) {
        if (!checkEquals(actualState->discard[player][i], expectedState->discard[player][i])) {
            debug("- Discard card %d ", i);
            printEqualsFail(actualState->discard[player][i], expectedState->discard[player][i]);
        }
    }

    for (i = 0; i < actualState->playedCardCount; i++) {
        if (!checkEquals(actualState->playedCards[i], expectedState->playedCards[i])) {
            debug("- Played card %d ", i);
            printEqualsFail(actualState->playedCards[i], expectedState->playedCards[i]);
        }
    }
}