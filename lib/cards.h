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

void initDeck(deck);

char rankChar(card);
char suitChar(card);

void swap(card*, card*);

void shuffleMtoN(deck, char, char);
void shuffle(deck);

void printMtoN(deck, char, char);
void printDeck(deck);

void quicksortMtoN(deck, char, char);

#endif // CARDS_H
