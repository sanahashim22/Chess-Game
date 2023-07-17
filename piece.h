#pragma once
#include"bscs22101_Header.h"
#include"Board.h"
#include<windows.h>
class Board;
class piece
{
protected:
	int ri, ci;
	color c;
	Board* b;
	void getRowColbyLeftClick(int& rpos, int& cpos)
	{
		HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
		DWORD Events;
		INPUT_RECORD InputRecord;
		SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
		do
		{
			ReadConsoleInput(hInput, &InputRecord, 1, &Events);
			if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
				rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
				break;
			}
		} while (true);
	}
	void gotoRowCol(int rpos, int cpos)
	{
		COORD scrn;
		HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
		scrn.X = cpos;
		scrn.Y = rpos;
		SetConsoleCursorPosition(hOuput, scrn);
	}
	void SetColor(int clr)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
	}
	bool isHorizontal(int sr,int sc,int dr,int dc) {
		return sr == dr;
	}
	bool isVertical(int sr, int sc, int dr, int dc) {
		return sc == dc;
	}
	bool isDiagonal(int sr, int sc, int dr, int dc) {
		return abs(sr - dr)== abs(sc - dc);
	}	
	bool ishorizPathClear1(int sr, int sc, int dr, int dc) {
		if (sc < dc) {
			for (int c = sc + 1; c < dc; c++) {
				if (b->getPieceAt(sr,c) != nullptr) {
					return false;
				}
			}
			return true;
		}
		else {
			for (int c = dc + 1; c < sc ; c++) {
				if (b->getPieceAt(sr, c) != nullptr) {
					return false;
				}
			}
			return true;
		}

	}
	bool ishorizPathClear2(int sr, int sc, int dr, int dc) {
		int cs, ce;
		if (sc < dc) {
			cs = sc + 1;
			ce = dc - 1;
		}
		else {
			cs = dc + 1;
			ce = sc - 1;
		}
		for (int c = cs; c <= ce; c++) {
			if (b->getPieceAt(sr, c) != nullptr) {
				return false;
			}
		}
		return true;
	}
	bool isvertPathClear1(int sr, int sc, int dr, int dc) {
		if (sr < dr) {
			for (int r = sr + 1; r < dr; r++) {
				if (b->getPieceAt(r, sc) != nullptr) {
					return false;
				}
			}
			return true;
		}
		else {
			for (int r = dr + 1; r < sr; r++) {
				if (b->getPieceAt(r, sc) != nullptr) {
					return false;
				}
			}
			return true;
		}

	}
	bool isvertPathClear2(int sr, int sc, int dr, int dc) {
		int rs, re;
		if (sr < dr) {
			rs = sr + 1;
			re = dr - 1;
		}
		else {
			rs = dr + 1;
			re = sr - 1;
		}
		for (int r = rs; r <= re; r++) {
			if (b->getPieceAt(r, sc) != nullptr) {
				return false;
			}
		}
		return true;
	}
	bool isdiagL2RpathClear1(int sr, int sc, int dr, int dc) {
		int d;
		if (sr < dr) {
			d = dr - sr - 1;
			for (int i = 1; i <= d; i++) {
				if (b->getPieceAt(sr+i, sc+i) != nullptr) {
					return false;
				}
			}
			return true;
		}
		else {
			d = (sr - dr - 1);
			for (int i = 1; i <= d; i++) {
				if (b->getPieceAt(sr-i, sc-i) != nullptr) {
					return false;
				}
			}
			return true;
		}

	}
	bool isdiagL2RpathClear2(int sr, int sc, int dr, int dc) {
		int d = abs(dr - sr) - 1;

		for (int i = 1; i <= d; i++) {
			if (sr < dr) {
				if (b->getPieceAt(sr+i, sc+i) != nullptr) {
					return false;
				}
			}
			else {
				if (b->getPieceAt(sr-i, sc-i) != nullptr) {
					return false;
				}
			}
		}
		return true;
	}
	bool isdiagR2LpathClear1(int sr, int sc, int dr, int dc) {
		int d;
		if (sr < dr) {
			d = dr - sr - 1;
			for (int i = 1; i <= d; i++) {
				if (b->getPieceAt(sr + i, sc - i) != nullptr) {
					return false;
				}
			}
			return true;
		}
		else {
			d = (sr - dr - 1);
			for (int i = 1; i <= d; i++) {
				if (b->getPieceAt(sr - i, sc + i) != nullptr) {
					return false;
				}
			}
			return true;
		}
	}
	bool isdiagR2LpathClear2(int sr, int sc, int dr, int dc) {
		int d = abs(dr - sr) - 1;
		for (int i = 1; i <= d; i++) {
			if (sr < dr) {
				if (b->getPieceAt(sr + i, sc - i) != nullptr) {
					return false;
				}
			}

			else {
				if (b->getPieceAt(sr - i, sc + i) != nullptr) {
					return false;
				}
			}
		}
		return true;

	}
	bool isHor(int sr, int sc, int dr, int dc)
	{
		return sr == dr;
	}
	bool isVer(int sr, int sc, int dr, int dc)
	{
		return sc == dc;
	}
	bool isDig(int sr, int sc, int dr, int dc)
	{
		return abs(sr - dr) == abs(sc - dc);
	}
	bool ishoriclr(int sr, int sc, int dr, int dc)
	{
		if (sc < dc)
		{
			for (int c = sc + 1; c < dc; c++)
			{
				if (b->getPieceAt(sr, c) != nullptr)//(B[sc.ri][c] != '-')
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			for (int c = dc + 1; c < sc; c++)
			{
				if (b->getPieceAt(sr, c) != nullptr)//(B[sc.ri][c] != '-')
				{
					return false;
				}
			}
			return true;
		}

	}
	bool ishoriclr2(int sr, int sc, int dr, int dc)
	{
		int rs, re;
		if (sr < dr)
		{
			rs = sr + 1, re = dr - 1;
		}
		else
		{
			rs = dr + 1, re = sr - 1;
		}
		for (int r = rs; r <= re; r++)
		{
			if (b->getPieceAt(r, sc) != nullptr)//(B[r][sc.ci] != '-')
			{
				return false;
			}
		}
		return true;
	}
	bool isverclr(int sr, int sc, int dr, int dc)
	{
		if (sr < dr)
		{
			for (int r = sr + 1; r < dr; r++)
			{
				if (b->getPieceAt(r, sc) != nullptr)//(B[r][sc.ci] != '-')
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			for (int r = dr - 1; r < sr; r--)
			{
				if (b->getPieceAt(r, sc) != nullptr)// (B[r][sc.ci] != '-')
				{
					return false;
				}
			}
			return true;
		}

	}
	bool isverclr2(int sr, int sc, int dr, int dc)
	{
		int rs, re;
		if (sr < dr)
		{
			rs = sr + 1, re = dr - 1;
		}
		else
		{
			rs = dr + 1, re = sr - 1;
		}
		for (int r = rs; r <= re; r++)
		{
			if (b->getPieceAt(r, sc) != nullptr)//(B[r][sc.ci] != '-')
			{
				return false;
			}
		}
		return true;
	}
	bool isDiagonalL2RPathClear1(int sr, int sc, int dr, int dc)
	{
		int d;
		if (sr < dr)
		{
			d = dr - sr - 1;
			for (int i = 1; i <= d; i++)
			{
				if (b->getPieceAt(sr + i, sc + i) != nullptr)
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			d = sr - dr - 1;
			for (int i = 1; i <= d; i++)
			{
				if (b->getPieceAt(sr - i, sc - i) != nullptr)//B[Sc.ri - i][Sc.ci - i] != '-')
				{
					return false;
				}
			}
			return true;
		}
	}
	bool isDiagonalR2LPathClear1(int sr, int sc, int dr, int dc)
	{
		int d;
		if (sr < dr)
		{
			d = dc - sc - 1;
			for (int i = 1; i <= d; i++)
			{
				if (b->getPieceAt(sr + i, sc - i) != nullptr)//Ps[sr + i][sc - i] !=nullptr)
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			d = sr - dr - 1;
			for (int i = 1; i <= d; i++)
			{
				if (b->getPieceAt(sr - i, sc + i) != nullptr)//[Sc.ri - i][Sc.ci + i] != '-')
				{
					return false;
				}
			}
			return true;
		}
	}
public:
	piece(int r, int c, color cl, Board* _b);
	virtual void draw(int ri,int ci) = 0;
	void move(int r, int c);
	color getColor();
	virtual bool islegalMove(Board* b,int sr, int sc, int dr, int dc) = 0;
	virtual char getsymbol() const = 0;
	virtual bool isking() = 0;

};
