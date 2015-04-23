//! EventManager class.
/*!
	 Handle Events.
*/
#pragma once
#include	<SFML\Window.hpp>
#include	<list>
#include	<memory>
#include	<stack>
#include	"Events.h"

typedef IEvent * ptr_event;
//! EventManager class.
/*!
	 Handle Events.
*/
class EventManager
{
public:
	//! EventManager constructor.
	/*!
	\param Takes the current window
	*/
	EventManager(sf::Window * window);
	//! EventManager destructor.
	~EventManager();
	//! Public member function to add an event.
	/*!
	\param Takes the event to add.
	This just pushes the event in the event list.
	*/
	void			addEvent(ptr_event);
	//! Public member function to clear event list
	void			clear();
	//! Public member function to pop an event on top of the event queue.
	void			poll();
	//! Public member function to check and wait for an event.
	void			wait();
private:
	//! Private member function used to check the list of event.
	/*!
	This method check the list to verify if an event is up.
	*/
	int							_checkEvent();
	/** 
    * a protected list of event
	*  list containing the events
    */
	std::list<ptr_event>		_eventList;
	/** 
    * a protected list of event to dispatch
	*  list containing the events to dispatch
    */
	std::stack<ptr_event>		_eventToDispatch;
	/** 
    * a protected variable event
	*  contains the event
    */
	sf::Event					_event;
	/** 
    * a protected variable window
	*  containing the window
    */
	sf::Window *				_window;
};
