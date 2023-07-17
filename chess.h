#pragma once
class Board;
class piece;
class player;
class piece;
struct position {
	int row, col;
};
class chess{
//protected:
	int sri=0, sci=0, dri=0, dci=0;
	int turn;
	player* ps[2];
	Board* b;
public:
	chess();
	void play();
	void displayTurnMsg(player* p);
	void selectPiece();
	void selectDestination();
	bool validSourceSelection(player* p,int r, int c);
	bool validDestSelection(player* p,int r, int c);
	void DisBor(int dim, int row, int col);
	void box(int sr, int sc, int ri, int ci, char sym, int color);
	bool** compute_highlight(player* b, int sri,int sci,int dim);
	void highlight(player* b, bool**& map, int dim, int brow, int bcol);
	void turnChange();
	void save();
	void load();
	position findking(player* s);
	bool check(player* s);
	bool selfcheck(player** s);
	bool checkmate(player* p);
	//bool selfcheck(piece* b, int dim, int turn);
	//bool check(piece* c, int dim, int turn);
	bool selfcheck(player* s);
	void unhighlight(player* ap, bool**& map, int dim, int brow, int bcol);
	void undo(piece* p);
	void redo(piece* p);
};

