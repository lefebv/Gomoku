#include	<exception>
#include	<memory>
#include	<iomanip>
#include	<iostream>
#include	"Board.h"

Board::Board(int width, int height) : _width(width), _height(height)
{
	this->_map.reserve(width * height);
	for (int y = 0; y < width; ++y)
	{
		for (int x = 0; x < height; ++x)
			this->_map.push_back(Intersection(x, y));
	}
}

Board::~Board()
{
}

void												Board::clear()
{
	for (std::vector<Intersection>::iterator it = this->_map.begin(); it != this->_map.end(); ++it)
		(*it).clearMask();
}

int										Board::getWidth() const
{
	return (this->_width);
}

int										Board::getHeight() const
{
	return (this->_height);
}

coords												Board::getOppositeEnd(coords c, coords cDir, enum eColor color)
{
	int												xDiff = cDir.x - c.x;
	int												yDiff = cDir.y - c.y;

	while (this->isOnBoard(c) &&
		!this->_map[this->_getIndex(c.x, c.y)].isEmpty() &&
		this->_map[this->_getIndex(c.x, c.y)].checkMask(GET_MASK(HAS_ONE, color)))
	{
		c.x += xDiff;
		c.y += yDiff;
	}
	if (this->isOnBoard(c) && this->_map[this->_getIndex(c.x, c.y)].isEmpty())
		return (c);
	else
		throw std::invalid_argument("Nothing found");
}

coords												Board::getOppositePawn(coords c, coords cDir, enum eColor color)
{
	int												xDiff = cDir.x - c.x;
	int												yDiff = cDir.y - c.y;

	c.x += xDiff;
	c.y += yDiff;
	while (this->isOnBoard(c) &&
		!this->_map[this->_getIndex(c.x, c.y)].isEmpty() &&
		this->_map[this->_getIndex(c.x, c.y)].checkMask(GET_MASK(HAS_ONE, color)))
	{
		c.x += xDiff;
		c.y += yDiff;
	}
	if (this->isOnBoard(c) && !this->_map[this->_getIndex(c.x, c.y)].isEmpty())
		return (c);
	else
		throw std::invalid_argument("Nothing found");
}

int										Board::countSuccessiveRows(coords c, coords cDir, enum eColor color)
{
	int									xDiff = cDir.x - c.x;
	int									yDiff = cDir.y - c.y;
	int									i;

	for (i = 0; this->isOnBoard(c) &&
		!this->_map[this->_getIndex(c.x, c.y)].isEmpty() &&
		this->_map[this->_getIndex(c.x, c.y)].checkMask(GET_MASK(HAS_ONE, color)); ++i)
	{
		c.x += xDiff;
		c.y += yDiff;
	}
	return (i);
}

coords												Board::getOpposite(coords c, coords cDir)
{
	int												xDiff = cDir.x - c.x;
	int												yDiff = cDir.y - c.y;
	coords											res;
	
	res.x = c.x - xDiff;
	res.y = c.y - yDiff;
	return (res);
}

std::list<Intersection *> *							Board::getNeighbours(int index)
{
	int									y = index / this->_width;
	int									x = index - (this->_width * y);
	std::list<Intersection *>	*					res = new std::list<Intersection *>();

	if (x >= this->_width || y >= this->_height)
		throw std::out_of_range("Board->getIntersection(): x or y out of bound");
	if (x > 0)
		res->push_front(&(this->_map[this->_getIndex(x - 1, y)]));
	if (x > 0 && y > 0)
		res->push_front(&(this->_map[this->_getIndex(x - 1, y - 1)]));
	if (x > 0 && y < this->_height)
		res->push_front(&(this->_map[this->_getIndex(x - 1, y + 1)]));
	if (y > 0)
		res->push_front(&(this->_map[this->_getIndex(x, y - 1)]));
	if (y > 0 && x < this->_width)
		res->push_front(&(this->_map[this->_getIndex(x + 1, y - 1)]));
	if (x < this->_width)
		res->push_front(&(this->_map[this->_getIndex(x + 1, y)]));
	if (x < this->_width && y < this->_height)
		res->push_front(&(this->_map[this->_getIndex(x + 1, y + 1)]));
	if (y < this->_height)
		res->push_front(&(this->_map[this->_getIndex(x, y + 1)]));
	return (res);
}


std::list<Intersection *> *							Board::getNeighbours(int x, int y)
{
	std::list<Intersection *>	*					res = new std::list<Intersection *>();

	if (x >= this->_width || y >= this->_height)
		throw std::out_of_range("Board->getIntersection(): x or y out of bound");
	if (x > 0)
		res->push_front(&(this->_map[this->_getIndex(x - 1, y)]));
	if (x > 0 && y > 0)
		res->push_front(&(this->_map[this->_getIndex(x - 1, y - 1)]));
	if (x > 0 && y < this->_height - 1)
		res->push_front(&(this->_map[this->_getIndex(x - 1, y + 1)]));
	if (y > 0)
		res->push_front(&(this->_map[this->_getIndex(x, y - 1)]));
	if (y > 0 && x < this->_width - 1)
		res->push_front(&(this->_map[this->_getIndex(x + 1, y - 1)]));
	if (x < this->_width - 1)
		res->push_front(&(this->_map[this->_getIndex(x + 1, y)]));
	if (x < this->_width - 1 && y < this->_height - 1)
		res->push_front(&(this->_map[this->_getIndex(x + 1, y + 1)]));
	if (y < this->_height - 1)
		res->push_front(&(this->_map[this->_getIndex(x, y + 1)]));
	return (res);
}

Intersection &										Board::getIntersection(int index) 
{
	if (index < this->_height * this->_width)
		return (this->_map[index]);
	throw std::out_of_range("Board->getIntersection()");
}

Intersection &										Board::getIntersection(int x, int y)
{
	if (x < this->_width)
	{
		if (y < this->_height)
			return (this->_map[this->_getIndex(x, y)]);
		throw std::out_of_range("Board->getIntersection(): y out of bound");
	}
	throw std::out_of_range("Board->getIntersection(): x out of bound");
}

int										Board::_getIndex(int x, int y)
{
	return ((y * this->_width) + x);
}

bool									Board::isOnBoard(coords c)
{
	return (c.x >= 0 && c.x < this->_width && c.y >= 0 && c.y < this->_height);
}

static int							addUpMask(int exp)
{
	return (static_cast<int>(std::pow(4.0, exp)));
}

void			Board::_propagateFromSquare(coords const & c)
{
	std::unique_ptr< std::list<Intersection *> >	n;
	std::list<Intersection *>::iterator				i;
	eColor											color;
	int												count1;
	int												count2;
	coords											tmp;

	n.reset(this->getNeighbours(c.x, c.y));
	for (i = n->begin(); i != n->end(); ++i)
	{
		coords				coord((*i)->getX(), (*i)->getY());
		if (!(*i)->isEmpty())
		{
			if ((*i)->checkMask(HAS_ONE))
				color = BLACK;
			else
				color = WHITE;
			tmp = coords(coord.x - (c.x - coord.x), coord.y - (c.y - coord.y));
			count1 = this->countSuccessiveRows(coord, tmp, color);
			coords								opposite = this->getOpposite(c, coord);
			tmp = coords(opposite.x - (coord.x - opposite.x), opposite.y - (coord.y - opposite.y));
			count2 = this->countSuccessiveRows(opposite, tmp, color);
			this->getIntersection(c.x, c.y).addMask(GET_MASK(addUpMask(count1 + count2), color));
			try
			{
				tmp = this->getOppositeEnd(coord, coords(coord.x - (c.x - coord.x), coord.y - (c.y - coord.y)), color);
				this->getIntersection(tmp.x, tmp.y).addMask(GET_MASK(addUpMask(count1), color));
			} catch (std::exception &) {
			}
		}
	}
}

void			Board::_updateNeighbours(coords const & orig, coords const & neigh)
{
	int												xDiff = neigh.x - orig.x;
	int												yDiff = neigh.y - orig.y;
	enum eColor										color = this->getIntersection(orig.x, orig.y).getColor();

	if (color == this->getIntersection(neigh.x, neigh.y).getColor())
	{
		int count1 = this->countSuccessiveRows(orig, neigh, color);
		int count2 = this->countSuccessiveRows(orig, this->getOpposite(orig, neigh), color);
		int total = count1 + count2 - 1;
		int x = orig.x;
		int y = orig.y;
		std::cout << "x = " << x << " y = " << y << " total = " << total << "count1 = " << count1 << std::endl;
		for (int i = 0; i < count1; ++i)
		{
			if (this->getIntersection(x, y).getMask() < (GET_MASK(HAS_ONE, color) | addUpMask(total - 1)))
			{
				this->getIntersection(x, y).clearMask();
				this->getIntersection(x, y).addMask(GET_MASK(HAS_ONE, color) | addUpMask(total - 1));
			}
			x += xDiff;
			y += yDiff;
		}
	}
	else
	{
		try
		{
			enum eColor rev = REV_COLOR(color);
			coords c = this->getOppositePawn(orig, neigh, rev);
			int tmp = GET_MASK(HAS_ONE, REV_COLOR(color));
			int x = orig.x + xDiff;
			int y = orig.y + yDiff;
			std::cout << "x = " << x << " y = " << y << std::endl;
			while (this->getIntersection(x, y).getColor() != color && !this->getIntersection(x, y).isEmpty())
			{
				this->getIntersection(x, y).clearMask();
				this->getIntersection(x, y).addMask(GET_MASK(HAS_ONE, rev));
				x += xDiff;
				y += yDiff;
			}
		} catch (std::exception &) {
		}
	}
}

void			Board::PropagateInfo(coords const & c)
{
	std::unique_ptr< std::list<Intersection *> >	neighbours;
	std::list<Intersection *>::iterator				it;

	neighbours.reset(this->getNeighbours(c.x, c.y));
	for (it = neighbours->begin(); it != neighbours->end(); ++it)
	{
		if ((*it)->isEmpty())
			this->_propagateFromSquare(coords((*it)->getX(), (*it)->getY()));
		else
			this->_updateNeighbours(c, coords((*it)->getX(), (*it)->getY()));
	}
}

int								Board::staticEvaluation(enum eColor min, enum eColor max)
{
	int							min_res = 0;
	int							max_res = 0;

	for (int i = 0; i < this->_height * this->_width; ++i)
	{
		Intersection tmp = this->getIntersection(i);
		if (!tmp.isEmpty())
		{
			if (tmp.getColor() == min)
				min_res += REV_MASK(tmp.getMask(), min);
			else
				max_res += REV_MASK(tmp.getMask(), max);
		}
	}
	return (max_res - min_res);
}

void							Board::printBoard()
{
	for (int y = 0; y < this->_height; ++y)
	{
		for (int x = 0; x < this->_width; ++x)
			std::cout << std::setw(6) << this->getIntersection(x, y).getMask();
		std::cout << std::endl;
	}
}