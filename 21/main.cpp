#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <random>
#include <chrono>

#include "cards_display.h"
#include "cards_display.cpp"

using std::vector;

Card pullOutACard(vector<Card> &cards) {
    int randomGetCard = rand() % cards.size();
    Card currentCard = cards[randomGetCard];
    cards.erase(cards.begin() + randomGetCard);
    return currentCard;
}

int getCardsValue(vector<Card> &cards) {
    int cardsValue = 0;
    int aces = 0;
    for (const Card &card: cards) {
        if (card.rank >= 11) {
            cardsValue += 10;
        } else {
            cardsValue += card.rank;
        }
        if (card.rank == 14) {
            cardsValue += 1;
            aces++;
        }
    }
    while (cardsValue > 21 && aces > 0) {
        cardsValue -= 10;
        aces--;
    }
    return cardsValue;
}

void saveProgress(int wins, int losses) {
    std::ofstream file("progress.txt");
    if (file.is_open()) {
        file << wins << "\n" << losses;
        file.close();
    }
}

void loadProgress(int &wins, int &losses) {
    std::ifstream file("progress.txt");
    if (file.is_open()) {
        file >> wins >> losses;
        file.close();
    }
}

int main() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);

    vector<Card> originalCards(36);
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 0; rank < 9; rank++) {
            auto card_suit = static_cast<CardSuit>(suit);
            originalCards[suit * 9 + rank] = {
                card_suit,
                rank + 6
            };
        }
    }

    vector<Card> cards(originalCards);
    std::shuffle(cards.begin(), cards.end(), rng);

    int wins = 0, losses = 0;
    loadProgress(wins, losses);

    char playAgain;
    do {
        std::vector<Card> playerCards;
        std::vector<Card> dealerCards;
        int playerValue = 0, dealerValue = 0;
        int choice;

        dealerCards.push_back(pullOutACard(cards));
        dealerValue = getCardsValue(dealerCards);

        for (int i = 0; i < 2; ++i) {
            playerCards.push_back(pullOutACard(cards));
        }
        playerValue = getCardsValue(playerCards);

        do {
            std::cout << "Your cards: " << std::endl;
            display_cards(playerCards);
            std::cout << "Your total value: " << playerValue << std::endl;

            std::cout << "Dealer's Cards: " << std::endl;
            display_cards(dealerCards);
            std::cout << "Dealer's total value: " << dealerValue << std::endl;

            std::cout << "Enter 1 to hit, 2 to stand: ";
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "You hit!" << std::endl;
                playerCards.push_back(pullOutACard(cards));
                playerValue = getCardsValue(playerCards);
                if (playerValue >= 21) {
                    std::cout << "Your cards: " << std::endl;
                    display_cards(playerCards);
                    std::cout << "Your total value: " << playerValue << std::endl;
                    if (playerValue > 21) {
                        std::cout << "Too much!" << std::endl;
                    }
                    break;
                }
            } else {
                std::cout << "You stand! Dealer's turn." << std::endl;
            }
        } while (choice != 2);

        if (playerValue < 21) {
            while (dealerValue < 17) {
                std::cout << "Dealer hits!" << std::endl;
                dealerCards.push_back(pullOutACard(cards));
                dealerValue = getCardsValue(dealerCards);
                std::cout << "Dealer's cards: " << std::endl;
                display_cards(dealerCards);
                std::cout << "Dealer's total value: " << dealerValue << std::endl;
            }
        }
        if (dealerValue <= 21 && playerValue <= 21) {
            std::cout << "Dealer stands!" << std::endl;
        }

        if (playerValue > 21) {
            std::cout << "You lost! You took too many cards." << std::endl;
            losses++;
        } else if (dealerValue > 21) {
            std::cout << "You won! Dealer took too many cards." << std::endl;
            wins++;
        } else if (playerValue > dealerValue) {
            std::cout << "You won!" << std::endl;
            wins++;
        } else if (playerValue == dealerValue) {
            std::cout << "Draw!" << std::endl;
        } else {
            std::cout << "Dealer won!" << std::endl;
            losses++;
        }

        saveProgress(wins, losses);
        std::cout << "Wins: " << wins << ", Losses: " << losses << "\n";

        std::cout << "Want to play again? (y/n): ";
        std::cin >> playAgain;
        if (playAgain == 'y') {
            cards = originalCards;
            std::shuffle(cards.begin(), cards.end(), rng);
        }
    } while (playAgain != 'n');

    return 0;
}
