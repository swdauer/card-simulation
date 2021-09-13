#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cards.h"

#define TRIALS 100000

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
