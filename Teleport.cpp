#include "Teleport.h"


Teleport::Teleport(sf::FloatRect rect, sf::Vector2f targetPos, int screen)
	: zoneRect(rect), targetPosition(targetPos), targetScreen(screen) {
}


bool Teleport::checkCollision(const sf::FloatRect& playerBounds) const {
	return zoneRect.intersects(playerBounds);
}

sf::FloatRect Teleport::getZoneRect() const {
	return zoneRect;
}

sf::Vector2f Teleport::getTargetPosition() const
{
	return targetPosition;
}

int Teleport::getTargetScreen() const
{
	return targetScreen;
}