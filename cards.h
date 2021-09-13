#ifndef CARDS_H
#define CARDS_H

#define NUM_SUITS 4
#define DECK_SIZE 52

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
