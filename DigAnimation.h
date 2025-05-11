#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class DigAnimation {
private:
    std::vector<sf::Texture> frames;
    sf::Sprite currentSprite;
    int currentFrame;
    float frameDuration;
    float elapsedTime;
    bool isPlaying;
    float scale;

public:
    DigAnimation();
    void loadFrames(const std::vector<std::string>& framePaths);
    void setPosition(const sf::Vector2f& position);
    void setScale(float newScale);
    void play();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isPlayingAnimation() const;
};