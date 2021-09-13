# card-simulation

## Purpose

The lib folder holds utility operations for conducting a simulation with a deck of cards. 
The root folder contains the simulations themselves.

## Lib

- Cards (`cards.c` and `cards.h`) contains functions used for operating on a deck and cards.
- Poker (`poker.c` and `poker.h`) contains functions for operating on poker hands.

## Layout

- Deck will be a data type containing each of the cards
- Each card will be a single char ranging from 0 to 51
- Use modulus with 4 to determine suit
- Use division by 4 to determine rank
