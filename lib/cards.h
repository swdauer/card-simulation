#ifndef CARDS_H
#define CARDS_H

/* card type */
#define NUM_SUITS 4
#define LG_NUM_SUITS 2 // this should be the log base 2 of NUM_SUITS
#define NUM_RANKS 13

// These macros only work if NUM_SUITS is a power of 2
#define SUIT(c) ((c) & (NUM_SUITS - 1)) // get last two bits from c
#define RANK(c) ((c) >> LG_NUM_SUITS) // get c / NUM_SUITS

typedef unsigned char card;

char rankChar(card);
char suitChar(card);

void swap(card*, card*);

void printCard(card);
/* end card type */

/* hand type */
// Each card here is a single bit. 
// Each element of hand is a different card rank. 
// Each on bit in the unsigned char corresponds to a different suit in increasing significance of S, H, D, C.
// E.G. hand[0] == 0x1 then the hand contains the 2 of spades and no other twos
// hand[0] == 0x3 then the hand contains the 2 of spades and hearts and no other twos
// hand[12] == 0xC then the hand contains the ace of diamonds and clubs and no other aces
typedef unsigned char hand[NUM_RANKS];

void printHand(hand);

void addToHand(hand, card);
/* end hand type */

/* deck type */
#define DECK_SIZE (NUM_SUITS*NUM_RANKS)

typedef card deck[DECK_SIZE];

void initDeck(deck);

void shuffleMtoN(deck, char m, char n);
void shuffle(deck);

void printMtoN(deck, char m, char n);
void printDeck(deck);
/* end deck type */

#endif // CARDS_H
