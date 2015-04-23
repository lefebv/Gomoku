#include		"Intersection.h"


Intersection::Intersection(int x, int y): _x(x), _y(y), _mask(0)
{
}

Intersection::Intersection(Intersection const & other)
{
	this->copy(other);
}

Intersection::~Intersection()
{
}

int			Intersection::getX() const
{
	return (this->_x);
}

int			Intersection::getY() const
{
	return (this->_y);
}

bool					Intersection::isEmpty() const
{
	if ((this->_mask & HAS_ONE) || (this->_mask & HAS_ONE_W))
		return (false);
	return (true);
}

bool					Intersection::checkMask(int mask) const
{
	if ((this->_mask & mask) != 0)
		return (true);
	return (false);
}

void					Intersection::addMask(int mask)
{
	this->_mask = this->_mask | mask;
}

void					Intersection::clearMask()
{
	this->_mask = 0;
}

int						Intersection::getMask() const
{
	return (this->_mask);
}

void					Intersection::copy(Intersection const & other)
{
	this->_x = other.getX();
	this->_y = other.getY();
	this->_mask = other.getMask();
}

enum eColor				Intersection::getColor() const
{
	return (this->_mask & HAS_ONE ? BLACK : WHITE);
}

Intersection &			Intersection::operator=(Intersection const & other)
{
	this->copy(other);
	return (*this);
}