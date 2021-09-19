#include <stdio.h>
#include <stdlib.h>
#include "cards.h"

void initDeck(deck d) {
    char i;
    for (i = 0; i < DECK_SIZE; i++) {
        d[i] = i;
    }
}

char rankChar(card c) {
    static char ranks[] = { '2', '3', '4', '5', '6', '7', '8',
                            '9', 'T', 'J', 'Q', 'K', 'A' };
    return ranks[RANK(c)];
}

char suitChar(card c) {
    static char suits[] = { 'S', 'H', 'D', 'C' };
    return suits[SUIT(c)];
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

void printMtoN(deck d, char m, char n) {
    char printed1 = 0;
    for (; m <= n; m++) {
        if (printed1) printf(",");
        printCard(d[m]);
        printed1 = 1;
        // printf("%c", m != n ? ',' : '\n');
    }
}

void printDeck(deck d) {
    printMtoN(d, 0, DECK_SIZE - 1);
}

void addToHandRS(hand* h, unsigned char rank, unsigned char suit) {
    h->byRank[rank] |= 0x1 << suit;
    h->bySuit[suit] |= 0x1 << rank;
}

void addToHand(hand* h, card c) {
    addToHandRS(h, RANK(c), SUIT(c));
}

void printHand(hand* h) {
    int i;
    char printed1 = 0;
    for (i = 0; i < NUM_RANKS; i++) {
        if (h->byRank[i]) {
            int j;
            for (j = 0; j < NUM_SUITS; j++) {
                if (h->byRank[i] & (0x1 << j)) {
                    if (printed1) printf(",");
                    printCard(RANK_SUIT_TO_CARD(i, j));
                    printed1 = 1;
                }
            }
        }
    }
    // if (printed1) printf("\n");
}
