//! IEvent class.
/*!
	 Handle all events types.
*/
#pragma once
#include	<SFML\Window.hpp>
#include	<functional>
#include	<climits>


struct	MouseRect
{
	MouseRect() {};
	MouseRect(int _x, int _y, int _width, int _height) : x(_x), y(_y), width(_width), height(_height) {};
	int		x;
	int		y;
	int		width;
	int		height;
};

//! IEvent class.
/*!
	 Handle all events types.
*/
class IEvent
{
public:
	//! IEvent destructor.
	virtual ~IEvent() {};
	//! virtual member function used to know if the event occured
	/*!
	\param Take the event in parameter
	\return true if the event occure, else, returns false.
	*/
	virtual bool		isUp(sf::Event const &) const = 0;
	//! virtual member function used to call the callback linked to an event
	/*!
	\param Take the event in parameter
	*/
	virtual void		dispatch(sf::Event const &) = 0;
};


//! KeyEvent class.
/*!
	Class used to handle Keyboard Events, it derives from the IEvent Interface
*/
class KeyEvent : public IEvent
{
public:
	//! KeyEvent constructor.
	/*!
	\param Takes the associated callback, the event.
	*/
	KeyEvent(std::function<void (sf::Event const &)> const & call, enum sf::Keyboard::Key const & key) : _key(key), _callback(call)
	{
	}
	//! KeyEvent destructor.
	~KeyEvent() {};
	//! Public member function used to know if the event occured
	/*!
	\param Take the event in parameter
	\return true if the event occure, else, returns false.
	*/
	bool				isUp(sf::Event const & e) const
	{
		if (e.type == sf::Event::KeyPressed && e.key.code == this->_key)
			return (true);
		return (false);
	}
	//! Public Member function used to call the callback linked to an event
	/*!
	\param Take the event in parameter
	*/
	void				dispatch(sf::Event const & e)
	{
		this->_callback(e);
	}
private:
	/** 
    * a private enum key
    * Containg all the keys to be monitored
    */
	enum sf::Keyboard::Key  _key;
	/** 
    * a private callback
    * Containg callback associated to the key
    */
	std::function<void (sf::Event const &)>	_callback;
};

//! MouseClick class.
/*!
	Class used to handle Mouse clicks Events, it derives from the IEvent Interface
*/
class MouseClick : public IEvent
{
public:
	//! MouseClick constructor.
	/*!
	\param Takes the associated callback and the click zone.
	*/
	MouseClick(std::function<void (int, int)> const & call, MouseRect const & rect) :  _rect(rect), _call(call) {}
	//! MouseClick destructor.
	~MouseClick() {};
	//! Public member function used to know if the event occured
	/*!
	\param Take the event in parameter
	\return true if the event occure, else, returns false.
	*/
	bool							isUp(sf::Event const & e) const
	{
		int							x = e.mouseButton.x;
		int							y = e.mouseButton.y;

		if (e.type == sf::Event::MouseButtonReleased && this->_rect.x == -1)
			return (true);
		if (e.type == sf::Event::MouseButtonReleased &&
			e.mouseButton.button == sf::Mouse::Left &&
			x >= this->_rect.x && x < (this->_rect.x + this->_rect.width) &&
			y >= this->_rect.y && y < (this->_rect.y + this->_rect.height))
			return (true);
		return (false);
	}
	//! Public Member function used to call the callback linked to an event
	/*!
	\param Take the event in parameter
	*/
	void							dispatch(sf::Event const & e)
	{
		this->_call(e.mouseButton.x, e.mouseButton.y);
	}
private:
	/** 
    * a private rectangle
    * Containg the zone to be monitored
    */
	MouseRect						_rect;
	/** 
    * a private callback
    * Containg callback associated to the key
    */
	std::function<void (int, int)>	_call;
};

//! CloseEvent class.
/*!
	Class used to handle the close event
*/
class CloseEvent : public IEvent
{
public:
	//! CloseEvent constructor.
	/*!
	\param Takes the associated callback.
	*/
	CloseEvent(std::function<void ()> const call) : _call(call)
	{
	}
	//! CloseEvent destructor.
	~CloseEvent() {};
	//! Public member function used to know if the event occured
	/*!
	\param Take the event in parameter
	\return true if the event occure, else, returns false.
	*/
	bool							isUp(sf::Event const & e) const
	{
		if (e.type == sf::Event::Closed)
			return (true);
		return (false);
	}
	//! Public Member function used to call the callback linked to an event
	/*!
	\param Take the event in parameter
	*/
	void							dispatch(sf::Event const & e)
	{
		this->_call();
	}
private:
	/** 
    * a private callback
    * Containg callback associated to the key
    */
	std::function<void ()>		_call;
};