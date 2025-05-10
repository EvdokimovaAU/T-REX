#include "Loot.h"

Loot::Loot(const sf::Texture& buriedTexture, const sf::Texture& dugOutTexture,
    const sf::Vector2f& pos, LootType lootType, BiomeType biomeType)
    : position(pos), isDug(false), type(lootType), biome(biomeType)
{
    buriedSprite.setTexture(buriedTexture);
    dugOutSprite.setTexture(dugOutTexture);

    // Увеличиваем размер спрайтов (было 0.25f, теперь 0.4f)
    float scale = 0.4f;
    buriedSprite.setScale(scale, scale);
    dugOutSprite.setScale(scale, scale);

    // Центрируем спрайты
    sf::FloatRect bounds = buriedSprite.getLocalBounds();
    buriedSprite.setOrigin(bounds.width / 2, bounds.height / 2);
    dugOutSprite.setOrigin(bounds.width / 2, bounds.height / 2);

    buriedSprite.setPosition(position);
    dugOutSprite.setPosition(position);
}

void Loot::dig() {
    isDug = true;
}

void Loot::draw(sf::RenderWindow& window) const {
    if (isDug) {
        if (dugOutSprite.getTexture()) {
            window.draw(dugOutSprite);
        }
    }
    else {
        if (buriedSprite.getTexture()) {
            window.draw(buriedSprite);
        }
    }
}

bool Loot::contains(const sf::Vector2f& point) const {
    sf::FloatRect bounds = isDug ? dugOutSprite.getGlobalBounds() : buriedSprite.getGlobalBounds();
    return bounds.contains(point);
}

bool Loot::getIsDug() const {
    return isDug;
}

LootType Loot::getType() const {
    return type;
}

BiomeType Loot::getBiome() const {
    return biome;
}

sf::Vector2f Loot::getPosition() const {
    return position;
}

sf::FloatRect Loot::getGlobalBounds() const {
    return isDug ? dugOutSprite.getGlobalBounds() : buriedSprite.getGlobalBounds();
}