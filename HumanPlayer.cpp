#pragma once
#include	"HumanPlayer.h"

HumanPlayer::HumanPlayer(EventManager *events, MouseRect const & rect): _ev(events), _rect(rect), _x(0), _y(0), _type(HUMAN)
{
}

HumanPlayer::~HumanPlayer()
{
}

coords			HumanPlayer::play()
{
	this->_x = 300;
	this->_y = 350;
	this->_ev->addEvent(new MouseClick(std::bind(&HumanPlayer::_storeCoords, this, std::placeholders::_1, std::placeholders::_2), this->_rect));
	this->_ev->wait();
	return (coords(this->_x, this->_y));
}

void			HumanPlayer::_storeCoords(int x, int y)
{
	if (x < 600 && x < 650)
	{
		this->_x = x;
		this->_y = y;
	}
}

enum PlayerType			HumanPlayer::getType() const
{
	return (this->_type);
}