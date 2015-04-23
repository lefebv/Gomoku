//! AIEasy class.
/*!
	 Handle the artificial intelligence of the computer player in a easy mode.
*/
#pragma once
#include	"AI.h"

class AIEasy : public AI
{
public:
	//! AIEasy constructor.
	/*!
	\param Takes the board as parameter to be able to have acces to the information needed.
	This class derives from AI class.
	*/
	AIEasy(Board *);
	//! Virtual AIEasy destructor.
	virtual ~AIEasy();
	//! Virtual member to play.
	virtual coords			play();
};
