#include "Player.h"
#include <string>

// Constructor Function
Player::Player(string playerName) {
	name = playerName;
}

void Player::addChip() {
	numChips++;
}

void Player::removeChip() {
	numChips--;
}

int Player::getNumChips() {
	return numChips;
}

string Player::getName() {
	return name;
}