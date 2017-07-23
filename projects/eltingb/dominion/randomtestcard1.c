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

void checkPlaySmithy(int n, int p, struct gameState *post) {
    int r;
    int handPos = 0;
    struct gameState pre;
    int i;
    int cardCount;
    int drawableCount;

    memcpy(&pre, post, sizeof(struct gameState));
    r = playSmithy(post, p, handPos);

    if (pre.deckCount[p] >= 3) {
        pre.playedCards[pre.playedCardCount] = pre.hand[p][handPos];
        pre.playedCardCount++;

        pre.handCount[p] += 2;
        pre.hand[p][pre.handCount[p] - 2] = pre.deck[p][pre.deckCount[p] - 1];
        pre.hand[p][pre.handCount[p] - 1] = pre.deck[p][pre.deckCount[p] - 2];
        pre.hand[p][handPos] = pre.deck[p][pre.deckCount[p] - 3];
        pre.hand[p][pre.handCount[p]] = -1;
        pre.deckCount[p] -= 3;
    }
    else if (pre.deckCount[p] + pre.discardCount[p] > 0) {
        cardCount = pre.deckCount[p] + pre.discardCount[p];
        drawableCount = (cardCount >= 3)
            ? 3
            : cardCount;
        pre.playedCards[pre.playedCardCount] = pre.hand[p][handPos];
        pre.playedCardCount++;

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
    else {
        pre.playedCards[pre.playedCardCount] = pre.hand[p][handPos];
        pre.playedCardCount++;
        pre.handCount[p]--;
        pre.hand[p][handPos] = post->hand[p][handPos];
        pre.hand[p][post->handCount[p]] = post->hand[p][post->handCount[p]];

    }

    /*debug("Deck count ");
    assertEquals(pre.deckCount[p], post->deckCount[p]);

    debug("Hand count ");
    assertEquals(pre.handCount[p], post->handCount[p]);

    debug("Discard count ");
    assertEquals(pre.discardCount[p], post->discardCount[p]);

    debug("Played count ");
    assertEquals(pre.playedCardCount, post->playedCardCount);

    for (i = 0; i < MAX_DECK; i++) {
        debug("Deck card %d ", i);
        assertEquals(pre.deck[p][i], post->deck[p][i]);
    }

    for (i = 0; i < MAX_HAND; i++) {
        debug("Hand card %d ", i);
        assertEquals(pre.hand[p][i], post->hand[p][i]);
    }

    for (i = 0; i < MAX_DECK; i++) {
        debug("Discard card %d ", i);
        assertEquals(pre.discard[p][i], post->discard[p][i]);
    }

    for (i = 0; i < post->playedCardCount; i++) {
        debug("Played card %d ", i);
        assertEquals(pre.playedCards[i], post->playedCards[i]);
    }*/

    debug("Test iteration %d return value ", n);
    assertEquals(r, 0);

    debug("Test iteration %d game state ", n);
    assertEquals(memcmp(&pre, post, sizeof(struct gameState)), 0);
}

int main() {
    struct gameState G;
    int i;
    int n;
    int p;

    printf("RANDOM CARD TEST 1\n\n");
    printf("Testing playSmithy():\n");

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
        G.playedCardCount = floor(Random() * 5);
        checkPlaySmithy(n, p, &G);
    }

    printResults();

    return 0;
}