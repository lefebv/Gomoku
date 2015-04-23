//! GameRenderer class.
/*!
	Handle everything about the game rendering.
*/
#pragma once
#include	<SFML\Graphics.hpp>
#include	<SFML\Window.hpp>
#include	<queue>
#include	<functional>
#include	"Events.h"
#include	"Board.h"

typedef std::reference_wrapper<sf::Drawable> draw_ref;
//! GameRenderer class.
/*!
	Handle everything about the game rendering.
*/
class GameRenderer
{
public:
	//! GameRenderer constructor.
	GameRenderer();
	//! GameRenderer destructor.
	~GameRenderer();
	//! Public member function to load the board.
	/*!
	\param Takes the board to get any board information
	Load every board textures.
	*/
	void					loadBoard(Board const &);
	//! Public member function to draw the board.
	/*!
	\param Takes the board as parameter to be able to have acces to the information needed.
	Draw the board.
	*/
	void					drawBoard(Board &);
	//! Public member function to clear the board.
	/*!
	Clear all textures
	*/
	void					clear();
	//! Public member function to get the size of a board square.
	/*!
	Return the size of the square.
	*/
	float					getSpace() const;
	//! Public member function to get current window.
	/*!
	\return A pointer to the current window.
	*/
	sf::RenderWindow *		getWindow();
	//! Public member function to get the used font.
	/*!
	\return the used font
	*/
	sf::Font const &		getFont() const;
	//! Public member function to get the board coordinates.
	/*!
	\return the board coordinates
	*/
	MouseRect				getBoardCoords() const;
	//! Public member function to draw anything on the window.
	/*!
	\param sprite to be drawn
	*/
	void					draw(sf::Sprite const &);
private:
	//! Private member function to load game background.
	/*!
	Just load the game background using the sprite.
	*/
	void					_loadGameBackground();
	//! Private member function to draw the board.
	/*!
	\param The board to be drawn.
	*/
	void					_loadIntersections(Board const &);
	//! Private member function to draw all pawns on the board.
	/*!
	\param The boardin order to know the pawns positions.
	*/
	void					_loadPawns(Board &);
	//! Private member function to load margins, space, and any distance on the display.
	/*!
	\param The board to get the information needed.
	*/
	void					_loadLimits(Board const &);
    /** 
    * a private variable Width.
    * Contains the window's width
    */
	int			_width;
	/** 
    * a private variable Height
    * Contains the window's Height
    */
	int			_height;
    /** 
    * a private variable Space.
    * Contains the space between intersections
    */
	float					_space;
    /** 
    * a private variable side margin.
    * Contains the side margin value
    */
	float					_sideMargin;
    /** 
    * a private variable top margin.
    * Contains the top margin value
    */
	float					_topMargin;
    /** 
    * a private variable bottom Margin.
    * Contains the bottom margin value
    */
	float					_bottomMargin;
	/** 
    * a private texture of the background.
    * Contains the texture got from the file.
    */
	sf::Texture				_boardImage;
    /** 
    * a private sprite board.
    * Contains all the static part of the display (background + grid)
    */
	sf::Sprite				_board;
    /** 
    * a private sprite board.
    * Contains the final sprite of the game display
    */
	sf::Sprite				_finalSprite;
	/** 
    * a private board texture.
    * Contains the drawn display
    */
	sf::RenderTexture		_boardTexture;
	/** 
    * a private window.
    * Contains the window
    */
	sf::RenderWindow		_win;
	/** 
    * a private font.
    * Contains the font used.
    */
	sf::Font				_font;
};
