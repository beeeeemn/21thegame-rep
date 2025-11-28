#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <string>

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
    else if (CurrentCard == "В") {
        CurrentCardValue += 2;
    }
    else if (CurrentCard == "Д") {
        CurrentCardValue += 3;
    }
    else if (CurrentCard == "К") {
        CurrentCardValue += 4;
    }
    else if (CurrentCard == "Т" && CurrentCardValue <= 10) {
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
    srand(time(NULL));

    std::vector<std::string> OriginalCards = { "6", "6", "6", "6", "7", "7", "7", "7", "8", "8", "8", "8", "9", "9", "9", "9", "10", "10", "10", "10", "В", "В", "В", "В", "Д", "Д", "Д", "Д", "К", "К", "К", "К", "Т", "Т", "Т", "Т" };
    std::vector<std::string> Cards = OriginalCards;
    std::random_shuffle(Cards.begin(), Cards.end());

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
            std::cout << "Ваши карты: ";
            for (const auto& card : PlayerCards) std::cout << card << " ";
            std::cout << "(сумма: " << PlayerValue << ")\n";

            std::cout << "Карта дилера: " << DealerCards[0] << " (остальные скрыты)\n";

            std::cout << "Введите 1, если хотите взять карту.\n";
            std::cout << "Введите 0, если хотите остановиться.\n";
            std::cin >> Choice;
            if (Choice == 1) {
                std::string CurrentCard = PullOutACard("", Cards);
                std::cout << "Ваша карта: " << CurrentCard << std::endl;
                PlayerCards.push_back(CurrentCard);
                CardValueToInt(CurrentCard, PlayerValue);
                std::cout << "Ваш баланс = " << PlayerValue << std::endl;
                if (PlayerValue >= 21) {
                    gameOver = true;
                }
            }
        } while (Choice != 0 && !gameOver);

        if (PlayerValue < 21) {
            std::cout << "Ход дилера:\n";
            while (DealerValue < 17) {
                std::string CurrentCard = PullOutACard("", Cards);
                DealerCards.push_back(CurrentCard);
                CardValueToInt(CurrentCard, DealerValue);
                std::cout << "Карты дилера: ";
                for (size_t i = 0; i < DealerCards.size(); ++i) {
                    std::cout << DealerCards[i] << " ";
                }
                std::cout << "(сумма: " << DealerValue << ")\n";
            }
        }

        std::cout << "Карты дилера: ";
        for (const auto& card : DealerCards) std::cout << card << " ";
        std::cout << "(сумма: " << DealerValue << ")\n";

        if (PlayerValue > 21) {
            std::cout << "Перебор! Вы проиграли.\n";
            losses++;
        }
        else if (DealerValue > 21 || PlayerValue > DealerValue) {
            std::cout << "Вы выиграли!\n";
            wins++;
        }
        else if (PlayerValue == DealerValue) {
            std::cout << "Ничья!\n";
        }
        else {
            std::cout << "Дилер выиграл!\n";
            losses++;
        }

        SaveProgress(wins, losses);
        std::cout << "Побед: " << wins << ", Поражений: " << losses << "\n";

        std::cout << "Играть ещё? (y/n): ";
        std::cin >> PlayAgain;
        if (PlayAgain == 'y') {
            Cards = OriginalCards;
            std::random_shuffle(Cards.begin(), Cards.end());
        }
    } while (PlayAgain == 'y');

    std::cout << "Игра окончена.\n";
    return 0;
}