#pragma once
#include		"Bitmasks.h"

class Intersection
{
public:
	Intersection(int, int);
	Intersection(Intersection const &);
	~Intersection();
	int								getX() const;
	int								getY() const;
	bool							checkMask(int) const;
	bool							isEmpty() const;
	void							addMask(int);
	void							clearMask();
	Intersection &					operator=(Intersection const &);
	int								getMask() const;
	enum eColor						getColor() const;
	void							copy(Intersection const &);
private:
	int					_x;
	int					_y;
	int					_mask;
};
