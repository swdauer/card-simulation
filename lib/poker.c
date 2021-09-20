#include <stdio.h>
#include "cards.h"
#include "poker.h"

unsigned char countBits(cardSet s) {
    unsigned char count = 0;
    for (; s != 0; s >>= 1) {
        if (s & 0x1) count++;
    }
    return count;
}

handEvaluation evaluate(hand* h) {
    handEvaluation flush = {};
    handEvaluation straight = {};
    handEvaluation straightFlush = {};
    handEvaluation sets = {};

    checkFlush(&flush, h);
    checkStraight(&straight, h);

    if (flush.handType && straight.handType) {
        checkStraightFlush(&straightFlush, h);
        if (straightFlush.handType) return straightFlush;
    }

    checkSets(&sets, h);

    if (sets.handType == FOUR_OF_A_KIND) return sets;
    else if (sets.handType == FULL_HOUSE) return sets;
    else if (flush.handType == FLUSH) return flush;
    else if (straight.handType == STRAIGHT) return straight;
    else return sets;
}

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
                    addToHandRS(&(e->h), j, i);
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
                        addToHandRS(&(e->h), j, k);
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
                addToHandRS(&(e->h), NUM_RANKS - 1, j);
                break;
            }
        }
        for (j = 0; j < 4; j++) {
            int k;
            for (k = 0; k < NUM_SUITS; k++) {
                if (h->byRank[j] & (0x1 << k)) {
                    addToHandRS(&(e->h), j, k);
                    break;
                }
            }
        }
    }
}

void checkStraightFlush(handEvaluation* e, hand* h) {
    cardSet bitMask = 0x1F << (NUM_RANKS - 5);
    int i, j;
    for (j = NUM_RANKS - 1; j >= 4; j--) {
        for (i = 0; i < NUM_SUITS; i++) {
            // printf("%X\n%X\n\n", bitMask, h->bySuit[i]);
            if ((bitMask & h->bySuit[i]) == bitMask) {
                e->handType = STRAIGHT_FLUSH;
                int k;
                for (k = j; k >= j - 4; k--)
                    addToHandRS(&(e->h), k, i);
                return;
            }
        }
        bitMask >>= 1;
    }
    // check for Ace to Five straight flush
    bitMask = 0x100F;
    for (i = 0; i < NUM_SUITS; i++) {
        if ((bitMask & h->bySuit[i]) == bitMask) {
            e->handType = STRAIGHT_FLUSH;
            addToHandRS(&(e->h), NUM_RANKS - 1, i);
            for (j = 0; j < 4; j++)
                addToHandRS(&(e->h), j, i);
            return;
        }
    }
}

void checkSets(handEvaluation* e, hand* h) {
    unsigned char maxSize = 0, penMaxSize = 0;
    unsigned char top5[5] = {};
    int top5Alloc = 0;
    unsigned char maxRank, penMaxRank;
    int i;
    for (i = NUM_RANKS - 1; i >= 0; i--) {
        unsigned char currSize = countBits(h->byRank[i]);
        if (currSize > 0 && top5Alloc < 5) {
            top5[top5Alloc++] = i;
        }
        if (currSize > maxSize) {
            penMaxRank = maxRank;
            penMaxSize = maxSize;
            maxRank = i;
            maxSize = currSize;
        } else if (currSize > penMaxSize) {
            penMaxRank = i;
            penMaxSize = currSize;
        }
    }

    if (maxSize == 4) { // four of a kind
        e->handType = FOUR_OF_A_KIND;
        for (i = 0; i < NUM_SUITS; i++) {
            addToHandRS(&(e->h), maxRank, i);
        }
        for (i = 0; i < 5; i++) {
            if (top5[i] != maxRank) {
                int j;
                for (j = 0; j < NUM_SUITS; j++) {
                    if (h->byRank[top5[i]] & (0x1 << j)) {
                        addToHandRS(&(e->h), top5[i], j);
                        break;
                    }
                }
                break;
            }
        }
        return;
    }

    if (maxSize == 3 && penMaxSize >= 2) { // full house
        e->handType = FULL_HOUSE;
        for (i = 0; i < NUM_SUITS; i++) {
            if (h->byRank[maxRank] & (0x1 << i))
                addToHandRS(&(e->h), maxRank, i);
        }
        int count = 0;
        for (i = 0; i < NUM_SUITS; i++) {
            if (h->byRank[penMaxRank] & (0x1 << i)) {
                count++;
                addToHandRS(&(e->h), penMaxRank, i);
                if (count == 2) break;
            }
        }
        return;
    }

    if (maxSize == 3) { // three of a kind
        e->handType = THREE_OF_A_KIND;
        for (i = 0; i < NUM_SUITS; i++) {
            if (h->byRank[maxRank] & (0x1 << i))
                addToHandRS(&(e->h), maxRank, i);
        }
        int count = 0;
        for (i = 0; i < 5; i++) {
            if (top5[i] != maxRank) {
                int j;
                for (j = 0; j < NUM_SUITS; j++) {
                    if (h->byRank[top5[i]] & (0x1 << j)) {
                        addToHandRS(&(e->h), top5[i], j);
                        count++;
                        break;
                    }
                }
            }
            if (count == 2) return;
        }
    }

    if (maxSize == 2 && penMaxSize == 2) { // two pair
        e->handType = TWO_PAIR;
        for (i = 0; i < NUM_SUITS; i++) {
            if (h->byRank[maxRank] & (0x1 << i))
                addToHandRS(&(e->h), maxRank, i);
            if (h->byRank[penMaxRank] & (0x1 << i))
                addToHandRS(&(e->h), penMaxRank, i);
        }
        for (i = 0; i < 5; i++) {
            if (top5[i] != maxRank && top5[i] != penMaxRank) {
                int j;
                for (j = 0; j < NUM_SUITS; j++) {
                    if (h->byRank[top5[i]] & (0x1 << j)) {
                        addToHandRS(&(e->h), top5[i], j);
                        break;
                    }
                }
                break;
            }
        }
        return;
    }

    if (maxSize == 2) { // pair
        e->handType = PAIR;
        for (i = 0; i < NUM_SUITS; i++) {
            if (h->byRank[maxRank] & (0x1 << i))
                addToHandRS(&(e->h), maxRank, i);
        }
        int count = 0;
        for (i = 0; i < 5; i++) {
            if (top5[i] != maxRank) {
                int j;
                for (j = 0; j < NUM_SUITS; j++) {
                    if (h->byRank[top5[i]] & (0x1 << j)) {
                        addToHandRS(&(e->h), top5[i], j);
                        count++;
                        break;
                    }
                }
            }
            if (count == 3) return;
        }
    }

    // nothing
    e->handType = NOTHING;
    for (i = 0; i < 5; i++) {
        int j;
        for (j = 0; j < NUM_SUITS; j++) {
            if (h->byRank[top5[i]] & (0x1 << j)) {
                addToHandRS(&(e->h), top5[i], j);
                break;
            }
        }
    }
    return;
}

void printHandEval(handEvaluation* e) {
    static char* handTypeStr[] = {
        "", "straight_flush", "four_of_a_kind",
        "full_house", "flush", "straight", "three_of_a_kind",
        "two_pair", "pair", "nothing"
    };

    printf("%s", handTypeStr[e->handType]);
    // printHand(&(e->h));
}

// If e1 is better than e2 then return 1
// If e2 is better than e1 then return -1
// If e1 ties with e2 then return 0
int compareHE(handEvaluation* e1, handEvaluation* e2) {
    if (e1->handType < e2->handType) {
        return 1;
    } else if (e1->handType > e2->handType) {
        return -1;
    }

    // comparing straights
    if (e1 == STRAIGHT_FLUSH || e1 == STRAIGHT) {
        unsigned char e1Top, e2Top;

        int i;
        for (i = NUM_RANKS - 1; i >= 0; i--) {
            if (e1->h.byRank[i]) {
                e1Top = i;
                break;
            }
        }
        if (e1Top == NUM_RANKS - 1 && e1->h.byRank[4])
            e1Top = 4;
        for (i = NUM_RANKS - 1; i >= 0; i--) {
            if (e2->h.byRank[i]) {
                e2Top = i;
                break;
            }
        }
        if (e2Top == NUM_RANKS - 1 && e2->h.byRank[4])
            e2Top = 4;

        if (e1Top > e2Top) return 1;
        else if (e1Top < e2Top) return -1;
        else return 0;
    }

    // comparing flushes and nothings
    if (e1 == FLUSH || e1 == NOTHING) {
        unsigned char e1CurrPosn = NUM_RANKS, e2CurrPosn = NUM_RANKS - 1;
        int count;

        for (count = 0; count < 5; count++) {
            for (e1CurrPosn = e1CurrPosn - 1; !(e1->h.byRank[e1CurrPosn]); e1CurrPosn--);
            for (e2CurrPosn = e2CurrPosn - 1; !(e2->h.byRank[e2CurrPosn]); e2CurrPosn--);
            if (e1CurrPosn > e2CurrPosn) return 1;
            else if (e1CurrPosn < e2CurrPosn) return -1;
        }
        return 0;
    }

    return compareSetsHE(e1, e2);
}

int compareSetsHE(handEvaluation* e1, handEvaluation* e2) {
    if (e1 == FOUR_OF_A_KIND) {
        unsigned char e1SetRank = NUM_RANKS,
            e2SetRank = NUM_RANKS,
            e1CardRank = NUM_RANKS,
            e2CardRank = NUM_RANKS;

        unsigned char i;
        for (i = NUM_RANKS - 1; i >= 0; i--) {
            if (e1->h.byRank[i]) {
                if (countBits(e1->h.byRank[i]) == 4) e1SetRank = i;
                else e1CardRank = i;
            }
            if (e2->h.byRank[i]) {
                if (countBits(e2->h.byRank[i]) == 4) e2SetRank = i;
                else e2CardRank = i;
            }
            if (e1SetRank != NUM_RANKS &&
                e1CardRank != NUM_RANKS &&
                e2SetRank != NUM_RANKS &&
                e2CardRank != NUM_RANKS)
                break;
        }
        if (e1SetRank > e2SetRank) return 1;
        else if (e1SetRank < e2SetRank) return -1;
        else {
            if (e1CardRank > e2CardRank) return 1;
            else if (e1CardRank < e2CardRank) return -1;
            else return 0;
        }
    }
}
