#include	"Bitmasks.h"
#include	"GameRenderer.h"

GameRenderer::GameRenderer()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	this->_win.create(sf::VideoMode(600, 650), "Gomoku", sf::Style::Close, settings);
	this->_width = this->_win.getSize().x;
	this->_height = this->_win.getSize().y;
	this->_boardTexture.create(this->_width, this->_height);
	this->_font.loadFromFile("Track.ttf");
}

GameRenderer::~GameRenderer()
{
	this->_win.close();
}

void				GameRenderer::drawBoard(Board & board)
{
	this->_win.clear();
	this->_win.draw(this->_board);
	this->_loadPawns(board);
	this->_win.display();
	
}

void				GameRenderer::clear()
{
	this->_win.clear();
	this->_boardTexture.clear();
}

sf::RenderWindow *		GameRenderer::getWindow()
{
	return (&this->_win);
}

void				GameRenderer::loadBoard(Board const & board)
{
	this->_loadLimits(board);
	this->_boardImage.setRepeated(true);
	this->_boardImage.loadFromFile("sprite_board.jpg");
	this->_loadGameBackground();
	this->_loadIntersections(board);
	this->_boardTexture.display();
	this->_board.setTexture(this->_boardTexture.getTexture());
}

void				GameRenderer::_loadGameBackground()
{
	sf::Sprite		back(this->_boardImage, sf::IntRect(0, 0, this->_width, this->_height));
	sf::RectangleShape	rect(sf::Vector2f(140, 50));
	sf::Text			txt;

	txt.setFont(this->_font);
	txt.setColor(sf::Color::Black);
	this->_boardTexture.draw(back);

	rect.setPosition(10, 10);
	rect.setSize(sf::Vector2f(100, 30));
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(2);
	rect.setOutlineColor(sf::Color::Black);
	this->_boardTexture.draw(rect);

	txt.setPosition(15, 8);
	txt.setString("Menu");
	this->_boardTexture.draw(txt);

	rect.setPosition(430, 10);
	rect.setSize(sf::Vector2f(150, 30));
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(2);
	rect.setOutlineColor(sf::Color::Black);
	this->_boardTexture.draw(rect);

	txt.setPosition(435, 8);
	txt.setString("Restart");
	this->_boardTexture.draw(txt);
}

void					GameRenderer::_loadLimits(Board const & board)
{
	if (this->_width > this->_height)
		this->_space = (float)this->_height /  ((float)board.getHeight() + 1.0);
	else
		this->_space = (float)this->_width /  ((float)board.getWidth() + 1.0);
	this->_sideMargin = (this->_width - ((board.getWidth() - 1) * this->_space)) / 2.0;
	this->_topMargin = ((this->_height - ((board.getHeight() - 1) * this->_space)) / 2.0) + 25;
	this->_bottomMargin = ((board.getHeight() - 1) * this->_space);
}

void				GameRenderer::_loadIntersections(Board const & board)
{
	float						x = this->_sideMargin;
	float						y = this->_topMargin;
	int				i;

	sf::RectangleShape	line(sf::Vector2f((float)((board.getWidth() - 1) * this->_space), 2.0));
	line.setFillColor(sf::Color::Black);
	for (i = 0; i <= board.getHeight() - 1; y += this->_space)
	{
		line.setPosition(sf::Vector2f(this->_sideMargin, y));
		this->_boardTexture.draw(line);
		++i;
	}
	line.setSize(sf::Vector2f((float)(board.getHeight() - 1) * this->_space, 2.0));
	line.rotate(90.0);
	for (i = 0; i <= board.getWidth() - 1; x += this->_space)
	{
		line.setPosition(sf::Vector2f(x, this->_topMargin));
		this->_boardTexture.draw(line);
		++i;
	}
}



void						GameRenderer::_loadPawns(Board & board)
{
	int			x;
	int			y;
	float					diameter = (this->_space / 2) - 1;
	sf::CircleShape			c(diameter);

	c.setOutlineThickness(1);
	c.setOutlineColor(sf::Color::Black);
	for (y = 0; y < board.getHeight(); ++y)
	{
		for (x = 0; x < board.getWidth(); ++x)
		{
			if (!board.getIntersection(x, y).isEmpty())
			{
				if (board.getIntersection(x, y).checkMask(HAS_ONE))
					c.setFillColor(sf::Color::Black);
				else
					c.setFillColor(sf::Color::White);
				c.setPosition((x * this->_space) + this->_sideMargin - diameter, (y * this->_space) + this->_topMargin - diameter);
				this->_win.draw(c);
			}
		}
	}
}

MouseRect					GameRenderer::getBoardCoords() const
{
	return (MouseRect(this->_sideMargin, this->_topMargin, this->_width - (2 * this->_sideMargin), this->_bottomMargin));
}

float						GameRenderer::getSpace() const
{
	return (this->_space);
}

void						GameRenderer::draw(sf::Sprite const & s)
{
	this->_win.draw(s);
}

sf::Font const &			GameRenderer::getFont() const
{
	return (this->_font);
}