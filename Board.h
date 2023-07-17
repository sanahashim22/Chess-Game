#pragma once
#include"bscs22101_Header.h"
class piece;
class Board
{
	piece*** ps;
public:
	Board();
	void displayBoard();
	piece* getPieceAt(int r, int c);
    void setPieceAt(int row, int col, piece* p) {
        ps[row][col] = p;
		if (p == nullptr) {
			ps[row][col] = nullptr;
		}
    }
	void Move(int sri, int sci, int dri, int dci);
	void setBishop(int r, int c, color col);
	void setKnight(int r, int c, color col);
	void setQueen(int r, int c, color col);
	void setKing(int r, int c, color col);
	void setRook(int r, int c, color col);
	void setPawn(int r, int c, color col);
	const Board& operator=(const Board& a);
	void deep(const Board& a);
};

