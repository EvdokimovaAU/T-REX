#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum class LootType { BONES, PLANT, TOOTH, UNICORN, NOTHING };
enum class BiomeType { DESERT, JUNGLE, ARCTICA };

class Loot {
private:
    sf::Sprite buriedSprite;
    sf::Sprite dugOutSprite;
    sf::Sprite diggingSprite;
    sf::Sprite brokenSprite;
    sf::Vector2f position;
    bool wasCounted;
    bool isDug;
    bool isDigging;
    bool isBroken;
    LootType type;
    BiomeType biome;
    float diggingTime;
    float requiredDiggingTime;

public:
    Loot(const sf::Texture& buriedTexture,
        const sf::Texture& dugOutTexture,
        const sf::Texture& brokenTexture,
        const sf::Vector2f& pos,
        LootType lootType,
        BiomeType biomeType);

    void dig();
    void breakLoot();
    void draw(sf::RenderWindow& window) const;
    bool contains(const sf::Vector2f& point) const;
    bool getIsDug() const;
    bool getIsDigging() const;
    bool getIsBroken() const;
    LootType getType() const;
    BiomeType getBiome() const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    void setType(LootType newType);
    void setBiome(BiomeType newBiome);
    void setWasCounted(bool counted);
    bool getWasCounted() const;
    void update(float deltaTime);
    void startDigging();
};