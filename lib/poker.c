#include "cards.h"
#include "poker.h"

handEvaluation evaluate(hand* h) {
    handEvaluation flush;
    handEvaluation straight;
    handEvaluation straightFlush;
    handEvaluation sets;

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
