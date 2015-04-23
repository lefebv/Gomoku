#include <SFML/Graphics.hpp>
#include "Board.h"
#include "GameRenderer.h"
#include "stdafx.h"
#include "Gomoku.h"
#include "EventManager.h"
#include "Bitmasks.h"
#include "Game.h"
#include	"Menu.h"

void					onExit()
{
	exit(EXIT_SUCCESS);
}

int APIENTRY _tWinMain(_In_ HINSTANCE,
                     _In_opt_ HINSTANCE,
                     _In_ LPTSTR,
                     _In_ int)
{
	Board			board(19, 19);
	GameRenderer	rend;
	EventManager	ev(rend.getWindow());
	Game			game(&rend, &ev, &board);
	Menu			m(&ev, &rend, &board);

	ev.addEvent(new CloseEvent(std::bind(&onExit)));
	ev.addEvent(new KeyEvent(std::bind(&onExit), sf::Keyboard::Escape));
	rend.loadBoard(board);
	m.run();
    return (0);
}
