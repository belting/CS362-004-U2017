/*
Brian Elting
7/23/2017
CS 362 Section 400

Random tests for Village card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rngs.h"

// Test Village with provided game state
void checkPlayVillage(int n, int p, struct gameState *post) {
    int r;
    int handPos = 0;
    struct gameState pre;

    // Copy game state
    memcpy(&pre, post, sizeof(struct gameState));
    r = playVillage(post, p, handPos);

    // Set expected number of actions
    pre.numActions += 2;

    // Set expected played cards
    pre.playedCards[pre.playedCardCount] = pre.hand[p][handPos];
    pre.playedCardCount++;

    // Set expected state when deck has cards
    if (pre.deckCount[p] > 0) {
        pre.hand[p][handPos] = pre.deck[p][pre.deckCount[p] - 1];
        pre.hand[p][pre.handCount[p]] = -1;
        pre.deckCount[p]--;
    }
    // Set expected state when deck must be shuffled
    else if (pre.discardCount[p] > 0) {
        memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
        memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);

        pre.hand[p][post->handCount[p]] = post->hand[p][post->handCount[p]];
        pre.hand[p][handPos] = post->hand[p][handPos];
        pre.deckCount[p] = pre.discardCount[p] - 1;
        pre.discardCount[p] = 0;
    }
    // Set expected state when deck and discard pile are empty
    else {
        pre.handCount[p]--;
        pre.hand[p][handPos] = post->hand[p][handPos];
        pre.hand[p][post->handCount[p]] = post->hand[p][post->handCount[p]];
    }

    // Compare actual and expected game states
    printRandomTestResult(post, &pre, p, r, n);
}

int main() {
    struct gameState G;
    int i;
    int n;
    int p;

    printf("RANDOM TEST CARD 2\n\n");
    printf("Testing playVillage():\n");

    SelectStream(2);
    PutSeed(3);

    // Run tests 10,000 times
    for (n = 0; n < 10000; n++) {
        // Set random game state
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * 2);
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * (MAX_HAND - 1)) + 1;
        G.playedCardCount = floor(Random() * MAX_DECK);

        // Test Village with randomized game state
        checkPlayVillage(n, p, &G);
    }

    printResults();

    return 0;
}