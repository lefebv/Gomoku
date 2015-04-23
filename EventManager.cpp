#include	"EventManager.h"

EventManager::EventManager(sf::Window * win) : _window(win)
{
}

EventManager::~EventManager()
{
	this->_eventList.clear();
}

void			EventManager::addEvent(ptr_event e)
{
	this->_eventList.push_front(e);
}

void			EventManager::clear()
{
	std::list<ptr_event>::iterator it = this->_eventList.begin();

	while (it != this->_eventList.end())
	{
		delete (*it);
		it = this->_eventList.erase(it);
	}
	while (!this->_eventToDispatch.empty())
	{
		delete this->_eventToDispatch.top();
		this->_eventToDispatch.pop();
	}
}

void			EventManager::poll()
{
	this->_window->pollEvent(this->_event);
	this->_checkEvent();
}

void			EventManager::wait()
{
	int			dispatched = 0;

	do
	{
		this->_window->waitEvent(this->_event);
		dispatched = this->_checkEvent();
	} while (dispatched == 0);
}

int				EventManager::_checkEvent()
{
	std::list<ptr_event>::iterator	it = this->_eventList.begin();
	int								i = 0;

	while (it != this->_eventList.end())
	{
		if ((*it)->isUp(this->_event))
		{
			this->_eventToDispatch.push(*it);
			it = this->_eventList.erase(it);
			++i;
		}
		else
			++it;
	}
	while (!this->_eventToDispatch.empty())
	{
		this->_eventToDispatch.top()->dispatch(this->_event);
		if (!this->_eventToDispatch.empty())
		{
			delete this->_eventToDispatch.top();
			this->_eventToDispatch.pop();
		}
	}
	return (i);
}
