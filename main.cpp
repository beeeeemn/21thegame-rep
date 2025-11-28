#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <string>
#include <random>
#include <chrono>

std::string PullOutACard(std::string CurrentCard, std::vector<std::string>& Cards) {
    int RandomGetCard = rand() % Cards.size();
    CurrentCard = Cards[RandomGetCard];
    Cards.erase(Cards.begin() + RandomGetCard);
    return CurrentCard;
}

void CardValueToInt(std::string& CurrentCard, int& CurrentCardValue) {
    if (CurrentCard == "6" || CurrentCard == "7" || CurrentCard == "8" || CurrentCard == "9" || CurrentCard == "10") {
        CurrentCardValue += stoi(CurrentCard);
    }
    else if (CurrentCard == "J") {
        CurrentCardValue += 2;
    }
    else if (CurrentCard == "Q") {
        CurrentCardValue += 3;
    }
    else if (CurrentCard == "K") {
        CurrentCardValue += 4;
    }
    else if (CurrentCard == "A" && CurrentCardValue <= 10) {
        CurrentCardValue += 11;
    }
    else {
        CurrentCardValue += 1;
    }
}

void SaveProgress(int wins, int losses) {
    std::ofstream file("progress.txt");
    if (file.is_open()) {
        file << wins << "\n" << losses;
        file.close();
    }
}

void LoadProgress(int& wins, int& losses) {
    std::ifstream file("progress.txt");
    if (file.is_open()) {
        file >> wins >> losses;
        file.close();
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);

    std::vector<std::string> OriginalCards = { "6", "6", "6", "6", "7", "7", "7", "7", "8", "8", "8", "8", "9", "9", "9", "9", "10", "10", "10", "10", "J", "J", "J", "J", "Q", "Q", "Q", "Q", "K", "K", "K", "K", "A", "A", "A", "A" };
    std::vector<std::string> Cards = OriginalCards;
    std::shuffle(Cards.begin(), Cards.end(), rng);

    int wins = 0, losses = 0;
    LoadProgress(wins, losses);

    char PlayAgain;
    do {
        std::vector<std::string> PlayerCards;
        std::vector<std::string> DealerCards;
        int PlayerValue = 0, DealerValue = 0;
        int Choice;
        bool gameOver = false;

        std::string dealerFirst = PullOutACard("", Cards);
        DealerCards.push_back(dealerFirst);
        CardValueToInt(dealerFirst, DealerValue);

        for (int i = 0; i < 2; ++i) {
            std::string CurrentCard = PullOutACard("", Cards);
            PlayerCards.push_back(CurrentCard);
            CardValueToInt(CurrentCard, PlayerValue);
        }

        do {
            std::cout << "Your cards: ";
            for (const auto& card : PlayerCards) std::cout << card << " ";
            std::cout << "(The amount of your cards: " << PlayerValue << ")\n";

            std::cout << "Dealer's Cards: " << DealerCards[0] << "\n";

            std::cout << "Enter 1 if want to play again\n";
            std::cout << "Enter 0 if want to stop\n";
            std::cin >> Choice;
            if (Choice == 1) {
                std::string CurrentCard = PullOutACard("", Cards);
                std::cout << "Your card: " << CurrentCard << std::endl;
                PlayerCards.push_back(CurrentCard);
                CardValueToInt(CurrentCard, PlayerValue);
                std::cout << "The amount of your cards = " << PlayerValue << std::endl;
                if (PlayerValue >= 21) {
                    gameOver = true;
                }
            }
        } while (Choice != 0 && !gameOver);

        if (PlayerValue < 21) {
            std::cout << ":\n";
            while (DealerValue < 17) {
                std::string CurrentCard = PullOutACard("", Cards);
                DealerCards.push_back(CurrentCard);
                CardValueToInt(CurrentCard, DealerValue);
                std::cout << "The amount of dealer's cards: ";
                for (size_t i = 0; i < DealerCards.size(); ++i) {
                    std::cout << DealerCards[i] << " ";
                }
                std::cout << "(The amount of dealer's cards: " << DealerValue << ")\n";
            }
        }

        std::cout << "Dealer's turn: ";
        for (const auto& card : DealerCards) std::cout << card << " ";
        std::cout << "(The amount ofdealer's cards: " << DealerValue << ")\n";

        if (PlayerValue > 21) {
            std::cout << "You lose! You took too many cards.\n";
            losses++;
        }
        else if (DealerValue > 21 || PlayerValue > DealerValue) {
            std::cout << "You won!\n";
            wins++;
        }
        else if (PlayerValue == DealerValue) {
            std::cout << "Draw!\n";
        }
        else {
            std::cout << "The Dealer won!\n";
            losses++;
        }

        SaveProgress(wins, losses);
        std::cout << "Wins: " << wins << ", Losses: " << losses << "\n";

        std::cout << "Want to play again? (y/n): ";
        std::cin >> PlayAgain;
        if (PlayAgain == 'y') {
            Cards = OriginalCards;
            std::shuffle(Cards.begin(), Cards.end(), rng);
        }
    } while (PlayAgain != 'n');

    std::cout << "TEST2\n";
    return 0;
}