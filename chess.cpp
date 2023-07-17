#include "chess.h"
#include "player.h"
#include "piece.h"
#include "Board.h"
#include "goto.h"
#include <time.h>
#include <string>
#include<iostream>
#include<fstream>
using namespace std;

chess::chess() {
	gotoRC(64, 0);
	ps[0] = new player("sana",BLACK);
	ps[1] = new player("hina", WHITE);
	b = new Board();
	srand(time(0));
	turn = rand() % 2;
}
void chess::displayTurnMsg(player* p) {
	gotoRC(65, 0);
	cout << p->getName()<<"'s Turn\n";
}
void chess::selectPiece() {
	int x, y;
	getRowColbyLeftClick(x, y);
	//mygetRowColbyLeftClick(x, y, t, ptime);
	sri = x / 8;
	sci = y / 8;
}
void chess::selectDestination() {
	int x, y;
	getRowColbyLeftClick(x, y);
    //mygetRowColbyLeftClick(x, y, t, ptime);

	dri = x / 8;
	dci = y / 8;
}
bool chess::validSourceSelection(player* p, int r, int c) {
	if (r < 0 || r >= 8 || c < 0 || c >= 8) {
		return false;
	}
	piece* pi = b->getPieceAt(r, c);
	return pi != nullptr && pi->getColor() == p->getColor();
}
bool chess::validDestSelection(player* p, int r, int c) {
	if (r < 0 || r >= 8 || c < 0 || c >= 8) {
		return false;
	}
	piece* pi = b->getPieceAt(r, c);
	return pi == nullptr || pi->getColor() != p->getColor();
}
void chess::turnChange() {
	if (turn == 1) {
		turn = 0;
	}
	else {
		turn = 1;
	}
}
void chess::DisBor(int dim, int row, int col)
{
	char sym = -37;
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			if ((i + j) % 2 == 0) {
				box(i * row, j * col, row, col, sym, 2);
				gotoRC((i * row) + (row / 2), (j * col) + (row / 2));
				if (b->getPieceAt(i, j) != nullptr)
					b->getPieceAt(i, j)->draw((i * row) + (row / 2), (j * col) + (row / 2));
				else
					cout << "";
			}
			else
			{
				box(i * row, j * col, row, col, sym, 5);
				gotoRC((i * row) + (row / 2), (j * col) + (row / 2));
				if (b->getPieceAt(i, j) != nullptr)
					b->getPieceAt(i, j)->draw((i * row) + (row / 2), (j * col) + (row / 2));
				else
					cout << "";
			}
		}
	}
}
void chess::box(int sr, int sc, int ri, int ci, char sym, int color)
{
	for (int r = 0; r < ri; r++)
	{
		for (int c = 0; c < ci; c++)
		{
			gotoRC(sr + r, sc + c);
			SC(color);
			cout << sym;
		}
	}
}

void chess::undo(piece* p) {
	piece* q = b->getPieceAt(dri, dci);
	b->setPieceAt(sri, sci, q);
	b->setPieceAt(dri, dci, p);
}
void chess::redo(piece* p) {
	piece* q = b->getPieceAt(sri, sci);
	b->setPieceAt(dri, dci, q);
	b->setPieceAt(sri, sci, p);
}
bool** chess::compute_highlight(player* c, int sri,int sci, int dim) {
	bool** bmap = new bool* [dim];
	for (int i = 0; i < dim; i++) {
		bmap[i] = new bool[dim] {};
	}
	//int dc;
	for (int ri = 0; ri < dim; ri++) {
		for (int ci = 0; ci < dim; ci++) {
			int dri = ri;
			int dci = ci;
			if (validDestSelection(c, dri, dci) && b->getPieceAt(sri, sci)->islegalMove(b, sri, sci, dri, dci)) {
				bmap[ri][ci] = true;
			}
		}
	}
	return bmap;
}
void chess::highlight(player* b, bool**& map, int dim, int brow, int bcol) {
	char sym = -37;
	for (int r = 0; r < dim; r++) {
		for (int c = 0; c < dim; c++) {
			if (map[r][c] == true) {
				box(r * brow, c * bcol, brow, bcol, sym, 3);

			}
		}
	}
}

void chess::unhighlight(player* ap, bool**& map, int dim, int brow, int bcol)
{
	char sym = -37;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (map[r][c] == true)
			{
				if ((r + c) % 2 == 0)
				{
					box(r * brow, c * bcol, brow, bcol, sym, 2);
				}
				else
				{
					box(r * brow, c * bcol, brow, bcol, sym, 5);
				}
			}
		}
	}
}
position chess::findking(player* s) {
	position dc;
	dc.col = 0;
	dc.row = 0;
	
	//position dc;
	for (int ri = 0; ri < 8; ri++) {
		for (int ci = 0; ci < 8; ci++) {
			//	if ((ismypiece(b[r][c], turn)) && (b[r][c] == 'K' || b[r][c] == 'k')) {
			if (b->getPieceAt(ri,ci) != nullptr && b->getPieceAt(ri,ci)->isking() == true
				&& b->getPieceAt(ri, ci)->getColor() != s->getColor()) {
				dc.col = ci;
				dc.row = ri;
				return dc;
			}
		}
	}
	return dc;
}

bool chess::check(player* ap) {
	turnChange();
	position FindKing = findking(ap);
	turnChange();
	int sri = 0, sci = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			sri = i, sci = j;
			if (validSourceSelection(ps[turn], sri, sci) && 
				b->getPieceAt(sri, sci)->islegalMove(b, sri, sci, FindKing.row, FindKing.col))
			{
				return true;
			}
		}
	}
	return false;
}
bool chess::selfcheck(player** ap)
{
	
	bool che = false;
	turnChange();
	che = check(ap[turn]);
	if (che == true)
	{
		turnChange();
		gotoRC(68, 0);
		cout << "It's a self check!  ";
		return true;
	}
	else
	{
		turnChange();
		return false;
	}

}
bool chess::checkmate(player* p)
{
	if (!check(p))
	{
		return false;
	}
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			if (validSourceSelection(p, r, c))
			{
				piece* pp = b->getPieceAt(r, c);
				for (int tr = 0; tr < 8; tr++)
				{
					for (int tc = 0; tc < 8; tc++)
					{
						if (validDestSelection(p, tr, tc) && pp->islegalMove(b, r, c, tr, tc))
						{
							Board* tempB = new Board();
							tempB->deep(*b);
							tempB->Move(r, c, tr, tc);
							if (!check(p))
							{
								return false;
							}
						}
					}
				}
			}
		}
	}
	/*
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			if (validSourceSelection(p, r, c))
			{
				piece* pp = b->getPieceAt(r, c);
				for (int tr = 0; tr < 8; tr++)
				{
					for (int tc = 0; tc < 8; tc++)
					{
						if (validDestSelection(p, tr, tc) && pp->islegalMove(b, r, c, tr, tc))
						{
							Board tempB = *b;
							tempB.Move(r, c, tr, tc);
							if (!check(p))
							{
								return false;
							}
						}
					}
				}
			}
		}
	}*/
	return true;
}

/*
bool chess::check(player* s) {
	turnChange();
	position dc;
	dc = findking(s);
	turnChange();
	int sc = 0;
	int sr = 0;
	for (int ri = 0; ri < 8; ri++) {
		for (int ci = 0; ci < 8; ci++) {
			sc = ci;
			sr = ri;
			if (validSourceSelection(ps[turn],sr,sc) && b->getPieceAt(sr,sc)->islegalMove(b, sr, sc, dc.row, dc.col)) {
				return true;

			}
		}
	}
	return false;
}

//bool chess::selfcheck(player* s) {
//	turnChange();
//	return check(s);
//}

bool chess::selfcheck(player* s) {
	position dc = findking(s); // find the king of the current player
	int sc = 0;
	int sr = 0;
	for (int ri = 0; ri < 8; ri++) {
		for (int ci = 0; ci < 8; ci++) {
			sc = ci;
			sr = ri;
			// check if the current player's piece at (sr, sc) can legally move to (dc.row, dc.col)
			if (validSourceSelection(ps[turn], sr, sc) && b->getPieceAt(sr, sc)->islegalMove(b, sr, sc, dc.row, dc.col)) {
				return true;
			}
		}
	}
	return false;
}
*/
/*

bool ismypiece(piece* sym, int turn) {
	if (sym && turn == WHITE && isupper(sym->getsymbol())) {
		return true;
	}
	else if (sym && turn == BLACK && islower(sym->getsymbol())) {
		return true;
	}
	return false;
}

bool chess::check(piece* c, int dim, int turn) {
	turnChange();
	bool kingFound = false;
	int kingRow=-1, kingCol=-1;
	char kingSymbol = (turn == BLACK) ? 'K' : 'k';
	// Find the location of the king
	for (int ri = 0; ri < dim; ri++) {
		for (int ci = 0; ci < dim; ci++) {
			if (c && ismypiece(b->getPieceAt(ri, ci), turn) && c->getsymbol() == kingSymbol) {
				kingFound = true;
				kingRow = ri;
				kingCol = ci;
				break;
			}
		}
		if (kingFound) break;
	}
	// Check if any opposing piece can attack the king
	for (int ri = 0; ri < dim; ri++) {
		for (int ci = 0; ci < dim; ci++) {
			if (ismypiece(b->getPieceAt(ri, ci), 1 - turn) && b->getPieceAt(ri, ci)->islegalMove(b, ri, ci, kingRow, kingCol)) {
				turnChange();
				return true;
			}
		}
	}
	turnChange();
	return false;
}


bool chess::selfcheck(piece* c, int dim, int turn) {
	turnChange();
	return check(c, dim, turn);
}
*/
/*
bool ismypiece(piece* sym, int turn) {
    if (turn == WHITE && isupper(sym->getsymbol())) {
        return true;
    }
    else if (turn == BLACK && islower(sym->getsymbol())) {
        return true;
    }
    return false;
}

bool chess::check(piece* c, int dim, int turn) {
	turnChange();
	bool kingFound = false;
	int kingRow, kingCol;
	char kingSymbol = (turn == BLACK) ? 'K' : 'k';
	// Find the location of the king
	for (int ri = 0; ri < dim; ri++) {
		for (int ci = 0; ci < dim; ci++) {
			if (ismypiece(b->getPieceAt(ri, ci), turn) && c->getsymbol() == kingSymbol) {
				kingFound = true;
				kingRow = ri;
				kingCol = ci;
				break;
			}
		}
		if (kingFound) break;
	}
	turnChange();
	// Check if any opposing piece can attack the king
	for (int ri = 0; ri < dim; ri++) {
		for (int ci = 0; ci < dim; ci++) {
			if (ismypiece(b->getPieceAt(ri, ci), 1 - turn) && b->getPieceAt(sri, sci)->islegalMove(b, ri, ci, kingRow, kingCol)) {
				return true;
			}
		}
	}
	return false;
}


bool chess::selfcheck(piece* b, int dim, int turn) {
	turnChange();
	return check(b, dim, turn);
}*/
void _sleep(int l) {
	for (int i = 0; i < l * 100000; i++);
}
void chess::save()
{
	ofstream wrt("save.txt");
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			if (b->getPieceAt(r, c) == nullptr)
			{
				wrt << '-';
				continue;
			}
			else if (b->getPieceAt(r, c)->getsymbol() == 'P')
				wrt << 'P';
			else if (b->getPieceAt(r, c)->getsymbol() == 'p')
				wrt << 'p';
			else if (b->getPieceAt(r, c)->getsymbol() == 'K')
				wrt << 'K';
			else if (b->getPieceAt(r, c)->getsymbol() == 'k')
				wrt << 'k';
			else if (b->getPieceAt(r, c)->getsymbol() == 'Q')
				wrt << 'Q';
			else if (b->getPieceAt(r, c)->getsymbol() == 'q')
				wrt << 'q';
			else if (b->getPieceAt(r, c)->getsymbol() == 'R')
				wrt << 'R';
			else if (b->getPieceAt(r, c)->getsymbol() == 'r')
				wrt << 'r';
			else if (b->getPieceAt(r, c)->getsymbol() == 'N')
				wrt << 'N';
			else if (b->getPieceAt(r, c)->getsymbol() == 'n')
				wrt << 'n';
			else if (b->getPieceAt(r, c)->getsymbol() == 'B')
				wrt << 'B';
			else if (b->getPieceAt(r, c)->getsymbol() == 'b')
				wrt << 'b';
		}
		wrt << endl;
	}
}
void chess::load()
{
	ifstream rdr("save.txt");

	char piece;
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			rdr >> piece;
			switch (piece)
			{
			case 'P':
				b->setPawn(r, c, WHITE);
				break;
			case 'p':
				b->setPawn(r, c, BLACK);
				break;
			case 'K':
				b->setKing(r, c, WHITE);
				break;
			case 'k':
				b->setKing(r, c, BLACK);
				break;
			case 'Q':
				b->setQueen(r, c, WHITE);
				break;
			case 'q':
				b->setQueen(r, c, BLACK);
				break;
			case 'R':
				b->setRook(r, c, WHITE);
				break;
			case 'r':
				b->setRook(r, c, BLACK);
				break;
			case 'B':
				b->setBishop(r, c, WHITE);
				break;
			case 'b':
				b->setBishop(r, c, BLACK);
				break;
			case 'N':
				b->setKnight(r, c, WHITE);
				break;
			case 'n':
				b->setKnight(r, c, BLACK);
				break;
			case'-':
				b->setPieceAt(r, c, nullptr);
				break;
			}

		}

	}
}
void chess::play() {
	Board* a;
	a = new Board();
	Board* d;
	d = new Board();
	bool** map = new bool* [8];
	for (int r = 0; r < 8; r++)
	{
		map[r] = new bool[8] {};
	}
	char n;
	cout << "Do you want to load previous game?(y/n) " << endl;
	cin >> n;
	if (n == 'y' || n == 'Y') {
		load();
	}
	else {

	}
	system("cls");
	DisBor(8, 8, 8);
	piece* p;
	p = b->getPieceAt(sri, sci);
	int t = 0;
	while (true) {
		t++;
		//int ptime = ps[turn]->GetTime();
		displayTurnMsg(ps[turn]);
	do {
		do {
			do {
				do {
				//	do {
						/*if (selfcheck(ps)) {
							undo(p);
						}*/
						//gotoRC(66, 0);
						//cout << "Select Piece (ri,ci) : " << endl;
						t++;
						selectPiece();

						//selectPiece(t,ptime);
					} while (!validSourceSelection(ps[turn], sri, sci));
					map = compute_highlight(ps[turn], sri, sci, 8);
					highlight(ps[turn], map, 8, 8, 8);
					//gotoRC(67, 0);
					//cout << "Select Destination (ri,ci) : " << endl;
					selectDestination();

					//selectDestination(t,ptime);
					unhighlight(ps[turn], map, 8, 8, 8);
				    p = b->getPieceAt(dri, dci);

				} while (!b->getPieceAt(sri, sci)->islegalMove(b, sri, sci, dri, dci));
			} while (!validDestSelection(ps[turn], dri, dci));
		} while (!map[dri][dci]);
	//} while (selfcheck(ps));
	t = 0;
	//ps[turn]->SetTime(ptime);

	b->Move(sri, sci, dri, dci);


	if (check(ps[turn]) == true) {
		gotoRC(68, 0);
		cout << "CHECK....." << endl;
		_sleep(10000);
		system("cls");
		displayTurnMsg(ps[turn]);

	}
	if (checkmate(ps[turn])) {
		gotoRC(68, 0);
		cout << "CHECK MATE....." << endl;
		_sleep(10000);
		system("cls");
		displayTurnMsg(ps[turn]);
	}

		
	DisBor(8, 8, 8);



		//undo
		char input;
		gotoRC(68, 0);
		cout << "\n\n\n\nDo you want to undo? (y/n)" << endl;
	    q:
		cin >> input;
		switch (input) {
		case 'n':
			//turnChange();

			break;
		case 'N':
			//turnChange();

			break;
		case 'Y':
			undo(p);
			system("cls");
			DisBor(8, 8, 8);
			turnChange();
			cout << "\n\n\n\nDo you want to redo? (y/n)" << endl;
			char i;
			cin >> i;
			if (i == 'n' || i == 'N') {
				break;
			}
			if (i == 'y' || i=='Y') {
				b->Move(sri, sci, dci, dri);
				DisBor(8, 8, 8);
				turnChange();
			}
			break;
		case 'y':
			undo(p);
			//system("cls");
			DisBor(8, 8, 8);
			turnChange();

			cout << "\n\n\n\nDo you want to redo? (y/n)" << endl;
			char j;
			cin >> j;
			if (j == 'n' || j == 'N') {
				break;
			}
			if (j == 'y' || j == 'Y') {
				//b->Move(sri, sci, dci, dri);
				redo(p);
				DisBor(8, 8, 8);
				turnChange();
				system("cls");
				displayTurnMsg(ps[turn]);
				DisBor(8, 8, 8);
			}
			break;
		default:
			cout << "\n\n\n\nYou enter wrong choice!!!! please enter (y/n)....." << endl;
			goto q;
		}
		turnChange();
		save();
	}
}
