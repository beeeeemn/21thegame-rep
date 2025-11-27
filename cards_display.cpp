#include <iostream>
#include <vector>
#include "cards_display.h"

using std::string;
using std::vector;

const vector<string> CLUBS = {
    R"(│    _    │)",
    R"(│   ( )   │)",
    R"(│  (_,_)  │)",
    R"(│    |    │)"
};
const vector<string> DIAMONDS = {
    R"(│    ^    │)",
    R"(│   / \   │)",
    R"(│   \ /   │)",
    R"(│    '    │)"
};
const vector<string> HEARTS = {
    R"(│   _ _   │)",
    R"(│  ( V )  │)",
    R"(│   \ /   │)",
    R"(│    '    │)"
};
const vector<string> SPADES = {
    R"(│    .    │)",
    R"(│   /.\   │)",
    R"(│  (_._)  │)",
    R"(│    |    │)"
};
const vector<string> HIDDEN = {
    R"(│#########│)",
    R"(│#########│)",
    R"(│#########│)",
    R"(│#########│)"
};

void display_cards(vector<Card> cards) {
    vector<char> corner_symbol(cards.size());
    vector<vector<string> > center_symbol(cards.size());

    for (int i = 0; i < cards.size(); i++) {
        switch (cards[i].suit) {
            case Clubs:
                center_symbol[i] = CLUBS;
                break;
            case Diamonds:
                center_symbol[i] = DIAMONDS;
                break;
            case Hearts:
                center_symbol[i] = HEARTS;
                break;
            case Spades:
                center_symbol[i] = SPADES;
                break;
            case Hidden:
                center_symbol[i] = HIDDEN;
        }

        switch (cards[i].rank) {
            case 10:
                corner_symbol[i] = '1';
                break;
            case 11:
                corner_symbol[i] = 'J';
                break;
            case 12:
                corner_symbol[i] = 'Q';
                break;
            case 13:
                corner_symbol[i] = 'K';
                break;
            case 14:
                corner_symbol[i] = 'A';
                break;
            default:
                corner_symbol[i] = '0' + cards[i].rank;
                break;
        }
    }

    for (int i = 0; i < cards.size(); i++) {
        std::cout << "┌─────────┐  ";
    }
    std::cout << std::endl;
    for (int i = 0; i < cards.size(); i++) {
        if (cards[i].suit == Hidden) { std::cout << "│#########│  "; } else {
            if (cards[i].rank == 10) {
                std::cout << "│ " << corner_symbol[i] << "0      │  ";
            } else { std::cout << "│ " << corner_symbol[i] << "       │  "; }
        }
    }
    std::cout << std::endl;
    for (int row = 0; row < center_symbol[0].size(); row++) {
        for (int i = 0; i < cards.size(); i++) {
            std::cout << center_symbol[i][row] << "  ";
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < cards.size(); i++) {
        if (cards[i].suit == Hidden) { std::cout << "│#########│  "; } else {
            if (cards[i].rank == 10) {
                std::cout << "│      " << corner_symbol[i] << "0 │  ";
            } else { std::cout << "│       " << corner_symbol[i] << " │  "; }
        }
    }
    std::cout << std::endl;
    for (int i = 0; i < cards.size(); i++) {
        std::cout << "└─────────┘  ";
    }
    std::cout << std::endl;
}
