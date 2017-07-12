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
    int testHand[10] = { adventurer, silver, copper, adventurer, estate, duchy, village, smithy, copper, copper };
    int testDeck[10] = { duchy, adventurer, estate, smithy, village, remodel, mine, smithy, estate, estate };
    int treasureCards[3] = { copper, silver, gold };
    int treasurePos[10];
    int expected;
    int isCurrentPlayer;
    int deckPos;
    int expectedDiscardCount;
    int treasuresFound;

    printf("Testing playAdventurer():\n");

    for (player = 0; player < numPlayer; player++) {
        for (handCount = 1; handCount < maxHandCount; handCount++) {
            for (deckCount = 3; deckCount < maxDeckCount; deckCount++) {
                // Initialize game state
                memset(&G, 23, sizeof(struct gameState));
                initializeGame(numPlayer, k, seed, &G);

                // Initialize cards
                memcpy(&G.hand[player], &testHand, handCount * sizeof(int));
                G.handCount[player] = handCount;
                memcpy(&G.deck[player], &testDeck, deckCount * sizeof(int));
                G.deckCount[player] = deckCount;
                G.discardCount[player] = 0;

                // Clear treasure positions
                for (i = deckCount - 1; i >= 0; i--) {
                    treasurePos[i] = 0;
                }

                // Insert treasure cards throughout deck
                for (i = 0; i < 3; i++) {
                    deckPos = (deckCount / 3) * (i + 1);
                    deckPos = i;
                    G.deck[player][deckPos] = treasureCards[i];
                    treasurePos[deckPos] = 1;
                }

                // Determine number of cards we expect to be discarded
                treasuresFound = 0;
                expectedDiscardCount = 0;
                i = deckCount - 1;
                while (treasuresFound < 2) {
                    if (treasurePos[i]) {
                        treasuresFound++;
                    }
                    else {
                        expectedDiscardCount++;
                    }
                    i--;
                }

                // Copy game state
                memcpy(&testG, &G, sizeof(struct gameState));

                debug("Test player %d with %d hand cards, %d deck cards, check adventurer in hand before play: ", player, handCount, deckCount);
                assertEquals(G.hand[player][0], adventurer);

                // Play Adventurer card
                playAdventurer(&G, player);

                debug("Test player %d with %d hand cards, %d deck cards, check adventurer removed from hand after play: ", player, handCount, deckCount);
                assertNotEquals(G.hand[player][0], adventurer);

                debug("Test player %d with %d hand cards, %d deck cards, check last played card: ", player, handCount, deckCount);
                assertEquals(G.playedCards[G.playedCardCount - 1], adventurer);

                debug("Test player %d with %d hand cards, %d deck cards, check played card count: ", player, handCount, deckCount);
                assertEquals(G.playedCardCount, testG.playedCardCount + 1);

                // Test hand, deck and discard counts for all players
                for (i = 0; i < numPlayer; i++) {
                    isCurrentPlayer = player == i;

                    debug("Test player %d with %d hand cards, %d deck cards, check player %d hand count: ", player, handCount, deckCount, i);

                    expected = (isCurrentPlayer)
                        ? testG.handCount[i] + 1
                        : testG.handCount[i];

                    assertEquals(G.handCount[i], expected);

                    debug("Test player %d with %d hand cards, %d deck cards, check player %d deck count: ", player, handCount, deckCount, i);

                    expected = (isCurrentPlayer)
                        ? testG.deckCount[i] - expectedDiscardCount - 2
                        : testG.deckCount[i];

                    assertEquals(G.deckCount[i], expected);

                    debug("Test player %d with %d hand cards, %d deck cards, check player %d discard count: ", player, handCount, deckCount, i);

                    expected = (isCurrentPlayer)
                        ? testG.discardCount[i] + expectedDiscardCount
                        : testG.discardCount[i];

                    assertEquals(G.discardCount[i], expected);
                }

            }
        }

    }

    printResults();

    return 0;
}