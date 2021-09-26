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
            for (count = 0; count < 5; count++) {
                e.r[count] = LEAST_SIG_BIT(flushRanks);
                flushRanks = REMOVE_LEAST_SIG_BIT(flushRanks);
            }
            return e;
        }
    }
    return e;
}

rank straightPresent(rankSet r) {
    rankSet mask = 0x1F << (NUM_RANKS - 5);
    for (mask = 0x1F; mask <= (0x1F << (NUM_RANKS - 5)); mask <<= 1) {
        if ((mask & r) == mask) return LEAST_SIG_BIT(mask);
    }
    // check for Ace to Five straight
    mask = (0xF << (NUM_RANKS - 4)) | 0x1;
    if ((mask & r) == mask) return 0x1 << (NUM_RANKS - 4);
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

    typedef struct rankList {
        int count;
        rank r;
        struct rankList* byCount;
        struct rankList* byRank;
    } rankList;

    rankList allocSpace[NUM_RANKS] = {};
    rankList* byCountHead = NULL;
    rankList* byRankHead = NULL;
    rankList* byRankTail = NULL;

    int i;
    for (i = 0; i < NUM_RANKS; i++) {
        int count = countSuitSet(h->byRank[i]);
        if (count) {
            allocSpace[i].count = count;
            allocSpace[i].r = INDEX_TO_RANK_OR_SUIT(i);
            if (byCountHead) { // there is already one element in both byCountHead and byRankHead lists
                // count is bigger than all counts in the byCountHead list
                if (count > byCountHead->count) {
                    allocSpace[i].byCount = byCountHead;
                    byCountHead = &allocSpace[i];
                } else {
                    rankList* prev = byCountHead;
                    rankList* curr = byCountHead->byCount;
                    while (curr != NULL && curr->count >= count) {
                        prev = prev->byCount;
                        curr = curr->byCount;
                    }
                    prev->byCount = &allocSpace[i];
                    allocSpace[i].byCount = curr;
                }
                byRankTail->byRank = &allocSpace[i];
                byRankTail = &allocSpace[i];
            } else {
                byCountHead = &allocSpace[i];
                byRankHead = &allocSpace[i];
                byRankTail = &allocSpace[i];
            }
        }
    }

    // rankList* curr = byRankHead;
    // while (curr != NULL) {
    //     printf("%c %d,", rankCharFromIndex(rankToIndex(curr->r)), curr->count);
    //     curr = curr->byRank;
    // }
    // printf("\n");
    // curr = byCountHead;
    // while (curr != NULL) {
    //     printf("%c %d,", rankCharFromIndex(rankToIndex(curr->r)), curr->count);
    //     curr = curr->byCount;
    // }
    // printf("\n");

    if (byCountHead->count == 4) { // four of a kind
        e.handType = FOUR_OF_A_KIND;
        e.r[0] = byCountHead->r;
        if (byRankHead->r != e.r[0]) e.r[1] = byRankHead->r;
        else e.r[1] = byRankHead->byRank->r;
    } else if (byCountHead->count == 3 && byCountHead->byCount->count >= 2) { // full house
        e.handType = FULL_HOUSE;
        e.r[0] = byCountHead->r;
        rankList* curr = byRankHead;
        // this while sets curr to the highest rank != e.r[0] and whose count is >= 2
        while (curr->r == e.r[0] || curr->count < 2) curr = curr->byRank;
        e.r[1] = curr->r;
    } else if (byCountHead->count == 3) { // three of a kind
        e.handType = THREE_OF_A_KIND;
        e.r[0] = byCountHead->r;
        e.r[1] = byCountHead->byCount->r;
        e.r[2] = byCountHead->byCount->byCount->r;
    } else if (byCountHead->count == 2 && byCountHead->byCount->count == 2) { // two pair
        e.handType = TWO_PAIR;
        e.r[0] = byCountHead->r;
        e.r[1] = byCountHead->byCount->r;
        rankList* curr = byRankHead;
        // this while sets curr to the highest rank != e.r[0] and != e.r[1]
        while (curr->r == e.r[0] || curr->r == e.r[1]) curr = curr->byRank;
        e.r[2] = curr->r;
    } else if (byCountHead->count == 2) { // pair
        e.handType = PAIR;
        e.r[0] = byCountHead->r;
        rankList* curr = byCountHead->byCount;
        for (i = 1; i <= 3; i++) {
            e.r[i] = curr->r;
            curr = curr->byCount;
        }
    } else { // nothing
        e.handType = NOTHING;
        rankList* curr = byRankHead;
        for (i = 0; i < 5; i++) {
            e.r[i] = curr->r;
            curr = curr->byRank;
        }
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
