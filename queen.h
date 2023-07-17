#pragma once
#include "piece.h"
class queen:public piece{
public:
	queen(int r, int c, color cl, Board* _b);
	virtual void draw(int ri,int ci);
    virtual bool isking() {
        return false;
    }
    /*
    bool islegalMove(Board* b, int sr, int sc, int dr, int dc) {

        if (b->getPieceAt(dr, dc) != nullptr && b->getPieceAt(dr, dc)->getColor() == b->getPieceAt(sr, sc)->getColor())
            return false;
        if (!isHor(sr, sc, dr, dc) && !isVer(sr, sc, dr, dc) && !isDig(sr, sc, dr, dc))
            return false;
        if (isHor(sr, sc, dr, dc))
            return (ishoriclr(sr, sc, dr, dc) || ishorizPathClear2(sr, sc, dr, dc));
        if (isVer(sr, sc, dr, dc))
            return (isverclr(sr, sc, dr, dc) || isverclr2(sr, sc, dr, dc));
        if (isDig(sr, sc, dr, dc))
            return (isdiagL2RpathClear1(sr, sc, dr, dc) || isdiagL2RpathClear2(sr, sc, dr, dc)
                || isdiagR2LpathClear1(sr, sc, dr, dc) || isdiagR2LpathClear2(sr, sc, dr, dc));
        return true;
    }
    */
    
    bool islegalMove(Board* b, int sr, int sc, int dr, int dc) {
        if (b->getPieceAt(dr, dc) != nullptr && b->getPieceAt(dr, dc)->getColor() 
            == b->getPieceAt(sr, sc)->getColor()) {
            return false;
        }
        if (!isHorizontal(sr, sc, dr, dc) && !isVertical(sr, sc, dr, dc) && 
            !isDiagonal(sr, sc, dr, dc)) {
            return false;
        }
        if (isHorizontal(sr, sc, dr, dc)) {
            if (!ishorizPathClear1(sr, sc, dr, dc) || !ishorizPathClear2(sr, sc, dr, dc)) {
                return false;
            }
        }
        if (isVertical(sr, sc, dr, dc)) {
            if (!isvertPathClear1(sr, sc, dr, dc) || !isvertPathClear2(sr, sc, dr, dc)) {
                return false;
            }
        }

        if (isDiagonal(sr, sc, dr, dc)) {
            if (isdiagL2RpathClear1(sr, sc, dr, dc) || isdiagL2RpathClear2(sr, sc, dr, dc)
                || isdiagR2LpathClear1(sr, sc, dr, dc) || isdiagR2LpathClear2(sr, sc, dr, dc)) {
                return true;
            }
        }

        return true;
    }
    char getsymbol() const override {
        return ((c == WHITE) ? 'Q' : 'q');
    }
};

