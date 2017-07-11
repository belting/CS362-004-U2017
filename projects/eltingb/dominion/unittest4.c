#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define NUM_TEST_CARDS 6

int getExpectedCoins(int cards[], int bonus) {
    int coins = bonus;

    coins += cards[0] * 1; // Copper
    coins += cards[1] * 2; // Silver
    coins += cards[2] * 3; // Gold

    // Ignore other cards as they don't add coins

    return coins;
}

int main() {
    int i;
    int player;
    int seed = 1000;
    int numPlayer = 2;
    int maxHandCount = 20;
    int maxBonus = 20;
    int handCount;
    int bonus;
    struct gameState G;
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    int testCards[NUM_TEST_CARDS] = { copper, silver, gold, adventurer, estate, duchy };
    int testCardCounts[NUM_TEST_CARDS];
    int actualScore;
    int expectedScore;
    int testCard;

    printf("Testing updateCoins():\n");

    for (player = 0; player < numPlayer; player++) {
        for (handCount = 0; handCount < maxHandCount; handCount++) {
            for (bonus = 0; bonus < maxBonus; bonus++) {
                // Test mixture of cards

                // Initialize game state
                memset(&G, 23, sizeof(struct gameState));
                initializeGame(numPlayer, k, seed, &G);

                // Clear all card counts
                for (i = 0; i < NUM_TEST_CARDS; i++) {
                    testCardCounts[i] = 0;
                }

                // Add cards to hand
                G.handCount[player] = handCount;
                for (i = 0; i < handCount; i++) {
                    G.hand[player][i] = testCards[i % NUM_TEST_CARDS];
                    testCardCounts[i % NUM_TEST_CARDS]++;
                }

                updateCoins(player, &G, bonus);

                expectedScore = getExpectedCoins(testCardCounts, bonus);
                actualScore = G.coins;

                debug("Test player %d with %d hand cards and %d bonus, using mixed cards: ", player, handCount, bonus);
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

                    // Add cards to hand
                    G.handCount[player] = handCount;
                    for (i = 0; i < handCount; i++) {
                        G.hand[player][i] = testCards[testCard];
                        testCardCounts[testCard]++;
                    }

                    updateCoins(player, &G, bonus);

                    expectedScore = getExpectedCoins(testCardCounts, bonus);
                    actualScore = G.coins;

                    debug("Test player %d with %d hand cards and %d bonus, using card %d: ", player, handCount, bonus, testCards[testCard]);
                    assertEquals(actualScore, expectedScore);
                }

            }
        }

    }

    printResults();

    return 0;
}