#include "piece.h"

piece::piece(int r, int c, color cl,Board* _b) {
	this->ri = r;
	this->ci = c;
	this->c = cl;
	this->b = _b;
}

void piece::move(int r, int c) { 
	this->ri = r;
	this->ci = c;
}

color piece::getColor() {
	return c;
}
