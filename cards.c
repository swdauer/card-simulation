#include <stdio.h>
#include <stdlib.h>
#include "cards.h"

void initDeck(deck d) {
    char i;
    for (i = 0; i < DECK_SIZE; i++) {
        d[i] = i;
    }
}

void swap(char* x, char* y) {
    char holder = *x;
    *x = *y;
    *y = holder;
}

/* Implementation of Fisher-Yates shuffle using Durstenfeld's Algorithm 235. */
void shuffleMtoN(deck d, char m, char n) {
    for (; n > m; n--) {
        int j = rand() % (n - m + 1);
        // char holder = d[n];
        // d[n] = d[m + j];
        // d[m + j] = holder;
        swap(d + n, d + (m + j));
    }
}

void shuffle(deck d) {
    shuffleMtoN(d, 0, DECK_SIZE - 1);
}

void printMtoN(deck d, char m, char n) {
    for (; m <= n; m++) {
        printf("%d%c", d[m], m != n ? ',' : '\n');
    }
}

void printDeck(deck d) {
    printMtoN(d, 0, DECK_SIZE - 1);
}
