#pragma once
#include "piece.h"

class bishop :public piece{
public:
	bishop(int r, int c, color cl, Board* _b);
	virtual void draw(int ri,int ci);
	virtual bool isking() {
		return false;
	}
    bool islegalMove(Board* b, int sr, int sc, int dr, int dc) {
		return (isDiagonal(sr, sc, dr, dc) && (isdiagL2RpathClear1(sr, sc, dr, dc) ||
			isdiagR2LpathClear1(sr, sc, dr, dc)));
	}
	char getsymbol() const override {
		return ((c == WHITE) ? 'B' : 'b');
	}
};

