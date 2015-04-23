#include	<memory>
#include	"Referee.h"
#include	"Bitmasks.h"

Referee::Referee(Board *b): _b(b)
{
}

Referee::~Referee()
{
}



bool			Referee::Victory(coords const & c, enum eColor color)
{
	//First method to check victory. Will be improved later for optimization.
	int countNumberOfSameColoredPowns = 0;
	int tmpX = c.x - 4;
	int tmpY = c.y - 4;
	bool win = false;

	//First we check on the X axe
	while(tmpX <= c.x + 4)
	{
		if (tmpX >= 0 && tmpX <= 18)
		{
			if(this->_b->getIntersection(tmpX, c.y).checkMask(GET_MASK(HAS_ONE, color)))
			{
				countNumberOfSameColoredPowns++;
				if (countNumberOfSameColoredPowns == 5)			
					win = true;
				printf("count = " + countNumberOfSameColoredPowns);
			}
			else
				countNumberOfSameColoredPowns = 0;
		}
		tmpX++;
	}
	countNumberOfSameColoredPowns = 0;
	//Then we check on the Y axe
	while(tmpY <= c.y + 4)
	{
		if (tmpY >= 0 && tmpY <= 18)
		{
			if(this->_b->getIntersection(c.x, tmpY).checkMask(GET_MASK(HAS_ONE, color)))
			{
				countNumberOfSameColoredPowns++;
				if (countNumberOfSameColoredPowns == 5)			
					win = true;
			}
			else
				countNumberOfSameColoredPowns = 0;
		}
		tmpY++;
	}
	//Then we check on diagonal
	tmpX = c.x - 4;
	tmpY = c.y - 4;
	countNumberOfSameColoredPowns = 0;
	while(tmpY <= c.y + 4 && tmpX <= c.x + 4)
	{
		if (tmpY >= 0 && tmpY <= 18 && tmpX >= 0 && tmpX <= 18)
		{
			if(this->_b->getIntersection(tmpX, tmpY).checkMask(GET_MASK(HAS_ONE, color)))
			{
				countNumberOfSameColoredPowns++;
				if (countNumberOfSameColoredPowns == 5)			
					win = true;
			}
			else
				countNumberOfSameColoredPowns = 0;
		}
		tmpY++;
		tmpX++;
	}
	//Then we check the second diagonal
	tmpX = c.x - 4;
	tmpY = c.y + 4;
	countNumberOfSameColoredPowns = 0;
	while(tmpY >= c.y - 4 && tmpX <= c.x + 4)
	{
		if (tmpY >= 0 && tmpY <= 18 && tmpX >= 0 && tmpX <= 18)
		{
			if(this->_b->getIntersection(tmpX, tmpY).checkMask(GET_MASK(HAS_ONE, color)))
			{
				countNumberOfSameColoredPowns++;
				if (countNumberOfSameColoredPowns == 5)			
					win = true;
			}
			else
				countNumberOfSameColoredPowns = 0;
		}
		tmpY--;
		tmpX++;
	}
	if (win == true)
	{
		//MSG WINNER + QUIT GAME OR RESTARD MSG
		return (true);
	}
	return (false);
}

bool			Referee::CheckAround(coords const & c)
{
	std::unique_ptr< std::list<Intersection *> >	neighbours;
	std::list<Intersection *>::iterator				it;

	neighbours.reset(this->_b->getNeighbours(c.x, c.y));
	for (it = neighbours->begin(); it != neighbours->end() && (*it)->isEmpty(); ++it);
	if (it == neighbours->end())
		return (false);
	return (true);
}

bool			Referee::isMoveValid(coords const & c, enum eColor color)
{
	if (this->_b->getIntersection(c.x, c.y).isEmpty())
		return (this->CheckAround(c));
	return (false);
}