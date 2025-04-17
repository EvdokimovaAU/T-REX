#include "Teleport.h"

// коструктор
Teleport::Teleport(sf::FloatRect rect, sf::Vector2f targetPos, int screen)
	: zoneRect(rect), targetPosition(targetPos), targetScreen(screen) {
}

// метод для проверки пересечения зоны перехода с персонажем
bool Teleport::checkCollision(const sf::FloatRect& playerBounds) const {
	return zoneRect.intersects(playerBounds);
}

sf::FloatRect Teleport::getZoneRect() const {
	return zoneRect;
}

// геттеры
sf::Vector2f Teleport::getTargetPosition() const
{
	return targetPosition;
}

int Teleport::getTargetScreen() const
{
	return targetScreen;
}