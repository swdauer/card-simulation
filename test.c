#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cards.h"

#define TRIALS 100000

void printN(deck d, char n) {
    char i;
    for (i = 0; i < n; i++) {
        printf("%d%c", d[i], i != n - 1 ? ',' : '\n');
    }
}

void printDeck(deck d) {
    printN(d, DECK_SIZE);
}


int main() {
    srand(time(NULL));
    deck d;
    initDeck(d);
    int i;
    for (i = 0; i < TRIALS; i++) {
        shuffle(d);
        printN(d, 5);
    }
    return 0;
}
