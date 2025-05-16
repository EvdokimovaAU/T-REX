#include "Loot.h"

Loot::Loot(const sf::Texture& buriedTexture,
    const sf::Texture& dugOutTexture,
    const sf::Texture& brokenTexture,
    const sf::Vector2f& pos,
    LootType lootType,
    BiomeType biomeType)
    : position(pos), isDug(false), isDigging(false), isBroken(false),
    diggingTime(0.f), requiredDiggingTime(1.5f),
    type(lootType), biome(biomeType), wasCounted(false)
{
    // Инициализация спрайтов
    buriedSprite.setTexture(buriedTexture);
    dugOutSprite.setTexture(dugOutTexture);
    brokenSprite.setTexture(brokenTexture);

    // Используем текстуру закопанного для состояния копания, но делаем темнее
    diggingSprite.setTexture(buriedTexture);
    diggingSprite.setColor(sf::Color(150, 150, 150));

    // Установка масштаба для всех спрайтов
    float scale = 0.5f;
    buriedSprite.setScale(scale, scale);
    dugOutSprite.setScale(scale, scale);
    diggingSprite.setScale(scale, scale);
    brokenSprite.setScale(scale, scale);

    // Центрирование и позиционирование спрайтов
    auto centerSprite = [](sf::Sprite& sprite) {
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2, bounds.height / 2);
        };

    centerSprite(buriedSprite);
    centerSprite(dugOutSprite);
    centerSprite(diggingSprite);
    centerSprite(brokenSprite);

    buriedSprite.setPosition(position);
    dugOutSprite.setPosition(position);
    diggingSprite.setPosition(position);
    brokenSprite.setPosition(position);
}

void Loot::dig() {
    isDug = true;
}

void Loot::breakLoot() {
    isBroken = true;
    isDigging = false;
    isDug = false;
}

void Loot::draw(sf::RenderWindow& window) const {
    if (isBroken) {
        window.draw(brokenSprite);
    }
    else if (isDug) {
        window.draw(dugOutSprite);
    }
    else if (isDigging) {
        window.draw(diggingSprite);
    }
    else {
        window.draw(buriedSprite);
    }
}

bool Loot::contains(const sf::Vector2f& point) const {
    if (isBroken) {
        return brokenSprite.getGlobalBounds().contains(point);
    }
    return isDug ? dugOutSprite.getGlobalBounds().contains(point)
        : buriedSprite.getGlobalBounds().contains(point);
}

bool Loot::getIsDug() const {
    return isDug && !isBroken;
}

bool Loot::getIsDigging() const {
    return isDigging && !isBroken;
}

bool Loot::getIsBroken() const {
    return isBroken;
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
    if (isBroken) {
        return brokenSprite.getGlobalBounds();
    }
    return isDug ? dugOutSprite.getGlobalBounds()
        : buriedSprite.getGlobalBounds();
}

void Loot::setType(LootType newType) {
    type = newType;
}

void Loot::setBiome(BiomeType newBiome) {
    biome = newBiome;
}

void Loot::setWasCounted(bool counted) {
    wasCounted = counted;
}

bool Loot::getWasCounted() const {
    return wasCounted;
}

void Loot::update(float deltaTime) {
    if (isDigging && !isBroken) {
        diggingTime += deltaTime;
        if (diggingTime >= requiredDiggingTime) {
            isDigging = false;
            isDug = true;
        }
    }
}

void Loot::startDigging() {
    if (!isDug && !isDigging && !isBroken) {
        isDigging = true;
        diggingTime = 0.f;
    }
}