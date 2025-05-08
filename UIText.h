#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class UIText {
private:
    sf::Text text;
    sf::Font font;
    std::string defaultFontPath = "fonts/arial.ttf";

public:
    UIText();
    UIText(const std::string& content, unsigned int size, const sf::Color& color, float posX, float posY);

    void setContent(const std::string& content);
    void setPosition(float x, float y);
    void setColor(const sf::Color& color);
    void setSize(unsigned int size);

    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
};