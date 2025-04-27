#include "Loot.h"

Loot::Loot(const sf::Texture& buriedTexture, const sf::Texture& dugOutTexture,
    const sf::Vector2f& pos, LootType lootType)
    : position(pos), isDug(false), type(lootType) {
    buriedSprite.setTexture(buriedTexture);
    dugOutSprite.setTexture(dugOutTexture);

    // Установка позиции и масштаба
    buriedSprite.setPosition(position);
    dugOutSprite.setPosition(position);
    float scale = 0.5f; // Масштаб можно настроить
    buriedSprite.setScale(scale, scale);
    dugOutSprite.setScale(scale, scale);
}

void Loot::dig() {
    isDug = true;
}

void Loot::draw(sf::RenderWindow& window) const {
    if (isDug) {
        window.draw(dugOutSprite);
    }
    else {
        window.draw(buriedSprite);
    }
}

bool Loot::contains(const sf::Vector2f& point) const {
    sf::FloatRect bounds = buriedSprite.getGlobalBounds();
    return bounds.contains(point);
}

bool Loot::getIsDug() const {
    return isDug;
}

LootType Loot::getType() const {
    return type;
}