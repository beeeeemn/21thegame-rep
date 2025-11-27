#pragma once
#include <vector>

enum CardSuit {
    Clubs = 0,
    Diamonds = 1,
    Hearts = 2,
    Spades = 3,
    Hidden = 4
};

struct Card {
    CardSuit suit;
    int rank;
};

void display_cards(std::vector<Card> cards);
