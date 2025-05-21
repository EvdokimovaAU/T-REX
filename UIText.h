#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class UIText 
{
private:
    sf::Text text;
    sf::Font font;
    std::string defaultFontPath = "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/Arial.ttf"; 

public:
    UIText();

    // конструктор с параметрами
    UIText(const std::string& content, unsigned int size, const sf::Color& color, float posX, float posY);

    void setContent(const std::string& content);
    void setPosition(float x, float y);
    void setColor(const sf::Color& color);
    void setSize(unsigned int size);

    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const; // получение ограничивающего прямоугольника текста
};