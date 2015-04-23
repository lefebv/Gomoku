#include	"Game.h"
#include	<math.h>

static void		changeTurn(enum eColor & c)
{
	if (c == BLACK)
		c = WHITE;
	else
		c = BLACK;
}


Game::Game(GameRenderer *rend, EventManager *ev, Board *board) : _turn(BLACK), _render(rend), _events(ev), _board(board), _white(0), _black(0), _isRunning(false), _ref(board)
{
}

Game::~Game()
{
	delete this->_white;
	delete this->_black;
}

void			Game::setBlack(IPlayer * black)
{
	this->_black = black;
}

void			Game::loadEvents()
{
	this->_events->addEvent(new MouseClick(std::bind(&Game::_menu, this, std::placeholders::_1, std::placeholders::_2), MouseRect(10, 10, 100, 30)));
	this->_events->addEvent(new MouseClick(std::bind(&Game::_restart, this, std::placeholders::_1, std::placeholders::_2), MouseRect(430, 10, 150, 30)));
}

void			Game::setWhite(IPlayer * white)
{
	this->_white = white;
}

void			Game::reset()
{
	this->_isRunning = false;
	this->_board->clear();
	delete this->_white;
	delete this->_black;
	this->_white = 0;
	this->_black = 0;
}

void			Game::stop()
{
	this->_isRunning = false;
}

void			Game::_menu(int, int)
{
	this->_isRunning = false;
	this->_return = true;
}

void			Game::_restart(int, int)
{
	this->_isRunning = false;
	this->_return = false;
}

void			Game::_init()
{
	std::unique_ptr< std::list<Intersection *> >	tmp;

	this->_isRunning = true;
	this->_return = false;
	this->_boardCoords = this->_render->getBoardCoords();
	this->_space = this->_render->getSpace();
	this->_board->clear();
	this->_board->getIntersection(9,9).addMask(HAS_ONE);
	tmp.reset(this->_board->getNeighbours(9, 9));
	for (std::list<Intersection *>::iterator it = tmp->begin(); it != tmp->end(); ++it)
		(*it)->addMask(TWO);
	this->_turn = BLACK;
	this->_render->drawBoard(*(this->_board));
}


bool			Game::run()
{
	coords		coord;

	this->loadEvents();
	this->_init();
	while (this->_isRunning)
	{
		changeTurn(this->_turn);
		this->_render->drawBoard(*(this->_board));
		if (this->_turn == WHITE)
			this->_playWhite();
		else
			this->_playBlack();
	}
	return (this->_return);
}

void						Game::_playBlack()
{
	coords		coord;

	do
	{
		coord = this->_black->play();
		if (this->_black && this->_black->getType() == HUMAN)
			coord = this->_getCoords(coord);
	}
	while (this->_isRunning && !this->_ref.isMoveValid(coord, BLACK));
	if (this->_isRunning)
	{
		this->_board->getIntersection(coord.x, coord.y).addMask(HAS_ONE);
		if (this->_ref.Victory(coord, BLACK))
			this->_victory(BLACK);
		else
			this->_board->PropagateInfo(coord);
	}
}

void						Game::_playWhite()
{
	coords		coord;

	do
	{
		coord = this->_white->play();
		if (this->_white && this->_white->getType() == HUMAN)
			coord = this->_getCoords(coord);
	}
	while (this->_isRunning && !this->_ref.isMoveValid(coord, WHITE));
	if (this->_isRunning)
	{
		this->_board->getIntersection(coord.x, coord.y).addMask(HAS_ONE_W);
		if (this->_ref.Victory(coord, WHITE))
			this->_victory(WHITE);
		else
			this->_board->PropagateInfo(coord);
	}
}

void								Game::_victory(enum eColor c)
{
	std::string						s;
	sf::Text						t;

	this->_render->drawBoard(*(this->_board));
	t.setPosition(200, 10);
	t.setFont(this->_render->getFont());
	if (c == BLACK)
	{
		s = "Black ";
		t.setColor(sf::Color::Black);
	}
	else
	{
		s = "White ";
		t.setColor(sf::Color::White);
	}
	s += "wins!";
	t.setString(s);
	this->_render->getWindow()->draw(t);
	this->_render->getWindow()->display();
	this->_isRunning = true;
	while (this->_isRunning)
		this->_events->wait();
}

static float						round(float f)
{
	return (static_cast<float>(floor(f + 0.5)));
}

coords						Game::_getCoords(coords c)
{
	float						x;
	float					y;

	x = ((float)c.x - (float)this->_boardCoords.x) / this->_space;
	y = ((float)c.y - (float)this->_boardCoords.y) / this->_space;
	return (coords(static_cast<int>(round(x)), static_cast<int>(round(y))));
}