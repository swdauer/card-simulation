#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/cards.h"
#include "lib/poker.h"

#define NUM_TRIALS 100000

// two holdem hands vs eachother
void holdemHeadsUp(unsigned long long numTrials, deck d) {
    printf(
        "hand1_0,hand1_1,h1_type,"
        "hand2_0,hand2_1,h2_type,"
        "board_0,board_1,board_2,"
        "board_3,board_4,winner\n"
    );
    unsigned long long i;
    for (i = 0; i < numTrials; i++) {
        shuffle(d);

        hand board = {};
        hand h1Hole = {};
        hand h1 = {};
        hand h2Hole = {};
        hand h2 = {};

        int j;
        for (j = 0; j < 5; j++) {
            addToHand(&board, d[j]);
            addToHand(&h1, d[j]);
            addToHand(&h2, d[j]);
        }
        for (j = 5; j < 7; j++) {
            addToHand(&h1Hole, d[j]);
            addToHand(&h1, d[j]);
        }
        for (j = 7; j < 9; j++) {
            addToHand(&h2Hole, d[j]);
            addToHand(&h2, d[j]);
        }

        handEvaluation e1 = evaluate(&h1);
        handEvaluation e2 = evaluate(&h2);

        int comp = compareHE(&e1, &e2);

        printHand(&h1Hole);
        putchar(',');
        printHandEval(&e1);
        putchar(',');
        printHand(&h2Hole);
        putchar(',');
        printHandEval(&e2);
        putchar(',');
        printHand(&board);
        putchar(',');
        if (comp == 1) putchar('1');
        else if (comp == -1) putchar('2');
        else putchar('0');
        putchar('\n');

    }
}

int main() {
    srand(time(NULL));
    deck d;
    initDeck(d);

    unsigned long long numTrials = 0;
    scanf("%llu", &numTrials);
    // printf("%llu\n", numTrials);
    holdemHeadsUp(numTrials, d);
    return 0;
}
