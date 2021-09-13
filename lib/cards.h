#ifndef CARDS_H
#define CARDS_H

#define NUM_SUITS 4
#define LG_NUM_SUITS 2 // this should be the log base 2 of NUM_SUITS
#define DECK_SIZE 52

// These macros only work if NUM_SUITS is a power of 2
#define SUIT(c) ((c) & (NUM_SUITS - 1)) // get last two bits from c
#define RANK(c) ((c) >> LG_NUM_SUITS) // get c / NUM_SUITS

typedef char card;
typedef card deck[DECK_SIZE];
typedef struct hand {
    card c;
    struct hand* next;
} hand;

void initDeck(deck);

char rankChar(card);
char suitChar(card);

void swap(card*, card*);

void shuffleMtoN(deck, char m, char n);
void shuffle(deck);

void printMtoN(deck, char m, char n);
void printDeck(deck);

// void quicksortMtoN(deck, char m, char n);

hand* addToHand(hand* head, hand* allocSpace, card);

#endif // CARDS_H
