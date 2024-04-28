#pragma once
// This class represents the object that controls the flow of the game

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Player.h"

using namespace std;

class GameDisplay
{
	public:
		// Functions used to control the flow of the game
		void startGame();
		void printRules();
		void addPlayers();
		void playRound(int round);
		bool checkForWinner();
		string getWinnerName();

	private:
		vector<Player> playerList;
		int numPlayers;
		ifstream inFS;

		// Variables to be used in turn-based logic
		int roundNumber = 1;
		int currentPlayerIndex;
		int previousPlayerIndex;
		int nextPlayerIndex;
		int numDice;
		int diceResult;

		// Variable to end the game
		bool isGameOver = false;
};

