#pragma once
#include <string>

using namespace std;

class Player
{
	public:
		// Constructor
		Player(string playerName);
		// Functions to modify player attributes
		void addChip();
		void removeChip();
		int getNumChips();
		string getName();

	private:
		string name;
		int numChips = 3;
};

