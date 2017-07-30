/*
Brian Elting
7/22/2017
CS 362 Section 400

Random tests for Smithy card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rngs.h"

// Test Smithy with provided game state
void checkPlaySmithy(int n, int p, struct gameState *post) {
    int r;
    int handPos = 0;
    struct gameState pre;
    int i;
    int cardCount;
    int drawableCount;

    // Copy game state
    memcpy(&pre, post, sizeof(struct gameState));
    r = playSmithy(post, p, handPos);

    // Set expected played cards
    pre.playedCards[pre.playedCardCount] = pre.hand[p][handPos];
    pre.playedCardCount++;

    // Set expected state when deck has at least 3 cards
    if (pre.deckCount[p] >= 3) {
        pre.handCount[p] += 2;
        pre.hand[p][pre.handCount[p] - 2] = pre.deck[p][pre.deckCount[p] - 1];
        pre.hand[p][pre.handCount[p] - 1] = pre.deck[p][pre.deckCount[p] - 2];
        pre.hand[p][handPos] = pre.deck[p][pre.deckCount[p] - 3];
        pre.hand[p][pre.handCount[p]] = -1;
        pre.deckCount[p] -= 3;
    }
    // Set expected state when deck must be shuffled
    else if (pre.deckCount[p] + pre.discardCount[p] > 0) {
        cardCount = pre.deckCount[p] + pre.discardCount[p];
        drawableCount = (cardCount >= 3)
            ? 3
            : cardCount;

        memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
        memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);

        pre.handCount[p] += drawableCount - 1;
        for (i = 0; i < drawableCount; i++) {
            pre.hand[p][post->handCount[p] - i] = post->hand[p][post->handCount[p] - i];
        }

        pre.hand[p][handPos] = post->hand[p][handPos];
        pre.deckCount[p] = pre.discardCount[p] - (drawableCount - pre.deckCount[p]);
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

    printf("RANDOM TEST CARD 1\n\n");
    printf("Testing playSmithy():\n");

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

        // Test Smithy with randomized game state
        checkPlaySmithy(n, p, &G);
    }

    printResults();

    return 0;
}