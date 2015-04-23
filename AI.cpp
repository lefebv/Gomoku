#include	<algorithm>
#include	"AI.h"

AI::AI(Board * b) : _board(b)
{
}

AI::~AI()
{
}

PlayerType					AI::getType() const
{
	return (COMPUTER);
}

static bool						comp(AI::inter_pair const & a, AI::inter_pair const & b)
{
	return (a.first > b.first);
}

void						AI::collectInformations()
{
	for (int i = 0; i < this->_board->getWidth() * this->_board->getHeight(); ++i)
	{
		Intersection		tmp = this->_board->getIntersection(i);

		if (tmp.isEmpty() && tmp.getMask() != 0)
			this->_interList.push_front(inter_pair(tmp.getMask(), tmp));
	}
	this->_interList.sort(&comp);
}

