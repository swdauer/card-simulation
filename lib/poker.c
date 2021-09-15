#include "cards.h"
#include "poker.h"

unsigned char countBits(cardSet s) {
    unsigned char count = 0;
    for (; s != 0; s >>= 1) {
        if (s & 0x1) count++;
    }
    return count;
}

// handEvaluation evaluate(hand* h) {
//     handEvaluation flush = {};
//     handEvaluation straight = {};
//     handEvaluation straightFlush = {};
//     handEvaluation sets = {};

//     checkFlush(&flush, h);
//     checkStraight(&straight, h);

//     if (flush.handType && straight.handType) {
//         checkStraightFlush(&straightFlush, h);
//         if (straightFlush.handType) return straightFlush;
//     }

//     checkSets(&sets, h);

//     if (sets.handType == FOUR_OF_A_KIND) return sets;
//     else if (sets.handType == FULL_HOUSE) return sets;
//     else if (flush.handType == FLUSH) return flush;
//     else if (straight.handType == STRAIGHT) return straight;
//     else return sets;
// }

// checkFlush returns after finding the first flush.
// If the hand size is less than 10, then this will always be the best flush.
// Otherwise there could be a better flush.
void checkFlush(handEvaluation* e, hand* h) {
    int i;
    for (i = 0; i < NUM_SUITS; i++) {
        if (countBits(h->bySuit[i]) >= 5) {
            e->handType = FLUSH;
            int j, count = 0;
            for (j = NUM_RANKS - 1; j > 0 && count < 5; j--) {
                if ((h->bySuit[i]) & (0x1 << j)) {
                    e->h.byRank[j] = 0x1 << i;
                    count++;
                }
            }
            return;
        }
    }
}

void checkStraight(handEvaluation* e, hand* h) {
    int i;
    for (i = NUM_RANKS - 1; i >= 0 + 4; i--) {
        char straightAtI = 1;
        int j;
        for (j = i; j >= i - 4; j--) {
            straightAtI = straightAtI && h->byRank[j];
        }
        if (straightAtI) {
            e->handType = STRAIGHT;
            for (j = i; j >= i - 4; j--) {
                int k;
                for (k = 0; k < NUM_SUITS; k++) {
                    if (h->byRank[j] & (0x1 << k)) {
                        e->h.byRank[j] = 0x1 << k;
                        break;
                    }
                }
            }
            return;
        }
    }

    // Check for an Ace to 5 straight
    char aTo5Straight = 1;
    aTo5Straight = aTo5Straight && h->byRank[NUM_RANKS - 1];
    for (i = 0; i < 4; i++) {
        aTo5Straight = h->byRank[i] && aTo5Straight;
    }
    if (aTo5Straight) {
        e->handType = STRAIGHT;
        int j;
        for (j = 0; j < NUM_SUITS; j++) {
            if (h->byRank[NUM_RANKS - 1] & (0x1 << j)) {
                e->h.byRank[NUM_RANKS - 1] = 0x1 << j;
                break;
            }
        }
        for (j = 0; j < 4; j++) {
            int k;
            for (k = 0; k < NUM_SUITS; k++) {
                if (h->byRank[j] & (0x1 << k)) {
                    e->h.byRank[j] = 0x1 << k;
                    break;
                }
            }
        }
    }
}
