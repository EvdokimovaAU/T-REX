#include <iostream>
#include "Game.h"

int main()
{
	Game game;

	while (game.running()) // пока окно открыто
	{
		game.update(); // обновляем логику (обработка событий)
		game.render(); // отрисовка
	}

	return 0;
}