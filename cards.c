#include <stdio.h>
#include <stdlib.h>
#include "cards.h"

void initDeck(deck d) {
    char i;
    for (i = 0; i < DECK_SIZE; i++) {
        d[i] = i;
    }
}

/* Implementation of Fisher-Yates shuffle using Durstenfeld's Algorithm 235. */
void shuffle(deck d) {
    int i;
    for (i = DECK_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char holder = d[i];
        d[i] = d[j];
        d[j] = holder;
    }
}

void printMtoN(deck d, char m, char n) {
    for (; m <= n; m++) {
        printf("%d%c", d[m], m != n ? ',' : '\n');
    }
}

void printDeck(deck d) {
    printMtoN(d, 0, DECK_SIZE - 1);
}
