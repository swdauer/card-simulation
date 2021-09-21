#ifndef CARDS_H
#define CARDS_H

/* card type */
#define NUM_SUITS 4
#define NUM_RANKS 13

typedef int rank;
typedef int suit;

// i's start at least-significant bit
// if the i'th bit of card.rank is on, then the card is the i'th card in the range {2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A}
// if the i'th bit of card.suit is on, then the card is the i'th suit in the range {S, H, D, C}
typedef struct {
    rank r;
    suit s;
}card;

char rankChar(card);
char suitChar(card);
char rankCharFromIndex(int);
char suitCharFromIndex(int);

// 1 if r1 is better than r2
// -1 if r1 is worse than r2
// 0 if r1 is equal to r2
int compareRanks(rank r1, rank r2);
int compareCards(card c1, card c2);

void swap(card*, card*);

void printCard(card);
/* end card type */

/* hand type */

/* For byRank:
Each card here is a single bit.
Each element of byRank is a different card rank.
Each on bit in the unsigned short corresponds to a different suit in increasing significance of S, H, D, C.
E.G. byRank[0] == 0x1 then the hand contains the 2 of spades and no other twos
byRank[0] == 0x3 then the hand contains the 2 of spades and hearts and no other twos
byRank[12] == 0xC then the hand contains the ace of diamonds and clubs and no other aces
*/
/* For bySuit:
Each card here is a single bit.
Each element of bySuit is a different card suit.
Each on bit in the unsigned short corresponds to a different rank
    in increasing significance of 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A
E.G. bySuit[0] == 0x1 then the hand contains the 2 of spades and no other spades
bySuit[0] == 0x8 then the hand contains the 5 of spades and no other spades
bySuit[0] == 0x9 then the hand contains the 2 and 5 of spades and no other spades
*/
typedef struct {
    suit byRank[NUM_RANKS];
    rank bySuit[NUM_SUITS];
} hand;

void printHand(hand*);

void addToHand(hand*, card);

void zeroHand(hand*);
/* end hand type */

/* deck type */
#define DECK_SIZE (NUM_SUITS*NUM_RANKS)

typedef card deck[DECK_SIZE];

void initDeck(deck);

void shuffleMtoN(deck, char m, char n);
void shuffle(deck);

void printDeckMtoN(deck, char m, char n);
void printDeck(deck);
/* end deck type */

#endif // CARDS_H
