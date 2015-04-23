//! Game class.
/*!
	 Handle the game states.
*/
#pragma once
#include	"Referee.h"
#include	"HumanPlayer.h"
#include	"GameRenderer.h"
#include	"Bitmasks.h"
#include	"EventManager.h"

class Game
{
public:
	//! Game constructor.
	/*!
	\param Takes the board, the game renderer and the event manager as parameter to be able to have acces to the information needed.
	*/
	Game(GameRenderer *, EventManager *, Board *);
	//! Game Destructor.
	~Game();
	//! member function to set the type of player playing the black pawns
	/*!
	\param Player to be able to get the player type.
	This method sets the player to black pawns
	*/
	void				setBlack(IPlayer *);
	//! member function to set the type of player playing the white pawns
	/*!
	\param Player to be able to get the player type.
	This method sets the player to white pawns
	*/
	void				setWhite(IPlayer *);
	//! member function to reset the game
	void				reset();
	//! member function to launch the game
	/*!
	Contains a loop while the game is running.
	\return the state of the game.
	*/
	bool				run();
	//! member function to stop the game
	void				stop();
	//! member function to launch game events
	/*!
	Launch the two events needed during the games, for the restart and quit buttons.
	*/
	void				loadEvents();
private:
	//! Private member function initializing all values needed during the game.
	void				_init();
	//! Private member function restarting the game.
	/*!
	\param Takes two integers given by the callback, corresponding to the position of the mouse.
	This is the callback method for the restart button.
	*/
	void				_restart(int, int);
	//! Private member function to get back to the menu
	/*!
	\param Takes two integers given by the callback, corresponding to the position of the mouse.
	This is the callback method for the menu button.
	*/
	void				_menu(int, int);
	//! Private member function to display victory.
	/*!
	\param Takes the color of the winner
	This method stops the game and display a victory message on screen.
	*/
	void				_victory(enum eColor);
	//! Private member function to get the coordinates.
	/*!
	\param Takes the coordinates of the mouse.
	Return the coordinates of the pawn to be displayed.
	*/
	coords				_getCoords(coords);
	//! Private member function to play white pawn.
	/*!
	This method checks if the player is the white player one, and if possible, add a white pawn.
	*/
	void				_playWhite();
	//! Private member function to play black pawn.
	/*!
	This method checks if the player is the black player one, and if possible, add a black pawn.
	*/
	void				_playBlack();
	/** 
    * a private variable turn.
    * used to know what turn is playing, either black or white.
    */
	enum eColor			_turn;
	/** 
    * a private variable renderer.
    * Contains the game renderer of the game. Given in parameter of the menu constructor
	* Used to display everything on the window.
	*/
	GameRenderer *		_render;
    /** 
    * a private variable event.
    * Contains the Event manager of the game. Given in parameter of the menu constructor, and used to handle
	* event in the game page.
    */
	EventManager *		_events;
	/** 
    * a private variable board.
    * Contains the game's board.
	* Used to init, restart or render the game.
    */
	Board *				_board;
	/** 
    * a private variable Player white.
    * Contains the white player
    */
	IPlayer *			_white;
	/** 
    * a private variable Player black.
    * Contains the black player
    */
	IPlayer *			_black;
	/** 
    * a private variable space.
    * Used to define graphical spaces 
    */
	float				_space;
	/** 
    * a private variable return.
    * Used to give the state of the game.
    */
	bool				_return;
	/** 
    * a private variable return.
    * Used to give the state of the game.
    */
	bool				_isRunning;
	/** 
    * a private variable boardCoords
    * Contain the board Coordinates.
    */
	MouseRect			_boardCoords;
	/** 
    * a private variable referee.
    * contain the game referee to check every rules.
    */
	Referee				_ref;
};
