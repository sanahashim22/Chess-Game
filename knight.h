
#pragma once
#include "piece.h"

class knight :public piece{
public:
	knight(int r, int c, color cl, Board* _b);
	virtual void draw(int ri,int ci);
	virtual bool isking() {
		return false;
	}
	bool islegalMove(Board* b, int sr, int sc, int dr, int dc) {

		int r = abs(sr - dr);
		int c = abs(sc - dc);
		if (c == BLACK) {
			return ((r == 2 && c == 1) && (sr > dr));
		}
		else {
			return ((r == 2 && c == 1) && (sr < dr));
		}
	}
	char getsymbol() const override {
		return ((c == WHITE) ? 'N' : 'n');
	}
};

