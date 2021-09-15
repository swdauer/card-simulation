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
        }
    }
}
