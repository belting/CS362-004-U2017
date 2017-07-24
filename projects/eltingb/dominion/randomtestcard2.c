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

void checkPlayVillage(int n, int p, struct gameState *post) {
    int r;
    int handPos = 0;
    struct gameState pre;

    memcpy(&pre, post, sizeof(struct gameState));
    r = playVillage(post, p, handPos);

    pre.numActions += 2;

    pre.playedCards[pre.playedCardCount] = pre.hand[p][handPos];
    pre.playedCardCount++;

    if (pre.deckCount[p] > 0) {
        pre.hand[p][handPos] = pre.deck[p][pre.deckCount[p] - 1];
        pre.hand[p][pre.handCount[p]] = -1;
        pre.deckCount[p]--;
    }
    else if (pre.discardCount[p] > 0) {
        memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
        memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);

        pre.hand[p][post->handCount[p]] = post->hand[p][post->handCount[p]];
        pre.hand[p][handPos] = post->hand[p][handPos];
        pre.deckCount[p] = pre.discardCount[p] - 1;
        pre.discardCount[p] = 0;
    }
    else {
        pre.handCount[p]--;
        pre.hand[p][handPos] = post->hand[p][handPos];
        pre.hand[p][post->handCount[p]] = post->hand[p][post->handCount[p]];
    }

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

    for (n = 0; n < 10000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * 2);
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * (MAX_HAND - 1)) + 1;
        G.playedCardCount = floor(Random() * MAX_DECK);
        checkPlayVillage(n, p, &G);
    }

    printResults();

    return 0;
}