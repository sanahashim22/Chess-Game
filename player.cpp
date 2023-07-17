#include "player.h"


player::player(string n, color cl) {
	this->name = n;
	this->c = cl;
}

string player::getName() {
	return name;
}

color player::getColor() {
	return c;
}
