#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum class LootType {
    BONES,    // 0
    PLANT,    // 1
    TOOTH,    // 2
    UNICORN,  // 3
    NOTHING   // 4
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
    sf::Sprite diggingSprite;
    sf::Vector2f position;
    bool wasCounted;
    bool isDug;
    LootType type;
    BiomeType biome;

    bool isDigging;           // Флаг, что идет процесс раскопок
    float diggingTime;        // Таймер для раскопок
    float requiredDiggingTime;// Необходимое время для раскопок

public:
    Loot(const sf::Texture& buriedTexture, const sf::Texture& dugOutTexture,
        const sf::Vector2f& pos, LootType lootType, BiomeType biomeType);

    void dig();
    void draw(sf::RenderWindow& window) const;
    bool contains(const sf::Vector2f& point) const;
    bool getIsDug() const;
    LootType getType() const;
    BiomeType getBiome() const;


    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;

    void setType(LootType newType) { type = newType; }
    void setBiome(BiomeType newBiome) { biome = newBiome; }
    void setWasCounted(bool counted) { wasCounted = counted; }
    bool getWasCounted() const { return wasCounted; }
    void update(float deltaTime); // Добавляем метод обновления
    bool getIsDigging() const;
    void startDigging();
};