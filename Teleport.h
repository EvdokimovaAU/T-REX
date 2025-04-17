#pragma once

#include <iostream>
#include <vector>

using std::vector;

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Teleport
{
private:
	sf::FloatRect zoneRect; // область перехода
	sf::Vector2f targetPosition; // куда телепортировать
	int targetScreen; // номер экрана назначения

public:
	Teleport(sf::FloatRect rect, sf::Vector2f targetPos, int screen);

	// метод для проверки пересечения зоны перехода с персонажем
	// playerBounds - прямоугольник границ персонажа
	bool checkCollision(const sf::FloatRect& playerBounds) const;

	// геттеры
	sf::Vector2f getTargetPosition() const;
	int getTargetScreen() const;
	sf::FloatRect getZoneRect() const;

};

