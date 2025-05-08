#include "UIText.h"

UIText::UIText() {
    if (!font.loadFromFile(defaultFontPath)) {
        font = sf::Font();
    }
    text.setFont(font);
}

UIText::UIText(const std::string& content, unsigned int size, const sf::Color& color, float posX, float posY)
    : UIText() {
    setContent(content);
    setSize(size);
    setColor(color);
    setPosition(posX, posY);
}

void UIText::setContent(const std::string& content) {
    text.setString(content);
}

void UIText::setPosition(float x, float y) {
    text.setPosition(x, y);
}

void UIText::setColor(const sf::Color& color) {
    text.setFillColor(color);
}

void UIText::setSize(unsigned int size) {
    text.setCharacterSize(size);
}

void UIText::draw(sf::RenderWindow& window) const {
    window.draw(text);
}

sf::FloatRect UIText::getBounds() const {
    return text.getGlobalBounds();
}