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

handEvaluation evaluate(hand*);

#endif // POKER_H
