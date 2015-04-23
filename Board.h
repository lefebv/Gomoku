#pragma once
#include	<vector>
#include	<list>
#include	"IPlayer.h"
#include	"Intersection.h"

class Board
{
public:
	Board(int, int);
	~Board();
	void										clear();
	coords										getOppositeEnd(coords, coords, eColor);
	coords										getOppositePawn(coords, coords, eColor);
	int											countSuccessiveRows(coords, coords, enum eColor);
	coords										getOpposite(coords, coords);
	std::list<Intersection *> *					getNeighbours(int);
	std::list<Intersection *> *					getNeighbours(int, int);
	int											getWidth() const;
	int											getHeight() const;
	Intersection &								getIntersection(int);
	Intersection &								getIntersection(int, int);
	bool										isOnBoard(coords);
	void										PropagateInfo(coords const & c);
	void										printBoard();
	int											staticEvaluation(enum eColor, enum eColor);
private:
	void										_propagateFromSquare(coords const &);
	void										_updateNeighbours(coords const &, coords const &);
	int											_getIndex(int, int);
	std::vector<Intersection>					_map;
	int											_width;
	int											_height;
};
