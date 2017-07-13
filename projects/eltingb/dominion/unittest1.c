/*
Brian Elting
7/12/2017
CS 362 Section 400

Unit tests for fullDeckCount() function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define NUM_TEST_CARDS 4

int main() {
    int i;
    int player;
    int seed = 1000;
    int numPlayer = 2;
    int maxHandCount = 10;
    int maxDeckCount = 10;
    int maxDiscardCount = 20;
    int deckCount;
    int handCount;
    int discardCount;
    struct gameState G;
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    int testCards[NUM_TEST_CARDS] = { gold, province, village, gardens };
    int testCardCounts[NUM_TEST_CARDS];
    int actualCount;
    int expectedCount;

    printf("UNIT TEST 1\n\n");
    printf("Testing fullDeckCount():\n");

    // Test with several different variations of predefined inputs
    for (player = 0; player < numPlayer; player++) {
        for (deckCount = 0; deckCount < maxDeckCount; deckCount++) {
            for (handCount = 0; handCount < maxHandCount; handCount++) {
                for (discardCount = 0; discardCount < maxDiscardCount; discardCount++) {
                    // Initialize game state
                    memset(&G, 23, sizeof(struct gameState));
                    initializeGame(numPlayer, k, seed, &G);

                    // Clear all card counts
                    for (i = 0; i < NUM_TEST_CARDS; i++) {
                        testCardCounts[i] = 0;
                    }

                    // Add cards to deck
                    G.deckCount[player] = deckCount;
                    for (i = 0; i < deckCount; i++) {
                        G.deck[player][i] = testCards[i % NUM_TEST_CARDS];
                        testCardCounts[i % NUM_TEST_CARDS]++;
                    }

                    // Add cards to hand
                    G.handCount[player] = handCount;
                    for (i = 0; i < handCount; i++) {
                        G.hand[player][i] = testCards[i % NUM_TEST_CARDS];
                        testCardCounts[i % NUM_TEST_CARDS]++;
                    }

                    // Add cards to discard
                    G.discardCount[player] = discardCount;
                    for (i = 0; i < discardCount; i++) {
                        G.discard[player][i] = testCards[i % NUM_TEST_CARDS];
                        testCardCounts[i % NUM_TEST_CARDS]++;
                    }

                    // Run tests for all test cards
                    for (i = 0; i < NUM_TEST_CARDS; i++) {
                        debug("Test player %d with %d deck cards, %d hand cards, %d discard cards, counting card %d: ", player, deckCount, handCount, discardCount, testCards[i]);

                        actualCount = fullDeckCount(player, testCards[i], &G);
                        expectedCount = testCardCounts[i];
                        assertEquals(actualCount, expectedCount);
                    }

                }
            }
        }

    }
    
    printResults();

    return 0;
}