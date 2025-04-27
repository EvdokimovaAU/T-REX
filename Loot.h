#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum class LootType {
    BONES,
    PLANT,
    TOOTH,
    UNICORN,
    NOTHING
};

enum class BiomeType {
    DESERT,
    JUNGLE,
    ARCTICA
};

class Loot {
private:
    sf::Sprite buriedSprite;
    sf::Sprite dugOutSprite;
    sf::Vector2f position;
    bool isDug;
    LootType type;
    BiomeType biome;

public:
    Loot(const sf::Texture& buriedTexture, const sf::Texture& dugOutTexture,
        const sf::Vector2f& pos, LootType lootType, BiomeType biomeType);

    void dig();
    void draw(sf::RenderWindow& window) const;
    bool contains(const sf::Vector2f& point) const;
    bool getIsDug() const;
    LootType getType() const;
    BiomeType getBiome() const;

    // Добавляем новые методы доступа
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
};