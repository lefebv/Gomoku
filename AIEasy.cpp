#include	<random>
#include	"AIEasy.h"

AIEasy::AIEasy(Board * board): AI(board)
{
}

AIEasy::~AIEasy()
{
}

coords						AIEasy::play()
{
	std::list<inter_pair>::iterator	it;
	int								max;
	int								count = 0;
	int								rand;

	this->_interList.clear();
	this->collectInformations();
	max = this->_interList.front().first;
	for (it = this->_interList.begin(); it != this->_interList.end() && (*it).first == max; ++it)
		++count;
	rand = std::rand() % count;
	count = 0;
	for (it = this->_interList.begin(); it != this->_interList.end() && count < rand; ++it)
		++count;
	if (it == this->_interList.end())
		return (coords(this->_interList.front().second.getX(), this->_interList.front().second.getY()));
	else
		return (coords((*it).second.getX(), (*it).second.getY()));
}

