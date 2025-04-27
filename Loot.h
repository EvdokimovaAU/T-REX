#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum class LootType {
    BONES,
    PLANT,
    TOOTH,
    UNICORN,
    NOTHING
};

class Loot {
private:
    sf::Sprite buriedSprite;
    sf::Sprite dugOutSprite;
    sf::Vector2f position;
    bool isDug;
    LootType type;

public:
    Loot(const sf::Texture& buriedTexture, const sf::Texture& dugOutTexture,
        const sf::Vector2f& pos, LootType lootType);

    void dig();
    void draw(sf::RenderWindow& window) const;
    bool contains(const sf::Vector2f& point) const;
    bool getIsDug() const;
    LootType getType() const;
};
