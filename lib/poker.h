#ifndef POKER_H
#define POKER_H

enum handType {
    STRAIGHT_FLUSH = 1, FOUR_OF_A_KIND, FULL_HOUSE,
    FLUSH, STRAIGHT, THREE_OF_A_KIND, TWO_PAIR, PAIR,
    NOTHING
};

typedef struct {
    unsigned char handType;
    hand h;
} handEvaluation;

unsigned char countBits(cardSet);

// handEvaluation evaluate(hand*);

// These three check functions change handEvaluation->handType
// to 0 if they don't contain the respective hand type.
// Otherwise they change handEvaluation->handType to the proper constant.
// The provided handEvaluation must be fully zeroed for each of the check functions.
void checkFlush(handEvaluation*, hand*);
void checkStraight(handEvaluation*, hand*);
// void checkStraightFlush(handEvaluation*, hand*);

// void checkSets(handEvaluation*, hand*);

#endif // POKER_H
