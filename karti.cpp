#include <iostream>

#define CLUBS R"(
|   _   |
|  ( )  |
| (_'_) |
|   |   |
)"
#define DIAMONDS R"(
|   ^   |
|  / \  |
|  \ /  |
|   .   |
)"
#define HEARTS R"(
|  _ _  |
| ( v ) |
|  \ /  |
|   .   |
)"
#define SPADES R"(
|   .   |
|  /.\  |
| (_._) |
|   |   |
)"

enum CardSuit {
    Clubs,
    Diamonds,
    Hearts,
    Spades
};

struct Card {
    CardSuit suit;
    short rank;
};

void display_card(Card card) {
    char corner_symbol;
    std::string center_symbol;

    switch (card.suit) {
        case Clubs:
            center_symbol = CLUBS;
            break;
        case Diamonds:
            center_symbol = DIAMONDS;
            break;
        case Hearts:
            center_symbol = HEARTS;
            break;
        case Spades:
            center_symbol = SPADES;
            break;
    }

    switch (card.rank) {
        case 11:
            corner_symbol = 'J';
            break;
        case 12:
            corner_symbol = 'Q';
            break;
        case 13:
            corner_symbol = 'K';
            break;
        case 14:
            corner_symbol = 'A';
            break;
        default:
            corner_symbol = '0' + card.rank;
            break;
    }

    std::cout << "---------" << std::endl;
    std::cout << "| " << corner_symbol << "     |";
    std::cout << center_symbol;
    std::cout << "|     " << corner_symbol << " |" << std::endl;
    std::cout << "---------";
}

int main() {
    display_card({
        Diamonds,
        14
    });


    int a;
    std::cin >> a;
    return 0;
}