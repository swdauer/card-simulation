#ifndef POKER_H
#define POKER_H

enum handTypes {
    NOTHING, PAIR, TWO_PAIR,
    THREE_OF_A_KIND, STRAIGHT, FLUSH,
    FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH
};

// handEvaluation.handType is the type of hand e.g. straight, flush, full house
// the order corresponds to the handTypes enum
// r is the order of ranks in the 5 card hand forming handType
// for each type of hand r is different
// - handType == NOTHING or FLUSH -> r is the 5 highest ranks in the hand from greatest to least
// - handType == STRAIGHT or STRAIGHT_FLUSH -> r[0] is the highest rank of the straight
// - handType == PAIR or THREE_OF_A_KIND or FOUR_OF_A_KIND -> r[0] is the set rank and r[1-3] are the rest of the cards
// - handType == TWO_PAIR -> r[0] and r[1] are the pairs from greatest to least and r[2] is the single card
// - handType == FULL_HOUSE -> r[0] is the three of a kind and r[1] is the pair
typedef struct {
    int handType;
    rank r[5];
} handEvaluation;

// handEvaluation evaluate(hand*);

handEvaluation checkFlush(hand*);
handEvaluation checkStraight(hand*);

// returns the top rank of a straight in rankSet
// returns -1 if a straight is not present
rank straightPresent(rankSet);


#endif // POKER_H
