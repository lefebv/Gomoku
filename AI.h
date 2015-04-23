//! AI class.
/*!
	 Handle the artificial intelligence of the computer player.
*/
#pragma once
#include	"Board.h"

class AI : public IPlayer
{
public:
	//! AI constructor.
	/*!
	\param Takes the board as parameter to be able to have acces to the information needed.
	This class derives from the IPlayer interface class.
	*/
	AI(Board *);
	//! Virtual AI destructor.
	virtual ~AI();
	//! Virtual public member function used to collect information from the board.
	/*!
	This method list all the intersection masks if the intersections are not empty.
	*/
	virtual	void							collectInformations();
	//! Virtual public member function to play.
	virtual coords							play() = 0;
	//! Virtual public member function to get playerType.
	virtual PlayerType						getType() const;
	/** 
    * a public definition of inter_pair
	*  inter pair are a weigthed pair of intersection
    */
	typedef	std::pair<int, Intersection>	inter_pair;
protected:
	/** 
    * a protected variable board.
    * Contains the game's board.
	* Set in the AI constructor and used to acces to the board infomation.
    */
	Board *									_board;
	/** 
    * a protected list interlist
	*  interlist is a list of inter pairs
    */
	std::list<inter_pair>					_interList;
};
