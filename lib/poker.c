#include <stdio.h>
#include "cards.h"
#include "poker.h"

handEvaluation evaluate(hand* h) {
    handEvaluation flush = checkFlush(h);
    handEvaluation straight = checkStraight(h);

    if (flush.handType == FLUSH && straight.handType == STRAIGHT) {
        handEvaluation straightFlush = checkStraightFlush(h);
        if (straightFlush.handType == STRAIGHT_FLUSH) return straightFlush;
    }

    handEvaluation set = checkSet(h);

    if (set.handType == FOUR_OF_A_KIND || set.handType == FULL_HOUSE) return set;
    else if (flush.handType == FLUSH) return flush;
    else if (straight.handType == STRAIGHT) return straight;
    else return set; // THREE_OF_A_KIND, TWO_PAIR, PAIR, or NOTHING
}

// only works if there are fewer than 10 cards in the hand
handEvaluation checkFlush(hand* h) {
    handEvaluation e = {};
    int i;
    for (i = 0; i < NUM_SUITS; i++) {
        if (countRankSet(h->bySuit[i]) >= 5) {
            rankSet flushRanks = h->bySuit[i];
            e.handType = FLUSH;
            int count;
            for (count = 0; count < 5; count++) { // CHANGE HERE
                e.r[count] = LEAST_SIG_BIT(flushRanks);
                flushRanks = REMOVE_LEAST_SIG_BIT(flushRanks);
                // if (h->bySuit[i] & (0x1 << j)) {
                //     e.r[count++] = 0x1 << j;
                // }
            }
            return e;
        }
    }
    return e;
}

rank straightPresent(rankSet r) {
    rankSet mask = 0x1F << (NUM_RANKS - 5);
    int i = NUM_RANKS - 1;
    for (; mask >= 0x1F; mask >>= 1) { // CHANGE HERE
        if ((mask & r) == mask) return 0x1 << i;
        i--;
    }
    // check for Ace to Five straight
    mask = (0x1 << (NUM_RANKS - 1)) | 0xF; // CHANGE HERE
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

// only works if hand size is less than 10
handEvaluation checkStraightFlush(hand* h) {
    handEvaluation e = {};
    int i;
    for (i = 0; i < NUM_SUITS; i++) {
        rank top = straightPresent(h->bySuit[i]);
        if (top != -1) {
            e.handType = STRAIGHT_FLUSH;
            e.r[0] = top;
            return e;
        }
    }
    return e;
}

handEvaluation checkSet(hand* h) {
    handEvaluation e = {};
    rank top5[5] = {};
    int top5Counts[5] = {};

    int i;
    for (i = NUM_RANKS - 1; i >= 0; i--) { // CHANGE HERE
        int count = countSuitSet(h->byRank[i]);
        int j;
        for (j = 4; j >= 0 && count > top5Counts[j]; j--) {
            if (j < 4) {
                top5Counts[j + 1] = top5Counts[j];
                e.r[j + 1] = e.r[j];
            }
            top5Counts[j] = count;
            e.r[j] = 0x1 << i;
        }
    }

    if (top5Counts[0] == 4) { // four of a kind
        e.handType = FOUR_OF_A_KIND;
        e.r[2] = 0;
        e.r[3] = 0;
        e.r[4] = 0;
    } else if (top5Counts[0] == 3 && top5Counts[1] >= 2) { // full house
        e.handType = FULL_HOUSE;
        e.r[2] = 0;
        e.r[3] = 0;
        e.r[4] = 0;
    } else if (top5Counts[0] == 3) { // three of a kind
        e.handType = THREE_OF_A_KIND;
        e.r[3] = 0;
        e.r[4] = 0;
    } else if (top5Counts[0] == 2 && top5Counts[1] == 2) {
        e.handType = TWO_PAIR;
        e.r[3] = 0;
        e.r[4] = 0;
    } else if (top5Counts[0] == 2) {
        e.handType = PAIR;
        e.r[4] = 0;
    }
    return e;
}

void printHandType(int ht) {
    static char* hts[] = {
        "nothing","pair","two pair",
        "three of a kind","straight",
        "flush","full house","four of a kind",
        "straight flush"
    };
    printf("%s", hts[ht]);
}

int compareHE(handEvaluation* e1, handEvaluation* e2) {
    if (e1->handType > e2->handType) return 1;
    else if (e1->handType < e2->handType) return -1;

    int i;
    for (i = 0; i < 4 && e1->r[i]; i++) {
        if (compareRanks(e1->r[i], e2->r[i]))
            return compareRanks(e1->r[i], e2->r[i]);
    }
    return 0;
}
