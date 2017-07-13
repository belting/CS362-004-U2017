/*
Brian Elting
7/12/2017
CS 362 Section 400

Unit tests for scoreFor() function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define NUM_TEST_CARDS 6

int getExpectedCoins(int cards[]) {
    int i;
    int cardCount = 0;
    int score = 0;

    for (i = 0; i < NUM_TEST_CARDS; i++) {
        cardCount += cards[i];
    }

    score += cards[0] * -1; // Curse
    score += cards[1] * 1; // Estate
    score += cards[2] * 3; // Duchy
    score += cards[3] * 6; // Province
    score += cards[4] * 1; // Great Hall
    score += cards[5] * (cardCount / 10); // Gardens

    return score;
}

int main() {
    int i;
    int player;
    int seed = 1000;
    int numPlayer = 2;
    int maxHandCount = 5;
    int maxDeckCount = 10;
    int maxDiscardCount = 5;
    int deckCount;
    int handCount;
    int discardCount;
    struct gameState G;
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    int testCards[NUM_TEST_CARDS] = { curse, estate, duchy, province, great_hall, gardens };
    int testCardCounts[NUM_TEST_CARDS];
    int actualScore;
    int expectedScore;
    int testCard;

    printf("UNIT TEST 2\n\n");
    printf("Testing scoreFor():\n");

    // Test with several different variations of predefined inputs
    for (player = 0; player < numPlayer; player++) {
        for (deckCount = 0; deckCount < maxDeckCount; deckCount++) {
            for (handCount = 0; handCount < maxHandCount; handCount++) {
                for (discardCount = 0; discardCount < maxDiscardCount; discardCount++) {
                    // Test mixture of cards

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

                    expectedScore = getExpectedCoins(testCardCounts);
                    actualScore = scoreFor(player, &G);

                    debug("Test player %d with %d deck cards, %d hand cards, %d discard cards, using mixed cards: ", player, deckCount, handCount, discardCount);
                    assertEquals(actualScore, expectedScore);

                    // Test hands full of same card
                    for (testCard = 0; testCard < NUM_TEST_CARDS; testCard++) {
                        // Initialize game state
                        memset(&G, 23, sizeof(struct gameState));
                        initializeGame(numPlayer, k, seed, &G);

                        // Clear all card counts
                        for (i = 0; i < NUM_TEST_CARDS; i++) {
                            testCardCounts[i] = 0;
                        }

                        // Add cards to deck
                        for (i = 0; i < deckCount; i++) {
                            G.deck[player][i] = testCards[testCard];
                            testCardCounts[testCard]++;
                        }

                        // Add cards to hand
                        G.handCount[player] = handCount;
                        for (i = 0; i < handCount; i++) {
                            G.hand[player][i] = testCards[testCard];
                            testCardCounts[testCard]++;
                        }

                        // Add cards to discard
                        G.discardCount[player] = discardCount;
                        for (i = 0; i < discardCount; i++) {
                            G.discard[player][i] = testCards[testCard];
                            testCardCounts[testCard]++;
                        }

                        expectedScore = getExpectedCoins(testCardCounts);
                        actualScore = scoreFor(player, &G);

                        debug("Test player %d with %d deck cards, %d hand cards, %d discard cards, using card %d: ", player, deckCount, handCount, discardCount, testCards[testCard]);
                        assertEquals(actualScore, expectedScore);
                    }

                }
            }
        }

    }

    printResults();

    return 0;
}