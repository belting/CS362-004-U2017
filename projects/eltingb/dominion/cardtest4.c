/*
Brian Elting
7/12/2017
CS 362 Section 400

Unit tests for Village card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int main() {
    int i;
    int player;
    int seed = 1000;
    int numPlayer = 2;
    int maxHandCount = 10;
    int maxDeckCount = 10;
    int handCount;
    int deckCount;
    struct gameState G;
    struct gameState testG;
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    int testHand[10] = { village, silver, copper, adventurer, estate, duchy, village, smithy, copper, copper };
    int testDeck[10] = { duchy, adventurer, estate, smithy, minion, remodel, mine, smithy, estate, estate };
    int expected;
    int isCurrentPlayer;

    printf("CARD TEST 4\n\n");
    printf("Testing playVillage():\n");

    // Test with several different variations of predefined inputs
    for (player = 0; player < numPlayer; player++) {
        for (handCount = 1; handCount < maxHandCount; handCount++) {
            for (deckCount = 0; deckCount < maxDeckCount; deckCount++) {
                // Initialize game state
                memset(&G, 23, sizeof(struct gameState));
                initializeGame(numPlayer, k, seed, &G);

                // Initialize cards
                memcpy(&G.hand[player], &testHand, handCount * sizeof(int));
                G.handCount[player] = handCount;
                memcpy(&G.deck[player], &testDeck, deckCount * sizeof(int));
                G.deckCount[player] = deckCount;
                memcpy(&G.discard[player], &testDeck, (maxDeckCount - deckCount) * sizeof(int));
                G.discardCount[player] = maxDeckCount - deckCount;

                // Initialize number of actions
                G.numActions = 1;

                // Copy game state
                memcpy(&testG, &G, sizeof(struct gameState));

                debug("Test player %d with %d hand cards, %d deck cards, check village in hand before play: ", player, handCount, deckCount);
                assertEquals(G.hand[player][0], village);

                // Play Village card
                playVillage(&G, player, 0);

                debug("Test player %d with %d hand cards, %d deck cards, check village removed from hand after play: ", player, handCount, deckCount);
                assertNotEquals(G.hand[player][0], village);

                debug("Test player %d with %d hand cards, %d deck cards, check last played card: ", player, handCount, deckCount);
                assertEquals(G.playedCards[G.playedCardCount - 1], village);

                debug("Test player %d with %d hand cards, %d deck cards, check played card count: ", player, handCount, deckCount);
                assertEquals(G.playedCardCount, testG.playedCardCount + 1);

                debug("Test player %d with %d hand cards, %d deck cards, check number of actions: ", player, handCount, deckCount);
                assertEquals(G.numActions, testG.numActions + 2);

                // Test hand, deck and discard counts for all players
                for (i = 0; i < numPlayer; i++) {
                    isCurrentPlayer = player == i;

                    debug("Test player %d with %d hand cards, %d deck cards, check player %d hand count: ", player, handCount, deckCount, i);
                    assertEquals(G.handCount[i], testG.handCount[i]);

                    debug("Test player %d with %d hand cards, %d deck cards, check player %d deck count: ", player, handCount, deckCount, i);

                    if (isCurrentPlayer) {
                        expected = (deckCount == 0)
                            ? maxDeckCount - 1
                            : testG.deckCount[i] - 1;
                    }
                    else {
                        expected = testG.deckCount[i];
                    }
           
                    assertEquals(G.deckCount[i], expected);

                    debug("Test player %d with %d hand cards, %d deck cards, check player %d discard count: ", player, handCount, deckCount, i);

                    expected = (isCurrentPlayer && deckCount == 0)
                        ? 0
                        : testG.discardCount[i];

                    assertEquals(G.discardCount[i], expected);
                }

            }
        }

    }

    printResults();

    return 0;
}