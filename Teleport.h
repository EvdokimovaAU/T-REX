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
	sf::FloatRect zoneRect; 
	sf::Vector2f targetPosition; 
	int targetScreen; 

public:
	Teleport(sf::FloatRect rect, sf::Vector2f targetPos, int screen);

	
	bool checkCollision(const sf::FloatRect& playerBounds) const;

	
	sf::Vector2f getTargetPosition() const;
	int getTargetScreen() const;
	sf::FloatRect getZoneRect() const;

};