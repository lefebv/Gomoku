#pragma once
#include	"Board.h"

class Referee
{
public:
	Referee(Board *);
	~Referee();
	bool			Victory(coords const & c, enum eColor color);
	bool			CheckAround(coords const & c);
	bool			isMoveValid(coords const & c, enum eColor color);
private:
	Board *			_b;
};