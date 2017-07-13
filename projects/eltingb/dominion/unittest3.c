/*
Brian Elting
7/12/2017
CS 362 Section 400

Unit tests for isGameOver() function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define NUM_TEST_CARDS 27
#define MAX_EMPTY_PILES 5

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    struct gameState G;
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    int testCards[NUM_TEST_CARDS] = { curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast,
        gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute,
        ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map
    };
    int startTestCard;
    int emptyPiles;
    int testCard;
    int expectedResult;

    printf("UNIT TEST 3\n\n");
    printf("Testing isGameOver():\n");

    // Initialize game state
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);

    debug("Test if game over after initializing game: ");
    assertEquals(isGameOver(&G), 0);

    // Test with several different variations of predefined inputs
    for (emptyPiles = 0; emptyPiles <= MAX_EMPTY_PILES; emptyPiles++) {
        for (startTestCard = 0; startTestCard < NUM_TEST_CARDS; startTestCard++) {
            // Initialize game state
            memset(&G, 23, sizeof(struct gameState));
            initializeGame(numPlayer, k, seed, &G);

            expectedResult = 0;

            // Expect game to be over if 3 or more supply piles are empty
            if (emptyPiles >= 3) {
                expectedResult = 1;
            }

            // Empty supply piles
            for (i = 0; i < emptyPiles; i++) {
                testCard = testCards[(startTestCard + i) % NUM_TEST_CARDS];
                G.supplyCount[testCard] = 0;
                
                // Expect game to be over if Province supply pile is empty
                if (testCard == province) {
                    expectedResult = 1;
                }
            }

            debug("Test if game over when %d supply piles are empty, beginning with card %d: ", emptyPiles, testCards[startTestCard]);
            assertEquals(isGameOver(&G), expectedResult);
        }
    }

    printResults();

    return 0;
}