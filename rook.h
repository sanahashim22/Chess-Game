#pragma once
#include "piece.h"

class rook:public piece{
public:
	rook(int r, int c, color cl, Board* _b);
	virtual void draw(int ri,int ci);
	virtual bool isking() {
		return false;
	}
	bool islegalMove(Board* b, int sr, int sc, int dr, int dc) {
		return ((isHorizontal(sr,sc,dr,dc) && ishorizPathClear2(sr,sc,dr,dc)) ||
			(isVertical(sr,sc,dr,dc) && isvertPathClear2(sr,sc,dr,dc)));
	}
	char getsymbol() const override {
		return ((c == WHITE) ? 'R' : 'r');
	}
};

