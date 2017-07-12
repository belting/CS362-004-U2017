#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define NUM_TEST_CARDS 7

int getCardCost(int card) {
    switch (card) {
    case copper:
        return 0;
    case estate:
        return 2;
    case silver:
        return 3;
    case smithy:
        return 4;
    case minion:
        return 5;
    case gold:
        return 6;
    case province:
        return 8;
    default:
        debug("Cannot get cost of unknown card");
        return -9999;
    }
}

int main() {
    int i;
    int player;
    int seed = 1000;
    int numPlayer = 2;
    int maxHandCount = 8;
    int handCount;
    struct gameState G;
    struct gameState testG;
    int k[10] = { adventurer, council_room, feast, gardens, minion, remodel, smithy, village, baron, great_hall };
    int testHand[8] = { remodel, copper, estate, silver, smithy, minion, gold, province };
    int testGain[NUM_TEST_CARDS] = { copper, estate, silver, smithy, minion, gold, province };
    int expected;
    int isCurrentPlayer;
    int gainCard;
    int gainCardPos;
    int trashCard;
    int trashCardPos;
    int expectedCanPlay;
    int supplyCount[30] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
    int result;

    printf("Testing playRemodel():\n");

    for (player = 0; player < numPlayer; player++) {
        for (handCount = 2; handCount < maxHandCount; handCount++) {
            for (trashCardPos = 1; trashCardPos < handCount; trashCardPos++) {
                for (gainCardPos = 0; gainCardPos < NUM_TEST_CARDS; gainCardPos++) {
                    // Initialize game state
                    memset(&G, 23, sizeof(struct gameState));
                    initializeGame(numPlayer, k, seed, &G);

                    // Initialize cards
                    memcpy(&G.hand[player], &testHand, handCount * sizeof(int));
                    G.handCount[player] = handCount;
                    G.discardCount[player] = 0;
                    memcpy(&G.supplyCount, &supplyCount, (treasure_map + 1) * sizeof(int));

                    // Copy game state
                    memcpy(&testG, &G, sizeof(struct gameState));

                    debug("Test player %d with %d hand cards, trashing card %d to gain card %d, check remodel in hand before play: ", player, handCount, trashCard, gainCard);
                    assertEquals(G.hand[player][0], remodel);

                    gainCard = testGain[gainCardPos];
                    trashCard = testHand[trashCardPos];
                    // Play Remodel card
                    result = playRemodel(&G, player, trashCardPos, gainCard, 0);

                    expectedCanPlay = getCardCost(trashCard) + 2 >= getCardCost(gainCard);

                    debug("Test player %d with %d hand cards, trashing card %d to gain card %d, check result: ", player, handCount, trashCard, gainCard);

                    expected = (expectedCanPlay)
                        ? 0
                        : -1;
                    assertEquals(result, expected);

                    debug("Test player %d with %d hand cards, trashing card %d to gain card %d, check remodel removed from hand after play: ", player, handCount, trashCard, gainCard);
                    if (expectedCanPlay) {
                        assertNotEquals(G.hand[player][0], remodel);
                    }
                    else {
                        assertEquals(G.hand[player][0], remodel);
                    }

                    debug("Test player %d with %d hand cards, trashing card %d to gain card %d, check last played card: ", player, handCount, trashCard, gainCard);
                    if (expectedCanPlay) {
                        assertEquals(G.playedCards[G.playedCardCount - 1], remodel);
                    }
                    else {
                        assertNotEquals(G.playedCards[G.playedCardCount - 1], remodel);

                    }

                    debug("Test player %d with %d hand cards, trashing card %d to gain card %d, check played card count: ", player, handCount, trashCard, gainCard);
                    expected = (expectedCanPlay)
                        ? testG.playedCardCount + 1
                        : testG.playedCardCount;
                    assertEquals(G.playedCardCount, expected);

                    debug("Test player %d with %d hand cards, trashing card %d to gain card %d, check supply card count: ", player, handCount, trashCard, gainCard);
                    expected = (expectedCanPlay)
                        ? testG.supplyCount[gainCard] - 1
                        : testG.supplyCount[gainCard];
                    assertEquals(G.supplyCount[gainCard], expected);

                    // Test hand, deck and discard counts for all players
                    for (i = 0; i < numPlayer; i++) {
                        isCurrentPlayer = player == i;

                        debug("Test player %d with %d hand cards, trashing card %d to gain card %d, check player %d hand count: ", player, handCount, trashCard, gainCard, i);

                        expected = (isCurrentPlayer && expectedCanPlay)
                            ? testG.handCount[i] - 2
                            : testG.handCount[i];

                        assertEquals(G.handCount[i], expected);

                        debug("Test player %d with %d hand cards, trashing card %d to gain card %d, check player %d deck count: ", player, handCount, trashCard, gainCard, i);
                        assertEquals(G.deckCount[i], testG.deckCount[i]);

                        debug("Test player %d with %d hand cards, trashing card %d to gain card %d, check player %d discard count: ", player, handCount, trashCard, gainCard, i);

                        expected = (isCurrentPlayer && expectedCanPlay)
                            ? testG.discardCount[i] + 1
                            : testG.discardCount[i];

                        assertEquals(G.discardCount[i], expected);
                    }
                }
            }
        }

    }

    printResults();

    return 0;
}