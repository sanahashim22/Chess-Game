#include "Board.h"
#include "piece.h"
#include "rook.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include<iostream>
using namespace std;

Board::Board() {
	ps = new piece * *[8];
	for (int r = 0; r < 8; r++) {
		ps[r] = new piece *[8];
		for (int c = 0; c < 8; c++) {
			if (r == 0) {
				if (c == 0 || c==7) {
					ps[r][c] = new rook(r, c, WHITE, this);
				}
				else if (c == 1 || c==6) {
					ps[r][c] = new knight(r, c, WHITE, this);
				}
				else if (c == 2 || c==5) {
					ps[r][c] = new bishop(r, c, WHITE, this);
				}
				else if (c == 3) {
					ps[r][c] = new queen(r, c, WHITE, this);
				}
				else if (c == 4 ) {
					ps[r][c] = new king(r, c, WHITE, this);
				}
			}
			else if (r == 1) {
				ps[r][c] = new pawn(r,c,WHITE,this);
				
			}
			
			else if (r == 7) {
				if (c == 0 || c==7) {
					ps[r][c] = new rook(r, c, BLACK, this);
				}
				if (c == 1 || c == 6) {
					ps[r][c] = new knight(r, c, BLACK, this);
				}
				if (c == 2 || c == 5) {
					ps[r][c] = new bishop(r, c, BLACK, this);
				}
				if (c == 3) {
					ps[r][c] = new queen(r, c, BLACK, this);
				}
				if (c == 4) {
					ps[r][c] = new king(r, c, BLACK, this);
				}
			}
			else if (r == 6) {
				ps[r][c] = new pawn(r, c, BLACK, this);
				
			}
			
			
			else {
				ps[r][c] = nullptr;
			}
		}
	}
}
void Board::setPawn(int r, int c, color col)
{
	if (col == WHITE)
	{
		ps[r][c] = new pawn(r, c, WHITE, this);
	}
	else
		ps[r][c] = new pawn(r, c, BLACK, this);
}
void Board::setRook(int r, int c, color col)
{
	if (col == WHITE)
	{
		ps[r][c] = new rook(r, c, WHITE, this);
	}
	else
		ps[r][c] = new rook(r, c, BLACK, this);
}
void Board::setKing(int r, int c, color col)
{
	if (col == WHITE)
	{
		ps[r][c] = new king(r, c, WHITE, this);
	}
	else
		ps[r][c] = new king(r, c, BLACK, this);
}
void Board::setQueen(int r, int c, color col)
{
	if (col == WHITE)
	{
		ps[r][c] = new queen(r, c, WHITE, this);
	}
	else
		ps[r][c] = new queen(r, c, BLACK, this);
}
void Board::setKnight(int r, int c, color col)
{
	if (col == WHITE)
	{
		ps[r][c] = new knight(r, c, WHITE, this);
	}
	else
		ps[r][c] = new knight(r, c, BLACK, this);
}
void Board::setBishop(int r, int c, color col)
{
	if (col == WHITE)
	{
		ps[r][c] = new bishop(r, c, WHITE, this);
	}
	else
		ps[r][c] = new bishop(r, c, BLACK, this);
}
void Board::Move(int sri, int sci, int dri, int dci) {
	ps[dri][dci] = ps[sri][sci];
	ps[sri][sci] = nullptr;
}

piece* Board::getPieceAt(int r, int c) {
	return ps[r][c];
}
const Board& Board:: operator=(const Board& a) {
	this->ps = new piece * *[8];
	for (int r = 0; r < 8; r++) {
		this->ps[r] = new piece * [8];
		for (int c = 0; c < 8; c++) {
			if (a.ps[r][c] != nullptr) {
				this->ps[r][c] = a.ps[r][c];
			}
			else {
				this->ps[r][c] = nullptr;
			}
		}
	}
	return *this;
}
void Board::deep(const Board& a) {
	this->ps = new piece * *[8];
	for (int r = 0; r < 8; r++) {
		this->ps[r] = new piece * [8];
		for (int c = 0; c < 8; c++) {
			if (a.ps[r][c] != nullptr) {
				this->ps[r][c] = a.ps[r][c];
			}
			else {
				this->ps[r][c] = nullptr;
			}
		}
	}
}



void Board::displayBoard() {

	/*system("cls");
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (ps[r][c] == nullptr){
				cout << "-";
			}
			else {
				ps[r][c]->draw(r,c);
			}
		}
		cout << endl;
	}*/
}

