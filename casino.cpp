#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;
struct RoundResult {
 int roundNumber;
 string betType;
 string betChoice;
 int betAmount;
 int winningAmount;
 int outcomeNumber;
 string outcomeColor;
};
const int INITIAL_BALANCE = 1000;
const int MIN_BET = 1;
const int MAX_NUMBER = 36;
const int ZERO = 0;
void clearInputStream() {
 cin.clear();
 cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
int getValidatedInteger(const string &prompt, int min, int max) {
 int value;
 while (true) {
 cout << prompt;
 cin >> value;
 if (!cin.fail() && value >= min && value <= max) {
 clearInputStream();
 return value;
 }
else {

cout << "Invalid input. Please enter a number between " << min << "and " << max << ".\n";
 clearInputStream();
 }
 }
}
int getValidatedPositiveInteger(const string &prompt, int min) {
 int value;
 while (true) {
 cout << prompt;
 cin >> value;
 if (!cin.fail() && value >= min) {
 clearInputStream();
 return value;
 } else {
 cout << "Invalid input. Please enter a number greater than or equal to "
<< min << ".\n";
 clearInputStream();
 }
 }
}
string getColor(int number) {
 if (number == 0)
 return "Green";
 int redNumbers[] = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
 for (int red : redNumbers) {
 if (number == red)
 return "Red";
 }
 return "Black";
}
void displayBetOptions() {
 cout << "\nAvailable Bet Types:\n";
 cout << "1. Single Number Bet (Payout: 35:1)\n";
 cout << "2. Red/Black Bet (Payout: 1:1)\n";
 cout << "3. Even/Odd Bet (Payout: 1:1)\n";
 cout << "4. High/Low Bet (Payout: 1:1) [Low: 1-18, High: 19-36]\n";
 cout << "5. Dozen Bet (Payout: 2:1) [1st Dozen: 1-12, 2nd Dozen: 13-24, 3rdDozen: 25-36]\n";
 cout << "6. Exit Game\n";

 cout << "--------------------------------------------------\n";
}
int spinWheel() {
 return rand() % (MAX_NUMBER + 1);
}
int processSingleNumberBet(int betAmount, int outcome, RoundResult &result)
{
 int numberChoice = getValidatedInteger("Choose a number to bet on (0-36):", 0, 36);
 result.betChoice = to_string(numberChoice);
 result.betType = "Single Number";
 if (numberChoice == outcome) {
 int winAmount = betAmount * 35;
 cout << "Congratulations! The ball landed on " << outcome
 << ". You win $" << winAmount << "!\n";
 return winAmount;
 } else {
 cout << "Sorry, the ball landed on " << outcome
 << ". You lose your bet of $" << betAmount << ".\n";
 return -betAmount;
 }
}
int processRedBlackBet(int betAmount, int outcome, RoundResult &result) {
 cout << "Bet on:\n1. Red\n2. Black\n";
 int choice = getValidatedInteger("Enter your choice (1 or 2): ", 1, 2);
 string betColor = (choice == 1) ? "Red" : "Black";
 result.betChoice = betColor;
 result.betType = "Red/Black";
 string outcomeColor = getColor(outcome);
 if (outcome == 0) {
 cout << "The ball landed on 0 (Green). House wins.\n";
 return -betAmount;
 }
 if (betColor == outcomeColor) {
 cout << "Congratulations! The ball landed on " << outcome
 << " (" << outcomeColor << "). You win $" << betAmount << "!\n";
 return betAmount;
 } else {
 cout << "Sorry, the ball landed on " << outcome
 << " (" << outcomeColor << "). You lose your bet of $" << betAmount

<< ".\n";
 return -betAmount;
 }
}
int processEvenOddBet(int betAmount, int outcome, RoundResult &result) {
 cout << "Bet on:\n1. Even\n2. Odd\n";
 int choice = getValidatedInteger("Enter your choice (1 or 2): ", 1, 2);
 string betChoice = (choice == 1) ? "Even" : "Odd";
 result.betChoice = betChoice;
 result.betType = "Even/Odd";
 if (outcome == 0) {
 cout << "The ball landed on 0. House wins.\n";
 return -betAmount;
 }
 bool isEven = (outcome % 2 == 0);
 if ((isEven && choice == 1) || (!isEven && choice == 2)) {
 cout << "Congratulations! The ball landed on " << outcome
 << ". You win $" << betAmount << "!\n";
 return betAmount;
 } else {
 cout << "Sorry, the ball landed on " << outcome
 << ". You lose your bet of $" << betAmount << ".\n";
 return -betAmount;
 }
}
int processHighLowBet(int betAmount, int outcome, RoundResult &result) {
 cout << "Bet on:\n1. Low (1-18)\n2. High (19-36)\n";
 int choice = getValidatedInteger("Enter your choice (1 or 2): ", 1, 2);
 string betChoice = (choice == 1) ? "Low" : "High";
 result.betChoice = betChoice;
 result.betType = "High/Low";
 if (outcome == 0) {
 cout << "The ball landed on 0. House wins.\n";
 return -betAmount;
 }
 if ((choice == 1 && outcome >= 1 && outcome <= 18) ||
 (choice == 2 && outcome >= 19 && outcome <= 36)) {
 cout << "Congratulations! The ball landed on " << outcome
 << ". You win $" << betAmount << "!\n";
 return betAmount;
 } else {

 cout << "Sorry, the ball landed on " << outcome
 << ". You lose your bet of $" << betAmount << ".\n";
 return -betAmount;
 }
}
int processDozenBet(int betAmount, int outcome, RoundResult &result) {
 cout << "Bet on Dozen:\n";
 cout << "1. 1st Dozen (1-12)\n";
 cout << "2. 2nd Dozen (13-24)\n";
 cout << "3. 3rd Dozen (25-36)\n";
 int choice = getValidatedInteger("Enter your choice (1, 2, or 3): ", 1, 3);
 string betChoice;
 int lowerBound, upperBound;
 switch (choice) {
 case 1:
 betChoice = "1st Dozen";
 lowerBound = 1; upperBound = 12;
 break;
 case 2:
 betChoice = "2nd Dozen";
 lowerBound = 13; upperBound = 24;
 break;
 case 3:
 betChoice = "3rd Dozen";
 lowerBound = 25; upperBound = 36;
 break;
 default:
 betChoice = "1st Dozen";
 lowerBound = 1; upperBound = 12;
 break;
 }
 result.betChoice = betChoice;
 result.betType = "Dozen";
 if (outcome == 0) {
 cout << "The ball landed on 0. House wins.\n";
 return -betAmount;
 }
 if (outcome >= lowerBound && outcome <= upperBound) {
 int winAmount = betAmount * 2;
 cout << "Congratulations! The ball landed on " << outcome
 << ". You win $" << winAmount << "!\n";
 return winAmount;

 } else {
 cout << "Sorry, the ball landed on " << outcome
 << ". You lose your bet of $" << betAmount << ".\n";
 return -betAmount;
 }
}
class RouletteGame {
private:
 int balance;
 int roundCount;
 vector<RoundResult> history;
public:
 RouletteGame() : balance(INITIAL_BALANCE), roundCount(0) {
 srand(static_cast<unsigned int>(time(0)));
 }
 void displayBalance() {
 cout << "\nCurrent Balance: $" << balance << "\n";
 }
 void play() {
 cout << "Welcome to the Casino Roulette Game!\n";
 bool exitGame = false;
 while (!exitGame && balance >= MIN_BET) {
 roundCount++;
 cout <<
"\n============================================\n";
 cout << "Round " << roundCount << "\n";
 displayBalance();
 displayBetOptions();
 int betTypeChoice = getValidatedInteger("Select a bet type (1-6): ", 1,
6);
 if (betTypeChoice == 6) {
 cout << "Exiting game...\n";
 exitGame = true;
 break;
 }
 int betAmount = getValidatedPositiveInteger("Enter bet amount: $",
MIN_BET);

 if (betAmount > balance) {
 cout << "Insufficient balance. Bet cannot exceed $" << balance <<
".\n";
 continue;
 }
 int outcome = spinWheel();
 string outcomeColor = getColor(outcome);
 RoundResult result;
 result.roundNumber = roundCount;
 result.betAmount = betAmount;
 result.outcomeNumber = outcome;
 result.outcomeColor = outcomeColor;
 int winLossAmount = 0;
 switch (betTypeChoice) {
 case 1:
 winLossAmount = processSingleNumberBet(betAmount, outcome,
result);
 break;
 case 2:
 winLossAmount = processRedBlackBet(betAmount, outcome,
result);
 break;
 case 3:
 winLossAmount = processEvenOddBet(betAmount, outcome,
result);
 break;
 case 4:
 winLossAmount = processHighLowBet(betAmount, outcome,
result);
 break;
 case 5:
 winLossAmount = processDozenBet(betAmount, outcome, result);
 break;
 default:
 cout << "Invalid bet type selected. Skipping round.\n";
 continue;
 }
 result.winningAmount = winLossAmount;
 balance += winLossAmount;

 history.push_back(result);
 if (balance < MIN_BET) {
 cout << "Your balance is below the minimum bet. Game over!\n";
 break;
 }
 cout << "\nDo you want to continue playing? (y/n): ";
 char cont;
 cin >> cont;
 clearInputStream();
 if (cont == 'n' || cont == 'N') {
 exitGame = true;
 }
 }
 displaySummary();
 }
 void displaySummary() {
 cout <<
"\n============================================\n";
 cout << "Game Summary:\n";
 cout << left << setw(8) << "Round"
 << setw(18) << "Bet Type"
 << setw(18) << "Bet Choice"
 << setw(10) << "Bet"
 << setw(12) << "Win/Loss"
 << setw(16) << "Outcome" << "\n";
 cout << "----------------------------------------------------------------\n";
 for (const auto &res : history) {
 cout << left << setw(8) << res.roundNumber
 << setw(18) << res.betType
 << setw(18) << res.betChoice
 << "$" << setw(9) << res.betAmount
 << "$" << setw(11) << res.winningAmount
 << res.outcomeNumber << " (" << res.outcomeColor << ")\n";
 }
 cout << "----------------------------------------------------------------\n";
 cout << "Final Balance: $" << balance << "\n";
 cout << "Thanks for playing!\n";
 }
};

int main() {
 cout << "============================================\n";
 cout << " Welcome to Roulette Casino \n";
 cout << "============================================\n\n";
 cout << "In this game, you can bet on various outcomes on a roulettewheel.\n";
 cout << "Good luck and have fun!\n\n";
 RouletteGame game;
 game.play();
 cout << "\nThank you for visiting our Casino. Goodbye!\n";
 return 0;
}
