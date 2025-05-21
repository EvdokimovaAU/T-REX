#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum class LootType { BONES, PLANT, TOOTH, UNICORN, NOTHING };
enum class BiomeType { DESERT, JUNGLE, ARCTICA };

class Loot {
private:
    sf::Sprite buriedSprite; // закопанный
    sf::Sprite dugOutSprite; // раскопанный
    sf::Sprite diggingSprite; // в процессе
    sf::Sprite brokenSprite; // сломанный

    sf::Vector2f position; // позиция объекта на экране

    bool wasCounted;
    bool isDug; // раскопан ли
    bool isDigging; // раскапывается ли
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

    void dig(); // копание
    void breakLoot();
    void draw(sf::RenderWindow& window) const;
    bool contains(const sf::Vector2f& point) const; // содержиться ли подхлдящая точка
    bool getIsDug() const;
    bool getIsDigging() const;
    bool getIsBroken() const;
    LootType getType() const;
    BiomeType getBiome() const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const; 
    void setType(LootType newType); // установка нового типа лута
    void setBiome(BiomeType newBiome);
    void setWasCounted(bool counted); // получение значения
    bool getWasCounted() const; // обновление состояния объекта
    void update(float deltaTime);  // deltaTime - время, прошедшее с предыдущего кадра
    void startDigging();
};