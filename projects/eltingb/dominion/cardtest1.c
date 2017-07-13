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
    int testHand[10] = { smithy, silver, copper, adventurer, estate, duchy, village, smithy, copper, copper };
    int testDeck[10] = { duchy, adventurer, estate, copper, minion, remodel, mine, copper, estate, estate };
    int expected;
    int isCurrentPlayer;

    printf("Testing playSmithy():\n");

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

                // Copy game state
                memcpy(&testG, &G, sizeof(struct gameState));

                debug("Test player %d with %d hand cards, %d deck cards, check smithy in hand before play: ", player, handCount, deckCount);
                assertEquals(G.hand[player][0], smithy);

                // Play Smithy card
                playSmithy(&G, player, 0);

                debug("Test player %d with %d hand cards, %d deck cards, check smithy removed from hand after play: ", player, handCount, deckCount);
                assertNotEquals(G.hand[player][0], smithy);

                debug("Test player %d with %d hand cards, %d deck cards, check last played card: ", player, handCount, deckCount);
                assertEquals(G.playedCards[G.playedCardCount - 1], smithy);

                debug("Test player %d with %d hand cards, %d deck cards, check played card count: ", player, handCount, deckCount);
                assertEquals(G.playedCardCount, testG.playedCardCount + 1);

                // Test hand, deck and discard counts for all players
                for (i = 0; i < numPlayer; i++) {
                    isCurrentPlayer = player == i;

                    debug("Test player %d with %d hand cards, %d deck cards, check player %d hand count: ", player, handCount, deckCount, i);

                    expected = (isCurrentPlayer)
                        ? testG.handCount[i] + 2
                        : testG.handCount[i];

                    assertEquals(G.handCount[i], expected);

                    debug("Test player %d with %d hand cards, %d deck cards, check player %d deck count: ", player, handCount, deckCount, i);

                    if (isCurrentPlayer) {
                        expected = (deckCount < 3)
                            ? maxDeckCount - 3
                            : testG.deckCount[i] - 3;
                    }
                    else {
                        expected = testG.deckCount[i];
                    }

                    assertEquals(G.deckCount[i], expected);

                    debug("Test player %d with %d hand cards, %d deck cards, check player %d discard count: ", player, handCount, deckCount, i);

                    expected = (isCurrentPlayer && deckCount < 3)
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