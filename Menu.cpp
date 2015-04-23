#include	"AIEasy.h"
#include	"Menu.h"

Menu::Menu(EventManager * ev, GameRenderer * g, Board * b): _max(1), _ev(ev), _rend(g), _b(b), _game(g, ev, b), _whiteC(0), _blackC(0)
{
	this->_choiceStrings.reserve(1);
	this->_choiceStrings.push_back("Player");
	this->_choiceStrings.push_back("AI - easy");
	this->loadGraphics();
}

Menu::~Menu()
{
}

void				Menu::loadGraphics()
{
	sf::Texture		t;
	sf::Text		txt;
	sf::CircleShape	up(20, 3);
	sf::CircleShape down(20, 3);
	sf::RectangleShape	input(sf::Vector2f(200, 50));

	txt.setColor(sf::Color::Black);
	up.setFillColor(sf::Color::Black);
	down.setFillColor(sf::Color::Black);
	down.setRotation(180);
	this->_texture.create(600, 650);
	this->_texture.clear();
	t.setRepeated(true);
	t.loadFromFile("sprite_board.jpg");
	sf::Sprite		back(t, sf::IntRect(0, 0, 600, 650));
	this->_texture.draw(back);

	txt.setFont(this->_rend->getFont());
	txt.setPosition(130, 60);
	txt.setString("Epic Game Of Gomoku");
	this->_texture.draw(txt);

	txt.setPosition(280, 205);
	txt.setString("VS");
	this->_texture.draw(txt);

	up.setPosition(130, 150);
	this->_texture.draw(up);

	up.setPosition(430, 150);
	this->_texture.draw(up);

	down.setPosition(170, 300);
	this->_texture.draw(down);

	down.setPosition(470, 300);
	this->_texture.draw(down);

	input.setPosition(50, 200);
	this->_texture.draw(input);

	input.setPosition(350, 200);
	input.setFillColor(sf::Color::Black);
	this->_texture.draw(input);

	input.setPosition(230, 400);
	input.setSize(sf::Vector2f(140, 50));
	input.setFillColor(sf::Color::Transparent);
	input.setOutlineThickness(2);
	input.setOutlineColor(sf::Color::Black);
	this->_texture.draw(input);
	
	txt.setPosition(250, 405);
	txt.setString("Start");
	this->_texture.draw(txt);

	input.setPosition(230, 500);
	this->_texture.draw(input);

	txt.setString("Quit");
	txt.setPosition(265, 505);
	this->_texture.draw(txt);

	txt.setString(this->_choiceStrings[this->_whiteC]);
	txt.setColor(sf::Color::Black);
	txt.setPosition(60, 205);
	this->_texture.draw(txt);

	txt.setString(this->_choiceStrings[this->_blackC]);
	txt.setColor(sf::Color::White);
	txt.setPosition(360, 205);
	this->_texture.draw(txt);

	this->_texture.display();
	this->_rend->draw(sf::Sprite(this->_texture.getTexture()));
	this->_rend->getWindow()->display();
}

void					Menu::loadEvents()
{
	this->_ev->addEvent(new MouseClick(std::bind(&Menu::_decrWhite, this, std::placeholders::_1, std::placeholders::_2), MouseRect(140, 150, 30, 30)));
	this->_ev->addEvent(new MouseClick(std::bind(&Menu::_incrWhite, this, std::placeholders::_1, std::placeholders::_2), MouseRect(140, 270, 30, 30)));
	this->_ev->addEvent(new MouseClick(std::bind(&Menu::_decrBlack, this, std::placeholders::_1, std::placeholders::_2), MouseRect(440, 150, 30, 30)));
	this->_ev->addEvent(new MouseClick(std::bind(&Menu::_incrBlack, this, std::placeholders::_1, std::placeholders::_2), MouseRect(440, 270, 30, 30)));
	this->_ev->addEvent(new MouseClick(std::bind(&Menu::_startGame, this, std::placeholders::_1, std::placeholders::_2), MouseRect(230, 400, 140, 50)));
	this->_ev->addEvent(new MouseClick(std::bind(&Menu::_exit, this, std::placeholders::_1, std::placeholders::_2), MouseRect(230, 500, 140, 50)));
}

void					Menu::run()
{
	this->loadEvents();
	while (1)
		this->_ev->wait();
}

void					Menu::_incrWhite(int, int)
{
	sf::Text			txt;
	sf::RectangleShape	rect(sf::Vector2f(200, 50));

	if (this->_whiteC == this->_max)
		this->_whiteC = 0;
	else
		++this->_whiteC;
	txt.setFont(this->_rend->getFont());
	rect.setPosition(50, 200);
	this->_texture.draw(rect);
	txt.setString(this->_choiceStrings[this->_whiteC]);
	txt.setColor(sf::Color::Black);
	txt.setPosition(60, 205);
	this->_texture.draw(txt);
	this->_texture.display();
	this->_rend->draw(sf::Sprite(this->_texture.getTexture()));
	this->_rend->getWindow()->display();
	this->_ev->addEvent(new MouseClick(std::bind(&Menu::_incrWhite, this, std::placeholders::_1, std::placeholders::_2), MouseRect(140, 270, 30, 30)));
}

void					Menu::_incrBlack(int, int)
{
	sf::Text			txt;
	sf::RectangleShape	rect(sf::Vector2f(200, 50));

	txt.setFont(this->_rend->getFont());
	if (this->_blackC == this->_max)
		this->_blackC = 0;
	else
		++this->_blackC;
	rect.setPosition(350, 200);
	rect.setFillColor(sf::Color::Black);
	this->_texture.draw(rect);
	txt.setString(this->_choiceStrings[this->_blackC]);
	txt.setColor(sf::Color::White);
	txt.setPosition(360, 205);
	this->_texture.draw(txt);
	this->_texture.display();
	this->_rend->draw(sf::Sprite(this->_texture.getTexture()));
	this->_rend->getWindow()->display();
	this->_ev->addEvent(new MouseClick(std::bind(&Menu::_incrBlack, this, std::placeholders::_1, std::placeholders::_2), MouseRect(440, 270, 30, 30)));
}

void					Menu::_decrWhite(int, int)
{
	sf::Text			txt;
	sf::RectangleShape	rect(sf::Vector2f(200, 50));

	txt.setFont(this->_rend->getFont());
	if (this->_whiteC == 0)
		this->_whiteC = this->_max;
	else
		--this->_whiteC;
	rect.setPosition(50, 200);
	this->_texture.draw(rect);
	txt.setString(this->_choiceStrings[this->_whiteC]);
	txt.setColor(sf::Color::Black);
	txt.setPosition(60, 205);
	this->_texture.draw(txt);
	this->_texture.display();
	this->_rend->draw(sf::Sprite(this->_texture.getTexture()));
	this->_rend->getWindow()->display();
	this->_ev->addEvent(new MouseClick(std::bind(&Menu::_decrWhite, this, std::placeholders::_1, std::placeholders::_2), MouseRect(140, 150, 30, 30)));
}

void					Menu::_decrBlack(int, int)
{
	sf::Text			txt;
	sf::RectangleShape	rect(sf::Vector2f(200, 50));

	txt.setFont(this->_rend->getFont());
	if (this->_blackC == 0)
		this->_blackC = this->_max;
	else
		--this->_blackC;
	rect.setPosition(350, 200);
	rect.setFillColor(sf::Color::Black);
	this->_texture.draw(rect);
	txt.setString(this->_choiceStrings[this->_blackC]);
	txt.setColor(sf::Color::White);
	txt.setPosition(360, 205);
	this->_texture.draw(txt);
	this->_texture.display();
	this->_rend->draw(sf::Sprite(this->_texture.getTexture()));
	this->_rend->getWindow()->display();
	this->_ev->addEvent(new MouseClick(std::bind(&Menu::_decrBlack, this, std::placeholders::_1, std::placeholders::_2), MouseRect(440, 150, 30, 30)));
}

IPlayer *				Menu::_getPlayer(int nb)
{
	if (nb == 0)
		return (new HumanPlayer(this->_ev, this->_rend->getBoardCoords()));
	else if (nb == 1)
		return (new AIEasy(this->_b));
	else
		return (NULL);
}

void					Menu::_startGame(int, int)
{
	bool				isExited = false;

	while (!isExited)
	{
		this->_ev->clear();
		this->_ev->addEvent(new CloseEvent(std::bind(&Menu::_exit, this, 0, 0)));
		this->_ev->addEvent(new KeyEvent(std::bind(&Menu::_exit, this, 0, 0), sf::Keyboard::Escape));
		this->_game.setBlack(this->_getPlayer(this->_blackC));
		this->_game.setWhite(this->_getPlayer(this->_whiteC));
		isExited = this->_game.run();
		this->_game.reset();
	}
	this->_rend->draw(sf::Sprite(this->_texture.getTexture()));
	this->_rend->getWindow()->display();
	this->_ev->clear();
	this->_ev->addEvent(new CloseEvent(std::bind(&Menu::_exit, this, 0, 0)));
	this->_ev->addEvent(new KeyEvent(std::bind(&Menu::_exit, this, 0, 0), sf::Keyboard::Escape));
	this->loadEvents();
}

void					Menu::_exit(int, int)
{
	exit(EXIT_SUCCESS);
}