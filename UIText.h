#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class UIText {
private:
    sf::Text text;
    sf::Font font;
    std::string defaultFontPath = "C:/Users/admin/Desktop/ÄÈÍÎÇÀÂÐ/ÄÈÍÎÇÀÂÐ/x64/Debug/Arial.ttf"; // Simplified path, place the font in your executable directory

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