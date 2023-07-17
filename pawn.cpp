#include "pawn.h"

#include<iostream>
using namespace std;
pawn::pawn(int r, int c, color cl, Board* _b) :piece(r, c, cl, _b) {}
void pawn::draw(int ri,int ci) {
	if (c == WHITE) {
		SetColor(7);
		gotoRowCol(ri - 2, ci);
		cout << char(-37);
		gotoRowCol(ri - 1, ci - 2);
		cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
		gotoRowCol(ri, ci - 1);
		cout << char(-37) << char(-37) << char(-37);
		gotoRowCol(ri + 1, ci - 3);
		cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	}
	else {
		SetColor(6);
		gotoRowCol(ri - 2, ci);
		cout << char(-37);
		gotoRowCol(ri - 1, ci - 2);
		cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
		gotoRowCol(ri, ci - 1);
		cout << char(-37) << char(-37) << char(-37);
		gotoRowCol(ri + 1, ci - 3);
		cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	}
}

