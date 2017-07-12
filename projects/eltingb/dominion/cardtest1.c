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
    int handCount;
    struct gameState G;
    struct gameState testG;
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    int testHand[10] = { smithy, silver, copper, adventurer, estate, duchy, village, smithy, copper, copper };
    int expected;
    int isCurrentPlayer;

    printf("Testing playSmithy():\n");

    for (player = 0; player < numPlayer; player++) {
        for (handCount = 1; handCount < maxHandCount; handCount++) {
            // Initialize game state
            memset(&G, 23, sizeof(struct gameState));
            initializeGame(numPlayer, k, seed, &G);

            // Initialize player hand
            memcpy(&G.hand[player], &testHand, handCount * sizeof(int));
            G.handCount[player] = handCount;

            // Copy game state
            memcpy(&testG, &G, sizeof(struct gameState));

            debug("Test player %d with %d hand cards, check smithy in hand before play: ", player, handCount);
            assertEquals(G.hand[player][0], smithy);

            // Play Smithy card
            playSmithy(&G, player, 0);

            debug("Test player %d with %d hand cards, check smithy removed from hand after play: ", player, handCount);
            assertNotEquals(G.hand[player][0], smithy);

            debug("Test player %d with %d hand cards, check last played card: ", player, handCount);
            assertEquals(G.playedCards[G.playedCardCount - 1], smithy);

            debug("Test player %d with %d hand cards, check played card count: ", player, handCount);
            assertEquals(G.playedCardCount, testG.playedCardCount + 1);

            // Test hand and deck counts for all players
            for (i = 0; i < numPlayer; i++) {
                isCurrentPlayer = player == i;

                debug("Test player %d with %d hand cards, check player %d hand count: ", player, handCount, i);

                expected = (isCurrentPlayer)
                    ? testG.handCount[i] + 2
                    : testG.handCount[i];

                assertEquals(G.handCount[i], expected);

                debug("Test player %d with %d hand cards, check player %d deck count: ", player, handCount, i);

                expected = (isCurrentPlayer)
                    ? testG.deckCount[i] - 3
                    : testG.deckCount[i];

                assertEquals(G.deckCount[i], expected);
            }


        }

    }

    printResults();

    return 0;
}