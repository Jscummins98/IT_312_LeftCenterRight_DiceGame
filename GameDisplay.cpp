using namespace std;

#include "GameDisplay.h"

// Function that executes the games functions
void GameDisplay::startGame() {
	// Create random seed for rolling dice
	srand(time(NULL));

	// Set up the game
	printRules();
	addPlayers();
	cout << "\nStarting the game..." << endl << endl;

	// Execute the game until someone wins
	while (isGameOver == false) {
		playRound(roundNumber);
		isGameOver = checkForWinner();
	}
	cout << "Game over! The winner is " << getWinnerName() << "!" << endl;
}

// Print the game rules to the console
void GameDisplay::printRules() {
	string currentLine;
	inFS.open("rules.txt");

	cout << "----------------------------\nRules for the LCR Dice Game\n----------------------------" << endl;
	while (getline(inFS, currentLine)) {
		cout << currentLine << endl;
	}
	cout << "----------------------------\nEnd Of Rules Section\n----------------------------" << endl;

	inFS.close();
}

// Function to add players to the game
void GameDisplay::addPlayers() {

	// Make sure the game consists of 3 or more players
	cout << "Enter number of players:";
	cin >> numPlayers;
	while (numPlayers < 3) {
		cout << "The game must have at least 3 players." << endl;
		cout << "Enter number of players:";
		cin >> numPlayers;
	}

	// Create the players and add them to the playersList vector
	string playerName;
	for (int i = 0; i < numPlayers; i++) {
		cout << "Enter name for Player " << i + 1 << ": ";
		cin >> playerName;
		Player newPlayer(playerName);
		playerList.push_back(newPlayer);
	}
}

// Function that executes the current players turn
void GameDisplay::playRound(int round) {
	// Get the indexes for the current player and the players to the left and right of current player
	currentPlayerIndex = (round - 1) % playerList.size();
	if (currentPlayerIndex == 0) {
		previousPlayerIndex = playerList.size() - 1;
	}
	else {
		previousPlayerIndex = currentPlayerIndex - 1;
	}
	if (currentPlayerIndex == playerList.size() - 1) {
		nextPlayerIndex = 0;
	}
	else {
		nextPlayerIndex = currentPlayerIndex + 1;
	}

	// Print round introduction to console
	cout << "Round " << round << ". " << playerList.at(currentPlayerIndex).getName() << "'s turn:" << endl;

	// Determine the number of dice for the current player
	if (playerList.at(currentPlayerIndex).getNumChips() > 3) {
		numDice = 3;
	}
	else {
		numDice = playerList.at(currentPlayerIndex).getNumChips();
	}
	cout << playerList.at(currentPlayerIndex).getName() << " has " << playerList.at(currentPlayerIndex).getNumChips() <<
		" chips and will roll " << numDice << " dice." << endl << endl;

	// Execute the player's dice rolls
	while (numDice > 0) {
		diceResult = rand() % 6 + 1;
		if (diceResult == 1) {
			cout << playerList.at(currentPlayerIndex).getName() << " rolled L so they pass a chip to " 
				<< playerList.at(previousPlayerIndex).getName() << endl;
			playerList.at(currentPlayerIndex).removeChip();
			playerList.at(previousPlayerIndex).addChip();
		}
		else if (diceResult == 2) {
			cout << playerList.at(currentPlayerIndex).getName() << " rolled R so they pass a chip to "
				<< playerList.at(nextPlayerIndex).getName() << endl;
			playerList.at(currentPlayerIndex).removeChip();
			playerList.at(nextPlayerIndex).addChip();
		}
		else if (diceResult == 3) {
			cout << playerList.at(currentPlayerIndex).getName() << " rolled C so they pass a chip to the center pot" << endl;
			playerList.at(currentPlayerIndex).removeChip();
		}
		else {
			cout << playerList.at(currentPlayerIndex).getName() << " rolled " << diceResult << " dots so nothing happens" << endl;
		}
		numDice--;
	}

	// Print the scoreboard for the end of the round
	cout << "\nScoreboard at the end of round " << roundNumber << ": " << endl;
	for (int i = 0; i < playerList.size(); i++) {
		cout << playerList.at(i).getName() << ": " << playerList.at(i).getNumChips() << endl;
	}
	cout << endl;

	roundNumber++;
}

// Function that checks if a player has won the game
bool GameDisplay::checkForWinner() {
	int playersWithChips = 0;
	for (int i = 0; i < playerList.size(); i++) {
		if (playerList.at(i).getNumChips() > 0) {
			playersWithChips++;
		}
		if (playersWithChips > 1) {
			return false;
		}
	}
	return true;
}

// Function that returns the name of the game winner
string GameDisplay::getWinnerName() {
	for (int i = 0; i < playerList.size(); i++) {
		if (playerList.at(i).getNumChips() > 0) {
			return playerList.at(i).getName();
		}
	}
	return "Error";
}
