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
    for (; m <= n; m++) {
        printCard(d[m]);
        printf("%c", m != n ? ',' : '\n');
    }
}

void printDeck(deck d) {
    printMtoN(d, 0, DECK_SIZE - 1);
}

// void quicksortMtoN(deck d, char m, char n) {
//     if (m >= n) return;

//     char i, partIndex = m;
//     for (i = m + 1; i <= n; i++) {
//         if (d[i] < d[partIndex]) {
//             swap(d + partIndex + 1, d + i);
//             swap(d + partIndex, d + partIndex + 1);
//         }
//     }
//     quicksortMtoN(d, m, partIndex - 1);
//     quicksortMtoN(d, partIndex + 1, n);
// }

hand* addToHand(hand* head, hand* allocSpace, card c) {
    allocSpace->c = c;
    allocSpace->next = head;
    return allocSpace;
}

void printHand(hand* head) {
    for (; head != NULL; head = head->next) {
        printCard(head->c);
        printf("%c", head->next != NULL ? ',' : '\n');
    }
}
