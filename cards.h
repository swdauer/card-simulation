#ifndef CARDS_H
#define CARDS_H

#define DECK_SIZE 52

typedef char deck[DECK_SIZE];

void shuffle(deck);
void initDeck(deck);

#endif // CARDS_H