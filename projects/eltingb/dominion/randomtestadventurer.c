/*
Brian Elting
7/23/2017
CS 362 Section 400

Random tests for Adventurer card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rngs.h"

int getRandomTreasureCard() {
    int num = floor(Random() * 3);

    switch (num) {
    case 0:
        return copper;
    case 1:
        return silver;
    case 2:
    default:
        return gold;
    }
}

int isTreasureCard(int card) {
    return card == copper || card == silver || card == gold;
}

int countTreasureCards(int cards[], int n) {
    int i;
    int count = 0;

    for (i = 0; i < n; i++) {
        if (isTreasureCard(cards[i])) {
            count++;
        }
    }

    return count;
}

int getNextTreasureCardIndex(int cards[], int start) {
    int i;

    for (i = start; i >= 0; i--) {
        if (isTreasureCard(cards[i])) {
            return i;
        }
    }
    
    return -1;
}

void addTreasureCards(int p, struct gameState *state) {
    int treasuresAdded = 0;
    int deckPos = -1;
    int discardPos = -1;
    int pos;

    int treasureCount = 2 + floor(Random() * 2);

    while (treasuresAdded < treasureCount) {
        if ((int)floor(Random() * 2) % 2 && state->deckCount[p] > 0) {
            pos = floor(Random() * state->deckCount[p]);
            if (pos != deckPos) {
                deckPos = pos;
                state->deck[p][deckPos] = getRandomTreasureCard();
                treasuresAdded++;
            }
        }
        else if (state->discardCount[p] > 0) {
            pos = floor(Random() * state->discardCount[p]);
            if (pos != discardPos) {
                discardPos = pos;
                state->discard[p][discardPos] = getRandomTreasureCard();
                treasuresAdded++;
            }
        }
    }
}

void checkPlayAdventurer(int n, int p, struct gameState *post) {
    int r;
    int handPos = 0;
    struct gameState pre;
    int treasureIndex;
    int cardsDrawn = 0;

    memcpy(&pre, post, sizeof(struct gameState));
    r = playAdventurer(post, p);

    pre.playedCards[pre.playedCardCount] = pre.hand[p][handPos];
    pre.playedCardCount++;

    if (countTreasureCards(pre.deck[p], pre.deckCount[p]) >= 2) {
        pre.handCount[p] += 1;
        treasureIndex = getNextTreasureCardIndex(pre.deck[p], pre.deckCount[p] - 1);
        pre.hand[p][pre.handCount[p] - 1] = pre.deck[p][treasureIndex];
        treasureIndex = getNextTreasureCardIndex(pre.deck[p], treasureIndex - 1);
        pre.hand[p][handPos] = pre.deck[p][treasureIndex];
        pre.hand[p][pre.handCount[p]] = -1;
        cardsDrawn = pre.deckCount[p] - treasureIndex;
        pre.deckCount[p] -= cardsDrawn;
        pre.discardCount[p] += cardsDrawn - 2;
        memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
    }
    else {
        memcpy(pre.deck[p], post->deck[p], sizeof(int) * MAX_DECK);
        memcpy(pre.discard[p], post->discard[p], sizeof(int) * MAX_DECK);
        memcpy(pre.hand[p], post->hand[p], sizeof(int) * MAX_HAND);

        pre.handCount[p] += 1;
        pre.discardCount[p] = post->discardCount[p];
        pre.deckCount[p] = post->deckCount[p];
    }

    printRandomTestResult(post, &pre, p, r, n);
}

int main() {
    struct gameState G;
    int i;
    int n;
    int p;
    int minCards = 2;
    int neededCards;

    printf("RANDOM TEST ADVENTURER\n\n");
    printf("Testing playAdventurer():\n");

    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < 10000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * 2);
        G.deckCount[p] = floor(Random() * MAX_DECK);

        neededCards = (G.deckCount[p] >= minCards)
            ? 0
            : minCards - G.deckCount[p];

        G.discardCount[p] = floor(Random() * (MAX_DECK - G.deckCount[p] - neededCards - 1)) + neededCards + 1;
        G.handCount[p] = floor(Random() * (MAX_HAND - 3)) + 1;
        G.playedCardCount = floor(Random() * MAX_DECK);

        addTreasureCards(p, &G);
        checkPlayAdventurer(n, p, &G);
    }

    printResults();

    return 0;
}