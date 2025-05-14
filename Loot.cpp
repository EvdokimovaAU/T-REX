#include "Loot.h"

Loot::Loot(const sf::Texture& buriedTexture, const sf::Texture& dugOutTexture,
    const sf::Vector2f& pos, LootType lootType, BiomeType biomeType)
    : position(pos), isDug(false), isDigging(false), diggingTime(0.f),
    requiredDiggingTime(1.5f), type(lootType), biome(biomeType)
{
    buriedSprite.setTexture(buriedTexture);
    dugOutSprite.setTexture(dugOutTexture);

    // ???????? ???????? ??? ?????????????? ????????? (????? ???????????? ???? ?? ????????????)
    diggingSprite.setTexture(buriedTexture);
    diggingSprite.setColor(sf::Color(150, 150, 150)); // ?????? ?????? ??? ??????????? ???????

    float scale = 0.4f;
    buriedSprite.setScale(scale, scale);
    dugOutSprite.setScale(scale, scale);
    diggingSprite.setScale(scale, scale);

    sf::FloatRect bounds = buriedSprite.getLocalBounds();
    buriedSprite.setOrigin(bounds.width / 2, bounds.height / 2);
    dugOutSprite.setOrigin(bounds.width / 2, bounds.height / 2);
    diggingSprite.setOrigin(bounds.width / 2, bounds.height / 2);

    buriedSprite.setPosition(position);
    dugOutSprite.setPosition(position);
    diggingSprite.setPosition(position);
}

void Loot::dig() {
    isDug = true;
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

void Loot::update(float deltaTime) {
    if (isDigging) {
        diggingTime += deltaTime;
        if (diggingTime >= requiredDiggingTime) {
            isDigging = false;
            isDug = true;
        }
    }
}

void Loot::startDigging() {
    if (!isDug && !isDigging) {
        isDigging = true;
        diggingTime = 0.f;
    }
}

bool Loot::getIsDigging() const {
    return isDigging;
}

void Loot::draw(sf::RenderWindow& window) const {
    if (isDug) {
        window.draw(dugOutSprite);
    }
    else if (isDigging) {
        window.draw(diggingSprite);
    }
    else {
        window.draw(buriedSprite);
    }
}