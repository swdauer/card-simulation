# card-simulation

## Layout

The lib folder holds utility operations for conducting a simulation with a deck of cards. 

The root folder contains the simulations themselves.

## lib

- cards (`cards.c` and `cards.h`) contains functions used for operating on a deck and cards.
- poker (`poker.c` and `poker.h`) contains functions for operating on poker hands.

### cards

**this section is outdated**

For a standard 52 card deck

- Deck will be a data type containing each of the cards
- Each card will be a single char ranging from 0 to 51
- Use modulus with 4 to determine suit
- Use division by 4 to determine rank

### poker

Need a way to compare hand strength

- There are nine different poker hands
- From highest to lowest they are
    1. Straight flush
    2. Four of a kind
    3. Full house
    4. Flush
    5. Straight
    6. Three of a kind
    7. Two pair
    8. Pair
    9. Nothing
- Let these be called "type"
- If a hand has a better type than another it wins at showdown
- If a hand has an equal type than another that the types are compared by card rank until there is a difference
- All hands are constructed with five cards only
- Will compare hands by evaluating type and comparing, if the type is the same then compare card by card
- In order to facilitate easy comparison the evaluate hand function will return a 2d-tuple of hand type and hand with byRank with only the five cards relevant to the hand
- If the hand doesn't contain a straight or a flush, then I don't need to check for a straight flush
- I can check for all the sets at the same time i.e. four of a kind, full house, three of a kind, two pair, and pair
