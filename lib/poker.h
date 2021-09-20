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

handEvaluation evaluate(hand*);

// These three check functions change handEvaluation->handType
// to 0 if they don't contain the respective hand type.
// Otherwise they change handEvaluation->handType to the proper constant.
// The provided handEvaluation must be fully zeroed for each of the check functions.
void checkFlush(handEvaluation*, hand*);
void checkStraight(handEvaluation*, hand*);
void checkStraightFlush(handEvaluation*, hand*);

// If there are no sets this returns the highest 5 cards by rank
void checkSets(handEvaluation*, hand*);

void printHandEval(handEvaluation*);

// If e1 is better than e2 then return 1
// If e2 is better than e1 then return -1
// If e1 ties with e2 then return 0
int compareHE(handEvaluation* e1, handEvaluation* e2);
int compareSetsHE(handEvaluation* e1, handEvaluation* e2);

#endif // POKER_H
