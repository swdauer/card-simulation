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

void printN(deck d, char n) {
    char i;
    for (i = 0; i < n; i++) {
        printf("%d%c", d[i], i != n - 1 ? ',' : '\n');
    }
}

void printDeck(deck d) {
    printN(d, DECK_SIZE);
}
