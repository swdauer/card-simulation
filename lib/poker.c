#include "cards.h"
#include "poker.h"

// handEvaluation evaluate(hand* h) {
//     handEvaluation flush = checkFlush(h);
//     handEvaluation straight = checkStraight(h);

//     if (flush.handType == FLUSH && straight.handType == STRAIGHT) {
//         handEvaluation straightFlush = checkStraightFlush(h);
//         if (straightFlush.handType == STRAIGHT_FLUSH) return straightFlush;
//     }

//     handEvaluation set = checkSets(h);

//     if (set.handType == FOUR_OF_A_KIND || set.handType == FULL_HOUSE) return set;
//     else if (flush.handType == FLUSH) return flush;
//     else if (straight.handType == STRAIGHT) return straight;
//     else return set; // THREE_OF_A_KIND, TWO_PAIR, PAIR, or NOTHING
// }

// only works if there are fewer than 10 cards in the hand
handEvaluation checkFlush(hand* h) {
    handEvaluation e = {};
    int i;
    for (i = 0; i < NUM_SUITS; i++) {
        if (countRankSet(h->bySuit[i]) >= 5) {
            e.handType = FLUSH;
            int j, count = 0;
            for (j = NUM_RANKS - 1; j >= 0 && count < 5; j--) {
                if (h->bySuit[i] & (0x1 << j)) {
                    e.r[count++] = 0x1 << j;
                }
            }
            return e;
        }
    }
    return e;
}

rank straightPresent(rankSet r) {
    rankSet mask = 0x1F << (NUM_RANKS - 5);
    int i = NUM_RANKS - 1;
    for (; mask >= 0x1F; mask >>= 1) {
        if ((mask & r) == mask) return 0x1 << i;
        i--;
    }
    // check for Ace to Five straight
    mask = (0x1 << (NUM_RANKS - 1)) | 0xF;
    if ((mask & r) == mask) return 0x8;
    return -1;
}

handEvaluation checkStraight(hand* h) {
    handEvaluation e = {};
    rankSet allRanks = 0;
    int i;
    for (i = 0; i < NUM_SUITS; i++)
        allRanks |= h->bySuit[i];

    rank top = straightPresent(allRanks);
    if (top != -1) {
        e.handType = STRAIGHT;
        e.r[0] = top;
    }
    return e;
}
