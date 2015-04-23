//! HumanPlayer class.
/*!
	 Class used to handle playing moves.
*/
#pragma once
#include	"Board.h"
#include	"EventManager.h"
#include	"IPlayer.h"

class HumanPlayer : public IPlayer
{
public:
	//! Human Player constructor.
	/*!
	\param Takes the event manager and the zone of the mouse position.
	*/
	HumanPlayer(EventManager *, MouseRect const &);
	//! Human Player destructor.
	~HumanPlayer();
	//! Public member function to play.
	/*!
	\return The position of the played pawn.
	*/
	coords				play();
	//! Public member function to get the player Type.
	/*!
	\return the type of human player contained in the PlayerType enum.
	*/
	enum PlayerType		getType() const;
private:
	//! Private member function to store the position of the mouse when the user clicks.
	/*!
	\param Takes the X and Y position of the mouse, and save it in _x and _y.
	Called by the callback method set with the event manager, to remember the position where the user clicked.
	*/
	void				_storeCoords(int, int);
    /** 
    * a private variable event.
    * Contains the Event manager of the game. Given in parameter of the Human Player constructor, and used to handle
	* player events.
    */
	EventManager *		_ev;
	/** 
    * a private variable rectangle
    * Contains the zone position of the mouse.
    */
	MouseRect			_rect;
	/** 
    * a private variable X
    * Contains the X position of the click.
    */
	int		_x;
	/** 
    * a private variable Y
    * Contains the Y position of the click.
    */
	int		_y;
	/** 
    * a private variable PlayerType
    * Contains the Type of player, stored in the PlayerType enum, and set from the Human Player constructor.
    */
	enum PlayerType		_type;
};

