# card-simulation

## Purpose

Here will be a library to simulate a deck of cards. It will provide the deck and deck operations such as shuffling as well as card operations like determining if two cards are the same rank or suit.

## Layout

- Deck will be a data type containing each of the cards
- Each card will be a single char ranging from 0 to 51
- Use modulus with 4 to determine suit
- Use division by 4 to determine rank
