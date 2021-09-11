#include <cards.h>
#include <stdlib.h>

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
