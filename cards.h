#ifndef CARDS_H
#define CARDS_H

#define DECK_SIZE 52

typedef char deck[DECK_SIZE];

void initDeck(deck);

void swap(char*, char*);

void shuffleMtoN(deck, char, char);
void shuffle(deck);

void printMtoN(deck, char, char);
void printDeck(deck);

#endif // CARDS_H
