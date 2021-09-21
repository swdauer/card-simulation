#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"

int compareRanks(rank r1, rank r2) {
    if (r1 > r2) return 1;
    else if (r1 < r2) return -1;
    else return 0;
}

int compareCards(card c1, card c2) {
    return compareRanks(c1.r, c2.r);
}

card cardFromIndices(int rankIndex, int suitIndex) {
    card c;
    c.r = 0x1 << rankIndex;
    c.s = 0x1 << suitIndex;
    return c;
}

void initDeck(deck d) {
    card currCard;
    card lastCard;
    lastCard.r = 0x1 << (NUM_RANKS - 1);
    lastCard.s = 0x1 << (NUM_SUITS - 1);
    int i = 0;
    for (currCard.r = 0x1; currCard.r <= lastCard.r; currCard.r <<= 1) {
        for (currCard.s = 0x1; currCard.s <= lastCard.s; currCard.s <<= 1) {
            memcpy(d + i++, &currCard, sizeof(card));
        }
    }
}

int cardRankToIndex(card c) {
    int i;
    for (i = 0; i < NUM_RANKS; i++) {
        if (c.r == 0x1 << i)
            return i;
    }
}

int cardSuitToIndex(card c) {
    int i;
    for (i = 0; i < NUM_SUITS; i++) {
        if (c.s == 0x1 << i)
            return i;
    }
}

char rankChar(card c) {
    return rankCharFromIndex(cardRankToIndex(c));
}

char rankCharFromIndex(int i) {
    static char ranks[] = { '2', '3', '4', '5', '6', '7', '8',
                            '9', 'T', 'J', 'Q', 'K', 'A' };
    return ranks[i];
}

char suitChar(card c) {
    return suitCharFromIndex(cardSuitToIndex(c));
}

char suitCharFromIndex(int i) {
    static char suits[] = { 'S', 'H', 'D', 'C' };
    return suits[i];
}

void swap(card* x, card* y) {
    card holder = *x;
    *x = *y;
    *y = holder;
}

/* Implementation of Fisher-Yates shuffle using Durstenfeld's Algorithm 235. */
void shuffleMtoN(deck d, char m, char n) {
    for (; n > m; n--) {
        int j = rand() % (n - m + 1);
        swap(d + n, d + (m + j));
    }
}

void shuffle(deck d) {
    shuffleMtoN(d, 0, DECK_SIZE - 1);
}

void printCard(card c) {
    printf("%c%c", rankChar(c), suitChar(c));
}

void printDeckMtoN(deck d, char m, char n) {
    char printed1 = 0;
    for (; m <= n; m++) {
        if (printed1) printf(",");
        printCard(d[m]);
        printed1 = 1;
        // printf("%c", m != n ? ',' : '\n');
    }
}

void printDeck(deck d) {
    printDeckMtoN(d, 0, DECK_SIZE - 1);
}

void zeroHand(hand* h) {
    memset(h, 0, sizeof(hand));
}

void addToHand(hand* h, card c) {
    h->byRank[cardRankToIndex(c)] |= c.s;
    h->bySuit[cardSuitToIndex(c)] |= c.r;
}

void printHand(hand* h) {
    int i;
    char printedOne = 0;
    for (i = 0; i < NUM_RANKS; i++) {
        card curr;
        curr.r = 0x1 << i;
        int j;
        for (j = 0; j < NUM_SUITS; j++) {
            curr.s = 0x1 << j;
            if (h->byRank[i] & curr.s) {
                if (printedOne) putchar(',');
                printCard(curr);
                printedOne = 1;
            }
        }
    }
}

int countSuitSet(suitSet s) {
    int i, count = 0;
    for (i = 0; i < NUM_SUITS; i++) {
        if (s & (0x1 << i)) count++;
    }
    return count;
}

int countRankSet(rankSet r) {
    int i, count = 0;
    for (i = 0; i < NUM_RANKS; i++) {
        if (r & (0x1 << i)) count++;
    }
    return count;
}
