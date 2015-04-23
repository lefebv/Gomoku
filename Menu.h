//! Menu class.
/*!
	 Handle display and button on the first page of the game.
*/
#pragma once
#include	"GameRenderer.h"
#include	"EventManager.h"
#include	"Game.h"

class Menu
{
public:
	//! Menu constructor.
	/*!
	\param Event.
	\param Game Renderer.
	\param Board.
	*/
	Menu(EventManager *, GameRenderer *, Board *);
	//! Referee destructor.
	~Menu();
	
	//! Public member function run
	/*!
	This method is called at the very beginning of the game, to create the first while that will wait
	for the player to chose setting from the menu page, or laungh the game.
	*/
	void					run();
	//! Public member function loadGraphics
	/*!
	This method is called at the very beginning of the game, to set everything displayed on the menu page.
	*/	
	void					loadGraphics();
	//! Public member function loadEvents
	/*!
	This method is called at the very beginning of the game, to set up every possible clicking event the user
	could do, in order to execute the right action after any event.
	*/
	void					loadEvents();
private:
	//! Private member function getPlayer taking an integer parameter
	/*!
	\param containing the player type. If it is 0, it would mean that it is a human player, if it is one, it 
	refers to an artificial inteligence.
	\return the corresponding player that has been created, depending of his type.
	*/
	IPlayer *				_getPlayer(int);
	//! Private member function incrementWhite
	/*!
	\param integers in param are send by the callback method, corresponding to the position of the mouse.
	This privated method is used to handle the button of the white player on the menu page.
	If player clicks on the top triangles to switch the player type,
	this method is called to set up everything.
	*/
	void					_incrWhite(int, int);
	//! Private member function incrementBlack
	/*!
	\param integers in param are send by the callback method, corresponding to the position of the mouse.
	This privated method is used to handle the button of the black player on the menu page.
	If player clicks on the top triangles to switch the player type,
	this method is called to set up everything.
	*/
	void					_incrBlack(int, int);
	//! Private member function decrementWhite
	/*!
	\param integers in param are send by the callback method, corresponding to the position of the mouse.
	This privated method is used to handle the button of the white player on the menu page.
	If player clicks on the bottom triangles to switch the player type,
	this method is called to set up everything.
	*/
	void					_decrWhite(int, int);
	//! Private member function decrementBlack
	/*!
	\param integers in param are send by the callback method, corresponding to the position of the mouse.
	This privated method is used to handle the button of the black player on the menu page.
	If player clicks on the bottom triangles to switch the player type,
	this method is called to set up everything.
	*/
	void					_decrBlack(int, int);
	//! Private member function startGame
	/*!
	\param integers in param are send by the callback method, corresponding to the position of the mouse.
	This privated method launches the game. initialize the two buttons' callback of the game page, and 
	loop until the game is over.
	*/
	void					_startGame(int, int);
	//! Private member function Exit
	/*!
	\param integers in param are send by the callback method, corresponding to the position of the mouse.
	Method stoping the game if the user click on the exit button.
	*/
	void					_exit(int, int);
    /** 
    * a private variable max.
    * Contains the number of different playerType
    */
	const int				_max;
    /** 
    * a private variable event.
    * Contains the Event manager of the game. Given in parameter of the menu constructor, and used to handle
	* event in the menu page.
    */
	EventManager *			_ev;
    /** 
    * a private variable renderer.
    * Contains the game renderer of the game. Given in parameter of the menu constructor
	* Used to display everything on the window.
	*/
	GameRenderer *			_rend;
	/** 
    * a private variable board.
    * Contains the game's board.
	* Used when we call the player's constructor.
    */
	Board *					_b;
	/** 
    * a private variable game.
    * Contains the game.
	* Used to launch the game.
    */
	Game					_game;
	/** 
    * a private variable whiteChoice.
    * Contains the type of the white player (human or computer).
    */
	int						_whiteC;
	/** 
    * a private variable blackChoice.
    * Contains the type of the black player (human or computer).
    */
	int						_blackC;
	/** 
    * a private variable choiceString
    * Contains the type of player that can be desplayed on the menu.
    */
	std::vector<std::string>	_choiceStrings;
	/** 
    * a private variable texture.
    * Contains the whole display of the menu page.
    */
	sf::RenderTexture		_texture;
};
