#pragma once
#include "piece.h"

class king :public piece {
public:
	king(int r, int c, color cl, Board* _b);
	virtual void draw(int ri, int ci);
	bool islegalMove(Board* b, int sr, int sc, int dr, int dc) {
		int r = abs(sr - dr);
		int c = abs(sc - dc);
		return ((((isHorizontal(sr, sc, dr, dc) && ishorizPathClear2(sr, sc, dr, dc)) ||
			(isVertical(sr, sc, dr, dc) && isvertPathClear2(sr, sc, dr, dc)))) ||
			(isDiagonal(sr, sc, dr, dc) && (isdiagL2RpathClear1(sr, sc, dr, dc) ||
				isdiagR2LpathClear1(sr, sc, dr, dc))) && r <= 1 && c <= 1);
	}
	char getsymbol() const override {
		return ((c == WHITE) ? 'K' : 'k');
	}

	virtual bool isking() {
		return true;
	}

};

