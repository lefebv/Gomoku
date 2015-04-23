//! IPlayer class.
/*!
	Any kind of player (human or computer), inherits from this interface.
*/
#pragma once

//! An structure of coordinates.
/*! Contains two integers, corresponding to the x and y position */
struct coords
{
	coords() {};
	coords(int _x, int _y) : x(_x), y(_y) {};
	int	x;
	int	y;
};

//! An enum of playerType.
/*! Contain the differents kinds of player in our game. */
enum PlayerType
{
	HUMAN, /*!< Enum value 0 is used to discribe human player. */  
	COMPUTER /*!< Enum value 1 is used to discribe computer player. */  
};
//! IPlayer class.
/*!
	Any kind of player (human or computer), inherits from this interface.
*/
class IPlayer
{
public:
	//! Public virtual destructor
	virtual ~IPlayer() {};
	//! Public virtual method play
	virtual coords	play() = 0;
	//! Public virtual method to get the player Type.
	virtual enum PlayerType		getType() const = 0;
};
